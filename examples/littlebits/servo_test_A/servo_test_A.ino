void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(5,0);
  delay(1000);
  analogWrite(5,90);
  delay(1000);
  analogWrite(5,200);
  delay(1000);
  analogWrite(5,300);
}
