#include "AStdAfx.h"

#include "SensorUltrasonic.h"

SensorUltrasonic::SensorUltrasonic(unsigned char echoPIN, unsigned char trigPIN, unsigned int maxDistance)
  : m_TrigPIN(trigPIN)
  , m_EchoPIN(echoPIN)
  , m_MaxDistance(maxDistance)
{
  pinMode(echoPIN, INPUT);
  pinMode(trigPIN, OUTPUT);
}

float SensorUltrasonic::GetCm()
{
  float distance = 0;
  
  digitalWrite(m_TrigPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(m_TrigPIN, HIGH);
  delayMicroseconds(5);
  digitalWrite(m_TrigPIN, LOW);

  distance = pulseIn(m_EchoPIN, HIGH, TIME_ECHO_OUT) / 58.2;

  // Distance = 0 Mean That Signal Has Been Time Out => Set MAX_DISTANCE For It.
  if(distance == 0)
  {
    distance = MAX_DISTANCE;
  }

  return distance;
}
