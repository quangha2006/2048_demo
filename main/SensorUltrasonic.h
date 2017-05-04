#pragma once

#define   MAX_DISTANCE    500
#define   TIME_ECHO_OUT   12000

class SensorUltrasonic
{
  public:
    SensorUltrasonic(unsigned char echoPIN, unsigned char trigPIN, unsigned int maxDistance = MAX_DISTANCE);
    
    float GetCm();

  private:
    unsigned int m_MaxDistance;
    
    unsigned char m_TrigPIN;
    unsigned char m_EchoPIN;
};
