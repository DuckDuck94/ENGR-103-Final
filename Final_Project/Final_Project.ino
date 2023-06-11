#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>

int slidePin = 7; //the switch
int buttonBPin = 5;
int level = 0;
int b = 1;
bool slide = 0;
volatile bool slideFlag = 0; //slide is automatically on
volatile bool buttonFlag = 0;
bool buttonA = 0;
bool buttonB = 0;

int sideColor; 
int score = 0;
int scoreKeep = 1;
int delaySpeed = 300;
int deathCount = 3;
int pattern[10] = {0,0,0,0,0,0,0,0,0,0}; //store the pattern
int pattenComp[10] = {0,0,0,0,0,0,0,0,0,0}; //store the pattern

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
  pinMode(LED_BUILTIN, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(slidePin), slideISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(buttonBPin), buttonISR, RISING);
}

void loop() {
    Serial.print("You're on level ");
    Serial.print(level);
    Serial.print("!");

  if (slideFlag && (deathCount != 0)) { //if turned on
    sideColor = random (2);
    colorBlink(sideColor);
    //give them time to input buttons
    delay(1000);
    Serial.println("Check");
    buttonA = CircuitPlayground.rightButton(); //returns a 1 or 0
    //Serial.println(buttonA);
    delay(delaySpeed);
    buttonB = CircuitPlayground.leftButton(); //returns a 1 or 0
    //turn this into a flag

    


    if (buttonFlag) { //buttonflag
      b = 0;
    }
    Serial.println(sideColor);
    delay(delaySpeed);
    //smtng smthng scoreKeep block stop uhh uhh
    //pattern[x] = sideColor;
    //play it once
    for (int x = 1; x < scoreKeep; x++){
      pattern[x] = sideColor;
    }
    //store the numbies in an array
    //pattern[(sizeof(pattern) / sizeof(int))+1] = sideColor;
  
 } 
  // while (score <= scoreKeep) {
  //   colorBlink(sideColor);
  // }
  // if (score == scoreKeep) {
  //   scoreKeep++;
  // }
  //if passed the level, scoreKeep++


// 1 == rightA, 0 == leftB
void colorBlink(int side) {
  if (side % 2 == 0) { //even 
    for (int i = 0; i < 5; i++) {
      CircuitPlayground.setPixelColor(i, 50, 50, 50);
    }
    //CircuitPlayground.playTone(50, delaySpeed);
    delay(delaySpeed);
    for (int i = 0; i < 5; i++) { 
      CircuitPlayground.setPixelColor(i, 0, 0, 0);
    }
  } else { //odd
    for (int i = 10; i >= 5; i--) {
      CircuitPlayground.setPixelColor(i, 50, 50, 50);
    }
    //CircuitPlayground.playTone(90, delaySpeed);
    delay (delaySpeed);
    for (int i = 10; i >= 5; i--) {
      CircuitPlayground.setPixelColor(i, 0, 0, 0);
    }
  }
}

void slideISR() {
  //want the switch to turn on
  slideFlag = !slideFlag;
}

void buttonISR() {
  buttonFlag = 0;
}