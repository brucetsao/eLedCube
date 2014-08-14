#define CUBESIZE 4
#define PLANESIZE CUBESIZE*CUBESIZE
#define PLANETIME 3333 
#define TIMECONST 20 
#define delaytime  180
#define anisize 34


int LEDPin[] = {
  22, 24, 26, 28, 30, 32, 34, 36, 23, 25, 27, 29, 31, 33, 35, 37};
int PlanePin[] = {
  40, 42, 41, 43};
int nowpos = 0 ;
int nowlayer = 0 ;
int lastpos = 0 ;
int lastlayer = 0 ;
int animator[]={
  1,2,3,4,8,12,16,15,14,26,22,23,27,
  47,46,45,41,37,33,34,35,36,56,60,64,
  63,62,61,57,53,54,55,59,58} 
;


void setup()
{
  Serial.begin(9600);
  Serial.println("program start here");
  int pin; 
  for (pin=0; pin< PLANESIZE; pin++)
  {
    pinMode( LEDPin[pin], OUTPUT );
   }
  for (pin=0; pin<CUBESIZE; pin++) 
  {
        pinMode( PlanePin[pin], OUTPUT );
     }
  initall();
}
void loop()
{
  int ani = 0 ;
  int layer=0 ;
  int pos= 0 ;
    Serial.print("The animator size is :(");
    Serial.print(sizeof(animator)/2);
    Serial.print(")\n");
  for (ani = 0 ; ani < sizeof(animator)/2; ani ++)
  {
      Serial.println(animator[ani]);
    nowlayer = (int)((animator[ani]-1)/16) ;
    nowpos = (animator[ani]-1) %16 ;

    // now turn on leds
    digitalWrite( PlanePin[nowlayer],HIGH );
    digitalWrite( LEDPin[nowpos], LOW );
    lastlayer = nowlayer ;
    lastpos = nowpos ;
    delay(delaytime); 
    // now turn off leds
    digitalWrite( PlanePin[lastlayer], LOW );
    digitalWrite( LEDPin[lastpos], HIGH );
  }
    initall();
    delay(900);
}


void initall()
{
  int pin; 

  for (pin=0; pin<CUBESIZE; pin++) 
  {
    digitalWrite( PlanePin[pin], LOW );
  }

    for (pin=0; pin<PLANESIZE; pin++)
  {
    digitalWrite( LEDPin[pin], HIGH );
  }
  
  
}


