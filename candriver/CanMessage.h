#pragma once

#include <stdint.h>
#include <string>
#include <windows.h>

class CanMessage {
public:
	CanMessage();
	CanMessage(uint32_t can_id);
	CanMessage(uint32_t can_id, bool ext, bool rtr);
    CanMessage(const CanMessage &msg);
    void cloneFrom(const CanMessage &msg);

	uint32_t getRawId() const;
	void setRawId(const uint32_t raw_id);

	uint32_t getId() const;
	void setId(const uint32_t id);

	bool isExtended() const;
	void setExtended(const bool isExtended);

	bool isRTR() const;
	void setRTR(const bool isRTR);

	bool isErrorFrame() const;
	void setErrorFrame(const bool isErrorFrame);

	uint8_t getLength() const;
	void setLength(const uint8_t dlc);

	uint8_t getByte(const uint8_t index) const;
	void setByte(const uint8_t index, const uint8_t value);

    uint64_t getU64() const;
    uint64_t extractRawSignal(uint8_t start_bit, const uint8_t length, const bool isBigEndian) const;

	void setData(const uint8_t d0);
	void setData(const uint8_t d0, const uint8_t d1);
	void setData(const uint8_t d0, const uint8_t d1, const uint8_t d2);
	void setData(const uint8_t d0, const uint8_t d1, const uint8_t d2, const uint8_t d3);
	void setData(const uint8_t d0, const uint8_t d1, const uint8_t d2, const uint8_t d3, const uint8_t d4);
	void setData(const uint8_t d0, const uint8_t d1, const uint8_t d2, const uint8_t d3, const uint8_t d4, const uint8_t d5);
	void setData(const uint8_t d0, const uint8_t d1, const uint8_t d2, const uint8_t d3, const uint8_t d4, const uint8_t d5, const uint8_t d6);
	void setData(const uint8_t d0, const uint8_t d1, const uint8_t d2, const uint8_t d3, const uint8_t d4, const uint8_t d5, const uint8_t d6, const uint8_t d7);
	void setDataPush(const uint8_t value);

    struct timeval getTimestamp() const;
    void setTimestamp(const struct timeval timestamp);
    void setTimestamp(const uint64_t seconds, const uint32_t micro_seconds);

    double getFloatTimestamp() const;

    std::wstring getIdString() const;
	std::wstring getDataHexString() const;

private:
	uint32_t _raw_id;
    uint8_t _dlc;

    union {
		uint8_t _u8[8];
		uint16_t _u16[4];
		uint32_t _u32[2];
		uint64_t _u64;
	};
    struct timeval _timestamp;

};
