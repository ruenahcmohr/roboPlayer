#include <stdio.h>
#include "returnValues.h"
#include "danStuff.h"
#include "interlin2.h"
#include "servoArm.h"
#include "transformer.h"

void cache0(float position);
void cache1(float position) ;
void cache2(float position);
void cache3(float position) ;
void cache4(float position);
void cache5(float position) ;

void motSync() ;
void playFile(char * filename) ;



int            stepDelay;
axies2_t       axies;
servoArm_t     OUT;   
   

int main(int argc, char * argv[]) {

   
   unsigned int  i;
   
   if (argc < 4) {
     printf("Usage %s devicein configin playfile\n", argv[0]);
     return 0;
   }   
   
   printf("Initializing\n");
   if (servoArmInit(&OUT, argv[1], argv[2]) != OK) {
     printf("port open error\n");
     return 0;
   }
   
   transZeroInput(&(OUT.buffer)) ; 

   
  axisInit( &axies, motSync );
  axisAdd(&axies, 0,  0, cache0);
  axisAdd(&axies, 0,  0, cache1);
  axisAdd(&axies, 0,  0, cache2);
  axisAdd(&axies, 0,  0, cache3);
  axisAdd(&axies, 0,  0, cache4);
  axisAdd(&axies, 0,  0, cache5); 
  
  
  axies.motionSteps = 40; // up the resolution
  SimotaniouslyLinearlyInterpolateMultiAxis( &axies );
  
  
  playFile(argv[3]) ;  

  return 0;
}

   


void cache0(float position) {
  OUT.buffer.in[0] = position;
}

void cache1(float position) {
  OUT.buffer.in[1] = position;
}

void cache2(float position) {
  OUT.buffer.in[2] = position;
}

void cache3(float position) {
  OUT.buffer.in[3] = position;
}

void cache4(float position) {
  OUT.buffer.in[4] = position;
}

void cache5(float position) {
  OUT.buffer.in[5] = position;
}


void motSync() {
  usleep(stepDelay);  
  transZeroOutput(&(OUT.buffer));
  transCalc(&(OUT.buffer));
  servoArmSync(&OUT); 
}


void playFile(char * filename) {

   FILE *input;
   float lasttime, time, A, B, C, D, E, F;

 
   // read 6 numbers per line, ended with linefeed, prefixed with delta time
   
   if ((input = fopen(filename, "rt")) == NULL) {  //open text file 'param 1' w/ err chk 
      printf("Unable to open %s for input.\n", filename);
   }

   while (fscanf(input, "%f, %f, %f, %f, %f, %f, %f \n", &time, &A, &B, &C, &D, &E, &F) == 7) {
     printf("%-04g sec : %-05g, %-05g, %-05g, %-05g, %-05g, %-05g \n", time, A, B, C, D, E, F);   
     
     time *= 1000000;                  // change to us
     //stepDelay = time / 40.0;          // 40steps
     stepDelay = 30000;       
     axies.motionSteps = time / 30000;   
     axies.axii[0].target = A;
     axies.axii[1].target = B;
     axies.axii[2].target = C;
     axies.axii[3].target = D;
     axies.axii[4].target = E;
     axies.axii[5].target = F;
     SimotaniouslyLinearlyInterpolateMultiAxis( &axies );
   }     
   
   fclose(input);


}

















