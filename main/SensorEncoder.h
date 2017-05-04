#pragma once

class SensorEncoder
{
  public:
    SensorEncoder(unsigned char interruptPIN);

    static void CountHoleNumberEncoder1();
    static void CountHoleNumberEncoder2();

    void StartEncoder1();
    void StartEncoder2();

    unsigned int GetHoldNumberEncoder1();
    unsigned int GetHoldNumberEncoder2();

    volatile static unsigned int m_HoleNumberEncoder1;
    volatile static unsigned int m_HoleNumberEncoder2;
    
  private:
    unsigned char m_InterruptPIN;

    unsigned char m_PinEncoder1;
    unsigned char m_PinEncoder2;
};
