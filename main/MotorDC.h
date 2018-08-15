#pragma once

#define   PWM_MAX   255

class MotorDC
{
  public:
    enum EMOTOR_STATE {M_RUN_FORWARD = 0, M_RUN_BACKWARD = 1, M_STOP = 2};

    MotorDC(unsigned char in1PIN, unsigned char in2PIN, unsigned char enAPIN);

    void RunForward (int numberPWM = PWM_MAX);
    void RunBackward(int numberPWM = PWM_MAX);
    int  GetSpeed();
    void Stop();

  private:
    int             m_PWM;
    unsigned char   m_IN1_PIN;
    unsigned char   m_IN2_PIN;
    unsigned char   m_EN_PIN;

    EMOTOR_STATE    m_MotorState;
};
