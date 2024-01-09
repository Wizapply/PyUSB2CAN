// dllmain.cpp

//Includes
#include "windows.h"
#include "candriver/candle.h"
#include "candriver/CandleApiInterface.h"

//Exporter
#define CSHARP_EXPORT __declspec(dllexport)
#define U2C_HANDLE_ERROR (-1)

//to C language
#ifdef __cplusplus
extern "C" {
#endif

//Global variable

//Functions

CSHARP_EXPORT int u2cScanDevicesNum()
{
    candle_list_handle clist;
    uint8_t num_interfaces = 0;
    if(candle_list_scan(&clist))
        candle_list_length(clist, &num_interfaces);
    candle_list_free(clist);

    return num_interfaces;
}

static void _u2cOpenApply(CandleApiInterface* handle, int bitrate, bool CanFDmode, bool ListenMode)
{
    if (handle == nullptr)
        return;

    MeasurementInterface mi;
    mi.setBitrate(bitrate);
    mi.setSamplePoint(875);
    mi.setCanFD(CanFDmode);
    mi.setListenOnlyMode(ListenMode);
    if (CanFDmode) {
        mi.setFdBitrate(bitrate);
        mi.setFdSamplePoint(875);
    }

    handle->applyConfig(mi);
}

CSHARP_EXPORT void* u2cOpen(int deviceNo, int bitrate, bool canfd_mode, bool listen_mode)
{
    candle_list_handle clist;
    uint8_t num_interfaces;
    void* deviceHandle = nullptr;

    if (candle_list_scan(&clist)) {
        candle_list_length(clist, &num_interfaces);
        if (num_interfaces > deviceNo)
        {
            candle_handle dev;
            if (candle_dev_get(clist, deviceNo, &dev)) {
                CandleApiInterface* cai = new CandleApiInterface(dev);
                //config
                _u2cOpenApply(cai, bitrate, canfd_mode, listen_mode);
                cai->open();
                deviceHandle = cai;
            }
        }
    }
    candle_list_free(clist);

    return deviceHandle;	//OK
}

CSHARP_EXPORT bool u2cClose(void* handle)
{
    CandleApiInterface* handle_cai = (CandleApiInterface*)handle;
    if (handle_cai == nullptr)
        return false;

    handle_cai->close();
    delete handle_cai;

    return true;	//OK
}

CSHARP_EXPORT bool u2cReadMessage(void* handle, int timeout_ms, uint32_t* id, byte* data, int* dlc, int* status)
{
    CanMessage res_mes;
    CandleApiInterface* handle_cai = (CandleApiInterface*)handle;
    if (handle_cai == nullptr)
        return false;

    if (handle_cai->readMessage(res_mes, timeout_ms))
    {
        *id = res_mes.getId();
        *dlc = res_mes.getLength();
        *status = res_mes.isRTR() ? 0x01 : 0x00;
        *status |= res_mes.isExtended() ? 0x02 : 0x00;
        *status |= res_mes.isErrorFrame() ? 0x04 : 0x00;

        for (int i = 0; i < res_mes.getLength(); ++i)
            data[i] = res_mes.getByte(i);

        return true;
    }
    return false;
}

CSHARP_EXPORT void u2cSendMessage(void* handle, uint32_t id, byte* data, int dlc, bool extId)
{
    CandleApiInterface* handle_cai = (CandleApiInterface*)handle;
    if (handle_cai == nullptr)
        return;

    CanMessage send_mes;
    if(extId) send_mes.setRawId(id);
    else send_mes.setRawId(id & 0x7FF);
    send_mes.setExtended(extId);
    for (int i = 0; i < dlc; ++i)
        send_mes.setData(data[i]);

    send_mes.setRTR(false);
    send_mes.setErrorFrame(false);

    handle_cai->sendMessage(send_mes);
}

CSHARP_EXPORT void u2cSendMessageRTR(void* handle, uint32_t id, bool extId)
{
    CandleApiInterface* handle_cai = (CandleApiInterface*)handle;
    if (handle_cai == nullptr)
        return;

    CanMessage send_mes;

    if (extId) send_mes.setRawId(id);
    else send_mes.setRawId(id & 0x7FF);
    send_mes.setExtended(extId);
    send_mes.setLength(0);
    send_mes.setRTR(true);
    send_mes.setErrorFrame(false);

    handle_cai->sendMessage(send_mes);
}

CSHARP_EXPORT void u2cSendMessageError(void* handle, uint32_t id, bool extId)
{
    CandleApiInterface* handle_cai = (CandleApiInterface*)handle;
    if (handle_cai == nullptr)
        return;

    CanMessage send_mes;
    if (extId) send_mes.setRawId(id);
    else send_mes.setRawId(id & 0x7FF);
    send_mes.setExtended(extId);
    send_mes.setLength(0);
    send_mes.setRTR(false);
    send_mes.setErrorFrame(true);

    handle_cai->sendMessage(send_mes);
}

#ifdef __cplusplus
}
#endif

//-----------------------------------------------------------
//for DLL
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

