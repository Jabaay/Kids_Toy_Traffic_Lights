#include <LiquidCrystal.h>

// Define pin numbers
const int redLED = 2;
const int yellowLED = 3;
const int greenLED = 4;
const int redButton = 7;
const int greenButton = 8;

const int pedestrianButton = 9;
const int pedestrianRedLED = 5;
const int pedestrianGreenLED = 6;
const int pedestrianRedWalkLED = 10;
const int pedestrianGreenWalkLED = 11;

// Define LCD properties
const int rs = 12;
const int en = 13;
const int d4 = A0;
const int d5 = A1;
const int d6 = A2;
const int d7 = A3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

bool pedestrianCrossing = false;

void setup() {
  // Initialize LED pins as output
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  
  // Initialize button pins as input with pull-up resistors
  pinMode(redButton, INPUT_PULLUP);
  pinMode(greenButton, INPUT_PULLUP);

  // Initialize button pin as input with pull-up resistor
  pinMode(pedestrianButton, INPUT_PULLUP);

  // Initialize LED pins as output
  pinMode(pedestrianRedLED, OUTPUT);
  pinMode(pedestrianGreenLED, OUTPUT);
  pinMode(pedestrianRedWalkLED, OUTPUT);
  pinMode(pedestrianGreenWalkLED, OUTPUT);

  // Initialize LCD
  lcd.begin(16, 2);

  // Display initial message
  lcdPrint("Do not Cross"); // Assuming starting state is no crossing
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

  // Check if pedestrian button is pressed
  if (digitalRead(pedestrianButton) == LOW) {
    // Activate pedestrian crossing
    pedestrianCrossing = true;
    activatePedestrianCrossing();
  } else {
    // Pedestrian button not pressed, reset crossing status
    pedestrianCrossing = false;
    resetPedestrianCrossing();
  }
}

void activateVehicleTraffic() {
  // Vehicle traffic sequence
  digitalWrite(greenLED, HIGH);
  delay(5000); // Green light duration: 5 seconds
  digitalWrite(greenLED, LOW);
  
  digitalWrite(yellowLED, HIGH);
  delay(2000); // Yellow light duration: 2 seconds
  digitalWrite(yellowLED, LOW);
  
  digitalWrite(redLED, HIGH);
  delay(5000); // Red light duration: 5 seconds
  digitalWrite(redLED, LOW);
}

void activatePedestrianCrossing() {
  // Display message on LCD
  lcdPrint("Cross");

  // Activate pedestrian red light and green walk light
  digitalWrite(pedestrianRedLED, HIGH);
  digitalWrite(pedestrianGreenWalkLED, HIGH);
  delay(5000); // Pedestrian crossing duration: 5 seconds

  // Flash pedestrian red walk LED
  for (int i = 0; i < 5; i++) {
    digitalWrite(pedestrianRedWalkLED, HIGH);
    delay(500);
    digitalWrite(pedestrianRedWalkLED, LOW);
    delay(500);
  }

  // Turn off pedestrian green walk light
  digitalWrite(pedestrianGreenWalkLED, LOW);

  // Activate pedestrian green light
  digitalWrite(pedestrianGreenLED, HIGH);
}

void resetPedestrianCrossing() {
  // Display message on LCD
  lcdPrint("No Cross");

  // Turn off pedestrian lights
  digitalWrite(pedestrianRedLED, LOW);
  digitalWrite(pedestrianGreenLED, LOW);
  digitalWrite(pedestrianRedWalkLED, LOW);
  digitalWrite(pedestrianGreenWalkLED, LOW);
}

// Function to print a message on the LCD
void lcdPrint(String message) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(message);
}
