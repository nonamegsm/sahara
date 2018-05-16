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
* @file streaming_dload_serial.cpp
* @class StreamingDloadSerial
* @package openpst/libopenpst
* @brief Streaming DLOAD protocol serial port implementation
*
* @author Gassan Idriss <ghassani@gmail.com>
*/

#include <iostream>
#include <fstream>
#include <string>
#include "qualcomm/streaming_dload_serial.h"

using namespace OpenPST::QC;

/**
* @brief StreamingDloadSerial() - Constructor
*
* @param std::string port - The device to connect to
* @param int baudrate - Defaults to 115200
* @param serial::Timeout - Timeout, defaults to 1000ms
*/
StreamingDloadSerial::StreamingDloadSerial(std::string port, int baudrate, int timeout) :
	HdlcSerial(port, baudrate, timeout),
	state({})
{
	state.hello.maxPreferredBlockSize = STREAMING_DLOAD_MAX_DATA_SIZE;
}

/**

* @brief ~StreamingDloadSerial() - Deconstructor
*/
StreamingDloadSerial::~StreamingDloadSerial()
{

}

StreamingDloadHelloResponse StreamingDloadSerial::sendHello(std::string magic, uint8_t version, uint8_t compatibleVersion, uint8_t featureBits)
{
	size_t rxSize;
	StreamingDloadHelloRequest  hello = {};
	std::vector<uint8_t> buffer;

	hello.command 			= kStreamingDloadHello;
	hello.version 			= version;
	hello.compatibleVersion = compatibleVersion;
	hello.featureBits 		= featureBits;

	memcpy(hello.magic, magic.c_str(), magic.size());

	write((uint8_t*)&hello, sizeof(hello));

	if (!(rxSize = read(buffer, STREAMING_DLOAD_MAX_RX_SIZE))){
		throw StreamingDloadSerialError("Device did not respond");
	}

	validateResponse(kStreamingDloadHelloResponse, reinterpret_cast<uint8_t*>(&buffer[0]), rxSize);

	memcpy(&state.hello, &buffer[0], sizeof(StreamingDloadHelloResponseHeader));

	int index = sizeof(StreamingDloadHelloResponseHeader);

	if (index + state.hello.flashIdLength > rxSize) {
		throw StreamingDloadSerialError("Flash ID overflow");
	}

	memcpy(&state.hello.flashIdenfier, &buffer[index], state.hello.flashIdLength);

	index += state.hello.flashIdLength;

	if (index + sizeof(state.hello.windowSize) > rxSize) {
		throw StreamingDloadSerialError("Window Size overflow");
	}

	memcpy(&state.hello.windowSize, &buffer[index], sizeof(state.hello.windowSize));

	index += sizeof(state.hello.windowSize);

	if (index + sizeof(state.hello.numberOfSectors) > rxSize) {
		throw StreamingDloadSerialError("Number of sectors overflow");
	}

	memcpy(&state.hello.numberOfSectors, &buffer[index], sizeof(state.hello.numberOfSectors));

	index += sizeof(state.hello.numberOfSectors);

	size_t sectorsSize = sizeof(uint32_t) * state.hello.numberOfSectors;

	if (index + sectorsSize > rxSize) {
		throw StreamingDloadSerialError("Sectors overflow");
	}

	memcpy(&state.hello.sectorSizes, &buffer[index], sectorsSize);

	index += sectorsSize;

	if (index + sizeof(state.hello.featureBits) > rxSize) {
		throw StreamingDloadSerialError("Feature bits overflow");
	}

	state.hello.featureBits = buffer[index];

	state.negotiated = true;

	return state.hello;
}

