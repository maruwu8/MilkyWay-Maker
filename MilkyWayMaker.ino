#include <Keypad.h>
#include <LiquidCrystal_I2C.h> 
#include <Servo.h>

const int ultrasonicTrigPin = 12;
const int ultrasonicEchoPin = 13;
const int servoPin = 11;


const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 3; //four columns
const int thresholdDistance = 3; // in cm

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

LiquidCrystal_I2C lcd(0x27, 16, 2); // ligne 8 
byte pin_rows[ROW_NUM] = {4, 5, 6, 7}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {8,9, 10}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);

int sensorInterrupt = 0;  // interrupt 0
int sensorPin = 2; //Digital Pin 2
unsigned int SetPoint = 400; //400 milileter
int buzzerPin = A3;
String code="";

/*The hall-effect flow sensor outputs pulses per second per litre/minute of flow.*/
float calibrationFactor = 40; //You can change according to your datasheet
 
volatile byte pulseCount =0;  
 
float flowRate = 0.0;
unsigned int flowMilliLitres =0;
unsigned long totalMilliLitres = 0, volume = 0;
 
unsigned long oldTime;
const int relais_moteur = 3; // the relay is connected to pin 3 of the Arduino board
Servo myServo;
bool objectDetected = false;
bool volumeEntered = false;
bool beepSequence = false;
bool beepSequence2 = false;
 
void setup()
{
  totalMilliLitres = 0;
  pinMode(relais_moteur, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  lcd.init(); // display initialization
  lcd.clear();
  lcd.backlight(); // activate the backlight
  lcd.setCursor(0, 0); // stand in the front line
  lcd.print("Insert volume:");
 
  Serial.begin(9600);
  myServo.attach(servoPin);
   myServo.write(70);
   pinMode(ultrasonicTrigPin, OUTPUT);
  pinMode(ultrasonicEchoPin, INPUT);
   delay(2000);
  pinMode(sensorPin, INPUT);
  digitalWrite(sensorPin, HIGH);
 
  attachInterrupt(sensorInterrupt, pulseCounter, FALLING); //you can use Rising or Falling
}
 
void loop()
{
  if (!objectDetected) {
    // Read distance from ultrasonic sensor
    int distance = getDistance();
    // Check if distance is below threshold
    if (distance < thresholdDistance) {
      // Move servo to 90 degrees
      delay(2000);
      myServo.write(120);
      delay(3000);
      // Reset servo to initial position
      myServo.write(70);
      // Set object detected flag to true
      objectDetected = true;
    }
  }

  // Wait for a moment before checking again
  delay(100);

  /////////////////////////////////////////
  char key = keypad.getKey();
 
  if (key) { // A key on the keyboard is pressed
    code += key;
    lcd.setCursor(0, 1); // stand on the second line
    lcd.print(code);  // show volume value
    delay(100);
  }
 
  if (key == '#') { // if you press the 'D' key
    if (code.toInt() <= 1000) {
      volume = code.toInt();
      volumeEntered = true;
      if(!beepSequence)
      {
        playBeepSequence(buzzerPin);
      beepSequence = true;
      }
      
      
  }
    else {
      lcd.clear();
      lcd.backlight(); 
      lcd.setCursor(0, 0); 
      lcd.print("Insert volume:");  
    }
    code = "";
  }

  if (key == '*') { // if you press the '*' key
   resetProcess();
   volumeEntered = false;
   return;
  }

  if(volumeEntered){
     if (totalMilliLitres < volume ) {
    digitalWrite(relais_moteur, HIGH); // Start the water pump
 
    if ((millis() - oldTime) > 1000) { // Only process counters once per second
      // Disable the interrupt while calculating flow rate and sending the value to the host
      detachInterrupt(sensorInterrupt);
   flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount) / calibrationFactor;
 
    oldTime = millis();
  
    flowMilliLitres = (flowRate / 60) * 1000;
 
    totalMilliLitres += flowMilliLitres;
 
    unsigned int frac;
 
    Serial.print("Flow rate: ");
    Serial.print(flowMilliLitres, DEC);  // Print the integer part of the variable
    Serial.print("mL/Second");
    Serial.print("\t");           
    lcd.clear();
    lcd.backlight(); 
    lcd.setCursor(0, 0); 
    lcd.print("debit:");
    lcd.print(flowMilliLitres);  // Show the flow rate on the lcd display   
        lcd.print(" ml/s");    
    // Print the cumulative total of litres flowed since starting
    Serial.print("Output Liquid Quantity: ");        
    Serial.print(totalMilliLitres,DEC);
 
    Serial.println("mL"); 
    Serial.print("\t");     
        lcd.setCursor(0, 1); 
        lcd.print("volume:");           
        lcd.print(totalMilliLitres);  // Show quantity filled   
    
    pulseCount = 0;
 
    attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
    }
}else  {
  digitalWrite(relais_moteur, LOW); // Stop the water pump
  volume=0;
  volumeEntered = false;
  if(!beepSequence2)
      {
        playBeepSequence(buzzerPin);
      beepSequence2 = true;
      }
      
  lcd.setCursor(0, 0); 
  lcd.print("Volume reached!"); 
   lcd.setCursor(0, 1); 
  lcd.print("Remove cup!"); 
  delay(12000);
  objectDetected = false;
  resetProcess();
  return;  
  }

  }
  }
 
void pulseCounter()
{
  pulseCount++;
}

void resetProcess() {
  totalMilliLitres = 0;
  volume = 0;
  byte pulseCount =0;  
  flowRate = 0.0;
  flowMilliLitres =0;
  beepSequence = false;
  beepSequence2 = false;
  code = "";
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Insert volume:");
}

int getDistance() {
  // Send trigger pulse
  digitalWrite(ultrasonicTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(ultrasonicTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultrasonicTrigPin, LOW);

  // Read echo pulse
  int duration = pulseIn(ultrasonicEchoPin, HIGH);

  // Convert duration to distance
  int distance = duration * 0.034 / 2;

  // Print distance to serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Return distance value
  return distance;
}

void playBeepSequence(int buzzerPin) {
  //pinMode(buzzerPin, OUTPUT);
  // Play the beep sequence once
  for (int j = 0; j < 3; j++) { // Play three short beeps
    tone(buzzerPin, 800, 300); // Play a tone of 800Hz for 100ms
    delay(400); // Wait for 100ms
  }
}

