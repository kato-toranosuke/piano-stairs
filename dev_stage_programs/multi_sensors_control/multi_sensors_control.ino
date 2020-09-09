#define nSensor 4

int echoPin[nSensor] = {2,5,8,11};
int trigPin[nSensor] = {3,6,9,12};
int Duration;
float Distance;

void setup() {
  Serial.begin(9600);
  for (int i=0; i<nSensor; i++){
    pinMode(trigPin[i], OUTPUT);
    pinMode(echoPin[i], INPUT);
  }
}

void loop() {
  for(int i=0; i < nSensor; i++){
    digitalWrite(trigPin[i], LOW);
    delayMicroseconds(1);
    digitalWrite(trigPin[i], HIGH);
    delayMicroseconds(11);
    digitalWrite(trigPin[i], LOW);
    
    Duration = pulseIn(echoPin[i], HIGH);
    if (Duration>0) {
      Distance = Duration/2;
      Distance = Distance*340*100/1000000; // ultrasonic speed is 340m/s = 34000cm/s = 0.034cm/us 
      //Serial.print(i);
      //Serial.print(": ");
      Serial.print(Distance);
      Serial.print(" cm, ");
    }

    delay(3);
  }
  Serial.println();
}
