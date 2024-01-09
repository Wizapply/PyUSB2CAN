#include "CandleApiInterface.h"

CandleApiInterface::CandleApiInterface(candle_handle handle)
  : _hostOffsetStart(0),
    _deviceTicksStart(0),
    _handle(handle),
    _numRx(0),
    _numTx(0),
    _numTxErr(0)
{
    _settings.setBitrate(500000);
    _settings.setSamplePoint(875);
    _settings.setListenOnlyMode(false);

    // sample point: 50.0%
    _timings.push_back(CandleApiTiming(48000000, 10000, 500, 300, 6, 8));
    _timings.push_back(CandleApiTiming(48000000, 20000, 500, 150, 6, 8));
    _timings.push_back(CandleApiTiming(48000000, 50000, 500, 60, 6, 8));
    _timings.push_back(CandleApiTiming(48000000, 83333, 500, 36, 6, 8));
    _timings.push_back(CandleApiTiming(48000000, 100000, 500, 30, 6, 8));
    _timings.push_back(CandleApiTiming(48000000, 125000, 500, 24, 6, 8));
    _timings.push_back(CandleApiTiming(48000000, 250000, 500, 12, 6, 8));
    _timings.push_back(CandleApiTiming(48000000, 500000, 500, 6, 6, 8));
    _timings.push_back(CandleApiTiming(48000000, 800000, 500, 3, 8, 9));
    _timings.push_back(CandleApiTiming(48000000, 1000000, 500, 3, 6, 8));

    // sample point: 62.5%
    _timings.push_back(CandleApiTiming(48000000, 10000, 625, 300, 8, 6));
    _timings.push_back(CandleApiTiming(48000000, 20000, 625, 150, 8, 6));
    _timings.push_back(CandleApiTiming(48000000, 50000, 625, 60, 8, 6));
    _timings.push_back(CandleApiTiming(48000000, 83333, 625, 36, 8, 6));
    _timings.push_back(CandleApiTiming(48000000, 100000, 625, 30, 8, 6));
    _timings.push_back(CandleApiTiming(48000000, 125000, 625, 24, 8, 6));
    _timings.push_back(CandleApiTiming(48000000, 250000, 625, 12, 8, 6));
    _timings.push_back(CandleApiTiming(48000000, 500000, 625, 6, 8, 6));
    _timings.push_back(CandleApiTiming(48000000, 800000, 600, 4, 7, 6));
    _timings.push_back(CandleApiTiming(48000000, 1000000, 625, 3, 8, 6));

    // sample point: 75.0%
    _timings.push_back(CandleApiTiming(48000000, 10000, 750, 300, 10, 4));
    _timings.push_back(CandleApiTiming(48000000, 20000, 750, 150, 10, 4));
    _timings.push_back(CandleApiTiming(48000000, 50000, 750, 60, 10, 4));
    _timings.push_back(CandleApiTiming(48000000, 83333, 750, 36, 10, 4));
    _timings.push_back(CandleApiTiming(48000000, 100000, 750, 30, 10, 4));
    _timings.push_back(CandleApiTiming(48000000, 125000, 750, 24, 10, 4));
    _timings.push_back(CandleApiTiming(48000000, 250000, 750, 12, 10, 4));
    _timings.push_back(CandleApiTiming(48000000, 500000, 750, 6, 10, 4));
    _timings.push_back(CandleApiTiming(48000000, 800000, 750, 3, 13, 5));
    _timings.push_back(CandleApiTiming(48000000, 1000000, 750, 3, 10, 4));

    // sample point: 87.5%
    _timings.push_back(CandleApiTiming(48000000, 10000, 875, 300, 12, 2));
    _timings.push_back(CandleApiTiming(48000000, 20000, 875, 150, 12, 2));
    _timings.push_back(CandleApiTiming(48000000, 50000, 875, 60, 12, 2));
    _timings.push_back(CandleApiTiming(48000000, 83333, 875, 36, 12, 2));
    _timings.push_back(CandleApiTiming(48000000, 100000, 875, 30, 12, 2));
    _timings.push_back(CandleApiTiming(48000000, 125000, 875, 24, 12, 2));
    _timings.push_back(CandleApiTiming(48000000, 250000, 875, 12, 12, 2));
    _timings.push_back(CandleApiTiming(48000000, 500000, 875, 6, 12, 2));
    _timings.push_back(CandleApiTiming(48000000, 800000, 867, 4, 11, 2));
    _timings.push_back(CandleApiTiming(48000000, 1000000, 875, 3, 12, 2));

    // sample point: 50.0%
    _timings.push_back(CandleApiTiming(16000000, 10000, 520, 64, 11, 12));
    _timings.push_back(CandleApiTiming(16000000, 20000, 500, 50, 6, 8));
    _timings.push_back(CandleApiTiming(16000000, 50000, 500, 20, 6, 8));
    _timings.push_back(CandleApiTiming(16000000, 83333, 500, 12, 6, 8));
    _timings.push_back(CandleApiTiming(16000000, 100000, 500, 10, 6, 8));
    _timings.push_back(CandleApiTiming(16000000, 125000, 500, 8, 6, 8));
    _timings.push_back(CandleApiTiming(16000000, 250000, 500, 4, 6, 8));
    _timings.push_back(CandleApiTiming(16000000, 500000, 500, 2, 6, 8));
    _timings.push_back(CandleApiTiming(16000000, 800000, 500, 1, 8, 10));
    _timings.push_back(CandleApiTiming(16000000, 1000000, 500, 1, 6, 8));

    // sample point: 62.5%
    _timings.push_back(CandleApiTiming(16000000, 10000, 625, 64, 14, 9));
    _timings.push_back(CandleApiTiming(16000000, 20000, 625, 50, 8, 6));
    _timings.push_back(CandleApiTiming(16000000, 50000, 625, 20, 8, 6));
    _timings.push_back(CandleApiTiming(16000000, 83333, 625, 12, 8, 6));
    _timings.push_back(CandleApiTiming(16000000, 100000, 625, 10, 8, 6));
    _timings.push_back(CandleApiTiming(16000000, 125000, 625, 8, 8, 6));
    _timings.push_back(CandleApiTiming(16000000, 250000, 625, 4, 8, 6));
    _timings.push_back(CandleApiTiming(16000000, 500000, 625, 2, 8, 6));
    _timings.push_back(CandleApiTiming(16000000, 800000, 625, 1, 11, 7));
    _timings.push_back(CandleApiTiming(16000000, 1000000, 625, 1, 8, 6));

    // sample point: 75.0%
    _timings.push_back(CandleApiTiming(16000000, 20000, 750, 50, 10, 4));
    _timings.push_back(CandleApiTiming(16000000, 50000, 750, 20, 10, 4));
    _timings.push_back(CandleApiTiming(16000000, 83333, 750, 12, 10, 4));
    _timings.push_back(CandleApiTiming(16000000, 100000, 750, 10, 10, 4));
    _timings.push_back(CandleApiTiming(16000000, 125000, 750, 8, 10, 4));
    _timings.push_back(CandleApiTiming(16000000, 250000, 750, 4, 10, 4));
    _timings.push_back(CandleApiTiming(16000000, 500000, 750, 2, 10, 4));
    _timings.push_back(CandleApiTiming(16000000, 800000, 750, 1, 13, 5));
    _timings.push_back(CandleApiTiming(16000000, 1000000, 750, 1, 10, 4));

    // sample point: 87.5%
    _timings.push_back(CandleApiTiming(16000000, 20000, 875, 50, 12, 2));
    _timings.push_back(CandleApiTiming(16000000, 50000, 875, 20, 12, 2));
    _timings.push_back(CandleApiTiming(16000000, 83333, 875, 12, 12, 2));
    _timings.push_back(CandleApiTiming(16000000, 100000, 875, 10, 12, 2));
    _timings.push_back(CandleApiTiming(16000000, 125000, 875, 8, 12, 2));
    _timings.push_back(CandleApiTiming(16000000, 250000, 875, 4, 12, 2));
    _timings.push_back(CandleApiTiming(16000000, 500000, 875, 2, 12, 2));
    _timings.push_back(CandleApiTiming(16000000, 800000, 900, 2, 7, 1));
    _timings.push_back(CandleApiTiming(16000000, 1000000, 875, 1, 12, 2));
}

