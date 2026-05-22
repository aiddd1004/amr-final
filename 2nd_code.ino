#define CUSTOM_SETTINGS
#define INCLUDE_TERMINAL_MODULE
#include <DabbleESP32.h>

const int rightMotorIN1 = 16; 
const int rightMotorIN2 = 17;
const int leftMotorIN3 = 18;
const int leftMotorIN4 = 19;

void setup() {
  Serial.begin(115200); 
  
  pinMode(rightMotorIN1, OUTPUT);
  pinMode(rightMotorIN2, OUTPUT);
  pinMode(leftMotorIN3, OUTPUT);
  pinMode(leftMotorIN4, OUTPUT);

  stopMotors();

  Dabble.begin("MyVoiceCar");
  Serial.println("Система готова!");
}

void loop() {
  Dabble.processInput();
  controlWithVoice();
}

void controlWithVoice() {
  if (Terminal.available() != 0) {
    String serialdata = Terminal.readString();
    serialdata.toLowerCase();
    
    Serial.print("Команда: ");
    Serial.println(serialdata);

    if (serialdata.indexOf("forward") != -1) {
      moveForward();      
    }
    else if (serialdata.indexOf("backward") != -1 || serialdata.indexOf("back") != -1) {
      moveBackward();    
    }
    else if (serialdata.indexOf("left") != -1) {
      turnLeft();
      delay(600);
      stopMotors();
    }
    else if (serialdata.indexOf("right") != -1) {
      turnRight();
      delay(600);
      stopMotors();
    }
    else if (serialdata.indexOf("dance") != -1) {
      dance();
    }
    else if (serialdata.indexOf("stop") != -1) {
      stopMotors();
    }
  }
}

void moveForward() {
  digitalWrite(rightMotorIN1, HIGH);
  digitalWrite(rightMotorIN2, LOW);
  digitalWrite(leftMotorIN3, LOW);
  digitalWrite(leftMotorIN4, HIGH);
}

void moveBackward() {
  digitalWrite(rightMotorIN1, LOW);
  digitalWrite(rightMotorIN2, HIGH);
  digitalWrite(leftMotorIN3, LOW);   // fixed: swapped vs original
  digitalWrite(leftMotorIN4, HIGH);  // fixed: swapped vs original
}

void turnLeft() {
  digitalWrite(rightMotorIN1, HIGH);
  digitalWrite(rightMotorIN2, LOW);
  digitalWrite(leftMotorIN3, HIGH);
  digitalWrite(leftMotorIN4, LOW);
}

void turnRight() {
  digitalWrite(rightMotorIN1, LOW);
  digitalWrite(rightMotorIN2, HIGH);
  digitalWrite(leftMotorIN3, LOW);
  digitalWrite(leftMotorIN4, HIGH);
}

void stopMotors() {
  digitalWrite(rightMotorIN1, LOW);
  digitalWrite(rightMotorIN2, LOW);
  digitalWrite(leftMotorIN3, LOW);
  digitalWrite(leftMotorIN4, LOW);
}

void dance() {
  Serial.println("Танцую!");
  for (int i = 0; i < 6; i++) {
    turnLeft();
    delay(300);
    stopMotors();
    delay(100);
    turnRight();
    delay(300);
    stopMotors();
    delay(100);
  }
  stopMotors();
  Serial.println("Танец окончен!");
}