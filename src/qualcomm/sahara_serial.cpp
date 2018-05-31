
/**
*
* (c) Gassan Idriss <ghassani@gmail.com>
*
* This file is part of libopenpst.
*
* libopenpst is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* libopenpst is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with libopenpst. If not, see <http://www.gnu.org/licenses/>.
*
* @file sahara_serial.cpp
* @class SaharaSerial
* @package openpst/libopenpst
* @brief Sahara protocol serial port implementation
*
* @author Gassan Idriss <ghassani@gmail.com>
*/

#include "qualcomm/sahara_serial.h"

using namespace OpenPST::QC;

/**
* @brief SaharaSerial
*
* @param std::string port
* @param int baudrate
* @param serial::Timeout - Timeout, defaults to 1000ms
*/
SaharaSerial::SaharaSerial(std::string port, int baudrate, int timeout ,bool encapsulate) :
//	OpenPST::Serial::GenericSerial(port, baudrate, timeout)
	OpenPST::QC::HdlcSerial(port, baudrate, timeout)
{
	intEncapsulateFlag=encapsulate;
}

/**
* @brief ~SaharaSerial
*/
SaharaSerial::~SaharaSerial()
{
}

SaharaHelloRequest SaharaSerial::readHello()
{
	size_t rxSize;
	SaharaHelloRequest ret = {};

	if (!(rxSize = read(reinterpret_cast<uint8_t*>(&ret), sizeof(ret),intEncapsulateFlag))) {
		throw SaharaSerialError("Did not receive hello. Not in sahara mode, already in a session, or requires restart");
	}

	validateResponse(kSaharaCommandHello, reinterpret_cast<SaharaHeader*>(&ret), rxSize);

	flush();

	return ret;
}


SaharaState SaharaSerial::sendHello(uint32_t mode, uint32_t version, uint32_t minVersion, uint32_t status)
{
	size_t rxSize;
	SaharaHelloResponse packet = {};
	SaharaState ret = {};
	std::vector<uint8_t> buffer;

	packet.header.command   = kSaharaCommandHelloResponse;
	packet.header.size      = sizeof(packet);
	packet.status           = status;
	packet.mode             = mode;
	packet.version          = version;
	packet.minVersion       = minVersion;

	write((uint8_t*)&packet, sizeof(packet),intEncapsulateFlag);

	try {
		rxSize = read(buffer, sizeof(ret),intEncapsulateFlag);
	}  catch (serial::IOException e) {
		/*
		 sometimes (at least in memory debug mode) the device
		 will reset itself and the hello needs to be re-read and
		 sent
		*/
		close();

		#ifdef _WIN32
			//Sleep(5000);nnm
		#else
			usleep(5 * 1000000);
		#endif

		open();

		readHello();

		write((uint8_t*)&packet, sizeof(packet),intEncapsulateFlag); // resend the hello response

		rxSize = read(buffer, SAHARA_MAX_PACKET_SIZE,intEncapsulateFlag);
	}

	flush();

	if (packet.mode == kSaharaModeCommand && isValidResponse(kSaharaCommandReady, reinterpret_cast<SaharaHeader*>(&buffer[0]), rxSize)) {
		memcpy(&ret.clientCommand, &buffer[0], sizeof(ret.clientCommand));
	} else if (packet.mode == kSaharaModeImageTxPending && isValidResponse(kSaharaCommandReadData, reinterpret_cast<SaharaHeader*>(&buffer[0]), rxSize)) {
		memcpy(&ret.imageTransfer, &buffer[0], sizeof(ret.imageTransfer));
	} else if (packet.mode == kSaharaModeMemoryDebug && isValidResponse(kSaharaCommandMemoryDebug, reinterpret_cast<SaharaHeader*>(&buffer[0]), rxSize)) {
		memcpy(&ret.memoryDebug, &buffer[0], sizeof(ret.memoryDebug));
	} else {
		throw SaharaSerialError("Unexpected or unsupported mode");
	}

	ret.mode 		= packet.mode;
	ret.version  	= packet.version;
	ret.minVersion  = packet.minVersion;

	return ret;
}


void SaharaSerial::switchMode(uint32_t mode)
{
	SaharaSwitchModeRequest packet = {};
	std::vector<uint8_t> buffer;

	LOGD("Requesting Mode Switch to %s (0x%02x)\n", getNamedMode(mode).c_str(), mode);

	packet.header.command   = kSaharaCommandSwitchMode;
	packet.header.size      = sizeof(packet);
	packet.mode             = mode;

	write(reinterpret_cast<uint8_t*>(&packet), packet.header.size,intEncapsulateFlag);
}

