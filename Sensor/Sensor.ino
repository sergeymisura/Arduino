
volatile int flag = 0;
volatile unsigned long lastTimestamp = 0;
volatile unsigned long lastTimeBetween = 0;
volatile byte data;
volatile byte buffer[4];
volatile byte ptr = 0;

volatile byte result[4];

void sensorInterrupt() {
  lastTimeBetween = micros() - lastTimestamp;
  lastTimestamp = micros();
  if (lastTimeBetween < 800) {
    if (digitalRead(2) == LOW) {
      data = lastTimeBetween < 400 ? 0 : 1;
      buffer[ptr >> 3] = (buffer[ptr >> 3] << 1) + data;
      ptr++;
      if (ptr == 32) {
        result[0] = buffer[0];
        result[1] = buffer[1];
        result[2] = buffer[2];
        result[3] = buffer[3];
        flag = 1;
      }
    }
  }
  else {
    ptr = 0;
  }
};

void setup() {
  Serial.begin(9600);
  attachInterrupt(0, sensorInterrupt, CHANGE);
}

void loop() {
  if (flag) {
    Serial.print(result[0]);
    Serial.print(' ');
    Serial.print(result[1]);
    Serial.print(' ');
    Serial.print(result[2]);
    Serial.print(' ');
    Serial.print(result[3]);
    Serial.println(' ');
    flag = 0;
  }
}