CandleApiInterface::~CandleApiInterface()
{
}

std::wstring CandleApiInterface::getName() const
{
    //return L"candle" + QString::number(getId() & 0xFF);
    return L"candleAPI";
}

std::wstring CandleApiInterface::getDetailsStr() const
{
    return std::wstring(getPath());
}

void CandleApiInterface::applyConfig(const MeasurementInterface &mi)
{
    _settings = mi;
}

unsigned CandleApiInterface::getBitrate()
{
    return _settings.bitrate();
}

uint32_t CandleApiInterface::getCapabilities()
{
    candle_capability_t caps;

    if (candle_channel_get_capabilities(_handle, 0, &caps)) {

        uint32_t retval = 0;

        if (caps.feature & CANDLE_MODE_LISTEN_ONLY) {
            retval |= CandleApiInterface::capability_listen_only;
        }

        if (caps.feature & CANDLE_MODE_ONE_SHOT) {
            retval |= CandleApiInterface::capability_one_shot;
        }

        if (caps.feature & CANDLE_MODE_TRIPLE_SAMPLE) {
            retval |= CandleApiInterface::capability_triple_sampling;
        }

        return retval;

    } else {
        return 0;
    }
}

std::list<CandleApiTiming> CandleApiInterface::getAvailableBitrates()
{
    std::list<CandleApiTiming> retval;

    candle_capability_t caps;
    if (candle_channel_get_capabilities(_handle, 0, &caps)) {
        int i = 0;
        for (const CandleApiTiming& t : _timings) {
            if (t.getBaseClk() == caps.fclk_can) {
                retval.push_back(t);
            }
        }
    }

    return retval;
}

