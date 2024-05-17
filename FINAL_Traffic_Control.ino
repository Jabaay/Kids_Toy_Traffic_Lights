#include <LiquidCrystal.h>

// Define pin numbers
const int redLED = 2;
const int yellowLED = 3;
const int greenLED = 4;
const int redButton = 7;
const int greenButton = 8;

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

  // Initialize LCD
  lcd.begin(16, 2);

  // Display initial message
  lcdPrint("Do not Cross"); // Assuming starting state is no crossing
}

void loop() {
  // Check if red button is pressed
  if (digitalRead(redButton) == LOW) {
    // Activate red traffic light
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, HIGH);
    // Update LCD
    lcdPrint("Cross");
    delay(10000); // Red light duration: 10 seconds
  }
  
  // Check if green button is pressed
  if (digitalRead(greenButton) == LOW) {
    // Activate green traffic light
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, HIGH);
    // Update LCD
    lcdPrint("Do Not Cross");
    delay(10000); // Green light duration: 10 seconds
  }

  // Automatic light switching if no buttons are pressed
  if (digitalRead(redButton) == HIGH && digitalRead(greenButton) == HIGH) {
    // Activate vehicle traffic sequence
    activateVehicleTraffic();
  }
}

void activateVehicleTraffic() {
  // Vehicle traffic sequence
  digitalWrite(greenLED, HIGH);
  lcdPrint("Do not Cross");
  delay(10000); // Green light duration: 10 seconds
  
  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, HIGH);
  lcdPrint("Do Not Cross");
  delay(3000); // Yellow light duration: 3 seconds
  
  digitalWrite(yellowLED, LOW);
  digitalWrite(redLED, HIGH);
  lcdPrint("Do not Cross");
  delay(10000); // Red light duration: 10 seconds
  digitalWrite(redLED, LOW);
}

// Function to print a message on the LCD
void lcdPrint(String message) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(message);
}
