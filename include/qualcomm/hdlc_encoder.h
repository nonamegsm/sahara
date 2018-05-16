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
* @file hdlc_encoder.h
* @package openpst/libopenpst
* @brief HDLC Encoding & Decoding
*
* @author Gassan Idriss <ghassani@gmail.com>
*/
#pragma once

#include "definitions.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

/* QCDM protocol frames are pseudo Async HDLC frames which end with a 3-byte
*  trailer. This trailer consists of the 16-bit CRC of the frame plus an ending
* "async control character" whose value is 0x7E.  The frame *and* the CRC are
* escaped before adding the trailing control character so that the control
* character (0x7E) and the escape marker (0x7D) are never seen in the frame.
*/
#define HDLC_ESC_CHAR           0x7D  /* Escape sequence 1st character value */
#define HDLC_ESC_MASK           0x20  /* Escape sequence complement value */
#define HDLC_CONTROL_CHAR       0x7E
#define HDLC_OVERHEAD_LENGTH    4
#define HDLC_TRAILER_LENGTH     3
#define HDLC_LEADING_LENGTH     1

namespace OpenPST {
	namespace QC {
		class HdlcEncoder {
			private:
				/* Table of CRCs for each possible byte, with a generator polynomial of 0x8408 */
				const uint16_t crc_table[256] = {
					0x0000, 0x1189, 0x2312, 0x329b, 0x4624, 0x57ad, 0x6536, 0x74bf,
					0x8c48, 0x9dc1, 0xaf5a, 0xbed3, 0xca6c, 0xdbe5, 0xe97e, 0xf8f7,
					0x1081, 0x0108, 0x3393, 0x221a, 0x56a5, 0x472c, 0x75b7, 0x643e,
					0x9cc9, 0x8d40, 0xbfdb, 0xae52, 0xdaed, 0xcb64, 0xf9ff, 0xe876,
					0x2102, 0x308b, 0x0210, 0x1399, 0x6726, 0x76af, 0x4434, 0x55bd,
					0xad4a, 0xbcc3, 0x8e58, 0x9fd1, 0xeb6e, 0xfae7, 0xc87c, 0xd9f5,
					0x3183, 0x200a, 0x1291, 0x0318, 0x77a7, 0x662e, 0x54b5, 0x453c,
					0xbdcb, 0xac42, 0x9ed9, 0x8f50, 0xfbef, 0xea66, 0xd8fd, 0xc974,
					0x4204, 0x538d, 0x6116, 0x709f, 0x0420, 0x15a9, 0x2732, 0x36bb,
					0xce4c, 0xdfc5, 0xed5e, 0xfcd7, 0x8868, 0x99e1, 0xab7a, 0xbaf3,
					0x5285, 0x430c, 0x7197, 0x601e, 0x14a1, 0x0528, 0x37b3, 0x263a,
					0xdecd, 0xcf44, 0xfddf, 0xec56, 0x98e9, 0x8960, 0xbbfb, 0xaa72,
					0x6306, 0x728f, 0x4014, 0x519d, 0x2522, 0x34ab, 0x0630, 0x17b9,
					0xef4e, 0xfec7, 0xcc5c, 0xddd5, 0xa96a, 0xb8e3, 0x8a78, 0x9bf1,
					0x7387, 0x620e, 0x5095, 0x411c, 0x35a3, 0x242a, 0x16b1, 0x0738,
					0xffcf, 0xee46, 0xdcdd, 0xcd54, 0xb9eb, 0xa862, 0x9af9, 0x8b70,
					0x8408, 0x9581, 0xa71a, 0xb693, 0xc22c, 0xd3a5, 0xe13e, 0xf0b7,
					0x0840, 0x19c9, 0x2b52, 0x3adb, 0x4e64, 0x5fed, 0x6d76, 0x7cff,
					0x9489, 0x8500, 0xb79b, 0xa612, 0xd2ad, 0xc324, 0xf1bf, 0xe036,
					0x18c1, 0x0948, 0x3bd3, 0x2a5a, 0x5ee5, 0x4f6c, 0x7df7, 0x6c7e,
					0xa50a, 0xb483, 0x8618, 0x9791, 0xe32e, 0xf2a7, 0xc03c, 0xd1b5,
					0x2942, 0x38cb, 0x0a50, 0x1bd9, 0x6f66, 0x7eef, 0x4c74, 0x5dfd,
					0xb58b, 0xa402, 0x9699, 0x8710, 0xf3af, 0xe226, 0xd0bd, 0xc134,
					0x39c3, 0x284a, 0x1ad1, 0x0b58, 0x7fe7, 0x6e6e, 0x5cf5, 0x4d7c,
					0xc60c, 0xd785, 0xe51e, 0xf497, 0x8028, 0x91a1, 0xa33a, 0xb2b3,
					0x4a44, 0x5bcd, 0x6956, 0x78df, 0x0c60, 0x1de9, 0x2f72, 0x3efb,
					0xd68d, 0xc704, 0xf59f, 0xe416, 0x90a9, 0x8120, 0xb3bb, 0xa232,
					0x5ac5, 0x4b4c, 0x79d7, 0x685e, 0x1ce1, 0x0d68, 0x3ff3, 0x2e7a,
					0xe70e, 0xf687, 0xc41c, 0xd595, 0xa12a, 0xb0a3, 0x8238, 0x93b1,
					0x6b46, 0x7acf, 0x4854, 0x59dd, 0x2d62, 0x3ceb, 0x0e70, 0x1ff9,
					0xf78f, 0xe606, 0xd49d, 0xc514, 0xb1ab, 0xa022, 0x92b9, 0x8330,
					0x7bc7, 0x6a4e, 0x58d5, 0x495c, 0x3de3, 0x2c6a, 0x1ef1, 0x0f78
				};
				
			public:
				/**
				* @brief encode - Encodes a buffer using hdlc protocol
				*
				* @param uint8_t* data - Pointer to the data to encode
				* @param size_t size   - The size of the input buffer
				* @param uint8_t** out - Heap allocated buffer which contains the encoded result (you need to delete[] this on your own)
				*
				* @return size_t - The encoded buffer size or 0 on error
				*/
				size_t encode(uint8_t* data, size_t size, uint8_t** out);

				/**
				* @brief encode - Encodes a vector buffer using hdlc protocol
				*
				* @param std::vector<uint8_t>& data - The buffer to encode
				*
				* @return size_t - The encoded vector size or 0 on error
				*/
				size_t encode(std::vector<uint8_t> &data);

				/**
				* @brief decode - Decodes a buffer using hdlc protocol
				*
				* @param uint8_t* data  - Pointer to the data to decode
				* @param size_t size    - The size of the input buffer
				* @param uint8_t** out  - Heap allocated buffer which contains the decoded result (you need to delete[] this on your own)
				*
				* @return size_t - The decoded buffer size or 0 on error
				*/
				size_t decode(uint8_t* data, size_t size, uint8_t** out);

				/**
				* @brief decode - Decodes a vector buffer using hdlc protocol
				*
				* @param std::vector<uint8_t>& data - The buffer to decode
				*
				* @return size_t - The decoded vector size or 0 on error
				*/
				size_t decode(std::vector<uint8_t> &data);

				/**
				* @brief crc16 - Encodes a buffer using hdlc protocol
				*
				* @param const char * buffer - The buffer to calculate the CRC
				* @param size_t - The size of the buffer
				*
				* @return uint16_t
				*/
				uint16_t crc16(const char *buffer, size_t len);
		};
	}
}