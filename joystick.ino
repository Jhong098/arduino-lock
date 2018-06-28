//#include <cmath>

#define joyX A0
#define joyY A1
#define UP 10
#define RIGHT 8
#define DOWN 11
#define LEFT 9

int button=2;
int buttonState = 0;
int buttonState1 = 0;

 int xOffset = 340;
 int yOffset = 687;

void setup() {
  pinMode(7,OUTPUT);

  pinMode(8,OUTPUT);
  
  pinMode(9,OUTPUT);
  
  pinMode(10,OUTPUT);


  pinMode(button,INPUT);
  digitalWrite(button, HIGH);
  Serial.begin(9600);
}
 
void loop() {
 int xValue = analogRead(joyX);
 int yValue = analogRead(joyY);
//   Serial.print(xValue);
//  Serial.print("\t");
//  Serial.println(yValue);

 int dir = getDirection(xValue, yValue);
 if (dir != -1) {
  digitalWrite(dir, HIGH);
 } else {
  digitalWrite(UP, LOW);
  digitalWrite(RIGHT, LOW);
  digitalWrite(DOWN, LOW);
  digitalWrite(LEFT, LOW);
 }
 Serial.print(dir);
 delay(100);
 dir = -1;
//
  
//  buttonState = digitalRead(button);
//  Serial.println(buttonState);
  


//  if (buttonState == LOW)
//  {
//    Serial.println("Switch = High");
//    digitalWrite(7, HIGH);
//  }
//  else{digitalWrite(7, LOW);}
//  buttonState1 = digitalRead(7);
  delay(100);
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


