#ifndef __servoarm
  #define __servoarm

  #include "returnValues.h"
  #include "transBuffer.h"
  #include "ssls3.h"
  #include "SSC8Spooler.h"


  typedef struct servoArm_s {

   SSC8Spooler_t  axii;
   transBuffer_t  buffer;

  } servoArm_t;

  void servoArmCharReciever(unsigned char * data, void * anchor);

#endif

