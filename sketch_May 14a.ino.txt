int vb=D4;
void setup() {
 // pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  pinMode(vb, INPUT);
Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
int abc= digitalRead(vb);
Serial.print(abc);
delay(1000);

Serial.print("my value\n");
delay(1000);


}
