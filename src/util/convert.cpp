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
* @file convert.h
* @package openpst/libopenpst
* @brief QCDM response conversion helper functions
*
* @author Gassan Idriss <ghassani@gmail.com>
* @author Matteson Raab <mraabhimself@gmail.com>
*/

#include "util/convert.h"

/**
* hexToString
* @param input
* @param length
*/
std::string hexToString(char *input, int length) {
	char outputBuffer[128];
	std::string result;

	for (int i = 0; i < length; i++) {
#ifdef _WIN32
		//sprintf_s(outputBuffer, "%c", hex_trans_display[input[i]]);
#else
		sprintf(outputBuffer, "%c", hex_trans_display[input[i]]);
#endif
		result.append(outputBuffer);
	}

	return result;
}

/**
* bytesToHex
* @param input
* @param length
*/
std::string bytesToHex(unsigned char* input, int size, bool byteswap) {
  std::string result;

  if (byteswap) {
	for (int i = size; i >= 0; i--) {
		char buffer[2];
#ifdef _WIN32
		//sprintf_s(buffer, "%02x", input[i]); nnm
#else
		sprintf(buffer, "%02x", input[i]);
#endif
		result.append(buffer);
	}
  } else {
	for (int i = 0; i < size; i++) {
		char buffer[2];
#ifdef _WIN32
		//sprintf_s(buffer, "%02x", input[i]);
#else
		sprintf(buffer, "%02x", input[i]);
#endif
		result.append(buffer);
	}
  }

  return result;
}

std::string min1Decode(unsigned char input[3]) {
	char buffer[6];
	int32_t i, chunk1, chunk2, chunk3;
	std::string str, result;

	str = bytesToHex(input, 4, false);
	i = strtoul(str.c_str(), nullptr, 16);

	chunk1 = (i & 0xFFC000) >> 14;
	chunk1 = ((chunk1 + 1) % 10) + (((((chunk1 % 100) / 10) + 1) % 10) * 10) + ((((chunk1 / 100) + 1) % 10) * 100);

	chunk2 = ((i & 0x3C00) >> 10) % 10;

	chunk3 = (i & 0x3FF);
	chunk3 = ((chunk3 + 1) % 10) + (((((chunk3 % 100) / 10) + 1) % 10) * 10) + ((((chunk3 / 100) + 1) % 10) * 100);

#ifdef _WIN32
	//sprintf_s(buffer, "%03i%i%i", chunk1, chunk2, chunk3); nnm
#else
	sprintf(buffer, "%03i%i%i", chunk1, chunk2, chunk3);
#endif
	result.append(buffer);

	return result;
}

std::string min2Decode(unsigned char input[1]) {
	char buffer[2];
	int32_t i, chunk;
	std::string str, result;

	str = bytesToHex(input, 2, false);
	i = strtoul(str.c_str(), nullptr, 16);

	chunk = ((i + 1) % 10) + (((((i % 100) / 10) + 1) % 10) * 10) + ((((i / 100) + 1) % 10) * 100);

#ifdef _WIN32
	//sprintf_s(buffer, "%03i", chunk); nnm
#else
	sprintf(buffer, "%03i", chunk);
#endif

	result.append(buffer);

	return result;
}

std::string sidDecode(unsigned char input[1]) {
	char buffer[4];
	std::string str, result;
	uint16_t i;

	str = bytesToHex(input, 2, false);
	i = (uint16_t)std::strtoul(str.c_str(), nullptr, 16);

#ifdef _WIN32
//	sprintf_s(buffer, "%5i", i); nnm
#else
	sprintf(buffer, "%5i", i);
#endif
	result.append(buffer);

	return result;
}

long HexToBytes(std::string input) {
	return std::strtoul(input.c_str(), nullptr, 16);
}