bool StreamingDloadSerial::sendUnlock(std::string code)
{
	size_t rxSize;
	std::vector<uint8_t> buffer;
	StreamingDloadUnlockRequest packet = {};

	packet.command = kStreamingDloadUnlock;
	//packet.code = std::stoul(code.c_str(), nullptr, 16); nnm

	write(reinterpret_cast<uint8_t*>(&packet), sizeof(packet));

	if (!(rxSize = read(buffer, STREAMING_DLOAD_MAX_RX_SIZE))){
		throw StreamingDloadSerialError("Device did not respond");
	}

	if (!rxSize) {
		LOGE("Device did not respond\n");
		return kStreamingDloadIOError;
	}

	return isValidResponse(kStreamingDloadUnlocked, buffer);
}

bool StreamingDloadSerial::setSecurityMode(uint8_t mode)
{

	size_t rxSize;
	std::vector<uint8_t> buffer;
	StreamingDloadSecurityModeRequest packet;

	packet.command = kStreamingDloadSecurityMode;
	packet.mode = mode;

	write(reinterpret_cast<uint8_t*>(&packet), sizeof(packet));

	if (!(rxSize = read(buffer, STREAMING_DLOAD_MAX_RX_SIZE))){
		throw StreamingDloadSerialError("Device did not respond");
	}

	return isValidResponse(kStreamingDloadSecurityModeReceived, buffer);
}

void StreamingDloadSerial::sendNop()
{
	size_t rxSize;
	std::vector<uint8_t> buffer;
	StreamingDloadNopRequest packet = {};

	packet.command = kStreamingDloadNop;
	packet.identifier = std::rand();

	write(reinterpret_cast<uint8_t*>(&packet), sizeof(packet));

	if (!(rxSize = read(buffer, STREAMING_DLOAD_MAX_RX_SIZE))){
		throw StreamingDloadSerialError("Device did not respond");
	}

	validateResponse(kStreamingDloadNopResponse, buffer);

	if (reinterpret_cast<StreamingDloadNopResponse*>(&buffer[0])->identifier != packet.identifier) {
		LOGD("Received NOP response but identifier did not match\n");
	}
}

void StreamingDloadSerial::sendReset()
{
	size_t rxSize;
	std::vector<uint8_t> buffer;
	StreamingDloadResetRequest packet = {};

	packet.command = kStreamingDloadReset;

	write(reinterpret_cast<uint8_t*>(&packet), sizeof(packet));

	if (!(rxSize = read(buffer, STREAMING_DLOAD_MAX_RX_SIZE))){
		throw StreamingDloadSerialError("Device did not respond");
	}

	validateResponse(kStreamingDloadResetAck, buffer);
}

void StreamingDloadSerial::sendPowerOff()
{
	size_t rxSize;
	std::vector<uint8_t> buffer;
	StreamingDloadResetRequest packet = {};

	packet.command = kStreamingDloadPowerOff;

	write(reinterpret_cast<uint8_t*>(&packet), sizeof(packet));

	if (!(rxSize = read(buffer, STREAMING_DLOAD_MAX_RX_SIZE))){
		throw StreamingDloadSerialError("Device did not respond");
	}

	validateResponse(kStreamingDloadPoweringDown, buffer);
}

uint8_t StreamingDloadSerial::readEcc()
{
	size_t rxSize;
	std::vector<uint8_t> buffer;
	StreamingDloadGetEccStateRequest packet = {};

	packet.command = kStreamingDloadGetEccState;

	write(reinterpret_cast<uint8_t*>(&packet), sizeof(packet));

	if (!(rxSize = read(buffer, STREAMING_DLOAD_MAX_RX_SIZE))){
		throw StreamingDloadSerialError("Device did not respond");
	}

	validateResponse(kStreamingDloadCurrentEccState, buffer);

	return reinterpret_cast<StreamingDloadGetEccStateResponse*>(&buffer[0])->status;
}

bool StreamingDloadSerial::setEcc(uint8_t status)
{
	size_t  rxSize;
	std::vector<uint8_t> buffer;
	StreamingDloadSetEccStateRequest packet = {};

	packet.command = kStreamingDloadSetEcc;
	packet.status = status;

	write(reinterpret_cast<uint8_t*>(&packet), sizeof(packet));

	if (!(rxSize = read(buffer, STREAMING_DLOAD_MAX_RX_SIZE))){
		throw StreamingDloadSerialError("Device did not respond");
	}

	return isValidResponse(kStreamingDloadSetEccResponse, buffer);
}

