import pyfirmata
import time

board = pyfirmata.Arduino('COM3')

def procOn():
    time.sleep(0.1)
    board.digital[8].write(1)
    time.sleep(0.1)
    board.digital[8].write(0)
    time.sleep(0.1)

def procOff():
    time.sleep(0.1)
    board.digital[9].write(1)
    time.sleep(0.1)
    board.digital[9].write(0)
    time.sleep(0.1)
