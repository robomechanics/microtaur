#include <iq_module_communicaiton.hpp>

#include <iq_module_communicaiton.hpp>


//MAKE SURE YOU PLUG IN THE BALANCE PORT CORRECTLY OR YOU RISK FRYING THE TEENSY!!
//ENSURE LEGS ARE CLOSE TO DESIRED POSITION OR MOTORS COULD INITIALISE TO THE WRONG ZERO

#include "Arduino_Microtaur_Library.hpp"
#include <PS2X_lib.h>

//Set up the IQ motor communication interface
IqSerial ser = IqSerial(Serial1);
MultiTurnAngleControlClient mot_0(0);
MultiTurnAngleControlClient mot_1(1);
MultiTurnAngleControlClient mot_2(2);
MultiTurnAngleControlClient mot_3(3);
MultiTurnAngleControlClient mot_4(4);
MultiTurnAngleControlClient mot_5(5);
MultiTurnAngleControlClient mot_6(6);
MultiTurnAngleControlClient mot_7(7);
MultiTurnAngleControlClient mot[8] = {mot_0, mot_1, mot_2, mot_3, mot_4, mot_5, mot_6, mot_7};

//IMU stuff
#include <Wire.h>
#define BNO_ADDR       0x28  // I2C address of BNO
#define EULER_ADDR     0x1A  // BNO register for EulerX
#define OPR_MODE       0x3D  // BNO register Operation Mode <3:0>
#define NDOF           0x0C  // desired mode
 
//Zero positions in radians for the motors
float motor_zeros[8] = {-0.42, 1.46, 2.71, 0.82, 3.20, -1.71, 1.52, 1.39};

//Creates leg objects
const int leg_count = 4;
Leg leg_0(0, motor_zeros);
Leg leg_1(1, motor_zeros);
Leg leg_2(2, motor_zeros);
Leg leg_3(3, motor_zeros);
Leg legs[leg_count] = {leg_0, leg_1, leg_2, leg_3};

//Walk parameters
int stepTime = 750;                 //Total time (in ms) to execute one step
float dutyFactor = 0.25;            //Portion of time spent off the ground
float strideLen = 0.065;             //Stride (in M) of the walk
float legLift = 0.02;               //How high off the ground (in M) the feet lift when moving forward
float standExtension = 0.08;        //Body height (in M) during walk
float approachAngle = PI/4;         //Angle at which the feet approach the ground when placing feet on ground
float strideOffset = 0.005;         //How far the front/back legs are offset from centered below motors
float stepTolerance = 0.025;
int   high_step = 0;

long prevTime;
float IMU[3] = {0,0,0};
float batt_voltage = 15.0;

float prevFrontX1 = 0;
float prevY1 = 0;
float prevFrontX2 = 0;
float prevY2 = 0;

float FrontForwardWalkX[4] = {0,0,0,0};
float ForwardWalkY[4] = {0,0,0,0};
float FrontBackwardWalkX[4] = {0,0,0,0};
float BackwardWalkY[4] = {0,0,0,0};
float BackForwardWalkX[4] = {0,0,0,0};
float BackBackwardWalkX[4] = {0,0,0,0};

//These are settings for the controller
#define PS2_DAT        A0      
#define PS2_CMD        A1  
#define PS2_SEL        A2 
#define PS2_CLK        A3
#define pressures      true
#define rumble         true
PS2X ps2x;
int error = 0;
byte vibrate = 0;

//Define the behaviour FSM
enum modes{
  SIT,
  WALK,
  BACK,
  TURNL,
  TURNR,
  PREP,
  HOP,
  WAIT,
  LAND
};
//initial state of the FSM
modes mode = SIT;

void setup() {
  ser.begin(500000);                    //The motors are set to run at 500,000 Baud
  Wire.begin();                         //Starts IMU I2C wire
  Wire.setClock(400000L);               //As fast as the IMU can communicate
  Serial.begin(115200);                 //Sets up USB Serial for debug or input
  Serial5.begin(9600);                  //Sets up bluetooth port for debug or input
  delay(1000);
  bno_write(BNO_ADDR, OPR_MODE, NDOF);  //Sends some setup commands to the BNO

  //This is to make the legs less violent on startup
  for(int i = 0; i < leg_count; ++i){
    legs[i].setPD(10.0, 0.1);
    legs[i].setExtension(0.06);
  }
  legs[0].setAngle(IMU[1]-0.25);
  legs[1].setAngle(IMU[1]+0.2);
  legs[2].setAngle(IMU[1]+0.2);
  legs[3].setAngle(IMU[1]-0.25);
  updateLegs();
  delay(1000);
  generateWalks();
  
  //Controller Stuff
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  
  prevTime = millis();
}

