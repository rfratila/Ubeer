// Right motor pin
const int pinAO1 = 4;
const int pinAO2 = 5;
const int pinAO3 = 6;

// Left motor pin
const int pinBO1 = 1;
const int pinBO2 = 2;
const int pinBO3 = 3;

const int pinLED = 13;

const int pinEchoTrigger = 9;// Sensor pin number
const int pinEchoResponse = 8;// Sensor pin number
 
void setup() {
  pinMode(pinAO1, OUTPUT);
  pinMode(pinAO2, OUTPUT);
  pinMode(pinAO3, OUTPUT);

  pinMode(pinBO1, OUTPUT);
  pinMode(pinBO2, OUTPUT);
  pinMode(pinBO3, OUTPUT);

  pinMode(pinLED, OUTPUT);

  pinMode(pinEchoTrigger, OUTPUT);
  pinMode(pinEchoResponse, INPUT);
    
  // Startup LED flash
  digitalWrite(pinLED, HIGH);   
  delay(5000);              
  digitalWrite(pinLED, LOW);
  delay(500);  
  digitalWrite(pinLED, HIGH);   
  delay(500);              
  digitalWrite(pinLED, LOW);
}

void loop() { 
  unsigned long distance = ping();
  forward(50);
  if (distance < 15) {
    brake();
    reverse(100);
    turn(45);
  }
}

// Sends a ping and returns in cm how far an obstacle is
unsigned long ping() {
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(pinEchoTrigger, LOW);
  delayMicroseconds(2);
  digitalWrite(pinEchoTrigger, HIGH);
  delayMicroseconds(5);
  digitalWrite(pinEchoTrigger, LOW);

  unsigned long duration = pulseIn(pinEchoResponse, HIGH);  
  unsigned long distance = duration / 58.2;
  
  delay(100);
  return distance;
}

void forward(int speed) {
  digitalWrite(pinAO1, HIGH);
  digitalWrite(pinAO2, LOW);
  digitalWrite(pinBO1, HIGH);
  digitalWrite(pinBO2, LOW);

  int  sig = map(speed, 1 , 100, 0, 255);
  analogWrite(pinAO3, sig);
  analogWrite(pinBO3, sig);
}

void reverse(int speed) {
  digitalWrite(pinAO1, LOW);
  digitalWrite(pinAO2, HIGH);
  digitalWrite(pinBO1, LOW);
  digitalWrite(pinBO2, HIGH);

  int  sig = map(speed, 1 , 100, 0, 255);
  analogWrite(pinAO3, sig);
  analogWrite(pinBO3, sig);
}

// POSITIVE degrees will turn to the RIGHT
// NEGATIVE degrees will turn to the LEFT
void turn(int degrees) {
  //time for 360
  int t = 10;
  int state[] = {digitalRead(pinAO1), digitalRead(pinAO2),digitalRead(pinBO1), digitalRead(pinBO2)};
  brake();
  
  if (degrees > 0){
    digitalWrite(pinAO1, HIGH);
    digitalWrite(pinAO2, LOW);
    digitalWrite(pinBO1, LOW);
    digitalWrite(pinBO2, HIGH);
  } else {
    digitalWrite(pinAO1, LOW);
    digitalWrite(pinAO2, HIGH);
    digitalWrite(pinBO1, HIGH);
    digitalWrite(pinBO2, LOW);
  }
  
  analogWrite(pinAO3, 255);
  analogWrite(pinBO3, 255);

  delay(abs(degrees*t));

  digitalWrite(pinAO1, state[0]);
  digitalWrite(pinAO2, state[1]);
  digitalWrite(pinBO1, state[2]);
  digitalWrite(pinBO2, state[3]);

  analogWrite(pinAO3, 255);
  analogWrite(pinBO3, 255);
}

void brake() {
  analogWrite(pinAO3, 0);
  analogWrite(pinBO3, 0);
}

