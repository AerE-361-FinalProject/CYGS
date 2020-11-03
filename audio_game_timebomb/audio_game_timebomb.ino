#include <Adafruit_NeoPixel.h>
#include <Adafruit_CircuitPlayground.h>
#include <time.h>
#include <Arduino.h>
void setup() {
  // put your setup code here, to run once:
  CircuitPlayground.begin();
  randomSeed(analogRead(0));
}

void loop() {
  // put your main code here, to run repeatedly:
  int i,j; //Counters
  int test[8];
  int guess[8];
  int rand_num;
  int life = 1;
  int num;
  for(i = 0; i < 8; i++){ //A loop to randomly play 8 high or low notes
    num = random(0,100);
    if(num < 50){
      test[i] = 0;
      CircuitPlayground.playTone(294,100);
    }else{
      test[i] = 1;
      CircuitPlayground.playTone(440,100);
    }
    delay(500);
  }
  for(i = 0; i < 8; i++){
    while(!CircuitPlayground.leftButton() && !CircuitPlayground.rightButton()){
      //J chillin' until you hit a button
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
    for(i = 0; i < 10; i++){
      CircuitPlayground.setPixelColor(i,255,0,0); //Red to indicate death
    }
  }else if(life == 1){
    for(i = 0; i < 10; i++){
      CircuitPlayground.setPixelColor(i,0,255,0); //Green to indicate success
    }    
  }
  delay(2000);
  for(i = 0; i < 10; i++){
      CircuitPlayground.setPixelColor(i,0,0,255); //Blue after the game is finished
  }
    while(!CircuitPlayground.leftButton() && !CircuitPlayground.rightButton()){
      //Press any button to play again
    }
  CircuitPlayground.clearPixels(); //Turns off the NeoPixels  
}
