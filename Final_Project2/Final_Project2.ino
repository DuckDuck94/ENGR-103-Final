#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>

int buttons[10] = {0,0,0,0,0,0,0,0,0,0}; //store the pattern
int pattern[10] = {0,0,0,0,0,0,0,0,0,0}; //store the pattern
int sideColor;
int level = 0;

int slidePin = 7;
int slideFlag = 0; 
int delaySpeed = 500;
int buttonA = 0;
int buttonB = 0;
int storePattern = 0;

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
  attachInterrupt(digitalPinToInterrupt(slidePin), slideISR, CHANGE);
  //attachInterrupt(digitalPinToInterrupt(buttonBPin), buttonISR, RISING);
}

void loop() {
  Serial.println("Flip the switch to START!");
  int deathCount = 3; 
  level = 0;
  while (slideFlag && (deathCount >= 0)) { //slide is on
    Serial.print("You're on level ");
    Serial.print(level);
    Serial.println("!");

    sideColor = random (2); //picks what side the lights will turn on
    colorBlink(sideColor); //plays out blink pattern

    //making random numbers so that buttons and side colors can match
    Serial.println(sideColor);
    if (sideColor == 1){
      pattern[level] = 5;
    } else if (sideColor == 0){
      pattern[level] = 4;
    }

    //signal that they can press the button
    CircuitPlayground.playTone(30, 200);
    CircuitPlayground.playTone(30, 200);
    //gives time to check button presses
    //delay(delaySpeed*5);

    //need to store NEW INPUT && CRETE NEW ARRAY
    for (int i = 0; pattern[i] != 0; i++){
      delay(500);
      Serial.println("Press Button");
      buttonA = CircuitPlayground.rightButton(); //returns a 1 or 0
      delay(200);
      if (buttonA){
        storePattern = 5;
        Serial.println("Right button pressed");
      }
      buttonB = CircuitPlayground.leftButton(); //returns a 1 or 0
      delay(200);
      if (buttonB){
        storePattern = 4;
        Serial.println("Left button pressed");
      }
      delay(500);
      buttons[i] = storePattern;
      Serial.println("Button Press End");
    }

    //delay(delaySpeed*((level+1)*5)); //player has to press button within this specific time frame for it to gather input

    //then compare pattern adn button array 
    for (int i = 0; pattern[i] != 0; i++){
      Serial.print("Print Pattern: ");
      Serial.println(pattern[i]);

      Serial.print("Input: ");
      Serial.println(buttons[i]);

      if (pattern[i] != buttons[i]){
        deathCount--;
      }
    }
    Serial.print("Death Count = ");
    Serial.print(deathCount);
    Serial.println("!");
    level++;
    if (level % 3 == 0){
      delaySpeed -= 25;
    }
  }

  if (deathCount <= 0) {
    Serial.println("Fin.");
    Serial.println("Final level reached: ");
    Serial.print(level);
    Serial.println("Flip the switch to START!");
    //end game
    slideISR(); //requires you to turn on teh game again
  }
  delay(700);
}

void slideISR() {
  //want the switch to turn on
  slideFlag = !slideFlag;
}

// void buttonISR() {
//   buttonFlag = 0;
// }

// 1 == rightA, 0 == leftB
void colorBlink(int side) {
  if (side % 2 == 0) { //even & left
    for (int i = 0; i < 5; i++) {
      CircuitPlayground.setPixelColor(i, 255, 102, 255); //pink
    }
    CircuitPlayground.playTone(50, delaySpeed);
    delay(delaySpeed);
    for (int i = 0; i < 5; i++) { 
      CircuitPlayground.setPixelColor(i, 0, 0, 0);
    }
  } else { //odd & right
    for (int i = 10; i >= 5; i--) {
      CircuitPlayground.setPixelColor(i, 102, 178, 255); //blue
    }
    CircuitPlayground.playTone(90, delaySpeed);
    delay (delaySpeed);
    for (int i = 10; i >= 5; i--) {
      CircuitPlayground.setPixelColor(i, 0, 0, 0);
    }
  }
}