bool StreamingDloadSerial::openMode(uint8_t mode)
{
	size_t rxSize;
	std::vector<uint8_t> buffer;
	StreamingDloadOpenRequest packet = {};

	packet.command = kStreamingDloadOpen;
	packet.mode = mode;

	write(reinterpret_cast<uint8_t*>(&packet), sizeof(packet));

	if (!(rxSize = read(buffer, STREAMING_DLOAD_MAX_RX_SIZE))){
		throw StreamingDloadSerialError("Device did not respond");
	}

	return isValidResponse(kStreamingDloadOpened, buffer);
}

bool StreamingDloadSerial::closeMode()
{
	size_t rxSize;
	std::vector<uint8_t> buffer;
	StreamingDloadCloseRequest packet = {};

	packet.command = kStreamingDloadClose;

	write(reinterpret_cast<uint8_t*>(&packet), sizeof(packet));

	if (!(rxSize = read(buffer, STREAMING_DLOAD_MAX_RX_SIZE))){
		throw StreamingDloadSerialError("Device did not respond");
	}

	return isValidResponse(kStreamingDloadClosed, buffer);
}

bool StreamingDloadSerial::openMultiImage(uint8_t imageType)
{
	size_t rxSize;
	std::vector<uint8_t> buffer;
	StreamingDloadOpenMultiImageRequest packet = {};

	packet.command = kStreamingDloadOpenMultiImage;
	packet.type = imageType;

	write(reinterpret_cast<uint8_t*>(&packet), sizeof(packet));

	if (!(rxSize = read(buffer, STREAMING_DLOAD_MAX_RX_SIZE))){
		throw StreamingDloadSerialError("Device did not respond");
	}

	return isValidResponse(kStreamingDloadOpenedMultiImage, buffer);
}


size_t StreamingDloadSerial::readFlash(uint32_t lba, size_t amount, std::vector<uint8_t> &out, size_t sectorSize)
{
	size_t rx;
	size_t total 	= 0;
	size_t step 	= amount;
	int blocksRead  = 0;

	std::vector<uint8_t> temp;
	StreamingDloadReadRequest packet = {};

	out.reserve(out.size() + amount);
	temp.reserve(STREAMING_DLOAD_MAX_RX_SIZE);

	if (state.negotiated && state.hello.maxPreferredBlockSize && step > state.hello.maxPreferredBlockSize) {
		step = state.hello.maxPreferredBlockSize;
	} else if (step > STREAMING_DLOAD_MAX_DATA_SIZE) {
		step = STREAMING_DLOAD_MAX_DATA_SIZE;
	}

	// align the requested amount to block size
	while(amount % sectorSize != 0) {
		amount++;
	}

	while (total < amount) {

		packet.command = kStreamingDloadRead;
		packet.address = lba + blocksRead;
		packet.length  = step;

		LOGD("Requesting %lu bytes starting from LBA %08X (%d sectors)\n",
			packet.length,
			packet.address,
			(packet.length / sectorSize)
		);

		write(reinterpret_cast<uint8_t*>(&packet), sizeof(packet));

		if (!(rx = read(temp, STREAMING_DLOAD_MAX_RX_SIZE))) {
			throw StreamingDloadSerialError("Device did not respond");
		}

		validateResponse(kStreamingDloadReadData, temp);

		if (reinterpret_cast<StreamingDloadReadResponse*>(&temp[0])->address != packet.address) {
			throw StreamingDloadSerialError("Packet address and response address differ");
		}


		// remove the command code, address to only keep the real data
		temp.erase(temp.end() - rx, ((temp.end() - rx) + sizeof(packet.command) + sizeof(packet.address)));

		out.reserve(out.size() + temp.size());

		std::copy(temp.begin(), temp.end(), std::back_inserter(out));

		total += temp.size();

		blocksRead += temp.size() / sectorSize;

		temp.clear();

	}

	return total;
}


