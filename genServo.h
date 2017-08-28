#ifndef __genServo
#define __genServo

#include "returnValues.h"
#include <stdio.h>


#define thisTarget(I) (servo[(I)].target)
#define thisScale(I)  (servo[(I)].scale)
#define thisZero(I)   (servo[(I)].zero)
#define thisUpdate(I) (servo[(I)].update)


typedef struct servo_s {
  volatile float  target;
  volatile char   update;
  volatile float  zero;
  volatile float  scale;
} servo_t;



Status_t ServoInit(servo_t *this);
Status_t ServoFini(servo_t *this);
Status_t ServoSetTarget(servo_t *this, float target);
Status_t servoGetTarget(servo_t *this, float * target);
Status_t servoDump(servo_t *this);

#endif
