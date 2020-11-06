#include <Adafruit_NeoPixel.h>
#include <Adafruit_CircuitPlayground.h>
#include <Arduino.h>
void setup() {
  // put your setup code here, to run once:
CircuitPlayground.begin();
int i 
int lightSequence[4];
int answer[4];
int response[4];
int life =1;
randomSeed(analogRead(0));

void loop() {
for (i =0; i< 4; i++) //loop to assign random sequence
{
  light = random(0,3);
    if(light == 0)
    {
      answer[i] = 0;
      CircuitPlayground.setPixelColor = (1, 255, 0, 0); //red
      CircuitPlayground.setPixelColor = (2, 255, 0, 0); //red
      CircuitPlayground.setPixelColor = (3, 255, 0, 0); //red
      CircuitPlayground.setPixelColor = (4, 255, 0, 0); //red
    }
    if (light == 1)      
    {
      answer[i] = 2;
      CiruitPlayground.setPixelColor = (1, 0, 0, 255); //blue
      CiruitPlayground.setPixelColor = (2, 0, 0, 255); //blue
      CiruitPlayground.setPixelColor = (3, 0, 0, 255); //blue
      CiruitPlayground.setPixelColor = (4, 0, 0, 255); //blue
    }
    if (light == 2)
    {
      answer[i] =2;
      CircuitPlayground.setPixelColor = (1,0, 255, 0); //green
      CircuitPlayground.setPixelColor = (2,0, 255, 0); //green
      CircuitPlayground.setPixelColor = (3,0, 255, 0); //green
      CircuitPlayground.setPixelColor = (4,0, 255, 0); //green
    }
    else
    {
      answer[i] = 3;
      CircuitPlayground.setPixelColor = (1, 125, 0, 125); //purple?
      CircuitPlayground.setPixelColor = (2, 125, 0, 125); //purple?
      CircuitPlayground.setPixelColor = (3, 125, 0, 125); //purple?
      CircuitPlayground.setPixelColor = (4, 125, 0, 125); //purple?
    }
    delay(800)
    
for(i=0; i <4; i++)
{
  while(!CircuitPlayground.cpTouch.A1() && !CircuitPlayground.cpTouch.A2() && !CircuitPlayground.cpTouch.A3() && !CircuitPlayground.cpTouch.A4())
   {
    
   }
   if(CircuitPlayground.cpTouch.A1())  //cp.touch_A(X) in python, setup for starting location of wires willl need to be the same for each game
   {
    response[i] = 0
   }
   if(CircuitPlayground.cpTouch.A2())
   {
    response[i] = 1
   }   
   if(CircuitPlayground.cpTouch.A3())
   {
    response[i] = 2
   }
   else if(CircuitPlayground.cpTouch.A4())
   {
    response[i] = 3
   }
  delay (500)

for(i=0; i <4; i++) //checking attempts
  {
      if (response[i] != answer[i])
      life = 0

      //add losing sequence here
}
