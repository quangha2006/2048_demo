#pragma once

#include <Arduino.h>

//// LOG.
#define   DEBUG_LOG   0

#if DEBUG_LOG
  #define   LOG(ARGS)       Serial.print  (ARGS)
  #define   LOGLN(ARGS)     Serial.println(ARGS)
#else
  #define   LOG(ARGS)
  #define   LOGLN(ARGS)
#endif
