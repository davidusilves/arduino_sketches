 #define normal_time 500

int level;
void setup() {
  pinMode(A0, INPUT);
  Serial.begin(9600);
  pinMode(2, OUTPUT);
}

void loop() {
  level = analogRead(A0);
  delay(normal_time);
  if (level < 200 ) {
    Serial.println("no light");
    digitalWrite(2, HIGH);
  }
 
  else  {
    Serial.println(level);
    digitalWrite(2, LOW);
  }
}