//Code updates at ~50 Hz on an arduino mega
//Code updates at ~100 Hz on a teensy 4.0 (yay!) - the actual math only takes .02 ms to run but the IMU takes .280-1.6 ms to get data and the motors constitute the rest of the time per loop (aprox 8-10 ms)
void loop() {
  updateLegs();                                     //Sends and recieves commands from motors and updates object variables
  
  //Battery protection                                          MAKE SURE YOU PLUG IN THE BALANCE PORT CORRECTLY OR YOU RISK FRYING THE TEENSY!!
  float new_voltage = analogRead(8)/1023.0*18.647;
  if(new_voltage >= 1){                             //In case the balancer is unplugged or being running from power supply
    batt_voltage = batt_voltage*0.99 + new_voltage*0.01; //filtering out the battery drop from jumping
  }
  if(batt_voltage < 12.5 && batt_voltage > 1 && new_voltage < 12.5){      
    for(int i = 0; i < leg_count*2; i++){
      ser.set(mot[i].ctrl_coast_);
    }
    Serial.println("LOW BATTERY");
    while(1);       //Waits with legs disabled to save the battery
  }

  //Read Controller Inputs
  ps2x.read_gamepad(false, vibrate);
  int left_stick_y  = -1*((ps2x.Analog(PSS_LY)-127)*2-1);
  int left_stick_x  = -1*((ps2x.Analog(PSS_LX)-127)*2-1);
  
  //Begin FSM Code
  if(mode == SIT){
    for(int i = 0; i < leg_count; ++i){
      legs[i].setPD(35.0, 0.1);
      //legs[i].setExtension(0.06);
    }
    high_step = 0;
    generateWalks();
    // This code points the legs down while standing and extends legs to stand on slopes at 1/2 the slope angle
    IMU[0] = IMU[0] - 0.02;
    legs[0].setExtension(-0.048*sin(IMU[0])-0.075*sin(IMU[1])+0.07);
    legs[1].setExtension(-0.048*sin(IMU[0])-0.075*sin(-1*IMU[1])+0.07);
    legs[2].setExtension(-0.048*sin(-1*IMU[0])-0.075*sin(-1*IMU[1])+0.07);
    legs[3].setExtension(-0.048*sin(-1*IMU[0])-0.075*sin(IMU[1])+0.07);
    legs[0].setAngle(IMU[1]-0.25);
    legs[1].setAngle(IMU[1]+0.2);
    legs[2].setAngle(IMU[1]+0.2);
    legs[3].setAngle(IMU[1]-0.25);
    if(left_stick_y >= 25 && left_stick_y != 255){
      prevTime = millis();
      mode = WALK;
    }/*
    if(left_stick_y <= -25 && left_stick_y != -255){
      prevTime = millis();
      mode = BACK;
    }
    if(left_stick_x >= 20 && left_stick_x != 255){
      prevTime = millis();
      mode = TURNL;
    }
    if(left_stick_x <= -20 && left_stick_x != -255){
      prevTime = millis();
      mode = TURNR;
    }*/
    if(ps2x.Button(PSB_CIRCLE)){
      prevTime = millis();
      //mode = PREP;
    }
  }else if(mode == WALK){

    long Mils = millis()-prevTime;

    //setting the PID values for all off-ground movements
    for(int i = 0; i < leg_count; ++i){
      legs[i].setPD(35.0, 0.1);
    }

    setWalkPosition(1, Mils);
    Mils = posmod(Mils+(stepTime/4), stepTime);
    setWalkPosition(3, Mils);
    Mils = posmod(Mils+(stepTime/2), stepTime);
    setWalkPosition(0, Mils);
    Mils = posmod(Mils+(3*stepTime/4), stepTime);
    setWalkPosition(2, Mils);
    
    if(millis() - prevTime > stepTime){
      prevTime = millis();
      mode = WALK;
    }
    if(left_stick_y <= 20 && left_stick_y != 255){
      prevTime = millis();
      mode = SIT;
    }
  }else if(mode == PREP){
    for(int i = 0; i < leg_count; ++i){
      legs[i].setPD(35.0, 0.1);
      legs[i].setExtension(0.05);
      legs[i].setAngle(-0.27);
    }
    if(millis() - prevTime > 150){
      prevTime = millis();
      mode = HOP;
    }
  }else if(mode == HOP){
    for(int i = 0; i < leg_count; ++i){
      legs[i].setPD(200.0, 0.1);
      legs[i].setOpenLoop(1.0);
    }
    mode = WAIT;
  }else if(mode == WAIT){
    //In this mode, none of the set commands are going to be called on the motors, so it should run faster
    //This mode is where the actual "jump" happens so it exits once the legs extend fully
    for(int i = 0; i < leg_count; ++i){
      if(legs[i].obs_leg_ext >= 0.11 ){
        prevTime = millis();
        mode = LAND;
      }
    }
  }else if(mode == LAND){
    for(int i = 0; i < leg_count; ++i){
      legs[i].setPD(20.0, 0.1);
      legs[i].setExtension(0.06);
      legs[i].setAngle(0.3);
    }
    if(millis() - prevTime >= 500){
      prevTime = millis();
      mode = SIT;
    }
  }
}

