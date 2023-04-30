// This example shows how to control the Jrk G2 over I2C by
// sending Set Target commands.
//
// The Jrk's input mode must be set to "Serial/I2C/USB".  The
// Jrk's device number must be set to its default value of 11.
//
// Please see https://github.com/pololu/jrk-g2-arduino for
// details on how to make the connections between the Arduino and
// the Jrk G2.

#include <JrkG2.h>

JrkG2I2C jrk;
JrkG2I2C leftJrk(12);
JrkG2I2C rightJrk(11);
void setup()
{
  // Set up I2C.
  Wire.begin();
}

void loop()
{
  delay(1000);
  leftJrk.setTarget(2348);
  rightJrk.setTarget(2348);
  delay(1000);
  leftJrk.setTarget(1748);
  rightJrk.setTarget(1748);
}
