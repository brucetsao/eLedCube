#include <avr/pgmspace.h> 

#define CUBESIZE 4
#define PLANESIZE CUBESIZE*CUBESIZE
#define PLANETIME 3333 
#define TIMECONST 20 
#define delaytime  150

int LEDPin[] = {22, 24, 26, 28, 30, 32, 34, 36, 23, 25, 27, 29, 31, 33, 35, 37};
int PlanePin[] = {40, 42, 41, 43};
int nowpos = 0 ;
int lastpos = 0 ;

void setup()
{
int pin; 
for (pin=0; pin<PLANESIZE; pin++) {
pinMode( LEDPin[pin], OUTPUT );
}
for (pin=0; pin<CUBESIZE; pin++) {
pinMode( PlanePin[pin], OUTPUT );
}
}
void loop()
{
  int layer=0 ;
  int pos= 0 ;
    for (layer = 0 ; layer <CUBESIZE ;layer++)
      {
        digitalWrite( PlanePin[layer], HIGH );
          for (pos = 0 ; pos <PLANESIZE ;pos++)
            {
                nowpos = pos ;
                  digitalWrite( LEDPin[lastpos], HIGH );
                  digitalWrite( LEDPin[nowpos], LOW );
                 lastpos = nowpos ;
                delay(delaytime); 
                  
            }
          digitalWrite( PlanePin[layer], LOW );
      }
}

