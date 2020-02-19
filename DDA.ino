#include <TDK_Diamond_Seeds.h>

float dValue;                 // dynamic sensor value
float sValue;                 // static sensor value
float alarmThreshold = 10;    // adjust to change alarm sensitivty
bool triggered = false;       // becomes true when diary removed
int p;
///////////////////////////////////////////////////////////////////////////////
void setup()
{
  // Initialize integral library.
  TDSs.begin();

  p=0;
  TDSs.setPixelColor(p,0,0,200);
  p=1;
  TDSs.setPixelColor(p,0,0,200);
  p=2;
  TDSs.setPixelColor(p,0,0,200);
  p=3;
  TDSs.setPixelColor(p,0,0,200);
  p=4;
  TDSs.setPixelColor(p,0,0,200);
  p=5;
  TDSs.setPixelColor(p,0,0,200);
  p=6;
  TDSs.setPixelColor(p,0,0,200);
  p=7;
  TDSs.setPixelColor(p,0,0,200);
  p=8;
  TDSs.setPixelColor(p,0,0,200);
  p=9;
  TDSs.setPixelColor(p,0,0,200);
  p=10;
  TDSs.setPixelColor(p,0,0,200);
  p=11;
  TDSs.setPixelColor(p,0,0,200);

//for (p=0; p<12; p=p+1) {
//  TDSs.setPixelColor(p,0,0,200);
//}

  // Wait for button press.
  while ( (TDSs.leftButton()  == false) && 
          (TDSs.rightButton() == false) ) {
            // Do nothing.
  }

  for (p=0; p<12; p=p+1) {
      TDSs.setPixelColor(p,0,0,0);
      delay(100);      
  }

  // Compute sensor value as average of 5 readings.
  sValue = 0;
  for (p=0; p<5; p=p+1) {
    dValue = TDSs.Tesla();
    sValue = sValue + dValue;
  }
  sValue = sValue / 5;
  
/*  sValue = 0; 

  p=0;
  dValue = TDSs.Tesla();
  sValue = sValue + dValue;
  p=1;
  dValue = TDSs.Tesla();
  sValue = sValue + dValue;
  p=2;
  dValue = TDSs.Tesla();
  sValue = sValue + dValue;
  p=3;
  dValue = TDSs.Tesla();
  sValue = sValue + dValue;
  p=4;
  dValue = TDSs.Tesla();
  sValue = sValue + dValue;

  sValue = sValue / 5;
*/

  delay(1000);
}

///////////////////////////////////////////////////////////////////////////////
void loop()
{

    // Get current sensor value.
    dValue = TDSs.Tesla();
    
    Serial.println(dValue);
    
    // Check sensor value to determine if alarm should be triggered.
    if (dValue > sValue + alarmThreshold) {
      // Turn on all the NeoPixels.
      for (p=0; p<12; p=p+1) {
        TDSs.setPixelColor(p,0,0,150);
      }
    }
    
    if (dValue < sValue + alarmThreshold) {
      for (p=0; p<12; p=p+1) {
        TDSs.setPixelColor(p,0,0,0);
      }
    }    
}
