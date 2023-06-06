#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>

int slidePin = 7; //the switch
int level = 0;
bool slide = 0;
volatile bool slideFlag = 0; //slide is automatically on
bool buttonA = 0;
bool buttonB = 0;
int sideColor; 
int score = 0;
int scoreKeep = 0;
int delaySpeed = 300;

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
  pinMode(LED_BUILTIN, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(slidePin), slideISR, CHANGE);
}

void loop() {
  if (slideFlag) { //if turned on
    sideColor = random (2);
    colorBlink(sideColor);
    //give them time to input buttons
    delay(delaySpeed*2);
    buttonA = CircuitPlayground.rightButton(); //returns a 1 or 0
    //Serial.println(buttonA);
    buttonB = CircuitPlayground.leftButton(); //returns a 1 or 0
    //Serial.println(buttonB);
    Serial.println(sideColor);
    delay(500);
    //store the numbies in an array
    
  }
  
  // while (score <= scoreKeep) {
  //   colorBlink(sideColor);
  // }
  // if (score == scoreKeep) {
  //   scoreKeep++;
  // }
  //if passed the level, scoreKeep++
}

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
  } else {
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