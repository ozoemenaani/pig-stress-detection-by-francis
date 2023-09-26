#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.   
#include <SoftwareSerial.h>

#define sensorMin 900
#define sensorMax 1023 
//  Variables
const int PulseWire = 0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED = LED_BUILTIN;          // The on-board Arduino LED, close to PIN 13.
int Threshold = 550;           // Determine which Signal to "count as a beat" and which to ignore.
                               // Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
                               // Otherwise leave the default "550" value. 

  SoftwareSerial B(8,9);
PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"

void setup() {   

  Serial.begin(115200);          // For Serial Monitor
B.begin(9600);
    
  lcd.begin(16, 2);



  // Configure the PulseSensor object, by assigning our variables to it. 
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED);       //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);  
    
  // Double-check the "pulseSensor" object was created and "began" seeing a signal. 
   if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.  
  }

}



void loop() {
if (pulseSensor.sawStartOfBeat()) {    // Constantly test to see if "a beat happened".
lcd.clear();
delay(1);
int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
                                               // "myBPM" hold this BPM value now. 
 Serial.println("♥  A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
 Serial.print("BPM: ");                        // Print phrase "BPM: " 
 Serial.println(myBPM);// Print the value inside of myBPM. 
 
  lcd.setCursor(0,0);
  lcd.print("Temp(*C): ");
  lcd.setCursor(0,1);
  lcd.print("Pulse: ");

  

   // read the input on analog pin 0:
  int sensorValue = analogRead(A1);
  // print out the value you read:
  int value = map(sensorValue, sensorMin, sensorMax, 0, 60);
  Serial.println(sensorValue);
  Serial.print(value); Serial.println("ºC");

  lcd.setCursor(7,1);
  lcd.print(myBPM);
    lcd.setCursor(10,0);
  lcd.print(value);
  
  B.print(myBPM); 
  B.print(",");
  B.print(value);
  B.print(";");
  
}
  delay(20);                    // considered best practice in a simple sketch.
}  
