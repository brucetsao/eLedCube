#define CUBESIZE 4
#define PLANESIZE CUBESIZE*CUBESIZE
#define PLANETIME 3333 
#define TIMECONST 20 
#define delaytime  180

int LEDPin[] = {22, 24, 26, 28, 30, 32, 34, 36, 23, 25, 27, 29, 31, 33, 35, 37};
int PlanePin[] = {40, 42, 41, 43};
int nowpos = 0 ;
int nowlayer = 0 ;
int lastpos = 0 ;
int lastlayer = 0 ;
int animator[]={1,2,3,4,8,12,16,15,14,13,9,5,6,7,11,10,
                10+16*1,6+16*1,7+16*1,11+16*1,15+16*1,14+16*1,13+16*1,9+16*1,5+16*1,1+16*1,2+16*1,3+16*1,4+16*1,8+16*1,12+16*1,16+16*1
                ,16+16*2,15+16*2,14+16*2,13+16*2,9+16*2,5+16*2,1+16*2,2+16*2,3+16*2,4+16*2,8+16*2,12+16*2,11+16*2,10+16*2,6+16*2,7+16*2
                 ,7+16*3,11+16*3,10+16*3,6+16*3,2+16*3,3+16*3,4+16*3,8+16*3,12+16*3,16+16*3,15+16*3,14+16*3,13+16*3,9+16*3,5+16*3,1+16*3} ;
void setup()
{
int pin; 
for (pin=0; pin<PLANESIZE; pin++) {
pinMode( LEDPin[pin], OUTPUT );
digitalWrite( LEDPin[pin], HIGH );
}
for (pin=0; pin<CUBESIZE; pin++) {
digitalWrite( PlanePin[pin], LOW );
}
}
void loop()
{
  int ani = 0 ;
  int layer=0 ;
  int pos= 0 ;
    for (ani = 0 ; ani < 64; ani ++)
    {
                  nowlayer = (int)((animator[ani]-1)/16) ;
                  nowpos = (animator[ani]-1) %16 ;
                  digitalWrite( PlanePin[lastlayer], LOW );
                  digitalWrite( LEDPin[lastpos], HIGH );
                   
                  digitalWrite( PlanePin[nowlayer],HIGH );
                  digitalWrite( LEDPin[nowpos], LOW );
                 lastlayer = nowlayer ;
                 lastpos = nowpos ;
                delay(delaytime); 

      }
}

