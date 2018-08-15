#pragma once

//// Define DIRECTION.
#define   DIR_12                    0

//// Define DISTANCE.
#define   DISTANCE_LEFT_RIGHT       15
#define   DISTANCE_SLOW_SPEED       30
#define   LOW_DISTANCE              15
#define   MED_DISTANCE              20
#define   HIG_DISTANCE              40

//// Define SPEED.
#define   STOP_CAR                  0
#define   LOW_SPEED                 130
#define   MED_SPEED                 150
#define   MAX_SPEED                 255

#define   DelayTime                 50
#define   DelayTime__TurnRight      480

//// MOTOR LEFT.
#define   EN_A                      5
#define   IN_1                      7
#define   IN_2                      8

//// MOTOR RIGHT.
#define   EN_B                      6
#define   IN_3                      9
#define   IN_4                      10

//// SENSOR SRF04.
#define   TRIG_PIN_HEAD             A3
#define   ECHO_PIN_HEAD             A2

//// SENSOR IR.
#define   IR_PIN_LEFT               A0
#define   IR_PIN_RIGHT              A1
#define   IR_PIN_HEAD               A2
#define   MODEL_IR                  1080

//// Following wall
#define FW_FLAG                     2

//// 3 SENSORS GET DISTANCE.
SharpIR                             disSensorL(IR_PIN_LEFT, MODEL_IR);                // LEFT.
SharpIR                             disSensorR(IR_PIN_RIGHT, MODEL_IR);               // RIGHT.
SharpIR                             disSensorH(IR_PIN_HEAD, MODEL_IR);               // HEAD.
//SensorUltrasonic                    disSensorH(ECHO_PIN_HEAD, TRIG_PIN_HEAD);         // HEAD.

//// MOTOR LEFT AND RIGHT.
MotorDC                             motorR(IN_1, IN_2, EN_A);
MotorDC                             motorL(IN_3, IN_4, EN_B);

//// BLUETOOTH DEVICE.
#define   BLT_RX_PIN                11
#define   BLT_TX_PIN                12
BluetoothDevice                     blueDevice;

////enum
enum Following_Wall {non = 0, left = 1, right = 2};

//// GLOBAL VARIABLEs.
int countLoop                      = 0;
int following_wall_dis_old_left    = 0;
int following_wall_dis_old_right   = 0;
Following_Wall following_wall_flag = non;
int following_wall_count           = 10;
int disToWall_sample[3]            = {};
int dis_index                      = 0;
int Keep_parallel_wall             = 0;
bool force_follw_wall              = false;
int disL                           = 0;
int disR                           = 0;
int disH                           = 0;
Following_Wall parallel_wall       = non;
