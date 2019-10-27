#include "serialMidi.h"

SerialPacket packet;

void serialMidi_Init()
{
  // Set MIDI baud rate:
  Serial.begin(57600);

  packet._startbyte = 0x5B;
  packet._endbyte = 0x5E;

  packet.pressure = 127;
  packet.rightKeys = 0;
  packet.leftKeys = 0;
}

void serialMidi_Loop()
{
  Serial.write((uint8_t*)&packet, sizeof(SerialPacket)); 
}