SaharaState SaharaSerial::switchModeAndHello(uint32_t mode)
{
	switchMode(mode);

	readHello();

	return sendHello(mode);
}

std::vector<uint8_t> SaharaSerial::sendClientCommand(uint32_t command)
{
	size_t rxSize;
	size_t dataSize;
	SaharaClientCommandRequest packet = {};
	SaharaClientCommandResponse resp = {};
	SaharaClientCommandExecuteDataRequest execDataPacket = {};
	std::vector<uint8_t> ret;

	LOGD("Sending Client Command: 0x%02x - %s\n", command, getNamedClientCommand(command).c_str());

	packet.header.command   = kSaharaCommandExecute;
	packet.header.size      = sizeof(packet);
	packet.command          = command;

	write((uint8_t*)&packet, sizeof(packet),intEncapsulateFlag);

	if (!(rxSize = read(reinterpret_cast<uint8_t*>(&resp), sizeof(resp),intEncapsulateFlag))) {
		throw SaharaSerialError("No response from device");
	}

	flush();

	validateResponse(kSaharaCommandExecuteResponse, reinterpret_cast<SaharaHeader*>(&resp), rxSize);

	dataSize = resp.size;

	execDataPacket.header.command = kSaharaCommandExecuteData;
	execDataPacket.header.size    = sizeof(SaharaClientCommandExecuteDataRequest);
	execDataPacket.command        = command;

	write((uint8_t*)&execDataPacket, sizeof(execDataPacket),intEncapsulateFlag);

	do {

		if (!(rxSize = read(ret, SAHARA_MAX_PACKET_SIZE,intEncapsulateFlag))) {
			throw SaharaSerialError("No response from device");
		}

		validateResponse(NULL, reinterpret_cast<SaharaHeader*>(&ret), rxSize);

	} while (ret.size() < dataSize);

#ifdef DEBUG
	LOGD("========\nDumping Data For Command: %s (%02X) - %lu bytes of expected %lu\n========\n\n",
		getNamedClientCommand(command).c_str(), command,
		ret.size(), dataSize
	);
	hexdump(reinterpret_cast<uint8_t*>(&ret[0]), ret.size());
#endif

	flush();

	return ret;
}


SaharaReadDataRequest SaharaSerial::sendImage(std::string filePath, SaharaReadDataRequest initialReadRequest)
{
	size_t fileSize;
	size_t totalSent = 0;
	SaharaReadDataRequest nextOffset = initialReadRequest;
	std::ifstream file(filePath.c_str(), std::ios::in | std::ios::binary);

	if (!file.is_open()) {
		std::stringstream ss;
		ss << "Could Not Open File " << filePath;
		throw SaharaSerialError(ss.str());
	}

	file.seekg(0, file.end);
	fileSize = (size_t)file.tellg();
	file.seekg(0, file.beg);

	LOGD("Loaded File %s With Size %lu\n", filePath.c_str(), fileSize);

	while (totalSent != fileSize) {

		uint32_t thisWriteOffset = nextOffset.offset;
		size_t thisWriteSize   = nextOffset.size;

		try {
			nextOffset = sendImage(file, thisWriteOffset, thisWriteSize);
		} catch (...) {
			file.close();
			throw;
		}

		totalSent += thisWriteSize;

		if ((nextOffset.offset == 0x00 && nextOffset.size == 0x00) || initialReadRequest.imageId != nextOffset.imageId) {
			break;
		}
	}

	LOGD("Sent %lu bytes\n", totalSent);

	file.close();

	if (initialReadRequest.imageId != nextOffset.imageId) {
		LOGD("Device is now requesting %lu bytes from image %02X - %s",
			nextOffset.size,
			nextOffset.imageId,
			getNamedRequestedImage(nextOffset.imageId)
		);
	}

	return nextOffset;
}

SaharaReadDataRequest SaharaSerial::sendImage(std::ifstream& file, uint32_t offset, size_t size)
{
	std::vector<uint8_t> buffer(size);

	file.seekg(0, file.end);

	size_t fileSize = file.tellg();

	if (offset > fileSize || (offset + size) > fileSize) {
		throw SaharaSerialError("Requested offset is past the file size");
	}

	file.seekg(offset, file.beg);

	file.read(reinterpret_cast<char*>(&buffer[0]), size);

	write(buffer,intEncapsulateFlag);

	return readNextImageOffset();
}


