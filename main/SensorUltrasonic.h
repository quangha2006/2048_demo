#pragma once

#define   MAX_DISTANCE    500
#define   TIME_ECHO_OUT   12000

class SensorUltrasonic
{
  public:
    SensorUltrasonic(unsigned char echoPIN, unsigned char trigPIN);

    int GetCm();

  private:
    unsigned char m_TrigPIN;
    unsigned char m_EchoPIN;
};