size_t StreamingDloadSerial::readFlash(uint32_t lba, size_t amount, std::ofstream& out, size_t sectorSize)
{
	size_t total  	  = 0;
	size_t step   	  = amount;
	std::vector<uint8_t> temp;
	int blocksRead  = 0;

	if (state.negotiated && state.hello.maxPreferredBlockSize && step > state.hello.maxPreferredBlockSize) {
		step = state.hello.maxPreferredBlockSize;
	} else if (step > STREAMING_DLOAD_MAX_DATA_SIZE) {
		step = STREAMING_DLOAD_MAX_DATA_SIZE;
	}

	// align the requested amount to block size
	while(amount % sectorSize != 0) {
		amount++;
	}

	temp.reserve(STREAMING_DLOAD_MAX_RX_SIZE);

	while (total < amount) {

		if ((amount - total) < step) {
			step = amount - total;
		}

		readFlash(lba+blocksRead, step, temp);

		out.write(reinterpret_cast<char *>(&temp[0]), temp.size());

		total += temp.size();

		blocksRead += temp.size() / sectorSize;

		temp.clear();
	}

	return total;
}

uint8_t StreamingDloadSerial::writePartitionTable(std::string fileName, bool overwrite)
{
	std::stringstream ss;
	size_t fileSize;
	std::ifstream file(fileName.c_str(), std::ios::in | std::ios::binary);

	if (!file.is_open()) {
		ss << "Could Not Open File " << fileName;
		throw StreamingDloadSerialError(ss.str());
	}

	file.seekg(0, file.end);
	fileSize = (size_t)file.tellg();
	file.seekg(0, file.beg);

	if (fileSize > 512) {
		file.close();
		throw StreamingDloadSerialError("File can\'t exceed 512 bytes");
	}

	size_t rxSize;
	std::vector<uint8_t> buffer;
	StreamingDloadPartitionTableRequest packet = {};

	packet.command = kStreamingDloadPartitionTable;
	packet.overrideExisting = overwrite;

	file.read(reinterpret_cast<char *>(&packet.data), fileSize);

	file.close();

	write(reinterpret_cast<uint8_t*>(&packet), sizeof(packet));

	if (!(rxSize = read(buffer, STREAMING_DLOAD_MAX_RX_SIZE))) {
		throw StreamingDloadSerialError("Device did not respond");
	}

	validateResponse(kStreamingDloadPartitionTableReceived, &buffer[0], rxSize);

	return reinterpret_cast<StreamingDloadPartitionTableResponse*>(&buffer[0])->status;
}

size_t StreamingDloadSerial::writeFlash(uint32_t lba, std::vector<uint8_t>& data, size_t sectorSize)
{
	return writeFlash(lba, &data[0], data.size(), sectorSize);
}

