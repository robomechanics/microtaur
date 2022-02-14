#include "Arduino.h"
#include "Arduino_Microtaur_Library.hpp"

Leg::Leg(int leg_number, float motor_zeros[8]){
  //I would like to at some point put the motor control objects inside the leg object, but when I tried that
  //I found that none of the motor control object functions worked as intended
  leg_num = leg_number;
  if(leg_num == 0){
    mot_1_zero = motor_zeros[0];
    mot_2_zero = motor_zeros[1];
  }else if(leg_num == 1){
    mot_1_zero = motor_zeros[2];
    mot_2_zero = motor_zeros[3];
  }else if(leg_num == 2){
    mot_1_zero = motor_zeros[4];
    mot_2_zero = motor_zeros[5];
  }else if(leg_num == 3){
    mot_1_zero = motor_zeros[6];
    mot_2_zero = motor_zeros[7];
  }

  obs_ang_1 = 0.0;
  obs_ang_2 = 0.0;
  obsX = 0;
  obsY = 0;

  ang_1 = 3*PI/4;
  ang_2 = -3*PI/4;
}

void Leg::setOpenLoop(float newThrottle){
  throttle = newThrottle;
  openLoop = 4;
}

void Leg::setXY(float new_X, float new_Y){
  if(selfX == new_X && selfY == new_Y){
    return;
  }
  selfX = new_X;
  selfY = new_Y;
  leg_ext = sqrt(selfX*selfX + selfY*selfY);
  if(leg_ext >= 0.12){
    leg_ext = 0.12;
  }
  if(leg_ext <= 0.05){
    leg_ext = 0.05;
  }
  leg_ang = atan(selfX/(-selfY));
  if(leg_num == 2 || leg_num == 3){
    leg_ang = -1*leg_ang;
  }
  float delta = acos((L1*L1 + L2*L2 - leg_ext*leg_ext)/(2*L2*L1));
  ang_1 = leg_ang - delta;
  ang_2 = leg_ang + delta;
  updateAng = 4;
}

void Leg::setExtension(float extension){
  if(extension == leg_ext){
    return;
  }
  if(extension >= 0.12){
    extension = 0.12;
  }
  if(extension <= 0.05){
    extension = 0.05;
  }
  leg_ext = extension;
  float delta = acos((L1*L1 + L2*L2 - leg_ext*leg_ext)/(2*L2*L1));
  ang_1 = leg_ang - delta;
  ang_2 = leg_ang + delta;
  updateAng = 4;
}

void Leg::setAngle(float angle){
  if(angle == leg_ang){
    return;
  }
  //TODO safeguard the leg angle numbers so that nobody can break anything.
  if(leg_num == 2 || leg_num == 3){
    angle = -1*angle;
  }
  leg_ang = angle;
  float delta = acos((L1*L1 + L2*L2 - leg_ext*leg_ext)/(2*L2*L1));
  ang_1 = leg_ang - delta;
  ang_2 = leg_ang + delta;
  updateAng = 4;
}

void Leg::setPD(float new_P, float new_D){
  if(new_P == P && new_D == D){
    return;
  }
  P = new_P;
  D = new_D;
  updatePD = 4;
}

float Leg::getAng(){
  return obs_leg_ang;
}

float Leg::getExt(){
  return obs_leg_ext;
}

void Leg::Update(float angle1, float angle2){
  if(angle1 != 0){
    obs_ang_1 = (-1*angle1)-mot_1_zero;
  }
  if(angle2 != 0){
    obs_ang_2 = angle2-mot_2_zero;
  }
  
  obs_leg_ang = (obs_ang_1 + obs_ang_2)/2;
  obs_leg_ext = sqrt(L1*L1 + L2*L2 - 2*L1*L2*cos(abs(obs_ang_2 - obs_ang_1)/2));

  obsX = obs_leg_ext*sin(obs_leg_ang);
  obsY = -1*obs_leg_ext*cos(obs_leg_ang);
}
