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
      TDSs.setPixelColor(p,0,0,200); // Moderately bright green color.
  }

  // Wait for button press.
  while ( (TDSs.leftButton()  == false) && 
          (TDSs.rightButton() == false) ) {
            // Do nothing.
  }

  for (p=0; p<12; p=p+1) {
      TDSs.setPixelColor(p,0,0,0); // Moderately bright green color.
      delay(100);      
  }
  
  // Compute sensor value as average of 5 readings.
  sValue = 0;
  for (p=0; p<5; p=p+1) {
    dValue = TDSs.Tesla();
    sValue = sValue + dValue;
  }
  sValue = sValue / 5;

  // Beep to indicate ARMED.
  TDSs.playTone(2000,100);
  delay(1000);
}

///////////////////////////////////////////////////////////////////////////////
void loop()
{
  // Check to see if alarm has been triggered.
  if (triggered) {
    // Sound the alarm.
    TDSs.playTone(2000, 500);
    delay(500);
    TDSs.playTone(3000, 500);
    delay(500);
  }
    // Get current sensor value.
    dValue = TDSs.Tesla();
    
    Serial.println(dValue);
    
    // Check sensor value to determine if alarm should be triggered.
    if (dValue > sValue + alarmThreshold) {
      triggered = true;  // Trigger the alarm.
      // Turn on all the NeoPixels.
      for (p=0; p<12; p=p+1) {
        TDSs.setPixelColor(p,0,0,150); // Moderately bright red color.
      }
    }
    
    if (dValue < sValue + alarmThreshold) {
      triggered = false;  // Trigger the alarm.
      for (p=0; p<12; p=p+1) {
        TDSs.setPixelColor(p,0,0,0);
      }
    }
    
}
