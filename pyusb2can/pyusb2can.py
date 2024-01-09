# -*- coding: utf-8 -*-
# Import
from ctypes import *
import time, platform, os
import struct

# define
# CanMessage Data Packet
class CanMessage(Structure):  
    def __init__(self):  
        self.id = 0
        self.data = bytearray(0)
        
        self.extID = False
        self.rtr = False
        self.errorframe = False
    def __str__(self):
        return 'id:0x{0:X}, dlc:{1:X}, data:{2}, extId:{3}, rtr:{4}'.format(self.id,len(self.data),self.data,self.extID,self.rtr)

# Main Class
class PyUSB2CAN():

    _u2clib = None

    def __init__(self, verbose:bool=False):
        libloadpath = os.path.dirname(__file__)
        if platform.system() == 'Windows':
            if platform.architecture()[0] == '64bit':
                libloadpath += '\\pyusb2can.dll'
            else:
                libloadpath += '\\pyusb2can32.dll'
        else:
            print("WINDOWS OS ONLY.")
            return
                
        if PyUSB2CAN._u2clib == None:
            PyUSB2CAN._u2clib = cdll.LoadLibrary(libloadpath)

            PyUSB2CAN._u2clib.u2cOpen.restype = c_void_p
            PyUSB2CAN._u2clib.u2cOpen.argtypes = [c_int, c_int, c_bool, c_bool]

            PyUSB2CAN._u2clib.u2cClose.restype = c_bool
            PyUSB2CAN._u2clib.u2cClose.argtypes = [c_void_p]
        
            PyUSB2CAN._u2clib.u2cReadMessage.restype = c_bool
            PyUSB2CAN._u2clib.u2cReadMessage.argtypes = [c_void_p, c_int, c_void_p, Array[c_ubyte], c_void_p, c_void_p]
        
            PyUSB2CAN._u2clib.u2cSendMessage.argtypes = [c_void_p, c_uint32, Array[c_ubyte], c_int, c_bool]
            PyUSB2CAN._u2clib.u2cSendMessageRTR.argtypes = [c_void_p, c_uint32, c_bool]
            PyUSB2CAN._u2clib.u2cSendMessageError.argtypes = [c_void_p, c_uint32, c_bool]
            
            PyUSB2CAN._u2clib.u2cScanDevicesNum.restype = int
            PyUSB2CAN._u2clib.u2cScanDevicesNum.argtypes = None
        
        self.verbose = verbose
        self._handle = -1

        if self.verbose: print ("LOADED USB2CAN DLL.")
    
    @property
    def devices(self):       
        return PyUSB2CAN._u2clib.u2cScanDevicesNum()
    
    def open(self, device_id, bitrate, fd_mode, listen_mode):
        if self._handle > 0:
            return False
        
        self._handle = PyUSB2CAN._u2clib.u2cOpen(device_id, bitrate, fd_mode, listen_mode)
        if self._handle is None:
            return False
        
        return True
    
    def close(self):
        if self._handle < 0:
            return False
        
        return PyUSB2CAN._u2clib.u2cClose(self._handle)
        
    def read_message(self, timeout_ms) -> CanMessage:
        if self._handle < 0:
            return None
        
        _CAN_BUFLEN = 8
        canid = c_uint32(0)
        databuf = bytearray(_CAN_BUFLEN)
        datalen = c_int(0)
        status = c_int(0)
        data = (c_ubyte * _CAN_BUFLEN).from_buffer(databuf)
        if PyUSB2CAN._u2clib.u2cReadMessage(self._handle,
                                                timeout_ms,
                                                byref(canid),
                                                data,
                                                byref(datalen),
                                                byref(status)) == False:
            return None

        canmes = CanMessage() 
        canmes.id = canid.value
        canmes.rtr = bool(status.value & 0x01)
        canmes.extID = bool(status.value & 0x02)
        canmes.errorframe = bool(status.value & 0x04)
        canmes.data = databuf[:datalen.value]

        return canmes

        
    def send_message(self, value:CanMessage):
        if self._handle < 0:
            return
        if value is None:
            return

        if type(value) is CanMessage:
            if value.errorframe:
                PyUSB2CAN._u2clib.u2cSendMessageError(self._handle, value.id, value.extID)
            elif value.rtr:
                PyUSB2CAN._u2clib.u2cSendMessageRTR(self._handle, value.id, value.extID)
            else:
                if value.data is None:
                    return
                bufdlc = len(value.data)
                buf = (c_ubyte * len(value.data)).from_buffer(value.data)
                PyUSB2CAN._u2clib.u2cSendMessage(self._handle, value.id, buf, bufdlc, value.extID)


#-----------------------------------------------
