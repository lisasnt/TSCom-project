const int trigPin = 2;
const int echoPin = 3;

volatile unsigned long startTime = 0; //Use volatile for varaibles changed by interupts
volatile unsigned long endTime = 0;
volatile bool pulseReceived = false;

float distance = 0.0;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  attachInterrupt(digitalPinToInterrupt(echoPin), handleEcho, CHANGE);

  Serial.begin(9600);

  Serial.println("Init done!");
}

void loop() {
  //Start the Arduino Echo by sending a 10us pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  if (pulseReceived) {
    pulseReceived = false;

    unsigned long duration = endTime - startTime;
    distance = (duration * 0.0343) / 2;
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  }

  delay(100);
}

// Interrupt Service Routine (ISR)
void handleEcho() {
  if (digitalRead(echoPin) == HIGH) {
    // Rising edge detected: Record the start time
    startTime = micros();
  } else {
    // Falling edge detected: Record the end time
    endTime = micros();
    pulseReceived = true; // Set the flag
  }
}