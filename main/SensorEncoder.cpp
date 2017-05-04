#include "AStdAfx.h"

#include "SensorEncoder.h"

volatile static unsigned int SensorEncoder::m_HoleNumberEncoder1 = 0;
volatile static unsigned int SensorEncoder::m_HoleNumberEncoder2 = 0;

SensorEncoder::SensorEncoder(unsigned char interruptPIN)
  : m_InterruptPIN(interruptPIN)
{}

void SensorEncoder::CountHoleNumberEncoder1()
{
  m_HoleNumberEncoder1++;
  LOG("Hole Encoder1 = ");
  LOG(m_HoleNumberEncoder1);
  LOGLN();
}

void SensorEncoder::CountHoleNumberEncoder2()
{
  m_HoleNumberEncoder2++;
  LOG("Hole Encoder2 = ");
  LOG(m_HoleNumberEncoder2);
  LOGLN();  
}

void SensorEncoder::StartEncoder1()
{
  m_HoleNumberEncoder1 = 0;
  attachInterrupt(digitalPinToInterrupt(m_InterruptPIN), SensorEncoder::CountHoleNumberEncoder1, RISING);
}
void SensorEncoder::StartEncoder2()
{
  m_HoleNumberEncoder2 = 0;
  attachInterrupt(digitalPinToInterrupt(m_InterruptPIN), SensorEncoder::CountHoleNumberEncoder2, RISING);
}

unsigned int SensorEncoder::GetHoldNumberEncoder1()
{
  unsigned int number;
  
  detachInterrupt(digitalPinToInterrupt(m_InterruptPIN));
  
  number = m_HoleNumberEncoder1;
  m_HoleNumberEncoder1 = 0;

  attachInterrupt(digitalPinToInterrupt(m_InterruptPIN), SensorEncoder::CountHoleNumberEncoder1, RISING);
  
  return number;
}

unsigned int SensorEncoder::GetHoldNumberEncoder2()
{
  unsigned int number;
  
  detachInterrupt(digitalPinToInterrupt(m_InterruptPIN));
  
  number = m_HoleNumberEncoder2;
  m_HoleNumberEncoder2 = 0;

  attachInterrupt(digitalPinToInterrupt(m_InterruptPIN), SensorEncoder::CountHoleNumberEncoder2, RISING);
  
  return number;
}
