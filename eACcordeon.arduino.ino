/*
 * Подключен модуль Bluetooth H-06 UART PIN0(TX), PIN1(RX)
 * https://lesson.iarduino.ru/page/bluetooth-modul-hc-06-podklyuchenie-k-arduino-upravlenie-ustroystvami-s-telefona
 * http://diyavr.ru/index.php/stati/item/12-bluetooth-modul-hc-06-i-mikrokontrollery
 *  
 * Подключен модуль датчика давления BMP-180 по I2C PIN21(SCL), PIN20(SDA)
 *  
 */

#include "config.h"

#include "keyboard.h"
#include "pressure.h"
#include "serialMidi.h"

void setup() {
  serialMidi_Init();
  keyboard_Init();
  pressure_Init();
}

//#define TEST_01
static bool RunTests();

void loop() {
  if (RunTests())
    return;
  
  pressure_Loop();
  keyboard_Loop();
  serialMidi_Loop();

}



//#define TEST_01
static bool RunTests()
{
  
#ifdef TEST_01
  for (int c=0; c<COLS; c++)
  {
    byte cPinId = colPins[c];
    digitalWrite(cPinId, HIGH); 

    Serial.print(" [");      
    Serial.print(cPinId);
    Serial.print("] ");      
    
    for (int r=0; r<ROWS; r++)
    {
      Serial.print(digitalRead(rowPins[r]));
      Serial.print(" ");      
    }
    digitalWrite(cPinId, LOW); 
  }
  
  Serial.println();
  delay(250);
  
  //Serial.println("pause");
  //pinMode(2, INPUT); 
  //delay(500);
  return true;
#endif

  return false;
}
