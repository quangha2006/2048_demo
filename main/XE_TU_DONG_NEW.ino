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

  blueDevice.SetPinBLT(BLT_RX_PIN, BLT_TX_PIN);     // Setup Debug With Bluetooth.

  disSensorL.GetCm();
  disSensorR.GetCm();
  if (disSensorL.GetCm() < disSensorR.GetCm())
  {
    following_wall_flag = left;
    parallel_wall = left;
  }
  else
  {
    following_wall_flag = right;
    parallel_wall = right;
  }
  following_wall_dis_old_left = disSensorL.GetCm();
  following_wall_dis_old_right = disSensorR.GetCm();
  force_follw_wall = false;
  motorL.RunForward(MED_SPEED);
  motorR.RunForward(MED_SPEED);
  LOG2("Setup DONE");
}

//////////// UPDATE ////////////
void loop()
{
  if (countLoop < 25)
  {
    countLoop++;
  }
  if (following_wall_count < 25)
  {
    following_wall_count ++;
  }
  //buttonStatus = digitalRead(FW_FLAG);
  //// GET DISTANCE.
  disL = disSensorL.GetCm();
  disR = disSensorR.GetCm();
  disH = disSensorH.GetCm();
  LOG2(disH, disR, disL);
  //// CONTROL CAR.
  if (disH <= DISTANCE_SLOW_SPEED)
  {
    motorL.RunForward(MED_SPEED);
    motorR.RunForward(MED_SPEED);
  }
  else
  {
    if (Keep_parallel_wall == 0)
    {
      motorL.RunForward(MAX_SPEED);
      motorR.RunForward(MAX_SPEED);
    }
    if (Keep_parallel_wall > 0)
    {
      motorL.RunForward(MAX_SPEED - Keep_parallel_wall);
      motorR.RunForward(MAX_SPEED);
    }
    if (Keep_parallel_wall < 0)
    {
      motorL.RunForward(MAX_SPEED);
      motorR.RunForward(MAX_SPEED + Keep_parallel_wall);
    }
  }

  disH = disSensorH.GetCm();
  if (disH <= LOW_DISTANCE) //15
  {
    // Update
    disL = disSensorL.GetCm();
    disR = disSensorR.GetCm();

    motorL.RunBackward(MED_SPEED);
    motorR.RunBackward(MED_SPEED);
    delay(250);
    motorL.Stop();
    motorR.Stop();
    LOG2("LOW_DISTANCE");
    LOG2(disH, disR, disL);

    if (following_wall_flag == left && disR > 15)
    {
      motorR.RunBackward(MED_SPEED);
      LOG2("Turn Head Right");
    }
    else if (following_wall_flag == right && disL > 15)
    {
      motorL.RunBackward(MED_SPEED);
      LOG2("Turn Head Left");
    }
    else
    {
      if (disR > disL)
      {
        motorR.RunBackward(MED_SPEED);
        LOG2("Turn Head Right");
      }
      else
      {
        motorL.RunBackward(MED_SPEED);
        LOG2("Turn Head Right");
      }
    }
    while (disSensorH.GetCm() <= LOW_DISTANCE)
    {
      delay(DelayTime);
    }
    motorL.Stop();
    motorR.Stop();
    following_wall_count += 7;
    //countLoop = 0;
  }

  // Tranh trai phai
  disL = disSensorL.GetCm();
  disR = disSensorR.GetCm();
  if ((disR <= DISTANCE_LEFT_RIGHT) && (countLoop > 5) && (disR != 0))
  {
    motorL.Stop();
    countLoop = 0;
    LOG2("Turn Left");
    delay(100);
    while (disSensorR.GetCm() <= 8)
    {
      motorR.Stop();
      motorL.RunBackward(LOW_SPEED);
      //delay(DelayTime);
    }

    motorL.Stop();
  }
  else if ((disL <= DISTANCE_LEFT_RIGHT) && (countLoop > 5) && (disL != 0))
  {
    motorR.Stop();
    countLoop = 0;
    LOG2("Turn Right");
    delay(100);
    while (disSensorL.GetCm() <= 8)
    {
      motorL.Stop();
      motorR.RunBackward(LOW_SPEED);
      //delay(DelayTime);
    }

    motorR.Stop();
  }

  // Following wall
  if (following_wall_count > 19)
  {
    if (following_wall_flag == left || following_wall_flag == non || force_follw_wall == true)
    {
      int left_new = disSensorL.GetCm();
      if (left_new - following_wall_dis_old_left >= MED_DISTANCE)
      {
        motorL.Stop();

        //LOG2("Turn Left: ", left_new - following_wall_dis_old_left);
        motorR.RunForward(MED_SPEED);
        delay(DelayTime__TurnRight);
        if (force_follw_wall)
        {
          following_wall_flag = left;
          force_follw_wall = false;
        }
        motorL.RunForward(MED_SPEED);
        countLoop = 0;
        following_wall_count = 0;
      }
      following_wall_dis_old_left = disSensorL.GetCm();
    }
    if (following_wall_flag == right || following_wall_flag == non || force_follw_wall == true)
    {
      int right_new = disSensorR.GetCm();
      if (right_new - following_wall_dis_old_right >= MED_DISTANCE)
      {
        motorR.Stop();

        //LOG2("Turn Right: ", right_new - following_wall_dis_old_right);

        motorL.RunForward(MED_SPEED);
        delay(DelayTime__TurnRight);
        if (force_follw_wall)
        {
          following_wall_flag = right;
          force_follw_wall = false;
        }
        motorR.RunForward(MED_SPEED);
        countLoop = 0;
        following_wall_count = 0;
      }
      following_wall_dis_old_right = disSensorR.GetCm();
    }

  }

  // Giu xe chay song song voi wall
  disL = disSensorL.GetCm();
  disR = disSensorR.GetCm();
  if (countLoop == 0)
  {
    dis_index = 0;
    Keep_parallel_wall = 0; // + - speed
    if (disL < disR)
    {
      parallel_wall = left;
    }
    else
    {
      parallel_wall = right;
    }
  }
  if (parallel_wall == left)
  {
    disToWall_sample[dis_index] = disSensorL.GetCm();
  }
  else
  {
    disToWall_sample[dis_index] = disSensorR.GetCm();
  }
  dis_index ++;
  if (dis_index >= 3)
  {
    if (disToWall_sample[0] <= disToWall_sample[1] && disToWall_sample[1] <= disToWall_sample[2] && disToWall_sample[0] < disToWall_sample[2]) // lech xa tuong
    {
      if (parallel_wall == left)
      {
          Keep_parallel_wall = 70;
          if (disToWall_sample[0] < disToWall_sample[1] && disToWall_sample[1] < disToWall_sample[2])
          {
            Keep_parallel_wall = 100;
          }
      }
      else
      {
          Keep_parallel_wall = -70;
          if (disToWall_sample[0] < disToWall_sample[1] && disToWall_sample[1] < disToWall_sample[2])
          {
            Keep_parallel_wall = -100;
          }
      }
    }
    else if (disToWall_sample[0] >= disToWall_sample[1] && disToWall_sample[1] >= disToWall_sample[2] && disToWall_sample[0] > disToWall_sample[2]) // lech vao tuong
    {
      if (parallel_wall == left)
      {
          Keep_parallel_wall = -70;
          if (disToWall_sample[0] > disToWall_sample[1] && disToWall_sample[1] > disToWall_sample[2])
          {
            Keep_parallel_wall = -100;
          }
      }
      else
      {
          Keep_parallel_wall = 70;
          if (disToWall_sample[0] > disToWall_sample[1] && disToWall_sample[1] > disToWall_sample[2])
          {
             Keep_parallel_wall = 100;
          }
      }
    }
    else // Chinh xe chay o giua
    {
      Keep_parallel_wall = 0;
      disL = disSensorL.GetCm();
      disR = disSensorR.GetCm();
      if (disL > disR)
      {
        if ((disL - disR) > 10)
        {
          Keep_parallel_wall = 70;
        }
      }
      else
      {
        if ((disR - disL) > 10)
        {
          Keep_parallel_wall = -70;
        }
      }
    }
    LOG2(disToWall_sample[0], disToWall_sample[1], disToWall_sample[2], Keep_parallel_wall);
    dis_index = 0;
  }
}
void LOG2(int disH, int disR, int disL)
{
#if DEBUG_LOG
  String logBlue;
  logBlue = "H: ";
  logBlue += disH;
  logBlue += ", L: ";
  logBlue += disL;
  logBlue += ", R: ";
  logBlue += disR;
  logBlue += ", CL: ";
  logBlue += countLoop;
  logBlue += ", bt: ";
  if (following_wall_flag == right)
  {
    logBlue += " FW: right";
  }
  else
  {
    logBlue += " FW: left";
  }
  blueDevice.SentToBluetoothDevice(logBlue);
#endif
}
void LOG2(int dis1, int dis2, int dis3, int set_speed)
{
#if DEBUG_LOG
  String logBlue = "dis 0: ";
  logBlue += dis1;
  logBlue += "dis 1: ";
  logBlue += dis2;
  logBlue += "dis 2: ";
  logBlue += dis3;
  logBlue += "Bu_Tru: ";
  logBlue += set_speed;
  blueDevice.SentToBluetoothDevice(logBlue);
#endif
}
void LOG2(String data)
{
#if DEBUG_LOG
  blueDevice.SentToBluetoothDevice(data);
#endif
}
void LOG2(String data, int i)
{
#if DEBUG_LOG
  data += i;
  blueDevice.SentToBluetoothDevice(data);
#endif
}

