#include "xyz.h"

#define CUBESIZE 4
#define PLANESIZE CUBESIZE*CUBESIZE
#define WAIT 200

/*
** Defining pins in array makes it easier to rearrange how cube is wired
** Adjust numbers here until LEDs flash in order - L to R, T to B
** Note that analog inputs 0-5 are also digital outputs 14-19!
** Pin DigitalOut0 (serial RX) and AnalogIn5 are left open for future apps
*/

//int LEDPin[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
int LEDPinCount = 16;
//int PlanePin[4] = {16, 17, 18, 19};
int PlanePinCount  = 4;

int LEDPin[] = {22, 24, 26, 28, 30, 32, 34, 36, 23, 25, 27, 29, 31, 33, 35, 37};
int PlanePin[] = {40, 42, 41, 43};

xyz directions[] = {{0,-1},{0,1},{4,0},{1,0},{-4,0},{-1,0}};
xyz now = {0,0};
xyz randomDirection;
xyz previousDirection={0,0};
xyz previousLocation={15,15};

// initialization
void setup()
{
  int pin; // loop counter
  // set up LED pins as output (active HIGH)
  for (pin=0; pin<PLANESIZE; pin++) {
    pinMode( LEDPin[pin], OUTPUT );
  }
  // set up plane pins as outputs (active LOW)
  for (pin=0; pin<CUBESIZE; pin++) {
    pinMode( PlanePin[pin], OUTPUT );
  }
  
  //Serial.begin(9600);

  planesOff();
  
  randomDirection = directions[random(6)];
  


}


void loop(){
  Serial.print("NOW: ");
  Serial.print(now.xz);
  Serial.print(":");
  Serial.println(now.y);
  
  Serial.print("Proposed direction: ");
  Serial.print(randomDirection.xz);
  Serial.print(":");
  Serial.println(randomDirection.y);
  
  // if its a valid direction and not going backwards, do it!
    if(valid(now, randomDirection) && !(inverse(randomDirection,previousDirection))){
      
      previousLocation = now;
      Serial.println("Accepted");
      previousDirection = randomDirection;
      now = move(now, randomDirection);
      
      // turn on the current led
      digitalWrite(LEDPin[now.xz],HIGH);
      digitalWrite(PlanePin[now.y],LOW);
      
      delay(WAIT);
      
      //turn off the previous one, but only if its on a different plane or pin
      if(!(previousLocation.xz == now.xz)){
        digitalWrite(LEDPin[previousLocation.xz],LOW);
      }
      if(!(previousLocation.y == now.y)){
        digitalWrite(PlanePin[previousLocation.y],HIGH);
      }
      
    }
    else{
      Serial.println("Rejected");
    }
    randomDirection = directions[random(6)];
     
      
}



void planesOff(){
    for(int thisPlane = 0; thisPlane < PlanePinCount; thisPlane++){
        digitalWrite(PlanePin[thisPlane],LOW);
    }
}
