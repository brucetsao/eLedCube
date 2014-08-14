#include <avr/pgmspace.h> 

#define CUBESIZE 4
#define PLANESIZE CUBESIZE*CUBESIZE
#define PLANETIME 3333 
#define TIMECONST 20 

int LEDPin[] = {22, 24, 26, 28, 30, 32, 34, 36, 23, 25, 27, 29, 31, 33, 35, 37};
int PlanePin[] = {40, 42, 41, 43};

void setup()
{
  Serial.begin(9600);
  Serial.println("led start here");
int pin; 
for (pin=0; pin<PLANESIZE; pin++) {
pinMode( LEDPin[pin], OUTPUT );
digitalWrite(LEDPin[pin] ,HIGH);

}
for (pin=0; pin<CUBESIZE; pin++) {
pinMode( PlanePin[pin], OUTPUT );
digitalWrite(PlanePin[pin] ,LOW);
}
   // digitalWrite(LEDPin[3] ,HIGH);
//    digitalWrite(PlanePin[1] ,LOW);
}
void loop()
{
  int p = 0 ;
  int i ,j ;
  for (i=0 ; i<CUBESIZE ; i++)
    {    
      digitalWrite(PlanePin[i] ,HIGH);
          for (j = 0 ; j <PLANESIZE;j++)
          {
             digitalWrite(LEDPin[j] ,LOW);
            delay(200) ;  
            p++ ;
             Serial.print(p);
           Serial.print("/" );
        }
    }
           Serial.print("\n" );
           p = 0 ;
   for (i=CUBESIZE -1 ; i>=0 ; i--)
    {    

          for (j = PLANESIZE-1 ; j >= 0;j--)
          {
             digitalWrite(LEDPin[j] ,HIGH);
            delay(200) ;  
                  p++ ;
           Serial.print(p);
           Serial.print("/" );
        }
             digitalWrite(PlanePin[i] ,LOW);
    }
           Serial.print("\n" );
} 