size_t StreamingDloadSerial::writeFlash(uint32_t lba, uint8_t* data, size_t amount, size_t sectorSize)
{
	size_t step = amount;
	size_t written = 0;
	size_t rx = 0;
	int blocksWritten = 0;

	StreamingDloadStreamWriteRequest* request = nullptr;
	uint8_t readbuff[STREAMING_DLOAD_MAX_RX_SIZE];
	StreamingDloadStreamWriteResponse* response = reinterpret_cast<StreamingDloadStreamWriteResponse*>(&readbuff);

	if (data == nullptr || !amount) {
		throw StreamingDloadSerialError("No data to write");
	}

	if (state.negotiated && state.hello.maxPreferredBlockSize && step > state.hello.maxPreferredBlockSize) {
		step = state.hello.maxPreferredBlockSize;
	} else if (step > STREAMING_DLOAD_MAX_DATA_SIZE) {
		step = STREAMING_DLOAD_MAX_DATA_SIZE;
	}

	request = reinterpret_cast<StreamingDloadStreamWriteRequest*>(new uint8_t[sizeof(StreamingDloadStreamWriteRequest) + step]);

	if (!request) {
		throw StreamingDloadSerialError("Error allocating memory for write");
	}

	while (written < amount) {
		request->command = kStreamingDloadStreamWrite;
		request->address = lba + blocksWritten;

		if ((amount - written) < step) {
			step = amount - written;
		}

		std::copy((data + written), (data + written + step), request->data);

		write(reinterpret_cast<uint8_t*>(request), step + sizeof(request->command) + sizeof(request->address));

		if (!(rx = read(readbuff, sizeof(readbuff)))) {
			delete[] request;
			throw StreamingDloadSerialError("Device did not respond");
		}

		validateResponse(kStreamingDloadBlockWritten, reinterpret_cast<uint8_t*>(&readbuff), rx);

		if (request->address != response->address) {
			delete[] request;
			throw StreamingDloadSerialError("Response address differs from requested write address");
		}

		written += step;
		blocksWritten += step/sectorSize;
	}

	delete[] request;

	return written;
}

/*
size_t StreamingDloadSerial::writeFlashUnframed(uint32_t address, uint8_t* data, size_t length, size_t sectorSize)
{
	size_t  rx = 0;
	size_t  total = sizeof(StreamingDloadUnframedStreamWriteRequest) + length;
	uint8_t rxbuffer[STREAMING_DLOAD_MAX_RX_SIZE];

	if (data == nullptr || !length) {
		throw StreamingDloadSerialError("No data to write");
	}

	StreamingDloadUnframedStreamWriteRequest* request = reinterpret_cast<StreamingDloadUnframedStreamWriteRequest*>(new uint8_t[total]());

	if (!request) {
		throw StreamingDloadSerialError("Error allocating memory for write");
	}

	request->command = kStreamingDloadUnframedStreamWrite;
	request->address = address;
	request->length  = length;

	std::copy(data, data + length, request->data);

	write(reinterpret_cast<uint8_t*>(request), total, false);

	if (!(rx = read(rxbuffer, sizeof(rxbuffer)))) {
		delete[] request;
		throw StreamingDloadSerialError("Device did not respond");
	}

	validateResponse(kStreamingDloadUnframedStreamWriteResponse, reinterpret_cast<uint8_t*>(&rxbuffer), rx);

	if (request->address != reinterpret_cast<StreamingDloadUnframedStreamWriteResponse*>(&rxbuffer)->address) {
		delete[] request;
		throw StreamingDloadSerialError("Response address differs from requested write address");
	}

	delete[] request;

	return total;
}*/

void StreamingDloadSerial::eraseFlash()
{
	size_t  rxSize;
	std::vector<uint8_t> buffer;
	StreamingDloadEraseFlashRequest packet = {};

	packet.command = kStreamingDloadEraseFlash;

	write(reinterpret_cast<uint8_t*>(&packet), sizeof(packet));

	if (!(rxSize = read(buffer, STREAMING_DLOAD_MAX_RX_SIZE))){
		throw StreamingDloadSerialError("Device did not respond");
	}

	validateResponse(kStreamingDloadFlashErased, buffer);
}

bool StreamingDloadSerial::isValidResponse(uint8_t expectedCommand, uint8_t* response, size_t responseSize)
{
	std::stringstream ss;

	if (responseSize <= 0) {
		return false;
	}

	if (response[0] != expectedCommand) {
		if (response[0] == kStreamingDloadLog) {
			StreamingDloadLogResponse* packet = (StreamingDloadLogResponse*)response;
			if (responseSize == sizeof(state.lastLog)) {
				memcpy(reinterpret_cast<uint8_t*>(&state.lastLog), packet, sizeof(state.lastLog));
			} else {
				LOGE("Response size doesnt match log response size\n");
			}
			return false;
		} else if (response[0] == kStreamingDloadError) {
			StreamingDloadErrorResponse* packet = (StreamingDloadErrorResponse*)response;
			if (responseSize == sizeof(state.lastError)) {
				memcpy(reinterpret_cast<uint8_t*>(&state.lastError), packet, sizeof(state.lastError));
			} else {
				LOGE("Response size doesnt match error response size\n");
			}
			return false;

		} else {
			return false;
		}
	}
	return true;
}

