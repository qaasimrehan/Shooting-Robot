#include <PS4Controller.h>

void setup() {
  Serial.begin(115200);
   PS4.begin("dc:a2:66:ac:39:22");//Wifi
  Serial.println("Ready.");
}

void loop() {
  // Below has all accessible outputs from the controller
  if (PS4.isConnected()) {
       Serial.printf("%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", PS4.LStickX(), PS4.LStickY(), PS4.RStickX(), PS4.RStickY(), PS4.R2(), PS4.L2(), PS4.L1(), PS4.R1(), PS4.Square(), PS4.Cross(), PS4.Circle(), PS4.Triangle(), PS4.Right(), PS4.Down(), PS4.Up(), PS4.Left(), PS4.UpRight(), PS4.DownRight(), PS4.UpLeft(), PS4.DownLeft(), PS4.Share(), PS4.Options(), PS4.L3(), PS4.R3(), PS4.Touchpad(), PS4.PSButton(), PS4.Charging(), PS4.Audio(), PS4.Mic(), PS4.Battery());//deadzone -10,10

  }
  delay(50);
}
