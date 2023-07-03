#include <MD_MAX72xx.h>
#include <SPI.h>
#include <Firmata.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 1
#define CLK_PIN 13
#define DIN_PIN 11
#define CS_PIN 7

// 13 - grn
// 11 - ylw
// 7 - red

byte previousPIN[TOTAL_PORTS];  // PIN means PORT for input
byte previousPORT[TOTAL_PORTS];

static int xPointer;
static int yPointer;

MD_MAX72XX _display = MD_MAX72XX(HARDWARE_TYPE, DIN_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

void outputPort(byte portNumber, byte portValue)
{
  // only send the data when it changes, otherwise you get too many messages!
  if (previousPIN[portNumber] != portValue) {
    Firmata.sendDigitalPort(portNumber, portValue);
    previousPIN[portNumber] = portValue;
  }
}

void setPinModeCallback(byte pin, int mode) {
  if (IS_PIN_DIGITAL(pin)) {
    pinMode(PIN_TO_DIGITAL(pin), mode);
  }
}

void digitalWriteCallback(byte port, int value)
{
  byte i;
  byte currentPinValue, previousPinValue;

  if (port < TOTAL_PORTS && value != previousPORT[port]) {
    for (i = 0; i < 8; i++) {
      currentPinValue = (byte) value & (1 << i);
      previousPinValue = previousPORT[port] & (1 << i);
      if(currentPinValue == 1){ // pin 8? wtf
        incPixel(true);
      }
      if(currentPinValue == 2){ // pin 9
        incPixel(false);
      }
    }
    previousPORT[port] = value;
  }
}

void incPixel(bool on) {
  _display.setPoint(xPointer, yPointer, on);
  if (xPointer <= 8){
    xPointer++;
  }
  if (xPointer == 8){
    xPointer = 0;
    yPointer++;
  }
}

void setup()
{
  Firmata.setFirmwareVersion(FIRMATA_FIRMWARE_MAJOR_VERSION, FIRMATA_FIRMWARE_MINOR_VERSION);
  Firmata.attach(DIGITAL_MESSAGE, digitalWriteCallback);
  Firmata.attach(SET_PIN_MODE, setPinModeCallback);
  Firmata.begin(57600);
  _display.begin();
}

void loop()
{
  byte i;

  for (i = 0; i < TOTAL_PORTS; i++) {
    outputPort(i, readPort(i, 0xff));
  }

  while (Firmata.available()) {
    Firmata.processInput();
  }
}