/*MECANUM OMNIDRIVE
 * This file contains various functions for moving a mecanum-wheeled robot,
 * specific quirks for the robot used in MECHENG 706 are included, as that
 * is the primary target hardware for this code.
 *
 * Note: as of version 2.0.0, all functions except void motion(<args>) are
 * obsolete.  Please do not use the other functions, they are very buggy.
 * Note:  Since version 2.1, all other functions have been removed.
 */

 /*
  * Author:
  *   James Donaldson, jdon759, 763530765.
  * Version: 2.1.3
  * Date of latest version:
  *   2021-03-17
  */
#ifndef MECANUM_OMNIDRIVE_H
#include <arduino.h>
#include <math.h>
#include <Servo.h>
#include "mecanum_omnidrive.h"

//Default motor control pins
const byte left_front = 46;
const byte left_rear = 47;
const byte right_rear = 50;
const byte right_front = 51;

Servo left_front_motor;  // create servo object to control Vex Motor Controller 29
Servo left_rear_motor;  // create servo object to control Vex Motor Controller 29
Servo right_rear_motor;  // create servo object to control Vex Motor Controller 29
Servo right_front_motor;  // create servo object to control Vex Motor Controller 29

//Please note that no control logic is provided in these functions

float fwd;      	//Forward component
float str;    	  	//strafe component
float rot;      	//rotation component
float norm;     	//for normalising
float lf, lr, rf, rr; 	//motor power values
float trans_percent;

/*====================================================*/


// mecanum_omnidrive() moves the robot in almsot any way you wish, including rotation.
// Do note that this is only an open loop function.  It is reccomended to
// incorporate this function into a closed loop system for best performance.

void mecanum_omnidrive(int power, float heading, ROTATION rot_direction, float rot_percent){

  //Moves wheels of robot in roughly the correct proportions to achieve
  // holonomic motion, EXCEPT for rotation while driving straight.
  //  INPUTS:
  //    power:   an integer between 0 and 500 which dictates the speed of motion
  //             NOTE:  it is reccomended to keep this value at 400 or below.
  //    heading: an float in degrees which tells the robot which way to drive
  //    rot_direction: a value of type ROTATION.  Can be either CW, NONE, or CCW
  //    rot_percent: a value between 0 and 100 which determines the proportion
  //                 of rotative to translative motion
  //  OUTPUTS:
  //    none

  //version 1.3

  // determine percent of performance dedicated to each of moving and rotating
  rot_percent /= 100.0;
  trans_percent = 1 - rot_percent;

  //assign values to the un-normalised componenets
  fwd = (float)power * cos((heading * PI)/180) * trans_percent;
  str = (float)power * sin((heading * PI)/180) * trans_percent;
  rot = (float)power * rot_percent * rot_direction;

  // if components are 0, don't divide by them!
  if((fwd==0)&&(str==0)&&(rot==0)){
    lf = 0;
    lr = 0;
    rf = 0;
    rr = 0;
  } else {
    //normalise component levels
    norm = abs(fwd) + abs(str) + abs(rot);
    lf = (fwd+str-rot)/norm;
    lr = (fwd-str-rot)/norm;
    rf = (fwd-str+rot)/norm;
    rr = (fwd+str+rot)/norm;

    //turn normalised power levels into proper power levels
    lf *= power;
    lr *= power;
    rf *= power;
    rr *= power;
  }


  //set motor power values
  left_front_motor.writeMicroseconds(1500 + (int)lf);
  left_rear_motor.writeMicroseconds(1500 + (int)lr);
  right_front_motor.writeMicroseconds(1500 - (int)(rf));
  right_rear_motor.writeMicroseconds(1500 - (int)rr);

  //done ;)
  return;
}

void disable_motors()
{
  left_front_motor.detach();  // detach the servo on pin left_front to turn Vex Motor Controller 29 Off
  left_rear_motor.detach();  // detach the servo on pin left_rear to turn Vex Motor Controller 29 Off
  right_rear_motor.detach();  // detach the servo on pin right_rear to turn Vex Motor Controller 29 Off
  right_front_motor.detach();  // detach the servo on pin right_front to turn Vex Motor Controller 29 Off

  pinMode(left_front, INPUT);
  pinMode(left_rear, INPUT);
  pinMode(right_rear, INPUT);
  pinMode(right_front, INPUT);
}

void enable_motors()
{
  left_front_motor.attach(left_front);  // attaches the servo on pin left_front to turn Vex Motor Controller 29 On
  left_rear_motor.attach(left_rear);  // attaches the servo on pin left_rear to turn Vex Motor Controller 29 On
  right_rear_motor.attach(right_rear);  // attaches the servo on pin right_rear to turn Vex Motor Controller 29 On
  right_front_motor.attach(right_front);  // attaches the servo on pin right_front to turn Vex Motor Controller 29 On
}

void stop_drive() //Stop
{
  left_front_motor.writeMicroseconds(1500);
  left_rear_motor.writeMicroseconds(1500);
  right_rear_motor.writeMicroseconds(1500);
  right_front_motor.writeMicroseconds(1500);
}

void brake(int power, float heading, ROTATION rot_direction, float rot_percent) // 
{
    mecanum_omnidrive(power, heading-180, rot_direction,  rot_percent);
    delay(20);
    stop_drive();
    delay(500);
}
#endif
