void forward(int speed) {
  digitalWrite(pinAO1, HIGH);
  digitalWrite(pinAO2, LOW);
  digitalWrite(pinBO1, HIGH);
  digitalWrite(pinBO2, LOW);

  int  sig map(speed, 1 , 100, 0, 255);
  analogWrite(pinAO3, sig);
  analogWrite(pinBO3, sig);
}

void reverse(int speed) {
  digitalWrite(pinAO1, LOW);
  digitalWrite(pinAO2, HIGH);
  digitalWrite(pinBO1, LOW);
  digitalWrite(pinBO2, HIGH);

  int  sig map(speed, 1 , 100, 0, 255);
  analogWrite(pinAO3, sig);
  analogWrite(pinBO3, sig);
}

//POSITIVE degree will turn to the RIGHT
//NEGATIVE degree will turn to the LEFT
void turn(int degrees) {
  //time for 360
  int t = 10
  int[] state = [digitalRead(pinAO1), digitalRead(pinAO2),
                digitalRead(pinBO1), digitalRead(pinBO2)]
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

  delay(abs(degrees*t))

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