SaharaReadDataRequest SaharaSerial::readNextImageOffset()
{
	size_t rxSize;
	SaharaReadDataRequest ret = {};

	if (!(rxSize = read(reinterpret_cast<uint8_t*>(&ret), sizeof(ret),intEncapsulateFlag))) {
		 throw SaharaSerialError("No response from device");
	}

	flush();

	validateResponse(kSaharaCommandReadData, reinterpret_cast<SaharaHeader*>(&ret), rxSize);

	// sahara sends a packet that is also an error packet, but it is actually end of image transfers
	// meaning no more images
	if (ret.header.command == kSaharaCommandEndImageTransfer) {
		ret.header.command = kSaharaCommandReadData;
		ret.size   = sizeof(ret);
		ret.offset = 0x00;
		ret.size   = 0x00;
	}

	return ret;
}


size_t SaharaSerial::readMemory(uint32_t address, size_t size, std::vector<uint8_t>&out)
{
	SaharaMemoryReadRequest packet;
	size_t rxSize;
	size_t readSoFar = 0;
	std::vector<uint8_t> buffer;

	out.reserve(size);

	buffer.reserve(size > SAHARA_MAX_MEMORY_REQUEST_SIZE ? SAHARA_MAX_MEMORY_REQUEST_SIZE : size);

	packet.header.command = kSaharaCommandMemoryRead;
	packet.header.size  = sizeof(packet);

	while (readSoFar < size) {

		packet.address = address + readSoFar;

		if (size > SAHARA_MAX_MEMORY_REQUEST_SIZE) {
			packet.size = SAHARA_MAX_MEMORY_REQUEST_SIZE;

			if ((size - readSoFar) < SAHARA_MAX_MEMORY_REQUEST_SIZE) {
				packet.size = size - readSoFar;
			}

		} else {
			packet.size = size;
		}

		write(reinterpret_cast<uint8_t*>(&packet), sizeof(packet),intEncapsulateFlag);

		while (available()) {
			if (!(rxSize = read(buffer, packet.size),intEncapsulateFlag)) {
				break;
			}

			readSoFar += rxSize;

			if (isErrorResponse(reinterpret_cast<SaharaHeader*>(&buffer[0]), rxSize)) {
				throw SaharaSerialError(getNamedErrorStatus(reinterpret_cast<SaharaEndImageTransferResponse*>(&buffer[0])->status));
			}

			std::copy(buffer.begin(), buffer.end(), std::back_inserter(out));

			buffer.empty();
		}
	}

	return readSoFar;
}

size_t SaharaSerial::readMemory(uint32_t address, size_t size, std::string outFilePath)
{
	std::ofstream file(outFilePath, std::ios::out | std::ios::binary | std::ios::trunc);

	if (!file.is_open()) {
		throw SaharaSerialError("Could not open file for writing");
	}

	size_t read = readMemory(address, size, file);

	file.close();

	return read;
}

size_t SaharaSerial::readMemory(uint32_t address, size_t size, std::ofstream& out)
{
	std::vector<uint8_t> buffer;

	readMemory(address, size, buffer);

	out.write(reinterpret_cast<char*>(&buffer[0]), buffer.size());

	return buffer.size();
}


void SaharaSerial::sendDone()
{
	size_t rxSize;
	SaharaDoneRequest packet = {};
	SaharaDoneResponse resp = {};

	packet.header.command = kSaharaCommandDone;
	packet.header.size = sizeof(packet);

	write((uint8_t*)&packet, sizeof(packet),intEncapsulateFlag);

	if (!(rxSize = read(reinterpret_cast<uint8_t*>(&resp), sizeof(resp)))) {
		 throw SaharaSerialError("No response from device");
	}

	flush();

	validateResponse(kSaharaCommandDoneResponse, reinterpret_cast<SaharaHeader*>(&resp), rxSize);
}

