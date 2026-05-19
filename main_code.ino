#define CUSTOM_SETTINGS
#define INCLUDE_TERMINAL_MODULE
#include <DabbleESP32.h>

// Настройка пинов (теперь они объявлены и ошибок не будет)
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

  stopMotors(); // Изначально стоим

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
    else if (serialdata.indexOf("backward") != -1 || serialdata == "back") {
      moveBackward();    
    }
    else if (serialdata.indexOf("left") != -1) {
      turnLeft();
      delay(600);    // Робот повернет 0.6 сек
      stopMotors();   // И остановится, чтобы не крутиться вечно
    }
    else if (serialdata.indexOf("right") != -1) {
      turnRight();
      delay(600);    // Робот повернет 0.6 сек
      stopMotors();   // И остановится
    }
    else if (serialdata.indexOf("stop") != -1) {
      stopMotors();
    }
  }
}

// ФУНКЦИИ ДВИЖЕНИЯ
void moveForward() {
  digitalWrite(rightMotorIN1, HIGH);
  digitalWrite(rightMotorIN2, LOW);
  digitalWrite(leftMotorIN3, LOW);
  digitalWrite(leftMotorIN4, HIGH);
}

void moveBackward() {
  digitalWrite(rightMotorIN1, LOW);
  digitalWrite(rightMotorIN2, HIGH);
  digitalWrite(leftMotorIN3, HIGH);
  digitalWrite(leftMotorIN4, LOW);
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