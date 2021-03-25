// Edit Cleaning up the code for project 1
// Date 25/03/21

// header files
#include <Servo.h>
#include "mecanum_omnidrive.h"
#include "light_flash.h" 

//
  ///light_flash_count(5);
  //light_flash_morse_code("x-x-x");

// Constant Variables


// Variables

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(13,OUTPUT);
  enable_motors();
  
}
void open_loop() {
  // FLASH START (READY, ATTENTION, 3, 2, 1)
  light_flash_morse_code("--xxx");
  
  // Forwards 1
  mecanum_omnidrive(500, 0, NONE, 0.0);
  delay(5000);
  brake(500, 0, NONE, 0.0);
  
  // Turn 1
  mecanum_omnidrive(500, 0, CW, 100.0);
  delay(600);
  stop_drive();
  
  //Forwards 2
  mecanum_omnidrive(500, 0, NONE, 0.0);
  delay(2250);
  brake(500, 0, NONE, 0.0);

  // Turn 2
  mecanum_omnidrive(500, 0, CW, 100.0);
  delay(800);
  stop_drive();
  
  // Forwards 3
  mecanum_omnidrive(500, 0, NONE, 0.0);
  delay(5000);
  brake(500, 0, NONE, 0.0);

  // Turn 3
  mecanum_omnidrive(500, 0, CW, 100.0);
  delay(600);
  stop_drive();
  
  // Forwards 4
  mecanum_omnidrive(500, 0, NONE, 0.0);
  delay(2400);
  brake(500, 0, NONE, 0.0);

  //FLASH END 
  light_flash_morse_code("xxx--");
  }
  
void loop() {
  open_loop();
  delay(5000);
}
