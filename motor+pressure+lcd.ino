// Sample using LiquidCrystal library

#include <LiquidCrystal.h>

// Declare L298N Dual H-Bridge Motor Controller directly since there is not a library to load

// Motor 1

int dir1PinA = 2;
int dir2PinA = 3;
int speedPinA = 9; // Needs to be a PWM pin to be able to control motor speed


// Constants

const int buttonFwr = 13;
const int buttonOff = 10;
const int buttonRvr = 6;

// Variables

int buttonFwrState = 0;
int buttonOffState = 0;
int buttonRvrState = 0;

// Initialize the library with the numbers of the interface pins

LiquidCrystal lcd (12, 11, 5, 4, 7, 8);

// Stores time for milli() function **replaces delay(), critical software function**

unsigned long interval = 400; // The time we need to wait
unsigned long previousMillis = 0; //  Millis() returns an unsigned long

// Pressure Sensor Definition

float readPressure(int pin)

{
        int pressureValue = analogRead(A1);
        float pressure = ((pressureValue / 1024.0) + 0.095) / 0.000009;
        return pressure;
}


// boolean claims (True or False)

bool forwardstate = false;
bool reversestate = false;

void setup()

{
        // Set up the LCD's number of columns and rows

        lcd.begin(16, 2);
        lcd.clear();

        // Initialize serial communication @ 9600 baud:

        Serial.begin(9600);

        // Define L298N Dual H-Bridge Motor Controller Pins

        pinMode(dir1PinA, OUTPUT);
        pinMode(dir2PinA, OUTPUT);
        pinMode(speedPinA, OUTPUT);

        // Define Pushbutton Pins

        pinMode(buttonFwr, INPUT);
        pinMode(buttonOff, INPUT);
        pinMode(buttonRvr, INPUT);
}

void loop()

{

        //Debugging
        Serial.println(reversestate);

        // Digital States of Pushbuttons

        buttonFwrState = digitalRead(buttonFwr);
        buttonOffState = digitalRead(buttonOff);
        buttonRvrState = digitalRead(buttonRvr);

        // Pressure Sensor

        float pressure = readPressure(A1);
        float millibars = pressure / 100;
        float kilopascal = pressure / 1000;

        // Constant LCD Display of Pressure Value (Regardless of Functions)

        unsigned long currentMillis = millis();
        if ((unsigned long)(currentMillis - previousMillis) >= interval) // ((time since last screen refresh - 0) >= 400) measured in milliseconds

        {
                lcd.setCursor(0,0); // Writes text for top row
                lcd.print("P= "); // Prints Pressure Sensor Val to LCD
                lcd.print(kilopascal);
                lcd.print( " kPa "); // Displays Pressure Value in Pascals (Pa)
                previousMillis = millis();
        }

        // Inflate Button Functions

        if (((forwardstate == false) && (buttonFwrState == HIGH)) || (forwardstate == true))

        {
                Serial.println("hello world."); // Debugging Easter Egg
                forwardstate = true;

                // Runs motor until pressure reaches max pressure

                if (pressure < 89999.00)         // Setting PressMAX to 100kPa

                {
                        analogWrite(speedPinA, 255);           // Sets speed variable via PWM
                        digitalWrite(dir1PinA, LOW);
                        digitalWrite(dir2PinA, HIGH);

                        // Serial Display

                        Serial.println("Motor 1 Forward");         // Prints out “Motor 1 Forward” on the serial monitor
                        Serial.println("   ");         // Creates a blank line printed on the serial monitor
                        Serial.println();
                        Serial.print("Pressure = ");
                        Serial.print(pressure);
                        Serial.println(" pascals ");
                        Serial.print("Pressure = ");
                        Serial.print(millibars);
                        Serial.println(" millibars ");
                        Serial.println();

                        //LCD Display Input Settings

                        lcd.setCursor(0,1);         // Writes text for bottom row
                        lcd.print("Motor 1 Forward    ");
                }

                if (pressure > 90000.00 && pressure < 100000.00)

                {
                        analogWrite(speedPinA, 100); // Sets speed variable via PWM
                        digitalWrite(dir1PinA, LOW);
                        digitalWrite(dir2PinA, HIGH);
                        lcd.setCursor(0,1);
                        lcd.print("Half Speed ****");
                }
                // Stops motor once pressure reaches max value

                else if (pressure > 100001.00)

                {

                        analogWrite(speedPinA, 0);         // Sets speed variable via PWM
                        digitalWrite(dir1PinA, LOW);
                        digitalWrite(dir2PinA, LOW);
                        Serial.println("Motor 1 Forward");         // Prints out “Motor 1 Forward” on the serial monitor
                        Serial.println();
                        Serial.print("Pressure = ");
                        Serial.print(pressure);
                        Serial.println(" pascals ");
                        Serial.println();
                        Serial.println("****Pressure Successfully Reached****");
                        Serial.println();
                        Serial.println(reversestate); // reversestate debugging


                        // LCD Display Input Settings

                        lcd.setCursor(0,1);         // Writes text for bottom row
                        lcd.print("PRESSURE REACHED    ");
                }
        }

        if ((forwardstate == true) && ((buttonOffState == HIGH) || (forwardstate == false)))

        {
                forwardstate = false;
                analogWrite(speedPinA, 0);
                digitalWrite(dir1PinA, LOW);
                digitalWrite(dir2PinA, LOW);

                // Debugging
                Serial.println(forwardstate);
                Serial.println(reversestate);
        }

// Off Button Functions

        if (buttonOffState == HIGH)

        {
                // Motor 1 Stop (Freespin)

                analogWrite(speedPinA, 0);
                digitalWrite(dir1PinA, LOW);
                digitalWrite(dir2PinA, HIGH);

                // Serial Display

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

                lcd.setCursor(0,1);         // Writes text for bottom row
                lcd.print("Motor 1 Stop     ");
        }

// Deflate Button Functions

        if (((reversestate == false) && (buttonRvrState == HIGH)) || (reversestate == true))

        {
                reversestate = true;

                // Motor 1 Reverse

                if (pressure > 100000.00)

                {
                        analogWrite(speedPinA, 255);
                        digitalWrite(dir1PinA, HIGH);
                        digitalWrite(dir2PinA, LOW);

                        // Serial Display

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

                        lcd.setCursor(0,1); // Writes text for bottom row
                        lcd.print("Motor 1 Reverse    ");
                }

                else if (pressure <= 20000.00)

                {
                        Serial.println("wutdoing y'all?");
                        analogWrite(speedPinA, 0);
                        digitalWrite(dir1PinA, LOW);
                        digitalWrite(dir2PinA, LOW);

                        // LCD Display

                        lcd.setCursor(0,1); //Writes text for bottom row
                        lcd.print(" ***DEFLATED*** ");
                }
        }
        if ((reversestate == true) && ((buttonOffState == HIGH) || (reversestate == false)))

        {
                reversestate = false;
                analogWrite(speedPinA, 0);
                digitalWrite(dir1PinA, LOW);
                digitalWrite(dir2PinA, LOW);
        }
}
