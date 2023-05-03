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

//Deadzone
const int deadzone = 20;  // Anything between -20 and 20 is stop

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

void Driveold() {
  double angle = map(PS4Controller[RStickX], 128, -128, -10000.0, 10000.0);
  double linear = map(PS4Controller[LStickY], -128, 128, -4000.0, 4000.0);

  if (PS4Controller[LStickY] < 15 && PS4Controller[LStickY] > -15) {
    linear = 0;
  }
  if (PS4Controller[RStickX] < 15 && PS4Controller[RStickX] > -15) {
    angle = 0;
  }


  double speed_wish_right = (angle * 0.3) / 2 + linear;
  double speed_wish_left = linear * 2 - speed_wish_right;

  int leftTarget = map(speed_wish_left, -3500, 3500, 1448, 2648);
  int rightTarget = map(speed_wish_right, -3500, 3500, 1448, 2648);

  Serial.print (speed_wish_left);
  Serial.print(" ");
  Serial.print (speed_wish_right);
  Serial.println();

  leftJrk.setTarget(leftTarget);
  rightJrk.setTarget(rightTarget);

}
int pulseToPWM(int pulse) {

 
    pulse = map(pulse, -128, 128, -500, 500);
    pulse = constrain(pulse, -255, 255);
 

  // Anything in deadzone should stop the motor  
  if ( abs(pulse) <= deadzone ) {
    pulse = 0;
  }

  return pulse;
}
void Drive(int speed_a, int speed_b) {

speed_a = map(speed_a, -255, 255, 1448, 2648);
speed_b = map(speed_b, -255, 255, 1448, 2648);

  // Limit speed between 1448 and 2648
  speed_a = constrain(speed_a, 1448, 2648);
  speed_b = constrain(speed_b, 1448, 2648);

  // Set speed
  leftJrk.setTarget(speed_a);
  rightJrk.setTarget(speed_b);
}

void loop() {
  Receive();
int y = pulseToPWM(PS4Controller[LStickY]);
int x = pulseToPWM(PS4Controller[RStickX]);
    // Mix for arcade drive
  int left = y + x;
  int right = y - x;
Serial.print (left);
  Serial.print(" ");
  Serial.print (right);
  Serial.println();
  // Drive motor
  Drive(left, right);

}
