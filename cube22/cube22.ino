#define CUBESIZE 4
#define PLANESIZE CUBESIZE*CUBESIZE
#define PLANETIME 220
#define TIMECONST 20 
#define delaytime  15
#define anisize 34


int LEDPin[] = {22, 24, 26, 28, 30, 32, 34, 36, 23, 25, 27, 29, 31, 33, 35, 37};
int PlanePin[] = {40, 42, 41, 43};
int nowpos = 0 ;
int nowlayer = 0 ;
int lastpos = 0 ;
int lastlayer = 0 ;
int animator[]={1,2,3,4,8,12,16,15,14,26,22,23,27,
  47,46,45,41,37,33,34,35,36,56,60,64,
  63,62,61,57,53,54,55,59,58} ;


byte imagemapping[16] ;
int imagedata[64] ;



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
  initdata();
}
void loop()
{
 refreshimage() ;
   delay(delaytime);  
   initall();
}

void refreshimage()
{
  int i,j,k ;
  int ledrow; // counts LEDs in refresh loop
  int ledcol; // counts LEDs in refresh loop
int ledlayer; // counts LEDs in refresh loop
int ledpin; // counts LEDs in refresh loop
  ledpin = 0;
    for ( ledlayer = 0 ; ledlayer <  CUBESIZE ; ledlayer++)
      {
        digitalWrite( PlanePin[ledlayer], HIGH );
          for (ledrow=0; ledrow<CUBESIZE; ledrow++) 
            {
              for (ledcol=0; ledcol<CUBESIZE; ledcol++) 
                {
                  if (bitRead(imagemapping[ledlayer *4 + ledrow],ledcol) == 1)
                    {
                       digitalWrite(LEDPin[ledrow *4 + ledcol], LOW)  ;
                       delayMicroseconds(PLANETIME) ; 
                       digitalWrite(LEDPin[ledrow *4 + ledcol], HIGH)  ;
                    }
                }
            }
        digitalWrite( PlanePin[ledlayer], LOW );
      }
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

void initdata()
{
  int i = 0 , j = 0 ;
  for (i=0 ; i < 16; i++)
      {
       imagemapping[i]=0 ;
      }
   for (i=0 ; i < 64; i++)
      {
       imagedata[i]=0 ;
      }     
      
   for (i=0 ; i < anisize ; i++)
      {
       
         imagedata[animator[i]-1]= 1 ;
      }     

  for (i=0 ; i < 16; i++)
      {
        for (j=0 ; j<4; j++)
          {
            if (imagedata[i*4+j] == 1)
              {
         //         count ++ ;
                  bitWrite(imagemapping[i], j, 1)  ;
              }
              else
              {
                  bitWrite(imagemapping[i], j, 0)  ;
              }
              

          }

      }

}
