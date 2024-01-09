/*

  Copyright (c) 2015, 2016 Hubert Denkmair <hubert@denkmair.de>

  This file is part of cangaroo.

  cangaroo is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  cangaroo is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with cangaroo.  If not, see <http://www.gnu.org/licenses/>.

*/
// Edited by WIZAPPLY 2024/1/6

#include "CanMessage.h"

#include <iostream>
#include <sstream>
#include <ios>     // std::left, std::right
#include <iomanip> 

static inline uint64_t XXH_swap64(uint64_t x)
{
	return ((x << 56) & 0xff00000000000000ULL) |
		((x << 40) & 0x00ff000000000000ULL) |
		((x << 24) & 0x0000ff0000000000ULL) |
		((x << 8) & 0x000000ff00000000ULL) |
		((x >> 8) & 0x00000000ff000000ULL) |
		((x >> 24) & 0x0000000000ff0000ULL) |
		((x >> 40) & 0x000000000000ff00ULL) |
		((x >> 56) & 0x00000000000000ffULL);
}

enum {
	id_flag_extended = 0x80000000,
	id_flag_rtr      = 0x40000000,
	id_flag_error    = 0x20000000,
	id_mask_extended = 0x1FFFFFFF,
	id_mask_standard = 0x7FF
};

CanMessage::CanMessage()
  : _raw_id(0), _dlc(0), _u64(0)
{
    _timestamp.tv_sec = 0;
    _timestamp.tv_usec = 0;
}

CanMessage::CanMessage(uint32_t can_id)
  : _dlc(0), _u64(0)
{
    _timestamp.tv_sec = 0;
    _timestamp.tv_usec = 0;
    setId(can_id);
}
CanMessage::CanMessage(uint32_t can_id, bool ext, bool rtr)
	: _dlc(0), _u64(0)
{
	_timestamp.tv_sec = 0;
	_timestamp.tv_usec = 0;
	setId(can_id);
	setExtended(ext);
	setRTR(rtr);
}

CanMessage::CanMessage(const CanMessage &msg)
{
    cloneFrom(msg);
}

void CanMessage::cloneFrom(const CanMessage &msg)
{
    _raw_id = msg._raw_id;
    _dlc = msg._dlc;
    _u64 = msg._u64;
    _timestamp = msg._timestamp;
}


uint32_t CanMessage::getRawId() const {
	return _raw_id;
}

void CanMessage::setRawId(const uint32_t raw_id) {
	_raw_id = raw_id;
}

uint32_t CanMessage::getId() const {
	if (isExtended()) {
		return _raw_id & id_mask_extended;
	} else {
		return _raw_id & id_mask_standard;
	}
}

void CanMessage::setId(const uint32_t id) {
    _raw_id &= ~ id_mask_extended;
    _raw_id = id;
    if (id>0x7FF) {
		setExtended(true);
	}
}

bool CanMessage::isExtended() const {
	return (_raw_id & id_flag_extended) != 0;
}

void CanMessage::setExtended(const bool isExtended) {
	if (isExtended) {
		_raw_id |= id_flag_extended;
	} else {
		_raw_id &= ~id_flag_extended;
	}
}

bool CanMessage::isRTR() const {
	return (_raw_id & id_flag_rtr) != 0;
}

void CanMessage::setRTR(const bool isRTR) {
	if (isRTR) {
		_raw_id |= id_flag_rtr;
	} else {
		_raw_id &= ~id_flag_rtr;
	}
}

bool CanMessage::isErrorFrame() const {
	return (_raw_id & id_flag_error) != 0;
}

void CanMessage::setErrorFrame(const bool isErrorFrame) {
	if (isErrorFrame) {
		_raw_id |= id_flag_error;
	} else {
		_raw_id &= ~id_flag_error;
    }
}

uint8_t CanMessage::getLength() const {
	return _dlc;
}

void CanMessage::setLength(const uint8_t dlc) {
	if (dlc<=8) {
		_dlc = dlc;
	} else {
		_dlc = 8;
	}
}

uint8_t CanMessage::getByte(const uint8_t index) const {
	if (index<sizeof(_u8)) {
		return _u8[index];
	} else {
		return 0;
	}
}

void CanMessage::setByte(const uint8_t index, const uint8_t value) {
	if (index<sizeof(_u8)) {
		_u8[index] = value;
    }
}

uint64_t CanMessage::getU64() const
{
    return _u64;
}

