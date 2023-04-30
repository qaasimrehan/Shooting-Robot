int PS4Controller[30];
#include <JrkG2.h>
JrkG2I2C jrk;
JrkG2I2C leftJrk(12);
JrkG2I2C rightJrk(11);

enum PS4Variable {
  LStickX,
  LStickY,
  RStickX,
  RStickY,
  R2,
  L2,
  L1,
  R1,
  Square,
  Cross,
  Circle,
  Triangle,
  Right,
  Down,
  Up,
  Left,
  UpRight,
  DownRight,
  UpLeft,
  DownLeft,
  Share,
  Options,
  L3,
  R3,
  Touchpad,
  PSButton,
  Charging,
  Audio,
  Mic,
  Battery,
  NumPS4Variables
};

void setup() {
  //set up I2C
  Wire.begin();
  
  // Start serial communication at 115200 baud
  Serial.begin(115200);

  // Set up Serial1 to read from external device
  Serial1.begin(115200);
}

void Receive() {
  // Read incoming message from Serial1
  if (Serial1.available() > 0) {
    String message = Serial1.readStringUntil('\n');

    int index = 0;  // initialize the index of the array
    while (message.length() > 0) {
      int pos = message.indexOf(' ');  // find the position of the next space
      if (pos == -1) {  // if there are no more commas in the string
        pos = message.length();  // set the position to the end of the string
      }
      String numString = message.substring(0, pos);  // extract the substring
      int num = numString.toInt();  // convert the substring to an integer
      PS4Controller[index] = num;  // store the integer in the array
      index++;  // increment the index
      message = message.substring(pos + 1);  // remove the parsed substring from the message
    }

    // Print to the serial monitor for testing purposes
   /* Serial.print("Message: ");
    for (int i = 0; i < 30; i++) {
      Serial.print(PS4Controller[i]);
      Serial.print(", ");
    }
    Serial.println();*/
  }
}

void Drive(){
  if (PS4Controller[LStickY] > 20){
  leftJrk.setTarget(2348);
  rightJrk.setTarget(2348);
  }  else if (PS4Controller[LStickY] < -20){
  leftJrk.setTarget(1748);
  rightJrk.setTarget(1748);
  }
  if (PS4Controller[LStickY] > -10 && PS4Controller[LStickY] < 10){
    leftJrk.stopMotor();
    rightJrk.stopMotor();
  }

  
  Serial.println(PS4Controller[LStickY]);
}


void loop() {
Drive();
Receive();
//Serial.println(PS4Controller[RStickX]);
}
