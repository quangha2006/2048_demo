/*
	SharpIR
	Arduino library for retrieving distance (in cm) from the analog GP2Y0A21Y and GP2Y0A02YK
	From an original version of Dr. Marcal Casas-Cartagena (marcal.casas@gmail.com)
  Version : 1.0 : Guillaume Rico
	https://github.com/guillaume-rico/SharpIR
*/

#pragma once
////

#ifdef ARDUINO
  #include "Arduino.h"
#elif defined(SPARK)
  #include "Particle.h"
#endif

#define NB_SAMPLE 25

class SharpIR
{
  public:

    SharpIR (int irPin, long sensorModel);
    int GetCm();

  private:

    void Sort(int a[], int size);

    int _irPin;
    long _model;
};
