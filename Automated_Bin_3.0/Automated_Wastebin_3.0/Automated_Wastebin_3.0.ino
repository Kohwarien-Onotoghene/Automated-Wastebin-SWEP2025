#include <Servo.h>    
#include <LiquidCrystal.h>


// HAND/OBJECT DETECTION UNLTRASONIC SENSOR
#define trigPin 3
#define echoPin 4

//FILL LEVEL DETECTION ULTRASONIC SENSOR
#define trig_trash 6
#define echo_trash 5

const int rs = 12, en = 11, d4 = 10, d5 = 9, d6 = 8, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


Servo myservo;

const int Servo_Initial_Position = 0;
const int Servo_Pin = 2;
const int SERVO_OPEN = 160;
const int SERVO_CLOSED= 0;

void setup() {
  Serial.begin(9600);   

  pinMode(trigPin, OUTPUT);   
  pinMode(echoPin, INPUT);  
  pinMode(trig_trash, OUTPUT);   
  pinMode(echo_trash, INPUT); 

  myservo.attach(Servo_Pin);  
  myservo.write(Servo_Initial_Position);

  
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Smart Bin Ready");
  lcd.setCursor(0, 1);
  lcd.print("Bin Status: OK");
  delay(2000);
}

void loop() {
  // ---HAND/OBJECT DETECTION 
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2;

// fill level DETECTION 
  digitalWrite(trig_trash, LOW);  
  delayMicroseconds(2);
  digitalWrite(trig_trash, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_trash, LOW);

  long duration_trash = pulseIn(echo_trash, HIGH);
  long fill_level = duration_trash * 0.034 / 2;


  if (distance < 45 && fill_level > 24) {  // IF you are less than 45cm away from the bin and the bin isn't full, then the servo will activate, opening the bin.
   myservo.write(SERVO_OPEN);
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("Bin Status: OK");
   lcd.setCursor(0, 1);
   lcd.print("Drop your waste");
   delay(3000); // keep open for 3 seconds before closing
   myservo.write(SERVO_CLOSED);
}

  else if (fill_level < 15)  {
    delay(50);
    myservo.write(SERVO_CLOSED);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Bin is full!");
    lcd.setCursor(0, 1);
    lcd.print("Lid Locked   ");
  }
  
  
  //For debugging, i.e checking if the sensors are working.
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
 
  Serial.print("Fill Level: ");
  Serial.print(fill_level);
  Serial.println(" cm");
  
  
  delay(500);
}