bool CandleApiInterface::setBitTiming(uint32_t bitrate, uint32_t samplePoint)
{
    candle_capability_t caps;
    if (!candle_channel_get_capabilities(_handle, 0, &caps)) {
        return false;
    }

    for (const CandleApiTiming& t : _timings) {
        if ( (t.getBaseClk() == caps.fclk_can)
          && (t.getBitrate()==bitrate)
          && (t.getSamplePoint()==samplePoint) )
        {
            candle_bittiming_t timing = t.getTiming();
            return candle_channel_set_timing(_handle, 0, &timing);
        }
    }

    // no valid timing found
    return false;
}

void CandleApiInterface::open()
{
    if (!candle_dev_open(_handle)) {
        // TODO what?
        return;
    }

    if (!setBitTiming(_settings.bitrate(), _settings.samplePoint())) {
        // TODO what?
        return;
    }

    uint32_t flags = 0;
    if (_settings.isListenOnlyMode()) {
        flags |= CANDLE_MODE_LISTEN_ONLY;
    }
    if (_settings.isOneShotMode()) {
        flags |= CANDLE_MODE_ONE_SHOT;
    }
    if (_settings.isTripleSampling()) {
        flags |= CANDLE_MODE_TRIPLE_SAMPLE;
    }

    _numRx = 0;
    _numTx = 0;
    _numTxErr = 0;

    uint32_t t_dev;
    if (candle_dev_get_timestamp_us(_handle, &t_dev)) {
        _hostOffsetStart = 0;
        _deviceTicksStart = t_dev;
    }

    candle_channel_start(_handle, 0, flags);
}

void CandleApiInterface::close()
{
    candle_channel_stop(_handle, 0);
    candle_dev_close(_handle);
}

void CandleApiInterface::sendMessage(const CanMessage &msg)
{
    candle_frame_t frame;

    frame.can_id = msg.getId();
    if (msg.isExtended()) {
        frame.can_id |= CANDLE_ID_EXTENDED;
    }
    if (msg.isRTR()) {
        frame.can_id |= CANDLE_ID_RTR;
    }

    frame.can_dlc = msg.getLength();
    for (int i=0; i<8; i++) {
        frame.data[i] = msg.getByte(i);
    }

    if (candle_frame_send(_handle, 0, &frame)) {
        _numTx++;
    } else {
        _numTxErr++;
    }
}

bool CandleApiInterface::readMessage(CanMessage &msg, unsigned int timeout_ms)
{
    candle_frame_t frame;

    if (candle_frame_read(_handle, &frame, timeout_ms)) {

        if (candle_frame_type(&frame)==CANDLE_FRAMETYPE_RECEIVE) {
            _numRx++;

            msg.setErrorFrame(false);
            msg.setId(candle_frame_id(&frame));
            msg.setExtended(candle_frame_is_extended_id(&frame));
            msg.setRTR(candle_frame_is_rtr(&frame));

            uint8_t dlc = candle_frame_dlc(&frame);
            uint8_t *data = candle_frame_data(&frame);
            msg.setLength(dlc);
            for (int i=0; i<dlc; i++) {
                msg.setByte(i, data[i]);
            }

            uint32_t dev_ts = candle_frame_timestamp_us(&frame) - _deviceTicksStart;
            uint64_t ts_us = _hostOffsetStart + dev_ts;

            uint64_t us_since_start = 0;
            if (us_since_start > 0x180000000) { // device timestamp overflow must have happend at least once
                ts_us += us_since_start & 0xFFFFFFFF00000000;
            }

            msg.setTimestamp(ts_us/1000000, ts_us % 1000000);

            return true;
        }

    }

    return false;
}

bool CandleApiInterface::updateStatistics()
{
    return true;
}

uint32_t CandleApiInterface::getState()
{
    return CandleApiInterface::state_ok;
}

int CandleApiInterface::getNumRxFrames()
{
    return (int)_numRx;
}

int CandleApiInterface::getNumRxErrors()
{
    return 0;
}

int CandleApiInterface::getNumTxFrames()
{
    return (int)_numTx;
}

int CandleApiInterface::getNumTxErrors()
{
    return (int)_numTxErr;
}

int CandleApiInterface::getNumRxOverruns()
{
    return 0;
}

int CandleApiInterface::getNumTxDropped()
{
    return 0;
}

std::wstring CandleApiInterface::getPath() const
{
    return std::wstring(candle_dev_get_path(_handle));
}

void CandleApiInterface::update(candle_handle dev)
{
    candle_dev_free(_handle);
    _handle = dev;
}
