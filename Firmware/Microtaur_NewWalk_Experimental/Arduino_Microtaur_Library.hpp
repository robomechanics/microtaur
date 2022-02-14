#include "iq_module_communicaiton.hpp"

#ifndef Arduino_Microtaur_Library_h
#define Arduino_Microtaur_Library_h

#include "Arduino.h"
#include <iq_module_communicaiton.hpp>

void updateLegs();

class Leg{
  public:

  int leg_num;

  float mot_1_zero;
  float mot_2_zero;

  float ang_1;
  float ang_2;
  float obs_ang_1;
  float obs_ang_2;

  float leg_ext;
  float obs_leg_ext;

  float leg_ang;
  float obs_leg_ang;

  float selfX;
  float selfY;
  float obsX;
  float obsY;

  float L1 = 0.040;
  float L2 = 0.080;

  float P = 10.0;
  float D = 0.1;

  int updatePD = 1;
  int updateAng = 1;

  int openLoop = 0;

  float throttle = 0;

  //Creates a new leg object
  Leg(int leg_number, float motor_zeros[8]);
  
  //Sets the leg openloop
  void setOpenLoop(float newThrottle);
  
  //Sets the leg x and y
  void setXY(float X, float Y);

  //Sets the leg extension
  void setExtension(float extension);

  //sets the leg angle
  void setAngle(float angle);

  //sets the motor PD values
  void setPD(float P, float D);

  //returns the leg angle
  float getAng();

  //returns the leg extension
  float getExt();
  
  //Updates some stuff.
  void Update(float angle1, float angle2);
};

#endif
