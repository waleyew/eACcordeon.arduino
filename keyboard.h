#ifndef keyboard_h
#define keyboard_h

#include "Arduino.h"
#include "serialMidi.h"

//=======================================================================
// Настройка клавиатуры
//=======================================================================
  
const uint8_t bass_pins[] = {
   A0,
   A1,
   A2,
   A3,
   A4,
   A5,
   A6,
   A7,
   A8,
   A9,
   A10,
   A11,
   A12,
   A13,
   A14,
   A15,
   32,
   33,
   34,
   35,
   36,
   37,
   38,
   39 
};

  const uint64_t O3_F = 1ULL << 23;       // ФА малой октавы (Первая нота полного аккордеона и 7/8)
  const uint64_t O3_F_DIEZ = 1ULL << 24;  // ФА ДИЕЗ малой октавы
  const uint64_t O3_G = 1ULL << 25;       // Соль малой октавы (первая нота у аккордеона 3/4)
  const uint64_t O3_G_DIEZ = 1ULL << 26;
  const uint64_t O3_A = 1ULL << 27;
  const uint64_t O3_A_DIEZ = 1ULL << 28;
  const uint64_t O3_B = 1ULL << 29;

  const uint64_t O4_C = 1ULL << 30;
  const uint64_t O4_C_DIEZ = 1ULL << 31;
  const uint64_t O4_D = 1ULL << 32;
  const uint64_t O4_D_DIEZ = 1ULL << 33;
  const uint64_t O4_E = 1ULL << 34;
  const uint64_t O4_F = 1ULL << 35;
  const uint64_t O4_F_DIEZ = 1ULL << 36;
  const uint64_t O4_G = 1ULL << 37;
  const uint64_t O4_G_DIEZ = 1ULL << 38;
  const uint64_t O4_A = 1ULL << 39;
  const uint64_t O4_A_DIEZ = 1ULL << 40;
  const uint64_t O4_B = 1ULL << 41;

  const uint64_t O5_C = 1ULL << 42;
  const uint64_t O5_C_DIEZ = 1ULL << 43;
  const uint64_t O5_D = 1ULL << 44;
  const uint64_t O5_D_DIEZ = 1ULL << 45;
  const uint64_t O5_E = 1ULL << 46;
  const uint64_t O5_F = 1ULL << 47;
  const uint64_t O5_F_DIEZ = 1ULL << 48;
  const uint64_t O5_G = 1ULL << 49;
  const uint64_t O5_G_DIEZ = 1ULL << 50;
  const uint64_t O5_A = 1ULL << 51ULL;
  const uint64_t O5_A_DIEZ = 1ULL << 52;
  const uint64_t O5_B = 1ULL << 53;

  const uint64_t O6_C = 1ULL << 54;
  const uint64_t O6_C_DIEZ = 1ULL << 55;
  const uint64_t O6_D = 1ULL << 56;
  const uint64_t O6_D_DIEZ = 1ULL << 57;
  const uint64_t O6_E = 1ULL << 58;           // Ми третьей октавы (последняя нота аккордеона 3/4)
  const uint64_t O6_F = 1ULL << 59;
  const uint64_t O6_F_DIEZ = 1ULL << 60;
  const uint64_t O6_G = 1ULL << 61;
  const uint64_t O6_G_DIEZ = 1ULL << 62;
  const uint64_t O6_A = 1ULL << 63;          // Ля третьей октавы (последняя нота полного аккордеона)

//define your keyboard ------------------------------------
#define ROWS 7 //four rows
#define COLS 5 //four columns

//=======================================================================
// Функции и определения для клавиатуры
//=======================================================================



#define rightKeyDown(key) (packet.rightKeys |= key)
#define rightKeyUp(key)   (packet.rightKeys &= ~key)


void keyboard_Init();

void keyboard_Loop();

#endif
