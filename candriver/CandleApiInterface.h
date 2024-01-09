#ifndef CANDLEAPIINTERFACE_H
#define CANDLEAPIINTERFACE_H

#include "MeasurementInterface.h"
#include "candle.h"
#include "CandleApiTiming.h"
#include "CanMessage.h"

#include <string>
#include <list>

class CandleApiInterface
{
public:
    enum {
        state_ok,
        state_warning,
        state_passive,
        state_bus_off,
        state_stopped,
        state_unknown
    };

    enum {
        capability_canfd = 0x01,
        capability_listen_only = 0x02,
        capability_triple_sampling = 0x04,
        capability_one_shot = 0x08,
        capability_auto_restart = 0x10,
        capability_config_os = 0x20
    };

public:
    CandleApiInterface(candle_handle handle);
    virtual ~CandleApiInterface();

    std::wstring getName() const;
    std::wstring getDetailsStr() const;

    void applyConfig(const MeasurementInterface &mi);

    unsigned getBitrate();

    uint32_t getCapabilities();
    std::list<CandleApiTiming> getAvailableBitrates();

    void open();
    void close();

    void sendMessage(const CanMessage &msg);
    bool readMessage(CanMessage &msg, unsigned int timeout_ms);

    bool updateStatistics();
    uint32_t getState();
    int getNumRxFrames();
    int getNumRxErrors();
    int getNumTxFrames();
    int getNumTxErrors();
    int getNumRxOverruns();
    int getNumTxDropped();

    std::wstring getPath() const;

    void update(candle_handle dev);

private:

    uint64_t _hostOffsetStart;
    uint32_t _deviceTicksStart;

    candle_handle _handle;
    MeasurementInterface _settings;

    uint64_t _numRx;
    uint64_t _numTx;
    uint64_t _numTxErr;

    std::list<CandleApiTiming> _timings;

    bool setBitTiming(uint32_t bitrate, uint32_t samplePoint);
};

#endif // CANDLEAPIINTERFACE_H
