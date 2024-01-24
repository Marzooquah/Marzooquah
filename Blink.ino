#include <TM1637Display.h>

  const int TM1637_CLK = 2;
  const int TM1637_DIO = 3;
  const int ECHO_PIN = 4;
  const int TRIG_PIN = 5;

  const float MICROSECONDS_TO_CM = 0.017;
  const int DISPLAY_BRIGHTNESS = 0x0A;

  const float BOX_HEIGHT = 195.0;  // Adjust the box height as needed

  TM1637Display display(TM1637_CLK, TM1637_DIO);

  const int NUM_READINGS = 15;
  float readings[NUM_READINGS];
  int readingsIndex = 0;

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  display.setBrightness(DISPLAY_BRIGHTNESS);
}

void loop() {
  // Triggering the ultrasonic sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  // Reading the duration of the echo pulse
  float duration_us = pulseIn(ECHO_PIN, HIGH, 20000);  // 20,000us timeout (adjust as needed)

  // Handling timeout
  if (duration_us == 0) {
    Serial.println("Timeout occurred");
    return;
  }

  // Calculating distance from duration
  float distance_cm = MICROSECONDS_TO_CM * duration_us;


  // Displaying distance on the TM1637 display
  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  distance_cm = distance_cm + 5;

  distance_cm = BOX_HEIGHT - distance_cm;
 
 if(distance_cm < 70){
  display.clear();
  return;
 }

  if(distance_cm > 70 ){
  distance_cm = distance_cm + 5;
 }

  if(distance_cm > 150 ){
  distance_cm = distance_cm + 5;
 }

  // Return if heigth is too low

  display.showNumberDec(static_cast<int>(distance_cm));

  // Display the average of the readings on the TM1637 display

  //displayAverage();
  delay(50);
  display.clear();
}
