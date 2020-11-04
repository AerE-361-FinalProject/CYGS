#include <Adafruit_NeoPixel.h>
#include <Adafruit_CircuitPlayground.h>
#include <time.h>
#include <Arduino.h>

#define INITIAL = 0; //Timer begins
#define AUDIOGAME = 1; //Playing the audio game, stored in a function
#define OPEN = 2; //Box is opened, player now needs to press a button to recieve their instructions
#define WIRES_1 = 3; //Player is removing the wires
#define WIRES_2 = 4; //Player is reattaching the wires
#define WIN = 5; //Player has won
int state;
void setup() {
  // put your setup code here, to run once:
  CircuitPlayground.begin(); //Needed for the Circuit Playground library
  randomSeed(analogRead(0));
  reset();
}
int audioGame(){
  //This will contain the finished audio game
  //Int return used to determine success or failure
    int i,j; //Counters
  int test[8];
  int guess[8];
  int rand_num;
  int life = 1;
  int num;
  for(i = 0; i < 8; i++){ //A loop to randomly play 8 high or low notes
    if(CircuitPlayground.lightSensor() < 40 && !CircuitPlayground.getAccelTap()){
      num = random(1,100);
      if(num < 50){
        test[i] = 0;
        CircuitPlayground.playTone(294,100);
      }else{
        test[i] = 1;
        CircuitPlayground.playTone(440,100);
      }
      delay(500);
    }else{
      return 1;
    }
  }
  
  for(i = 0; i < 8; i++){
    while(!CircuitPlayground.leftButton() && !CircuitPlayground.rightButton()){
      //J chillin' until you hit a button
      if(CircuitPlayground.lightSensor() < 40 && !CircuitPlayground.getAccelTap()){
      }else{
        return 1;
      }
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
      life = 0; //If you are wrong, you forfeit your life privileges (The bomb goes off)
    }
  }
  if(life == 0){
      return 1;
  }else if(life == 1){
    for(i = 0; i < 2; i++){
      CircuitPlayground.playTone(440,100);
      delay(100);
    }
    return 0;
  }
}
void boom(){
  //This will be the code run when the player loses the game
  int i; //NeoPixel counter
  CircuitPlayground.playTone(294,1000);
  while(!CircuitPlayground.leftButton() && !CircuitPlayground.rightButton()){
    for(i = 0; i < 10; i++){
      CircuitPlayground.setPixelColor(i,255,0,0);
    }
    delay(500); //Flashes red until player hits a button to restart the game.
    CircuitPlayground.clearPixels();
    delay(500);
  }
  reset();
}
void reset(){
  //This will contain the code to restart the game
  //Initial delay to give the player time after turning on the chip
  CircuitPlayground.clearPixels();
  delay(100);
  for(i = 0; i < 10; i++){
  }
  for(i = 0; i < 10; i++){//10 second countdown shown by blue lights
    delay(1000);
    CircuitPlayground.setPixelColor(i,0,0,0);
  }
  state = INITIAL;
}
void youwin(){
  //This code runs if you win the game
  while(!CircuitPlayground.leftButton() && !CircuitPlayground.rightButton()){
    for(i = 0; i < 10; i++){
      CircuitPlayground.setPixelColor(i,0,255,0);
    }
    delay(500); //Flashes green until player hits a button to restart the game.
    CircuitPlayground.clearPixels();
    delay(500);
  }
  reset();
}
void loop() {
  // put your main code here, to run repeatedly:
  //This will be the main game, use this for control flow of the game itself
  //More functions will likely be needed, but this will give us a general start
  int i; //Counter
  int check; //
  switch(state){
    case(INITIAL){
      //Begin timer
      state = AUDIOGAME;
      break;
    }
    case(AUDIOGAME){
      check = audioGame();
      if(check == 0){
        state = OPEN;
      }else{
        boom();
      }
      break;
    }
    case(OPEN){
      while(!CircuitPlayground.leftButton() && !CircuitPlayground.rightButton()){
        if(CircuitPlayground.getAccelTap()){
          boom();
        }
      }
      break;
    }
  }
}
