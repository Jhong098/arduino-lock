//#include <cmath>
#include <Servo.h>

Servo myservo;

#define joyX A0
#define joyY A1
#define UP 10
#define RIGHT 8
#define DOWN 11
#define LEFT 9

int button = 2;
int buttonState = 0;
int buttonState1 = 0;

int servoPos = 0;

int xOffset = 340;
int yOffset = 687;

enum STATE {
  LOCKED,
  UNLOCKED
};

const int UNLOCK_TIME = 5000;
STATE lockState = LOCKED;

int dir = -1; // STARTING DIRECTION
int lastDir = -1; // SAVED DIRECTION

void setup() {
  pinMode(7,OUTPUT);

  pinMode(8,OUTPUT);
  
  pinMode(9,OUTPUT);
  
  pinMode(10,OUTPUT);

  myservo.attach(13);

  pinMode(button,INPUT);

  Serial.begin(9600);
}
 
void loop() {
  if (lockState == LOCKED) {
    lock();
  } else {
    unlock();
  }
  
 int xValue = analogRead(joyX);
 int yValue = analogRead(joyY);
//   Serial.print(xValue);
//  Serial.print("\t");
//  Serial.println(yValue);

 dir = getDirection(xValue, yValue);
 
 if (dir != -1) {
  digitalWrite(dir, HIGH);
  checkState(dir);
 } else {
  digitalWrite(UP, LOW);
  digitalWrite(RIGHT, LOW);
  digitalWrite(DOWN, LOW);
  digitalWrite(LEFT, LOW);
 }
 delay(100);
 dir = -1;

  buttonState = digitalRead(button);

  if (buttonState == HIGH)
  {
    Serial.println("Switch = High");
    lock();
  }
  
  delay(100);
}

void lock() {
  myservo.write(90);
}

void unlock() {
  myservo.write(0);
  digitalWrite(UP, HIGH);
  digitalWrite(RIGHT, HIGH);
  digitalWrite(DOWN, HIGH);
  digitalWrite(LEFT, HIGH);
  delay(UNLOCK_TIME);
  reset();
}

void checkState(int dir) {
  // UNLOCK PATTERN
  constexpr int pattern [4] = { UP, DOWN, LEFT, RIGHT };
  int TERMINATING_DIR = pattern[3];

  if (lastDir != dir) {
      switch(dir) {
      case pattern[0]:
        if (lastDir != -1) {
          reset();
        } else {
          lastDir = pattern[0];
        }
        break;
      case pattern[1]:
        if (lastDir != pattern[0]) {
          reset();
        } else {
          lastDir = pattern[1];
        }
        break;
      case pattern[2]:
        if (lastDir != pattern[1]) {
          reset();
        } else {
          lastDir = pattern[2];
        }
        break;
      case pattern[3]:
        if (lastDir != pattern[2]) {
          reset();
        } else {
          lastDir = pattern[3];
        }
        break;
      default:
        reset();
    }
  }


  Serial.print(lastDir);

  if (lastDir == TERMINATING_DIR) {
    unlock();
  }
}

void reset() {
  Serial.print("resetting");
  lastDir = -1;
  digitalWrite(UP, LOW);
  digitalWrite(RIGHT, LOW);
  digitalWrite(DOWN, LOW);
  digitalWrite(LEFT, LOW);
}

int getDirection(int xValue, int yValue) {
    // up
  if (abs(yValue-1024)<=10)
  {
    Serial.println("UP");
    return UP;
  }

  // down
  if (xValue<=250 && yValue<=250)
  {
    Serial.println("DOWN");
    return DOWN;
  }
  // left
  if (abs(xValue-0)<=10 && yValue > 650)
  {
    Serial.println("LEFT");
    return LEFT;
  }
  //right
  if (abs(xValue-yOffset)<=10 && abs(yValue-yOffset) <= 10)
  {
    Serial.println("RIGHT");
    return RIGHT;
  }

  if (abs(xValue-xOffset)<=10 && abs(yValue-yOffset)<=10)
  {
    return -1;
  }
}


