#include <Adafruit_NeoPixel.h>
#include <Adafruit_CircuitPlayground.h>
#include <time.h>
#include <Arduino.h>
#include <Scheduler.h>

#define INITIAL  0 //Timer begins
#define AUDIOGAME  1 //Playing the audio game, stored in a function
#define OPEN  2 //Box is opened, player now needs to press a button to recieve their instructions
#define WIRES_1  3 //Player is removing the wires
#define WIRES_2  4 //Player is reattaching the wires
#define CapLimit 1000
#define Red 3
#define Yellow 2
#define Green 0
#define White 1

int state;
int wirestate = 0;
int order[4];
int wires[4] = {3,2,0,1}; //RED,YELLOW,GREEN,WHITE
int i,j;
void setup() {
  // put your setup code here, to run once:
  CircuitPlayground.begin(); //Needed for the Circuit Playground library
  randomSeed(analogRead(9));
  pinMode(3,INPUT);
  pinMode(2,INPUT);
  pinMode(0,INPUT);
  pinMode(1,INPUT);
  pinMode(13,OUTPUT);
  Scheduler.startLoop(timeLoop);
  reset();
}
void timeLoop(){
  delay(7000);
  if(j == 9){
    CircuitPlayground.setPixelColor(j,0,0,0);
    boom();
  }else if(j == -1){
    //Does nothing after the games has ended
  }else{
    CircuitPlayground.setPixelColor(j,0,0,0);
    j++;
  }
}
boolean capButton(int pad){
  if(CircuitPlayground.readCap(pad) > CapLimit){
    return true;
  }else{
    return false;
  }
}
void boom(){
  //This will be the code run when the player loses the game
  int i; //NeoPixel counter
  j=-1;
  CircuitPlayground.playTone(294,1000);
  while(!CircuitPlayground.leftButton() && !CircuitPlayground.rightButton()){
    for(i = 0; i < 10; i++){
      CircuitPlayground.setPixelColor(i,255,0,0);
    }
    delay(250); //Flashes red until player hits a button to restart the game.
    CircuitPlayground.clearPixels();
    delay(250);
  }
  reset();
}
void reset(){
  //This will contain the code to restart the game
  //Initial delay to give the player time after turning on the chip
  CircuitPlayground.clearPixels();
  delay(100);
  for(i = 0; i < 10; i++){
    CircuitPlayground.setPixelColor(i,0,0,255);
  }
  for(i = 0; i < 10; i++){//10 second countdown shown by blue lights
    delay(1000);
    CircuitPlayground.setPixelColor(i,0,0,0);
  }
  state = INITIAL;
  wirestate = 0;
}
void youwin(){
  //This code runs if you win the game
  while(!CircuitPlayground.leftButton() && !CircuitPlayground.rightButton()){
    j=-1;
    for(i = 0; i < 10; i++){
      CircuitPlayground.setPixelColor(i,0,255,0);
    }
    delay(250); //Flashes green until player hits a button to restart the game.
    CircuitPlayground.clearPixels();
    delay(250);
  }
  reset();
}
void loop() {
  // put your main code here, to run repeatedly:
  //This will be the main game, use this for control flow of the game itself
  //More functions will likely be needed, but this will give us a general start
  int check = 2; //
  int num;
  switch(state){
    case INITIAL:
      //Begin timer
        for(i = 0; i < 10; i++){
          CircuitPlayground.setPixelColor(i,0,0,255);
        }
        j = 0;
      state = AUDIOGAME;
      break;
    case AUDIOGAME:
  //This will contain the finished audio game
  //Int return used to determine success or failure
  int test[8];
  int guess[8];
  int rand_num;
  int num;
  for(i = 0; i < 8; i++){ //A loop to randomly play 8 high or low notes
    if(CircuitPlayground.lightSensor() < 300 && !CircuitPlayground.getAccelTap()){
      num = random(1,100);
      if(num < 50){
        test[i] = 0;
        CircuitPlayground.playTone(294,100);
      }else{
        test[i] = 1;
        CircuitPlayground.playTone(440,100);
      }
      delay(400);
    }else{
      boom();
    }
  }
  
  for(i = 0; i < 8; i++){
    while(!CircuitPlayground.leftButton() && !CircuitPlayground.rightButton()){
      //J chillin' until you hit a button
      yield();
    }
    if(CircuitPlayground.leftButton()){
      guess[i] = 0;
    }else if(CircuitPlayground.rightButton()){
      guess[i] = 1;
    }
    delay(200);
  }
  for(i = 0; i < 8; i++){ //Checks the players guesses
    if(test[i] != guess[i]){
      boom();
    }
  }
      for(i = 0; i < 3; i++){
      CircuitPlayground.playTone(440,100);
      delay(100);
      }
      state = OPEN;
      break;
    case OPEN:
      while(!CircuitPlayground.leftButton() && !CircuitPlayground.rightButton()){
        if(CircuitPlayground.getAccelTap()){
          boom();
        }
        yield();
      }
      state = WIRES_1;
      break;
    case WIRES_1:
      //Get the random sequence of wires
      
      switch(wirestate){
        case 0: //Blinks the order
          num =  random(4);
         order[0] = wires[num];
      while(wires[num] == order[0]){
        num =  random(4);
      }
      order[1] = wires[num];
      while(wires[num] == order[0] || wires[num] == order[1]){
        num =  random(4);
      }
      order[2] = wires[num];
      for(i = 0; i < 4; i++){
        if(wires[i] != order[0] && wires[i] != order[1] && wires[i] != order[2]){
          order[3] = wires[i];    
        }
      }
          for(i = 0; i < 4; i++){
            if(order[i] == 3){ //RED
              CircuitPlayground.setPixelColor(0,255,0,0);
              delay(500);
              CircuitPlayground.setPixelColor(0,0,0,0);
            }else if(order[i] == 2){ //YELLOW
              CircuitPlayground.setPixelColor(0,255,255,0);
              delay(500);
              CircuitPlayground.setPixelColor(0,0,0,0);            
            }else if(order[i] == 0){
              CircuitPlayground.setPixelColor(0,0,255,0);
              delay(500);
              CircuitPlayground.setPixelColor(0,0,0,0);              
            }else if(order[i] == 1){
              CircuitPlayground.setPixelColor(0,255,255,255);
              delay(500);
              CircuitPlayground.setPixelColor(0,0,0,0);            
            }else{
              CircuitPlayground.setPixelColor(0,255,0,255);
              delay(500);
              CircuitPlayground.setPixelColor(0,0,0,0);
            }
          }
          wirestate = 1;
          break;
        case 1://Now check to see if wires are removed in the correct order
            delay(500);
          if(wirestate1(order)){
            delay(250);
          }else if(wirestate2(order)){
            wirestate = 2;
            delay(250);
          }else{
            boom();
          }
          break;
        case 2:
            delay(500);
          if(wirestate2(order)){
            delay(250);
          }else if(wirestate3(order)){
            wirestate = 3;
            delay(250);
          }else{
            boom();
          }
          break;
        case 3:
            delay(500);
          if(wirestate3(order)){
            delay(250);
          }else if(wirestate4(order)){
            wirestate = 4;
            delay(250);
          }else{
            boom();
          }
          break;
        case 4:
            delay(500);
          if(wirestate4(order)){
            delay(250);
          }else if(wirestate5(order)){
            wirestate = 0;
            state = WIRES_2;
            delay(250);
          }else{
            boom();
          }
          break;
      }
      break;
    case WIRES_2:
      switch(wirestate){
        case 0:  //Blinks the order, in backwards order
          CircuitPlayground.setPixelColor(0,0,0,0);
          while(!CircuitPlayground.leftButton() && !CircuitPlayground.rightButton()){
            delay(50);
           }
           randomSeed(analogRead(10));
        num =  random(4);
         order[0] = wires[num];
      while(wires[num] == order[0]){
        num =  random(4);
      }
      order[1] = wires[num];
      while(wires[num] == order[0] || wires[num] == order[1]){
        num =  random(4);
      }
      order[2] = wires[num];
      for(i = 0; i < 4; i++){
        if(wires[i] != order[0] && wires[i] != order[1] && wires[i] != order[2]){
          order[3] = wires[i];    
        }
      }
          for(i = 0; i < 4; i++){
            if(order[3-i] == 3){ //RED
              CircuitPlayground.setPixelColor(0,255,0,0);
              delay(500);
              CircuitPlayground.setPixelColor(0,0,0,0);
            }else if(order[3-i] == 2){ //YELLOW
              CircuitPlayground.setPixelColor(0,255,255,0);
              delay(500);
              CircuitPlayground.setPixelColor(0,0,0,0);             
            }else if(order[3-i] == 0){ //Green
              CircuitPlayground.setPixelColor(0,0,255,0);
              delay(500);
              CircuitPlayground.setPixelColor(0,0,0,0);              
            }else if(order[3-i] == 1){ //White
              CircuitPlayground.setPixelColor(0,255,255,255);
              delay(500);
              CircuitPlayground.setPixelColor(0,0,0,0);              
            }else{
              CircuitPlayground.setPixelColor(0,255,0,255);
              delay(500);
              CircuitPlayground.setPixelColor(0,0,0,0); 
            }
          }
          wirestate = 1;
          break;
        case 1: //Now check to see if wires are removed in the correct order
          //Because we reversed the order vector, the code is identical.
            delay(500);
          if(wirestate5(order)){
            delay(250);
          }else if(wirestate4(order)){
            wirestate = 2;
            delay(250);
          }else{
            boom();
          }
          break;
        case 2:
            delay(500);
          if(wirestate4(order)){
            delay(250);
          }else if(wirestate3(order)){
            wirestate = 3;
            delay(250);
          }else{
            boom();
          }
          break;
        case 3:
            delay(500);
          if(wirestate3(order)){
            delay(250);
          }else if(wirestate2(order)){
            wirestate = 4;
            delay(250);
          }else{
            boom();
          }
          break;
        case 4:
            delay(500);
            CircuitPlayground.setPixelColor(0,255,0,0);
          if(wirestate2(order)){
            delay(250);
          }else if(wirestate1(order)){
            youwin();
          }else{
            boom();
          }
          break;
        }
        break;
      }        
  }

bool wirestate1(int order[]){
  if(capButton(order[0]) && capButton(order[1]) && capButton(order[2]) && capButton(order[3])){
    return true;
  }else{
    return false;
  }
}
bool wirestate2(int order[]){
  if(!capButton(order[0]) && capButton(order[1])&& capButton(order[2]) && capButton(order[3])){
    return true;
  }else{
    return false;
  }
}
bool wirestate3(int order[]){
  if(!capButton(order[0]) && !capButton(order[1]) && capButton(order[2]) && capButton(order[3])){
    return true;
  }else{
    return false;
  }
}
bool wirestate4(int order[]){
  if(!capButton(order[0]) && !capButton(order[1]) && !capButton(order[2]) && capButton(order[3])){
    return true;
  }else{
    return false;
  }
}
bool wirestate5(int order[]){
  if(!capButton(order[0]) && !capButton(order[1]) && !capButton(order[2]) && !capButton(order[3])){
    return true;
  }else{
    return false;
  }
}