void SaharaSerial::sendReset()
{
	size_t rxSize;
	SaharaResetRequest packet = {};
	SaharaResetResponse resp = {};

	packet.header.command = kSaharaCommandReset;
	packet.header.size = sizeof(packet);

	try {
		write(reinterpret_cast<uint8_t*>(&packet), sizeof(packet),intEncapsulateFlag);
		rxSize = read(reinterpret_cast<uint8_t*>(&resp), sizeof(resp),intEncapsulateFlag);
	} catch (...) {
		close();
		return;
	}

	validateResponse(kSaharaCommandResetResponse, reinterpret_cast<SaharaHeader*>(&resp), rxSize);

	close();
}

void SaharaSerial::close()
{
	serial::Serial::close();
}


void SaharaSerial::SetEncapsulationMode(bool Enc)
{
intEncapsulateFlag=Enc;
}

void SaharaSerial::validateResponse(uint32_t expectedResponseCommand, SaharaHeader* data, size_t dataSize)
{
	std::stringstream ss;
	if (!isValidResponse(expectedResponseCommand, data, dataSize)) {
		ss << "Devices responded with an error: " <<
			getNamedErrorStatus(reinterpret_cast<SaharaEndImageTransferResponse*>(data)->status);

		throw SaharaSerialError(ss.str());
	}
}

bool SaharaSerial::isValidResponse(uint32_t expectedResponseCommand, SaharaHeader* data, size_t dataSize)
{

	if (dataSize == 0) {
		LOGD("No data to validate\n");
		return false;
	} else if (isErrorResponse(data, dataSize)) {
		LOGD("Error Response\n");
		return false;
	} else if (!expectedResponseCommand || data->command == expectedResponseCommand) {
		return true;
	}

	// if command is kSaharaCommandReadData, and isErrorResponse passed as no error, its
	// actually a success response designating end of image transfer has been completed
	return expectedResponseCommand == kSaharaCommandReadData ? true : false;
}

bool SaharaSerial::isErrorResponse(SaharaHeader* data, size_t dataSize)
{
	return data->command == kSaharaCommandEndImageTransfer &&
		dataSize == sizeof(SaharaEndImageTransferResponse) &&
		reinterpret_cast<SaharaEndImageTransferResponse*>(data)->status != kSaharaStatusSuccess &&
		reinterpret_cast<SaharaEndImageTransferResponse*>(data)->status < kSaharaStatusMax;
}

std::string SaharaSerial::getNamedMode(uint32_t mode)
{
	switch (mode) {
		case kSaharaModeImageTxPending:  return "Image Transfer Pending";
		case kSaharaModeImageTxComplete: return "Image Transfer Complete";
		case kSaharaModeMemoryDebug:     return "Memory Debug";
		case kSaharaModeCommand:         return "Command Mode";
		default:                         return "Unknown";
	}
}

std::string SaharaSerial::getNamedClientCommand(uint32_t command)
{
	switch (command) {
		case kSaharaClientCmdNop:                       return "NOP";
		case kSaharaClientCmdSerialNumRead:             return "Read Serial Number";
		case kSaharaClientCmdMsmHWIDRead:               return "Read MSM HW ID";
		case kSaharaClientOemPkHashRead:                return "Read OEM PK Hash";
		case kSaharaClientCmdSwitchDMSS:                return "Switch To DMSS DLOAD";
		case kSaharaClientCmdSwitchToStreamingDload:    return "Switch To Streaming DLOAD";
		case kSaharaClientCmdReadDebugData:             return "Read Debug Data";
		case kSaharaClientCmdGetSblVersion:             return "Read SBL SW Version";
		default:                                        return "Unknown";
	}
}

