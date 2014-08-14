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
int imagedatatmp[16] ;
int systemstatus = 0;


void setup()
{
  Serial.begin(9600);    // open Serial Monitor 
   Serial2.begin(9600);   // setup Bluetooth use TX/RX pin Speed Rate
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
 systemstatus = 0  ;
}
void loop()
{
  int btnnum ;
  
  if (Serial2.available()) ;
  {
      btnnum = Serial2.read() ; 
       Serial2.println(btnnum);
  }
    switch (btnnum )
    {
      case 88 :    //CROSSOVER KEY
        systemstatus = 0 ;
        Serial.println("Turn Led Cube Off") ;
        break ;
        
      case  79 :
        systemstatus = 1 ;     //CIRCLE KEY
        Serial.println("Turn Led Cube Ons") ;
        break ;

      case  70 :
        systemstatus = 1 ;     //UP KEY
        Serial.println("Turn Led Cube UP") ;
        imageup();
        break ;

      case  66 :
        systemstatus = 1 ;     //DOWN KEY
        Serial.println("Turn Led Cube DOWN") ;
       imagedown();
        break ;

      case  82 :
        systemstatus = 1 ;     //RIGHT KEY
        Serial.println("Turn Led Cube RIGHT") ;
       imageright();
        break ;

      case  76 :
        systemstatus = 1 ;     //DOWN LEFT
        Serial.println("Turn Led Cube LEFT") ;
       imageleft();
        break ;


        }
  if  (systemstatus == 1)
      {
        refreshimage() ;
         delay(delaytime);  
      }
        else
      {
         initall();
      }
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
void imageright()
{
  int i = 0 ;
    for (i = 0 ; i < 64 ; i=i+16)
      {
          imagedatacopy(&imagedata[i], &imagedatatmp[0]) ;
          imagedata[i+0] = imagedatatmp[12] ;
          imagedata[i+1] = imagedatatmp[8] ;
          imagedata[i+2] = imagedatatmp[4] ;
          imagedata[i+3] = imagedatatmp[0] ;
          imagedata[i+4] = imagedatatmp[13] ;
          imagedata[i+5] = imagedatatmp[9] ;
          imagedata[i+6] = imagedatatmp[5] ;
          imagedata[i+7] = imagedatatmp[1] ;
          imagedata[i+8] = imagedatatmp[14] ;
          imagedata[i+9] = imagedatatmp[10] ;
          imagedata[i+10] = imagedatatmp[6] ;
          imagedata[i+11] = imagedatatmp[2] ;
          imagedata[i+12] = imagedatatmp[15] ;
          imagedata[i+13] = imagedatatmp[11] ;
          imagedata[i+14] = imagedatatmp[7] ;
          imagedata[i+15] = imagedatatmp[3] ;
      }
    transforimagemapping();
}

void imageleft()
{
  int i = 0 ;
    for (i = 0 ; i < 64 ; i=i+16)
      {
          imagedatacopy(&imagedata[i], &imagedatatmp[0]) ;
          imagedata[i+0] = imagedatatmp[3] ;
          imagedata[i+1] = imagedatatmp[7] ;
          imagedata[i+2] = imagedatatmp[11] ;
          imagedata[i+3] = imagedatatmp[15] ;
          imagedata[i+4] = imagedatatmp[2] ;
          imagedata[i+5] = imagedatatmp[6] ;
          imagedata[i+6] = imagedatatmp[10] ;
          imagedata[i+7] = imagedatatmp[14] ;
          imagedata[i+8] = imagedatatmp[1] ;
          imagedata[i+9] = imagedatatmp[5] ;
          imagedata[i+10] = imagedatatmp[9] ;
          imagedata[i+11] = imagedatatmp[13] ;
          imagedata[i+12] = imagedatatmp[0] ;
          imagedata[i+13] = imagedatatmp[4] ;
          imagedata[i+14] = imagedatatmp[8] ;
          imagedata[i+15] = imagedatatmp[12] ;
      }
    transforimagemapping();
}

void imageup()
{
    imagedatacopy(&imagedata[48], &imagedatatmp[0]) ;
    imagedatacopy(&imagedata[32], &imagedata[48]) ;
    imagedatacopy(&imagedata[16], &imagedata[32]) ;
    imagedatacopy(&imagedata[0], &imagedata[16]) ;
    imagedatacopy(&imagedatatmp[0], &imagedata[0]) ;
    transforimagemapping();
}


void imagedown()
{
    imagedatacopy(&imagedata[0], &imagedatatmp[0]) ;
    imagedatacopy(&imagedata[16], &imagedata[0]) ;
    imagedatacopy(&imagedata[32], &imagedata[16]) ;
    imagedatacopy(&imagedata[48], &imagedata[32]) ;
    imagedatacopy(&imagedatatmp[0], &imagedata[48]) ;
    transforimagemapping();
}


void imagedatacopy(int *src , int *tar)
{
int i ;
for(i = 0 ; i <16; i++)
  {
      *(tar+i) = *(src+i) ;     
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
  transformanimator();
  transforimagemapping();
}

void transformanimator()
{
    int i = 0 ;
    for (i=0 ; i < 64; i++)
      {
       imagedata[i]=0 ;
      }     
      
   for (i=0 ; i < anisize ; i++)
      {
       
         imagedata[animator[i]-1]= 1 ;
      }     

  
}

void transforimagemapping()
{
   int i = 0 , j = 0 ;
  for (i=0 ; i < 16; i++)
      {
       imagemapping[i]=0 ;
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
