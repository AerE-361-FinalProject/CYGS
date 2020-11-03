#include <Adafruit_NeoPixel.h>
#include <Adafruit_CircuitPlayground.h>
#include <time.h>
void setup() {
  // put your setup code here, to run once:
  CircuitPlayground.begin(); //Needed for the Circuit Playground library
  srand(time(NULL));
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
    num = rand() % 100;
    if(num < 40){
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
      return 1;
    }
  }else if(life == 1){
    for(i = 0; i < 10; i++){
      return 0;
    }    
  }
}
void boom(){
  //This will be the code run when the player loses the game
}
int wires(){
  //This will contain the code for the wire game
}
void loop() {
  // put your main code here, to run repeatedly:
  //This will be the main game, use this for control flow of the game itself
  //More functions will likely be needed, but this will give us a general start
}
