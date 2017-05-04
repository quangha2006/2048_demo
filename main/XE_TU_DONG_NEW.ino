#include "AStdAfx.h"

#include "SensorUltrasonic.h"
#include "BluetoothDevice.h"
#include "SharpIR.h"
#include "MotorDC.h"
#include "Defined.h"

//////////// SETUP ////////////
void setup()
{
  Serial.begin(9600);
  // Setup Debug With Bluetooth.
  blueDevice.SetPinBLT(BLT_RX_PIN, BLT_TX_PIN);

  motorL.RunForward(200);
  motorR.RunForward(200);
}

int curDir          = DIR_12;
int countLoop       = 0;
int countTurnLeft   = 0;
int speedMotorL     = 0;
int speedMotorR     = 0;

float sensorValue, inches, cm;    //Must be of type float for pow()

//////////// UPDATE ////////////
void loop()
{
  
  //delay(2000);
  // PV: Test Bluetooth END.
  if (countLoop < 25)
  {
    countLoop++;
  }

  //// GET DISTANCE.
  int disL = disSensorL.GetCm();
  int disR = disSensorR.GetCm();
  int disH = disSensorH.GetCm();

  LOG("Dis HEAD : ");
  LOG(disH);
  LOGLN("");

  LOG("Dis LEFT : ");
  LOG(disL);
  LOGLN("");

  LOG("Dis RIGHT: ");
  LOG(disR);
  LOGLN();
  LOGLN();
  String logblue = "Dis HEAD :";
  logblue += disH;
  // PV: Test Bluetooth START.
  blueDevice.SentToBluetoothDevice(logblue);
  //delay(300);

  //// CONTROL CAR.
  if (disH <= LOW_DISTANCE) //12
  {
    motorR.Stop();
    motorL.Stop();
    if (disSensorR.GetCm() > disSensorL.GetCm() || (disSensorR.GetCm() > 20 && disSensorL.GetCm() > 20))
    {
      motorR.RunBackward(MED_SPEED);
    }
    else
    {
      motorL.RunBackward(MED_SPEED);
    }

    while (disSensorH.GetCm() <= LOW_DISTANCE)
    {
      delay(DelayTime);
    }
    countLoop = 0;
    countTurnLeft = 0;
  }

  if ((disSensorR.GetCm() <= VERY_LOW_DISTANCE) && (countLoop > 7))
  {
    motorL.Stop();
    motorR.Stop();
    motorL.RunBackward(MED_SPEED);
    countLoop = 0;
    countTurnLeft = 0;

    while (disSensorR.GetCm() <= VERY_LOW_DISTANCE - 1)
    {
      delay(DelayTime);
    }
    motorL.Stop();
  }
  else if ((disSensorL.GetCm() <= VERY_LOW_DISTANCE) && (countLoop > 7))
  {
    motorL.Stop();
    motorR.Stop();
    motorR.RunBackward(MED_SPEED);
    countLoop = 0;
    countTurnLeft = 0;

    while (disSensorL.GetCm() <= VERY_LOW_DISTANCE - 1)
    {
      delay(DelayTime);
    }
    motorR.Stop();
  }

  // Turn left
  if ((countLoop > 20) && (countTurnLeft < 3))
  {
    countLoop = 0;

    if (disSensorL.GetCm() >= MED_DISTANCE)
    {
      countTurnLeft ++;
      motorL.Stop();
      motorR.RunForward(MED_SPEED);
      delay(DelayTime__TurnRight);
    }
  }
  motorL.RunForward(MAX_SPEED);
  motorR.RunForward(MAX_SPEED);
}
