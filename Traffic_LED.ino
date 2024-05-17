// Define pin numbers
const int redLED = 2;
const int yellowLED = 3;
const int greenLED = 4;
const int redButton = 7;
const int greenButton = 8;

void setup() {
  // Initialize LED pins as output
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  
  // Initialize button pins as input with pull-up resistors
  pinMode(redButton, INPUT_PULLUP);
  pinMode(greenButton, INPUT_PULLUP);
}

void loop() {
  // Check if red button is pressed
  if (digitalRead(redButton) == LOW) {
    // Activate vehicle traffic sequence
    activateVehicleTraffic();
  }
  
  // Check if green button is pressed
  if (digitalRead(greenButton) == LOW) {
    // Activate pedestrian crossing sequence
    activatePedestrianCrossing();
  }
}

void activateVehicleTraffic() {
  // Vehicle traffic sequence
  digitalWrite(greenLED, HIGH);
  delay(10000); // Green light duration: 10 seconds
  digitalWrite(greenLED, LOW);
  
  digitalWrite(yellowLED, HIGH);
  delay(2000); // Yellow light duration: 2 seconds
  digitalWrite(yellowLED, LOW);
  
  digitalWrite(redLED, HIGH);
  delay(10000); // Red light duration: 10seconds
  digitalWrite(redLED, LOW);
}
