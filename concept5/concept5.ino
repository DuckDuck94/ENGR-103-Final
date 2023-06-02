#include <Adafruit_CircuitPlayground.h>

volatile int modeControl = 0;
const int buttonAPin = 4;
const int buttonBPin = 5;
int slidePin = 7;

volatile bool A_flag = false;
volatile bool B_flag = false;
volatile bool slide_flag = false;

int val;

void setup() {
  CircuitPlayground.begin();
  // put your setup code here, to run once:
  randomSeed(analogRead(0));
  Serial.begin(9600);
  val = digitalRead(slidePin); //prints 0
  pinMode(buttonAPin, INPUT_PULLDOWN);
  pinMode (buttonBPin, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(buttonAPin), buttonA, RISING);
  attachInterrupt(digitalPinToInterrupt(buttonBPin), buttonB, RISING);
  attachInterrupt(digitalPinToInterrupt(slidePin), slideISR, CHANGE);

}

void loop() {
  //make a loop for the case so that it goes from 0-5 and loops back around
  if (A_flag) {
    delay(200);
    modeControl--;
    if (modeControl < 0) {
      modeControl = 5;
    }
    A_flag = false;
  }
  if(B_flag) {
    delay(200);
    modeControl++;
    if (modeControl > 6) {
      modeControl = 0;
    }
    B_flag = false;
  }

  if (slide_flag){
    val = digitalRead(slidePin);
    slide_flag = false;
  }
  
  if (val == 0) {//switch is on
    //delay(200);
    switch(modeControl){
    case 0:
      sparkle(50);
      break;
    case 1:
      rainbowCycle(100,10);
      break;
    case 2:
      circle(200);
      break;
    case 3:
      blink(200);
      break;
    case 4:
      bounce(200);
      break;
    case 5:
      mirror(200);
      break;
    default:
      break;
    }
    
  } else {
      CircuitPlayground.clearPixels();
  }

}

void slideISR() {
  slide_flag = true;
}

void buttonA() {
  A_flag = true; //raises flag/true
}

void buttonB() {
  B_flag = true; //raises flag/true
}

void mirror(int time) {
  int i = 0;
  int k = 9;
  while (i < 5){
    CircuitPlayground.setPixelColor(i, 255, 255, 255);
    CircuitPlayground.setPixelColor(k, 255, 255, 255);
    delay(time/2);
    i++;
    k--;
  }
  while (i >= 0){
    CircuitPlayground.setPixelColor(i, 0, 0, 0);
    CircuitPlayground.setPixelColor(k, 0, 0, 0);
    delay(time/2);
    i--;
    k++;
  }
}

void bounce(int time) {
  for (int i = 0; i < 10; i++) {
    CircuitPlayground.setPixelColor(i, 255, 255, 255);
    delay(time);
    //CircuitPlayground.setPixelColor(i, 0, 0, 0);
    delay(time/2);
  }
  for (int i = 9; i >= 0; i--) {
    //CircuitPlayground.setPixelColor(i, 255, 255, 255);
    delay(time/2);
    CircuitPlayground.setPixelColor(i, 0, 0, 0);
    delay(time/2);
    }
  delay(time);
}

void blink (int time){
  for(int i = 0; i < 9; i+=2) {
    CircuitPlayground.setPixelColor(i, 255, 255, 255);
  }
  delay(time/2);
  for(int i = 0; i < 9; i+=2) {
    CircuitPlayground.setPixelColor(i, 0, 0, 0);
  }
  delay(time/2);
  for(int i = 1; i < 10; i+=2) {
    CircuitPlayground.setPixelColor(i, 255, 255, 255);
  }
  delay(time/2);
  for(int i = 1; i < 10; i+=2) {
    CircuitPlayground.setPixelColor(i, 0, 0, 0);
  }
}

void circle(int time) {
  for (int i = 0; i < 9; i += 2) {
    CircuitPlayground.setPixelColor(i, 255, 255, 255);
    delay(time/2);
    CircuitPlayground.setPixelColor(i+1, 255, 255, 255);
    CircuitPlayground.setPixelColor(i, 0, 0, 0);
    delay(time/2);
    CircuitPlayground.setPixelColor(i+1, 0, 0, 0);
  }
}

void sparkle (int flash) {
  int LED_num = random (10);
  CircuitPlayground.setPixelColor(LED_num, 255, 255, 255);
  delay(flash/2);
  CircuitPlayground.setPixelColor(LED_num, 0, 0, 0);
  delay(flash/2);
}

void rainbowCycle(int currentSpeed, int stripLen) {

  // Make an offset based on the current millisecond count scaled by the current speed.

  uint32_t offset = millis() / currentSpeed;

  // Loop through each pixel and set it to an incremental color wheel value.

  for(int i=0; i<10; ++i) {

    CircuitPlayground.setPixelColor(i, CircuitPlayground.colorWheel(((i * 256 / stripLen) + offset) & 255));

  }

}

