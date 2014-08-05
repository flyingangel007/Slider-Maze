#include <CapacitiveSensor.h>

/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10 megohm between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50 kilohm - 50 megohm. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 * Best results are obtained if sensor foil and wire is covered with an insulator such as paper or plastic sheet
 */


CapacitiveSensor   cs = CapacitiveSensor(10,2);        // 1 megohm resistor between pins 4 & 2, pin 2 is sensor pin

void setup()                    
{

//   cs.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   Serial.begin(9600);

}

void loop() {

  Serial.println(touchDetect());
  
  delay(100);                             // arbitrary delay to limit data to serial port 
}

boolean touchDetect() {
  
  long total = cs.capacitiveSensor(30);
Serial.print(total);                  // print sensor output
Serial.print("  ");
  if(total > 500) {
    return true;
  }
  else {
    return false;
  }
}

