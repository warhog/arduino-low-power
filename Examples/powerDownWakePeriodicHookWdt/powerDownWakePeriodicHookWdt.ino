// **** INCLUDES *****
#include "LowPower.h"

void test() {
  Serial.println("hello watchdog");
  Serial.flush();
}

void setup()
{
    Serial.begin(38400);
    LowPower.addWdtHook(test);
}

void loop() 
{
    // Enter power down state for 8 s with ADC and BOD module disabled
    LowPower.powerDown(SLEEP_1S, ADC_OFF, BOD_OFF);  

}
