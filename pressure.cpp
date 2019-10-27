#include "pressure.h"

#include "MyAdafruit_BMP085.h"
#include <Wire.h>

Adafruit_BMP085 bmp;



uint32_t P0; // Значение нулевого давления 


void pressure_Init()
{
  if (!bmp.begin(BMP085_ULTRALOWPOWER)) 
  {
    Serial.println("* Could not find a valid BMP085 sensor, check wiring!");
    while (1) 
    {
    }
  }
  P0 = bmp.readPressure();
}

static bool readPressure(int32_t *p);

void pressure_Loop()
{ 
  int32_t pressure;
  if (!readPressure(&pressure))
    return;
  
  
  pressure = pressure / 3;
  if (pressure < 0)
  pressure = -pressure;
  
  if (pressure > 127)
    pressure = 127;

  packet.pressure = pressure;

  //Serial.print(pf);
  //Serial.print(" ");
  //Serial.println(pressure);

}


typedef enum readPressureStage
{
  psReadTemperatureEnter,
  psReadTemperatureWait,
  psReadPressureEnter,
  psReadPressureWait,
} readPressureStage;


readPressureStage stage;
int8_t stageWaitCnt;
int32_t RAW_T;
int32_t RAW_P;



static bool readPressure(int32_t *pressure)
{
  *pressure = bmp.readPressure() - P0;
  return true;

  switch(stage)
  {
    case psReadTemperatureEnter:
      bmp.write8(BMP085_CONTROL, BMP085_READTEMPCMD);
      stage = psReadTemperatureWait;
      stageWaitCnt = 5;
      break;
      
    case psReadTemperatureWait:
      if(stageWaitCnt-- < 0)
      {
        RAW_T = bmp.read16(BMP085_TEMPDATA);
        stage = psReadPressureEnter;
      }    
      else
        delay(1);
      break;
    
    case psReadPressureEnter:

      bmp.write8(BMP085_CONTROL, BMP085_READPRESSURECMD + (bmp.oversampling << 6));

      if (bmp.oversampling == BMP085_ULTRALOWPOWER) 
        stageWaitCnt = 5;
      else if (bmp.oversampling == BMP085_STANDARD) 
        stageWaitCnt = 8;
      else if (bmp.oversampling == BMP085_HIGHRES) 
        stageWaitCnt = 14;
      else 
        stageWaitCnt = 26;
      
      stage = psReadPressureWait;      
      break;
      
    case psReadPressureWait:
      if(stageWaitCnt-- < 0)
      {
        RAW_P = bmp.read16(BMP085_PRESSUREDATA);
        
        RAW_P <<= 8;
        RAW_P |= bmp.read8(BMP085_PRESSUREDATA+2);
        RAW_P >>= (8 - bmp.oversampling);
        
        int32_t B3, B5, B6, X1, X2, X3;
        uint32_t B4, B7;
        B5 = bmp.computeB5(RAW_T);
        
        // do pressure calcs
        B6 = B5 - 4000;
        X1 = ((int32_t)bmp.b2 * ( (B6 * B6)>>12 )) >> 11;
        X2 = ((int32_t)bmp.ac2 * B6) >> 11;
        X3 = X1 + X2;
        B3 = ((((int32_t)bmp.ac1*4 + X3) << bmp.oversampling) + 2) / 4;

        X1 = ((int32_t)bmp.ac3 * B6) >> 13;
        X2 = ((int32_t)bmp.b1 * ((B6 * B6) >> 12)) >> 16;
        X3 = ((X1 + X2) + 2) >> 2;
        B4 = ((uint32_t)bmp.ac4 * (uint32_t)(X3 + 32768)) >> 15;
        B7 = ((uint32_t)RAW_P - B3) * (uint32_t)( 50000UL >> bmp.oversampling );


        if (B7 < 0x80000000) {
          *pressure = (B7 * 2) / B4;
        } else {
          *pressure = (B7 / B4) * 2;
        }
        X1 = (*pressure >> 8) * (*pressure >> 8);
        X1 = (X1 * 3038) >> 16;
        X2 = (-7357 * *pressure) >> 16;

        *pressure = *pressure + ((X1 + X2 + (int32_t)3791)>>4);
       
        *pressure -= P0;
        stage = psReadTemperatureEnter;
        return true;      
      }    
      else
        delay(1);
      
      break;
  }

  return false;
}
