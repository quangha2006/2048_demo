#include "AStdAfx.h"

#include "MotorDC.h"

MotorDC::MotorDC(unsigned char in1PIN, unsigned char in2PIN, unsigned char enPIN)
  : m_PWM(PWM_MAX)
  , m_IN1_PIN(in1PIN)
  , m_IN2_PIN(in2PIN)
  , m_EN_PIN(enPIN)
  , m_MotorState(M_STOP)
{
  pinMode(enPIN , OUTPUT);
  pinMode(in1PIN, OUTPUT);
  pinMode(in2PIN, OUTPUT);
}

void MotorDC::RunForward(int numberPWM)
{
  if (m_MotorState != M_RUN_FORWARD || m_PWM != numberPWM)
  {
    //LOGLN("MOTOR RUN FORWARD ...");

    // Control Motor's SPEED.
    analogWrite(m_EN_PIN, numberPWM);

    digitalWrite(m_IN1_PIN, HIGH);
    digitalWrite(m_IN2_PIN, LOW);

    // Set Value.
    m_PWM = numberPWM;
    m_MotorState = M_RUN_FORWARD;
  }
}

void MotorDC::RunBackward(int numberPWM)
{
  if (m_MotorState != M_RUN_BACKWARD || m_PWM != numberPWM)
  {
    //LOGLN("MOTOR RUN BACKWARD ...");

    // Control Motor's SPEED.
    analogWrite(m_EN_PIN, numberPWM);

    digitalWrite(m_IN1_PIN, LOW);
    digitalWrite(m_IN2_PIN, HIGH);

    // Set Value.
    m_PWM = numberPWM;
    m_MotorState = M_RUN_BACKWARD;
  }
}

void MotorDC::Stop()
{
  if (m_MotorState != M_STOP)
  {
    //LOGLN("MOTOR STOP ...");

    digitalWrite(m_IN1_PIN, LOW);
    digitalWrite(m_IN2_PIN, LOW);

    // Set Value.
    m_MotorState = M_STOP;
  }
}
int MotorDC::GetSpeed()
{
  return m_PWM;
}

