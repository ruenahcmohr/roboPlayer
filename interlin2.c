#include "interlin2.h"

void axisInit(axies2_t * this, void (*Sync)(void)) {
 this->axii = NULL;
 this->axisCount = 0;
 this->motionSteps = 10;
 this->Sync = Sync;
}

void axisAdd(axies2_t * this, float initial, float target, void (*CachePos)(float position) ) {
  this->axisCount++;
  this->axii = realloc(this->axii, sizeof(axis2_t) * this->axisCount);
  this->axii[(this->axisCount)-1].start    = initial;
  this->axii[(this->axisCount)-1].position  = initial;
  this->axii[(this->axisCount)-1].target   = target;
  this->axii[(this->axisCount)-1].CachePos  = CachePos;
}

void dumpaxies(axies2_t * this ) {
  long i;
  
  for (i = 0; i < this->axisCount; i++) {
    printf( "%d: %f  %f  %f\n", i, this->axii[i].start, this->axii[i].position, this->axii[i].target);
  }
  printf("\n");
}


void SimotaniouslyLinearlyInterpolateMultiAxis(axies2_t * this) {
  float longest, i;
  int j;
  float temp;
    
  // set it all up, work out how big our master index is  
  longest = 0;
  for (j = 0; j < this->axisCount; j++) {
    this->axii[j].start = this->axii[j].position;
    if (abs(this->axii[j].target - this->axii[j].start) > abs(longest))   longest = abs(this->axii[j].target - this->axii[j].start);
  }     
  
  if (longest == 0) return;  // nothing to move here!
   
  for ( i = 0; i <= longest; i+=(longest/(this->motionSteps-1))) {
    for (j = 0; j < this->axisCount; j++) {   
     // RangeRemap(v,Il,Ih,Ol,Oh)
      this->axii[j].position = RangeRemap(i,0,longest,this->axii[j].start,this->axii[j].target);
      (*this->axii[j].CachePos)(this->axii[j].position);        
    }
    (*this->Sync)();
  }
 
}




//=============================-- Testing stuff --=================================


/*

void setFor1() {
  printf("1 Stepping forward\n");
}

void setBak1() {
  printf("1 Stepping back \n");
}

void setFor2() {
  printf("2 Stepping forward\n");
}

void setBak2() {
  printf("2 Stepping back \n");
}

void setFor3() {
  printf("3 Stepping forward\n");
}

void setBak3() {
  printf("3 Stepping back \n");
}

void setFor4() {
  printf("4 Stepping forward\n");
}

void setBak4() {
  printf("4 Stepping back \n");
}

void motSync() {
  printf("Sync \n");
}



int main(void) {

  axies_t axies;

  axisInit( &axies, motSync );
  axisAdd(&axies,  2,  27, setFor1, setBak1);
  axisAdd(&axies, -4, -18, setFor2, setBak2);
  axisAdd(&axies,  9, -10, setFor3, setBak3);
  axisAdd(&axies,  -10, 40, setFor4, setBak4);
  dumpaxies( &axies );
  SimotaniouslyLinearlyInterpolateMultiAxis( &axies );
  
 
  return 0;

}


*/
