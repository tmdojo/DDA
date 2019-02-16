#include <TDK_Diamond_Seeds.h>

uint16_t dValue;           // dynamic sensor value
uint16_t sValue;         // static sensor value
uint16_t alarmThreshold = 20;  // adjust to change alarm sensitivty
bool triggered = false;        // becomes true when diary removed
int p;
///////////////////////////////////////////////////////////////////////////////
void setup()
{
  // Initialize integral library.
  TDSs.begin();

  for (p=0; p<12; p=p+1) {
      TDSs.setPixelColor(p,0,0,200);
  }

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