//Mod that does not return negative values
int posmod(int x, int y){
  return x < 0 ? ((x + 1) % y) + y - 1 : x % y;
}

//Maps an input in a range to an output in a range using floats
float floatMap(float input, float inMin, float inMax, float outMin, float outMax){
  return (((input - inMin) / (inMax - inMin)) * (outMax - outMin) + outMin);
}

void updateLegs(){
  //gets IMU sensor data
  IMU_Read(IMU);
  //Updates the legs
  float obs_ang_1;
  float obs_ang_2;
  for(int i = 0; i < leg_count; ++i){
    //If statements ensure that set commands are only sent when necessary (speeds up the code)
    if(legs[i].openLoop > 0){
      ser.set(mot[i*2].ctrl_velocity_, legs[i].throttle*100);
      ser.set(mot[i*2+1].ctrl_velocity_, legs[i].throttle*100);
      legs[i].openLoop = legs[i].openLoop - 1;
    }else{
      if(legs[i].updateAng > 0){
        ser.set(mot[i*2].ctrl_angle_, -1*(legs[i].ang_1+legs[i].mot_1_zero));
        ser.set(mot[i*2+1].ctrl_angle_, legs[i].ang_2+legs[i].mot_2_zero);
        legs[i].updateAng = legs[i].updateAng - 1;
      }
    }
    if(legs[i].updatePD > 0){
      ser.set(mot[i*2].angle_Kp_,legs[i].P);
      ser.set(mot[i*2].angle_Kd_,legs[i].D);
      ser.set(mot[i*2+1].angle_Kp_,legs[i].P);
      ser.set(mot[i*2+1].angle_Kd_,legs[i].D);
      legs[i].updatePD = legs[i].updatePD - 1;
    }
    obs_ang_1 = 0.0;
    obs_ang_2 = 0.0;
    ser.get(mot[i*2].obs_angular_displacement_, obs_ang_1);
    ser.get(mot[i*2+1].obs_angular_displacement_, obs_ang_2);
    legs[i].Update(obs_ang_1, obs_ang_2);
  }
}

void bno_write(uint8_t i2c_addr, uint8_t reg, uint8_t data){
  Wire.beginTransmission(i2c_addr);
  Wire.write(reg);
  Wire.write(data);
  Wire.endTransmission(true);     // No idea why these work (or sometimes don't work?)
}

void IMU_Read(float IMU[]){
  struct{
    int16_t yaw, pitch, roll;
  } s;
  bno_read_multiple(BNO_ADDR, EULER_ADDR, (uint8_t*)&s, sizeof s);
  IMU[0] = (s.roll/900.0);
  IMU[1] = (s.pitch/900.0);
  IMU[2] = (s.yaw/900.0);
}

// read multiple BNO registers into object
void bno_read_multiple(uint8_t i2c_addr, uint8_t reg, uint8_t *obj, uint8_t length){
  for (uint32_t n=0; n<length; n++){
    if ((n & 31) == 0){
      Wire.beginTransmission(i2c_addr);
      Wire.write(reg+n);
      Wire.endTransmission(false);  // No idea why this works (or sometimes doesn't work?)
      Wire.requestFrom(i2c_addr, min(length-n, 32));
    }
    *obj++ = Wire.read();
  }
}

//generates walk points based on input walk parameters
void generateWalks(){

  FrontForwardWalkX[0] = strideLen/2 + strideOffset;
  BackForwardWalkX[0] = strideLen/2 - strideOffset;
  ForwardWalkY[0] = -1*standExtension;
  
  FrontForwardWalkX[1] = -strideLen/2 + strideOffset;
  BackForwardWalkX[1] = -strideLen/2 - strideOffset;
  ForwardWalkY[1] = -1*standExtension;
  
  FrontForwardWalkX[2] = strideOffset;
  BackForwardWalkX[2] = -1* strideOffset;
  ForwardWalkY[2] = -1*standExtension + legLift;
  
  FrontForwardWalkX[3] = strideLen/2+0.5*legLift*cos(approachAngle) + strideOffset;
  BackForwardWalkX[3] = strideLen/2+0.5*legLift*cos(approachAngle) - strideOffset;
  ForwardWalkY[3] = -1*standExtension+0.5*legLift*sin(approachAngle);
}