bool StreamingDloadSerial::isValidResponse(uint8_t expectedCommand, std::vector<uint8_t> &data)
{
	return isValidResponse(expectedCommand, &data[0], data.size());
}

void StreamingDloadSerial::validateResponse(uint8_t expectedCommand, uint8_t* response, size_t responseSize)
{
	std::stringstream ss;

	if (responseSize <= 0) {
		throw StreamingDloadSerialError("No Response");
	}

	if (response[0] != expectedCommand) {
		if (response[0] == kStreamingDloadLog) {
			StreamingDloadLogResponse* packet = (StreamingDloadLogResponse*)response;
			if (responseSize == sizeof(state.lastLog)) {
				memcpy(reinterpret_cast<uint8_t*>(&state.lastLog), packet, sizeof(state.lastLog));
			} else {
				LOGE("Response size doesnt match log response size %li %li\n", sizeof(state.lastLog), responseSize);
			}

			ss << "Received Log Response: " << (char*)&packet->text;
			throw StreamingDloadSerialError(ss.str());
		} else if (response[0] == kStreamingDloadError) {
			StreamingDloadErrorResponse* packet = (StreamingDloadErrorResponse*)response;
			if (responseSize == sizeof(state.lastError)) {
				memcpy(reinterpret_cast<uint8_t*>(&state.lastError), packet, sizeof(state.lastError));
			} else {
				LOGE("Response size doesnt match error response size %li %li\n", sizeof(state.lastError), responseSize);
			}
			ss << "Received Error Response: " << getNamedError(packet->code);
			throw StreamingDloadSerialError(ss.str(), packet->code);

		} else {
			throw StreamingDloadSerialError("Unexpected Response");
		}
	}
}

void StreamingDloadSerial::validateResponse(uint8_t expectedCommand, std::vector<uint8_t> &response)
{
	return validateResponse(expectedCommand, &response[0], response.size());
}

std::string StreamingDloadSerial::getNamedError(uint8_t code)
{
	switch (code) {
		case kStreamingDloadErrorInvalidDestinationAddress:     return "Invalid Destination Address";
		case kStreamingDloadErrorInvalidLength:                 return "Invalid Length";
		case kStreamingDloadErrorUnexpectedPacketEnd:           return "Unexpected End of Packet";
		case kStreamingDloadErrorInvalidCommand:                return "Invalid Command";
		case kStreamingDloadErrorWrongFlashIntelligentId:       return "Wrong Flash Intelligent ID";
		case kStreamingDloadErrorBadProgrammingVoltage:         return "Bad Programming Voltage";
		case kStreamingDloadErrorWriteVerifyFailed:             return "Write Verify Failed";
		case kStreamingDloadErrorIncorrectSecurityCode:         return "Incorrect Security Code";
		case kStreamingDloadErrorCannotPowerDown:               return "Cannot Power Down";
		case kStreamingDloadErrorNandProgrammingUnsupported:    return "NAND Flash Programming Not Supported";
		case kStreamingDloadErrorCommandOutOfSequence:          return "Command Out of Sequence";
		case kStreamingDloadErrorCloseDidNotSucceed:            return "Close Did Not Succeed";
		case kStreamingDloadErrorIncompatibleFeatureBits:       return "Incompatible Features Bits";
		case kStreamingDloadErrorOutOfSpace:                    return "Out of Space";
		case kStreamingDloadErrorInvalidSecurityMode:           return "Invalid Security Mode";
		case kStreamingDloadErrorMultiImageNandUnsupported:     return "Multi Image NAND Not Supported";
		case kStreamingDloadErrorPowerOffCmdUnsupported:        return "Power Off Command Not Supported";
		default:                                                return "Unknown";
	}
}

