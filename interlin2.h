#ifndef __interlin
#define __interlin

  #include <stdio.h>
  #include <math.h>
  #include <stdlib.h>
  #include "danStuff.h"
 
  typedef struct axis2_s    { 
    float start;
    float position; 
    float target; 
    char * ID;
    void (*CachePos)(float position);
  } axis2_t;

  typedef struct axies2_s   { 
    unsigned int motionSteps;
    long axisCount; 
    axis2_t * axii; 
    void (*Sync)(void);
  } axies2_t;
  
void axisInit(axies2_t * this, void (*Sync)(void)) ;
void axisAdd(axies2_t * this, float initial, float target, void (*CachePos)(float position) ) ;
void dumpaxies(axies2_t * this ) ;
void SimotaniouslyLinearlyInterpolateMultiAxis(axies2_t * this);
    

#endif 