void setWalkPosition(int leg, long Mils){

  if(Mils < 0){
    Mils = 0;
  }else if(Mils > stepTime){
    Mils - stepTime;
  }
  
  float frontX;
  float backX;
  float y;
  
  if(Mils < stepTime*(1.0-dutyFactor)){
      //Foot on ground
      frontX = floatMap(Mils, 0, stepTime*(1.0-dutyFactor), FrontForwardWalkX[0], FrontForwardWalkX[1]);
      backX = floatMap(Mils, 0, stepTime*(1.0-dutyFactor), BackForwardWalkX[0], BackForwardWalkX[1]);
      y = floatMap(Mils, 0, stepTime*(1.0-dutyFactor), ForwardWalkY[0], ForwardWalkY[1]);
      legs[leg].setPD(80.0, 0.1);
    }else if(Mils < stepTime*(1.0-dutyFactor)+(stepTime*dutyFactor)*(0.50)){
      //lifting foot off ground
      frontX = floatMap(Mils, stepTime*(1.0-dutyFactor), stepTime*(1.0-dutyFactor)+(stepTime*dutyFactor)*(0.50), FrontForwardWalkX[1], FrontForwardWalkX[2]);
      backX = floatMap(Mils, stepTime*(1.0-dutyFactor), stepTime*(1.0-dutyFactor)+(stepTime*dutyFactor)*(0.50), BackForwardWalkX[1], BackForwardWalkX[2]);
      y = floatMap(Mils, stepTime*(1.0-dutyFactor), stepTime*(1.0-dutyFactor)+(stepTime*dutyFactor)*(0.50), ForwardWalkY[1], ForwardWalkY[2]);
    }else if(Mils < stepTime*(1.0-dutyFactor)+(stepTime*dutyFactor)*(0.75)){
      //moving foot forward
      frontX = floatMap(Mils, stepTime*(1.0-dutyFactor)+(stepTime*dutyFactor)*(0.50), stepTime*(1.0-dutyFactor)+(stepTime*dutyFactor)*(0.75), FrontForwardWalkX[2], FrontForwardWalkX[3]);
      backX = floatMap(Mils, stepTime*(1.0-dutyFactor)+(stepTime*dutyFactor)*(0.50), stepTime*(1.0-dutyFactor)+(stepTime*dutyFactor)*(0.75), BackForwardWalkX[2], BackForwardWalkX[3]);
      y = floatMap(Mils, stepTime*(1.0-dutyFactor)+(stepTime*dutyFactor)*(0.50), stepTime*(1.0-dutyFactor)+(stepTime*dutyFactor)*(0.75), ForwardWalkY[2], ForwardWalkY[3]);
    }else{
      //placing foot on ground
      frontX = floatMap(Mils, stepTime*(1.0-dutyFactor)+(stepTime*dutyFactor)*(0.75), stepTime, FrontForwardWalkX[3], FrontForwardWalkX[0]);
      backX = floatMap(Mils, stepTime*(1.0-dutyFactor)+(stepTime*dutyFactor)*(0.75), stepTime, BackForwardWalkX[3], BackForwardWalkX[0]);
      y = floatMap(Mils, stepTime*(1.0-dutyFactor)+(stepTime*dutyFactor)*(0.75), stepTime, ForwardWalkY[3], ForwardWalkY[0]);
    }
    if(leg == 1 || leg == 2){
      legs[leg].setXY(frontX, y);
    }else{
      legs[leg].setXY(backX, y);
    }

    if(leg == 1 && Mils > stepTime*(1.0-dutyFactor) && sqrt(sq(legs[1].obsX - frontX) + sq(legs[1].obsY - y)) > stepTolerance){
      high_step = 1;
      float tempLift = legLift;
      float tempStand = standExtension;
      standExtension = 0.08;
      legLift = 0.035;
      generateWalks();
      standExtension = tempStand;
      legLift = tempLift;
    }
    if(leg == 1){
      Serial.print(legs[1].obsX*1000);
      Serial.print(" ");
      Serial.print(frontX*1000);
      Serial.print(" ");
      Serial.print(legs[1].obsY*1000);
      Serial.print(" ");
      Serial.print(y*1000);
      Serial.print(" ");
      Serial.print(sqrt(sq(legs[1].obsX - frontX) + sq(legs[1].obsY - y)) * 1000);
      Serial.print(" ");
      Serial.println(Mils);
    }
}
