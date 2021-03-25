//Header file for arduino

enum ROTATION {
  CW = -1,
  NONE = 0,
  CCW = 1
};

void mecanum_omnidrive(int power, float heading, ROTATION rot_direction, float rot_percent);
void disable_motors();
void enable_motors();
void stop_drive();
void brake(int power, float heading, ROTATION rot_direction, float rot_percent);
