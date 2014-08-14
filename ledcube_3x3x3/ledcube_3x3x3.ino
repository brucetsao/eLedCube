/*
  3x3x3 LED cube
 */

//intializing and declaring layers
int layer[3]={
  3,4,5};
//initializing and declaring leds, bottom right is led[0]
int led[9]={
  2,6,7,8,9,10,11,12,13};

int time = 250;

void setup()
{
  //setting leds to ouput
  for(int i = 0; i<9; i++)
  {
    pinMode(led[i], OUTPUT);
  }
  //setting layers to output
  for(int i = 0; i<3; i++)
  {
    pinMode(layer[i], OUTPUT);
  }
  //seeding random for random animations
  randomSeed(analogRead(10));
}
//++++++++++++++MAIN FUNCTION+++++++++++

void loop()
{
  turnEverythingOff();//turn all off
  flickerOn();
  turnEverythingOn();//turn all on
  delay(time);
  turnOnAndOffAllByLayerUpAndDownNotTimed();
  layerstompUpAndDown();
  turnOnAndOffAllByColumnSideways();
  delay(time);
  turnEverythingOff();
  randomflicker();
  randomRain();
  flickerOff();
  turnEverythingOff();
  
}


//+++++++++FUNCTIONS++++++++++

/////////turn all off
void turnEverythingOff()
{
  for(int i = 0; i<9; i++)
  {
    digitalWrite(led[i], 1);
  }
  for(int i = 0; i<3; i++)
  {
    digitalWrite(layer[i], 0);
  }
}

//////////turn all on
void turnEverythingOn()
{
  for(int i = 0; i<9; i++)
  {
    digitalWrite(led[i], 0);
  }
  //turning on layers
  for(int i = 0; i<3; i++)
  {
    digitalWrite(layer[i], 1);
  }
}
/////////////turn columns off
void turnColumnsOff()
{
  for(int i = 0; i<9; i++)
  {
    digitalWrite(led[i], 1);
  }
}
///////////////flicker on
void flickerOn()
{
  int i = 150;
  while(i != 0)
  {
    turnEverythingOn();
    delay(i);
    turnEverythingOff();
    delay(i);
    i-= 5;
  }
}
//// turn everything on and off by layer up and down NOT TIMED
void turnOnAndOffAllByLayerUpAndDownNotTimed()
{
  int x = 75;
  for(int i = 3; i != 0; i--)
  {
    turnEverythingOn();
    for(int i = 3; i!=0; i--)
    {
      digitalWrite(layer[i-1], 0);
      delay(x);
    }
    for(int i = 0; i<3; i++)
    {
      digitalWrite(layer[i], 1);
      delay(x);
    }
    for(int i = 0; i<3; i++)
    {
      digitalWrite(layer[i], 0);
      delay(x);
    }
    for(int i = 3; i!=0; i--)
    {
      digitalWrite(layer[i-1], 1);
      delay(x);
    }
  }
}
//////////turn everything on and off by column sideways
void turnOnAndOffAllByColumnSideways()
{
  int x = 75;
  turnEverythingOff();
  //turn on layers
  for(int i = 0; i<3; i++)
  {
    digitalWrite(layer[i], 1);
  }
  for(int y = 0; y<3; y++)
  {
    //turn on 0-2
    for(int i = 0; i<3; i++)
    {
      digitalWrite(led[i], 0);
      delay(x);
    }
    //turn on 3-5
    for(int i = 3; i<6; i++)
    {
      digitalWrite(led[i], 0);
      delay(x);
    }
    //turn on 6-8
    for(int i = 6; i<9; i++)
    {
      digitalWrite(led[i], 0);
      delay(x);

    }
    //turn off 0-2
    for(int i = 0; i<3; i++)
    {
      digitalWrite(led[i], 1);
      delay(x);
    }
    //turn off 3-5
    for(int i = 3; i<6; i++)
    {
      digitalWrite(led[i], 1);
      delay(x);
    }
    //turn off 6-8
    for(int i =6 ; i<9; i++)
    {
      digitalWrite(led[i], 1);
      delay(x);

    }
    //turn on 6-8
    for(int i = 6; i<9; i++)
    {
      digitalWrite(led[i], 0);
      delay(x);
    }
    //turn on 3-5
    for(int i = 3; i<5; i++)
    {
      digitalWrite(led[i], 0);
      delay(x);
    }
    //turn on 0-2
    for(int i = 0; i<3; i++)
    {
      digitalWrite(led[i], 0);
      delay(x);

    }
    //turn off 0-2
    for(int i = 0; i<3; i++)
    {
      digitalWrite(led[i], 1);
      delay(x);
    }
    //turn off 3-5
    for(int i = 3; i<6; i++)
    {
      digitalWrite(led[i], 1);
      delay(x);
    }
    //turn off 6-8
    for(int i = 6; i<9; i++)
    {
      digitalWrite(led[i], 1);
      delay(x);
    }
  }
}
////////up and down single layer
void layerstompUpAndDown()
{
  int x = 75;
  for(int i = 0; i<3; i++)
  {
    digitalWrite(layer[i], 0);
  }
  for(int y = 0; y<4; y++)
  {
    for(int count = 0; count<1; count++)
    { 
      for(int i = 0; i<3; i++)
      {
        digitalWrite(layer[i], 1);
        delay(x);
        digitalWrite(layer[i], 0);
      }
      for(int i = 3; i !=0; i--)
      {
        digitalWrite(layer[i-1], 1);
        delay(x);
        digitalWrite(layer[i-1], 0);
      }
    }
    for(int i = 0; i<3; i++)
    {
      digitalWrite(layer[i], 1);
      delay(x);
    }
    for(int i = 3; i!=0; i--)
    {
      digitalWrite(layer[i-1], 0);
      delay(x);
    }
  }
}
////////flicker off
void flickerOff()
{
  turnEverythingOn();
  for(int i = 0; i!= 150; i+=5)
  {
    turnEverythingOff();
    delay(i+50);
    turnEverythingOn();
    delay(i);
  }
}

////////random flicker
void randomflicker()
{
  turnEverythingOff();
  int x = 10;
  for(int i = 0; i !=750; i+=2)
  {
    int randomLayer = random(0,3);
    int randomLed = random(0,9);

    digitalWrite(layer[randomLayer], 1);
    digitalWrite(led[randomLed], 0);
    delay(x);
    digitalWrite(layer[randomLayer], 0);
    digitalWrite(led[randomLed], 1);
    delay(x); 
  }
}
//////////random rain
void randomRain()
{
  turnEverythingOff();
  int x = 100;
  for(int i = 0; i!=60; i+=2)
  {
    int randomLed = random(0,9);
    digitalWrite(led[randomLed], 0);
    digitalWrite(layer[0], 1);
    delay(x+50);
    digitalWrite(layer[0], 0);
    digitalWrite(layer[1], 1);
    delay(x);
    digitalWrite(layer[1], 0);
    digitalWrite(layer[2], 1);
    delay(x);
    digitalWrite(layer[2], 0);
    digitalWrite(layer[0], 1);
    delay(x+50);
    digitalWrite(layer[0], 0);
    digitalWrite(led[randomLed], 1);
  }
}