std::string StreamingDloadSerial::getNamedOpenMode(uint8_t mode)
{
	switch (mode) {
		case kStreamingDloadOpenModeBootloader:         return "Bootloader Download";
		case kStreamingDloadOpenModeBootableImage:      return "Bootable Image Download";
		case kStreamingDloadOpenModeCefs:               return "CEFS Image Download";
		default:                                        return "Unknown";
	}
}

std::string StreamingDloadSerial::getNamedMultiImage(uint8_t imageType)
{
	switch (imageType) {
		case kStreamingDloadOpenModeMultiNone:          return "None";
		case kStreamingDloadOpenModeMultiPbl:           return "Primary boot loader";
		case kStreamingDloadOpenModeMultiQcsblhHdCfg:   return "Qualcomm secondary boot loader header and config data";
		case kStreamingDloadOpenModeMultiQcsbl:         return "Qualcomm secondary boot loader";
		case kStreamingDloadOpenModeMultiOemsbl:        return "OEM secondary boot loader";
		case kStreamingDloadOpenModeMultiAmss:          return "AMSS modem executable";
		case kStreamingDloadOpenModeMultiApps:          return "AMSS applications executable";
		case kStreamingDloadOpenModeMultiObl:           return "MSM6250 OTP boot loader";
		case kStreamingDloadOpenModeMultiFotaui:        return "FOTA UI binary";
		case kStreamingDloadOpenModeMultiCefs:          return "Compact EFS2 image";
		case kStreamingDloadOpenModeMultiAppsBL:        return "AMSS applications boot loader";
		case kStreamingDloadOpenModeMultiApps_CEFS:     return "Apps CEFS image";
		case kStreamingDloadOpenModeMultiFlashBin:      return "Flash.bin for Windows Mobile";
		case kStreamingDloadOpenModeMultiDsp1:          return "DSP1 runtime image";
		case kStreamingDloadOpenModeMultiCustom:        return "User-defined partition";
		case kStreamingDloadOpenModeMultiDbl:           return "DBL image for Secure Boot 2.0";
		case kStreamingDloadOpenModeMultiOsbl:          return "OSBL image for Secure Boot 2.0";
		case kStreamingDloadOpenModeMultiFsbl:          return "FSBL image for Secure Boot 2.0";
		case kStreamingDloadOpenModeMultiDsp2:          return "DSP2 executable";
		case kStreamingDloadOpenModeMultiRaw:           return "Apps EFS2 raw image";
		case kStreamingDloadOpenModeMultiRofs1:         return "ROFS1 - Symbian";
		case kStreamingDloadOpenModeMultiRofs2:         return "ROFS2 - Symbian";
		case kStreamingDloadOpenModeMultiRofs3:         return "ROFS3 - Symbian";
		case kStreamingDloadOpenModeMultiEmmcUser:      return "EMMC USER partition";
		case kStreamingDloadOpenModeMultiEmmcBoot0:     return "EMMC BOOT0 partition";
		case kStreamingDloadOpenModeMultiEmmcBoot1:     return "EMMC BOOT1 partition";
		case kStreamingDloadOpenModeMultiRpmb:          return "EMMC RPMB";
		case kStreamingDloadOpenModeMultiGpp1:          return "EMMC GPP1";
		case kStreamingDloadOpenModeMultiGpp2:          return "EMMC GPP2";
		case kStreamingDloadOpenModeMultiGpp3:          return "EMMC GPP3";
		case kStreamingDloadOpenModeMultiGpp4:          return "EMMC GPP4";
		default:                                        return "Unknown";
	}
}

void StreamingDloadSerial::close()
{
	try {
		GenericSerial::close();
		state = {};
	} catch (...) {
		state = {};
	}
}
