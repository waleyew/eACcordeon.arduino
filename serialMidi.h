#ifndef SerialMidi_h
#define SerialMidi_h

#include "Arduino.h"

//=======================================================================
// Переменные и структуры для передачи данных по COM-порту
//=======================================================================
typedef struct SerialPacket
{
   uint8_t _startbyte;
   uint8_t pressure;
   uint64_t rightKeys;   
   uint64_t leftKeys;
   uint8_t _debugCharSymbol;
   uint8_t _endbyte;
} SerialPacket;

extern SerialPacket packet;

void serialMidi_Init();

void serialMidi_Loop();

#endif