uint64_t CanMessage::extractRawSignal(uint8_t start_bit, const uint8_t length, const bool isBigEndian) const
{
    if ((start_bit+length) > (getLength()*8)) {
        return 0;
    }

    uint64_t data = _u64;

    if (isBigEndian) {
        // it's magic. just swap the byte order and adjust the startbit, then it works like little endian
        data = XXH_swap64(data);
        start_bit = 63 - start_bit - length;
    }

    data >>= start_bit;

    uint64_t mask =  0xFFFFFFFFFFFFFFFF;
    mask <<= length;
    mask = ~mask;

    data &= mask;

    return data;
}

void CanMessage::setData(const uint8_t d0) {
	_dlc = 1;
	_u8[0] = d0;
}

void CanMessage::setData(const uint8_t d0, const uint8_t d1) {
	_dlc = 2;
	_u8[0] = d0;
	_u8[1] = d1;
}

void CanMessage::setData(const uint8_t d0, const uint8_t d1, const uint8_t d2) {
	_dlc = 3;
	_u8[0] = d0;
	_u8[1] = d1;
	_u8[2] = d2;
}

void CanMessage::setData(const uint8_t d0, const uint8_t d1, const uint8_t d2,
		const uint8_t d3) {
	_dlc = 4;
	_u8[0] = d0;
	_u8[1] = d1;
	_u8[2] = d2;
	_u8[3] = d3;
}

void CanMessage::setData(const uint8_t d0, const uint8_t d1, const uint8_t d2,
		const uint8_t d3, const uint8_t d4) {
	_dlc = 5;
	_u8[0] = d0;
	_u8[1] = d1;
	_u8[2] = d2;
	_u8[3] = d3;
	_u8[4] = d4;
}

void CanMessage::setData(const uint8_t d0, const uint8_t d1, const uint8_t d2,
		const uint8_t d3, const uint8_t d4, const uint8_t d5) {
	_dlc = 6;
	_u8[0] = d0;
	_u8[1] = d1;
	_u8[2] = d2;
	_u8[3] = d3;
	_u8[4] = d4;
	_u8[5] = d5;
}

void CanMessage::setData(const uint8_t d0, const uint8_t d1, const uint8_t d2,
		const uint8_t d3, const uint8_t d4, const uint8_t d5,
		const uint8_t d6) {
	_dlc = 7;
	_u8[0] = d0;
	_u8[1] = d1;
	_u8[2] = d2;
	_u8[3] = d3;
	_u8[4] = d4;
	_u8[5] = d5;
	_u8[6] = d6;
}

void CanMessage::setData(const uint8_t d0, const uint8_t d1, const uint8_t d2,
		const uint8_t d3, const uint8_t d4, const uint8_t d5, const uint8_t d6,
		const uint8_t d7) {
	_dlc = 8;
	_u8[0] = d0;
	_u8[1] = d1;
	_u8[2] = d2;
	_u8[3] = d3;
	_u8[4] = d4;
	_u8[5] = d5;
	_u8[6] = d6;
    _u8[7] = d7;
}

void CanMessage::setDataPush(const uint8_t value) {
	
	if (_dlc < 8) {
		_u8[_dlc] = value;
		_dlc++;
	}
}

timeval CanMessage::getTimestamp() const
{
    return _timestamp;
}

void CanMessage::setTimestamp(const timeval timestamp)
{
    _timestamp = timestamp;
}

void CanMessage::setTimestamp(const uint64_t seconds, const uint32_t micro_seconds)
{
    _timestamp.tv_sec = (long)seconds;
    _timestamp.tv_usec = (long)micro_seconds;
}

double CanMessage::getFloatTimestamp() const
{
    return (double)_timestamp.tv_sec + ((double)_timestamp.tv_usec/1000000);
}

std::wstring CanMessage::getIdString() const
{
	std::wostringstream ss;

    if (isExtended()) {
		ss << "0x" << std::setfill(L'0') << std::right << std::setw(8) << std::hex << getId();
    } else {
		ss << "0x" << std::setfill(L'0') << std::right << std::setw(3) << std::hex << getId();
    }
	return ss.str();
}

std::wstring CanMessage::getDataHexString() const
{
	std::wostringstream ss;
	ss << "";

	for (int i = 0; i < getLength(); i++) {
		ss << "0x" << std::setfill(L'0') << std::right << std::setw(2) << std::hex << getByte(i) << " ";
    }

	return ss.str();
}