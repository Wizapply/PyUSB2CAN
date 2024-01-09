import pyusb2can
import time

if __name__ == '__main__':
    
    can_dev = pyusb2can.PyUSB2CAN()
    #print(can_dev.devices)
    if not can_dev.open(0,500000,False,False):
        print('Open Error!')
        exit()
        
    #test
    canMes = pyusb2can.CanMessage()
    canMes.id = 0x777
    canMes.data = bytearray([0xFF])
    canMes.errorframe = True
    while True:
        #can_dev.send_message(canMes)
        res = can_dev.read_message(1000)
        if not res is None: print(res)
        time.sleep(0.1)