#include "keyboard.h"


//define the cymbols on the buttons of the keypads
uint64_t hexaKeys[COLS][ROWS] = {   
  
  {O3_G, O3_A, O3_G_DIEZ, O3_B, O3_A_DIEZ, O4_C, O4_C_DIEZ},  
  {O4_D, O4_D_DIEZ, O4_E, O4_F_DIEZ, O4_F, O4_G_DIEZ, O4_G},
  {O4_A_DIEZ, O4_A, O4_B, O5_C, O5_D, O5_C_DIEZ, O5_E},
  {O5_D_DIEZ, O5_F, O5_F_DIEZ, O5_G, O5_G_DIEZ, O5_A, O5_A_DIEZ},
  {O5_B, O6_C, O6_D, O6_C_DIEZ, O6_E, O6_D_DIEZ, 0},
//  {O3_G, O3_G_DIEZ, O3_A, O3_A_DIEZ, O3_B, O4_C, O4_C_DIEZ},
//  {O4_D, O4_D_DIEZ, O4_E, O4_F, O4_F_DIEZ, O4_G, O4_G_DIEZ},
//  {O4_A, O4_A_DIEZ, O4_B, O5_C, O5_C_DIEZ, O5_D, O5_D_DIEZ},
//  {O5_E, O5_F, O5_F_DIEZ, O5_G, O5_G_DIEZ, O5_A, O5_A_DIEZ},
//  {O5_B, O6_C, O6_C_DIEZ, O6_D, O6_D_DIEZ, O6_E, 0},
};

byte rowPins[ROWS] = {7,8,9,10,11,12,13}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {2,3,4,5,6}; //connect to the column pinouts of the keypad






void onKeyDown(int col, int row)
{
  uint64_t keyCode = hexaKeys[col][row];
  packet.rightKeys |= keyCode;
}



void keyboard_Init()
{
  // Инициализация клавиатуры
  for(int r=0; r<ROWS; r++)
    pinMode(rowPins[r], INPUT_PULLUP); 

  for(int c=0; c<COLS; c++)
  {
    byte cPinId = colPins[c];
    pinMode(cPinId, OUTPUT);
    digitalWrite(cPinId, LOW); 
  }
}

void keyboard_Loop()
{
  packet.rightKeys = 0;
  packet.leftKeys = 0;
    
  for (int c=0; c<COLS; c++)
  {
    byte cPinId = colPins[c];
    digitalWrite(cPinId, HIGH); 
    delay(1);
    for (int r=0; r<ROWS; r++)
    {
      if (digitalRead(rowPins[r]) == LOW)
        onKeyDown(c, r);
    }

    digitalWrite(cPinId, LOW);
    //pinMode(cPinId, INPUT); 
  }
}
