// Right motor pin
int pinAO1 = 4;
int pinAO2 = 5;
int pinAO3 = 6;

// Left motor pin
int pinBO1 = 1;
int pinBO2 = 2;
int pinBO3 = 3;

const int trig = 9;// Sensor pin number
const int echo = 8;// Sensor pin number

long duration, cm;
 
void setup() {
  pinMode(pinAO1, OUTPUT);
  pinMode(pinAO2, OUTPUT);
  pinMode(pinAO3, OUTPUT);

  pinMode(pinBO1, OUTPUT);
  pinMode(pinBO2, OUTPUT);
  pinMode(pinBO3, OUTPUT);

  boolean beginDelivery = false;
  Serial.begin(9600); // Initialize serial communications
}

void loop() { 
  ping();
  forward(50);
  if(cm < 15){
    brake();
    reverse(100);
    turn(45);
  }
}
  
  


void ping(){
  // establish variables for duration of the ping,
  // and the distance result in inches and centimeters  

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(echo, OUTPUT);
  digitalWrite(echo, LOW);
  delayMicroseconds(2);
  digitalWrite(echo, HIGH);
  delayMicroseconds(5);
  digitalWrite(echo, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(trig, INPUT);
  duration = pulseIn(trig, HIGH);

  // convert the time into a distance  
  cm = microsecondsToCentimeters(duration);
  
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  delay(100);
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
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

//POSITIVE degree will turn to the RIGHT
//NEGATIVE degree will turn to the LEFT
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

