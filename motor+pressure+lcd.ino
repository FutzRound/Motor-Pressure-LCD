//Sample using LiquidCrystal library

#include <LiquidCrystal.h>

// Declare L298N Dual H-Bridge Motor Controller directly since there is not a library to load.

// Motor 1

int dir1PinA = 2;
int dir2PinA = 3;
int speedPinA = 9; // Needs to be a PWM pin to be able to control motor speed

// Initialize the library with the numbers of the interface pins

LiquidCrystal lcd(12, 11, 5, 4, 7, 8);

// Pressure Sensor Definition

float readPressure(int pin) {
        int pressureValue = analogRead(A1);
        float pressure = ((pressureValue / 1024.0) + 0.095) / 0.000009;
        return pressure;
}

void setup() {  // Setup runs once per reset

        // Set up the LCD's number of columns and rows

        lcd.begin(16, 2);
        lcd.clear();

        // Initialize serial communication @ 9600 baud:

        Serial.begin(9600);

        // Define L298N Dual H-Bridge Motor Controller Pins

        pinMode(dir1PinA, OUTPUT);
        pinMode(dir2PinA, OUTPUT);
        pinMode(speedPinA, OUTPUT);

        // Possible to input pinMode for (A1) -- Pressure Sensor to use are variable to control ((dir1PinA/dir2PinA) Motor Output) ?

}

void loop() {

        // Pressure Sensor

        float pressure = readPressure(A1);
        float millibars = pressure / 100;

        // Initialize the Serial interface:

        if (Serial.available() > 0) {


                int inByte = Serial.read();
                int speed(); // Local variable

                switch (inByte) {

                // Define actions with Motor Control / Serial Print / LCD Print

                case '1':

                        // Motor 1 Forward

                        analogWrite(speedPinA, 255);// Sets speed variable via PWM
                        digitalWrite(dir1PinA, LOW);
                        digitalWrite(dir2PinA, HIGH);
                        Serial.println("Motor 1 Forward"); // Prints out “Motor 1 Forward” on the serial monitor
                        Serial.println("   "); // Creates a blank line printed on the serial monitor
                        Serial.println();
                        Serial.print("Pressure = ");
                        Serial.print(pressure);
                        Serial.println(" pascals ");
                        Serial.print("Pressure = ");
                        Serial.print(millibars);
                        Serial.println(" millibars ");
                        Serial.println();

                        // LCD Display Input Settings

                        lcd.clear();
                        lcd.setCursor(0,0); // Writes text for top row
                        lcd.print("Pressure = "); // Prints Pressure Sensor Val to LCD
                        lcd.print(pressure);
                        lcd.print(millibars);
                        lcd.setCursor(0,1); // Writes text for bottom row
                        lcd.print("Motor 1 Forward");
                        break;

                case '2':

                        // Motor 1 Stop (Freespin)

                        analogWrite(speedPinA, 0);
                        digitalWrite(dir1PinA, LOW);
                        digitalWrite(dir2PinA, HIGH);
                        Serial.println("Motor 1 Stop");
                        Serial.println("   ");
                        Serial.println();
                        Serial.print("Pressure = ");
                        Serial.print(pressure);
                        Serial.println(" pascals ");
                        Serial.print("Pressure = ");
                        Serial.print(millibars);
                        Serial.println(" millibars ");
                        Serial.println();

                        // LCD Display Input Settings

                        lcd.clear();
                        lcd.setCursor(0,0); // Writes text for top row
                        lcd.print("Pressure = "); // Prints Pressure Sensor Val to LCD
                        lcd.print(pressure);
                        lcd.setCursor(0,1); // Writes text for bottom row
                        lcd.print("Motor 1 Stop");
                        break;

                case '3':

                        // Motor 1 Reverse

                        analogWrite(speedPinA, 255);
                        digitalWrite(dir1PinA, HIGH);
                        digitalWrite(dir2PinA, LOW);
                        Serial.println("Motor 1 Reverse");
                        Serial.println("   ");
                        Serial.println();
                        Serial.print("Pressure = ");
                        Serial.print(pressure);
                        Serial.println(" pascals ");
                        Serial.print("Pressure = ");
                        Serial.print(millibars);
                        Serial.println(" millibars ");
                        Serial.println();

                        // LCD Display Input Settings

                        lcd.clear();
                        lcd.setCursor(0,0); // Writes text for top row
                        lcd.print("Pressure = "); // Prints Pressure Sensor Val to LCD
                        lcd.print(pressure);
                        lcd.setCursor(0,1); // Writes text for bottom row
                        lcd.print("Motor 1 Reverse");
                        break;

                default:

                        // Turn all the connections off if an unmapped key is pressed:

                        for (int thisPin = 2; thisPin < 11; thisPin++) {
                                digitalWrite(thisPin, LOW);
                        }
                }
        }
}