std::string SaharaSerial::getNamedErrorStatus(uint32_t status)
{
	switch (status) {
		case kSaharaStatusSuccess:                      return "Success";
		case kSaharaStatusInvalidCmd:                   return "Invalid Command";
		case kSaharaStatusProtocolMismatch:             return "Protocol Mismatch";
		case kSaharaStatusInvalidTargetProtocol:        return "Invalid Target Protocol";
		case kSaharaStatusInvalidHostProtocol:          return "Invalid Host Protocol";
		case kSaharaStatusInvalidPacketSize:            return "Invalid Packet Size";
		case kSaharaStatusUnexpectedImageId:            return "Unexpected Image ID";
		case kSaharaStatusInvalidHeaderSize:            return "Invalid Header Size";
		case kSaharaStatusInvalidDataSize:              return "Invalid Data Size";
		case kSaharaStatusInvalidImageType:             return "Invalid Image Type";
		case kSaharaStatusInvalidTxLength:              return "Invalid TX Length";
		case kSaharaStatusInvalidRxLength:              return "Invalid RX Length";
		case kSaharaStatusTxRxError:                    return "General TX RX Error";
		case kSaharaStatusUnsupportedNumPhdrs:          return "Cannot receive specified number of program headers";
		case kSaharaStatusInvalidPhdrSize:              return "Invalid data length received for program headers";
		case kSaharaStatusMultipleSharedSeg:            return "Multiple shared segments found in ELF image";
		case kSaharaStatusUninitPhdrLoc:                return "Uninitialized program header location";
		case kSaharaStatusInvalidDestAddress:           return "Invalid destination address";
		case kSaharaStatusInvalidImageHeaderSize:       return "Invalid data size receieved in image header";
		case kSaharaStatusInvalidElfHeader:             return "Invalid ELF header received";
		case kSaharaStatusUnknownError:                 return "Unknown Host Error";
		case kSaharaStatusTimeoutRx:                    return "RX Timeout";
		case kSaharaStatusTimeoutTx:                    return "TX Timeout";
		case kSaharaStatusInvalidMode:                  return "Invalid Host Mode";
		case kSaharaStatusInvalidMemoryRead:            return "Invalid Memory Read";
		case kSaharaStatusInvalidDataSizeRequest:       return "Invalid Data Size Request";
		case kSaharaStatusMemoryDebugNotSupported:      return "Memory Debug Not Supported";
		case kSaharaStatusInvalidModeSwitch:            return "Invalid Mode Switch";
		case kSaharaStatusExecFailure:                  return "Command Execute Failure";
		case kSaharaStatusExecCmdInvalidParam:          return "Invalid Command Parameter";
		case kSaharaStatusExecCmdUnsupported:           return "Command Unsupported";
		case kSaharaStatusExecDataInvalid:              return "Invalid Client Command";
		case kSaharaStatusHashTableAuthFailure:         return "Hash Table Auth Failure";
		case kSaharaStatusHashVerificationFailure:      return "Hash Table Verification Failure";
		case kSaharaStatusHashTableNotFound:            return "Hash Table Not Found";
		case kSaharaStatusTargetInitFailure:            return "Target Init Failure";
		case kSaharaStatusImageAuthFailure:             return "Image Auth Failure";
		case kSaharaStatusInvalidImgHashTableSize:      return "Invalid ELF Hash Table Size";
		default:                                        return "Unknown";
	}
}

std::string SaharaSerial::getNamedRequestedImage(uint32_t imageId)
{
	switch (imageId) {
		case kMbnImageNone:          return "None";
		case kMbnImageOemSbl:        return "OEM SBL";
		case kMbnImageAmss:          return "AMSS";
		case kMbnImageOcbl:          return "QCSBL";
		case kMbnImageHash:          return "Hash";
		case kMbnImageAppbl:         return "APPSBL";
		case kMbnImageHostDl:        return "HOSTDL";
		case kMbnImageDsp1:          return "DSP1";
		case kMbnImageFsbl:          return "FSBL";
		case kMbnImageDbl:           return "DBL";
		case kMbnImageOsbl:          return "OSBL";
		case kMbnImageDsp2:          return "DSP2";
		case kMbnImageEhostdl:       return "EHOSTDL";
		case kMbnImageNandprg:       return "NANDPRG";
		case kMbnImageNorprg:        return "NORPRG";
		case kMbnImageRamfs1:        return "RAMFS1";
		case kMbnImageRamfs2:        return "RAMFS2";
		case kMbnImageAdspQ5:        return "ADSP Q5";
		case kMbnImageAppsKernel:    return "APPS Kernel";
		case kMbnImageBackupRamfs:   return "Backup RAMFS";
		case kMbnImageSbl1:          return "SBL1";
		case kMbnImageSbl2:          return "SBL2";
		case kMbnImageRpm:           return "RPM";
		case kMbnImageSbl3:          return "SBL3";
		case kMbnImageTz:            return "TZ";
		case kMbnImageSsdKeys:       return "SSD Keys";
		case kMbnImageGen:           return "GEN";
		case kMbnImageDsp3:          return "DSP3";
		case kMbnImageAcdb:          return "ACDB";
		case kMbnImageWdt:           return "WDT";
		case kMbnImageMba:           return "MBA";
		default:                     return "Unknown";
	}
}
