#include <Servo.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ThingSpeak.h>
const char * myWriteAPIKey = "9B6ILVOYMUSVOADA";
unsigned long myChannelNumber = 691885;
const char *ssid =  "EC_IIOT_LAB";     // Enter your WiFi Name
const char *pass =  "Eciiotlab@103"; // Enter your WiFi Password
WiFiClient client;
Servo pickServo;
Servo dropServo;
const int s0 = D4;  
const int s1 = D5;  
const int s2 = D6;  
const int s3 = D7;  
const int out = D8;   
int red = 0;  
int green = 0;  
int blue = 0; 
int color=0;
int redcolor = 0;
int greencolor = 0;
int orangecolor = 0;
int yellowcolor = 0;
int CLOSE_ANGLE = 90;  // The closing angle of the servo motor arm
int OPEN_ANGLE = 10;  // The opening angle of the servo motor arm
void setup()   
{  
  Serial.begin(9600); 
  pinMode(s0, OUTPUT);  
  pinMode(s1, OUTPUT);  
  pinMode(s2, OUTPUT);  
  pinMode(s3, OUTPUT);  
  pinMode(out, INPUT);  
  digitalWrite(s0, HIGH);  
  digitalWrite(s1, HIGH);  
  pickServo.attach(D2);
  dropServo.attach(D3);
  pickServo.write(30);
  dropServo.write(73);
  ThingSpeak.begin(client);
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) 
     {
            delay(550);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
}  
void loop() 
{  
  digitalWrite(s2, LOW);  
  digitalWrite(s3, LOW);  
  //count OUT, pRed, RED  
  red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  digitalWrite(s3, HIGH);  
  //count OUT, pBLUE, BLUE  
  blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  digitalWrite(s2, HIGH);  
  //count OUT, pGreen, GREEN  
  green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH); 
  Serial.print("R Intensity:");  
  Serial.print(red, DEC);  
  Serial.print(" G Intensity: ");  
  Serial.print(green, DEC);  
  Serial.print(" B Intensity : ");  
  Serial.print(blue, DEC);  
   delay(100);
  if(red<22 & red>12 & green<48 & green>38 &blue<43 & blue>33){
    dropServo.write(10);
    delay(700);
    redcolor++;
    Serial.print("Red");
    open1();
    delay(200);
    close1();
    ThingSpeak.writeField(myChannelNumber, 1,redcolor, myWriteAPIKey);
  }

  if(red<33 & red>23 & green<26 & green>16 & blue<35 & blue>25){
    dropServo.write(90);
    delay(700);
    yellowcolor++;
    Serial.print("green");
    open1();
    delay(200);
    close1();
    ThingSpeak.writeField(myChannelNumber, 2,greencolor, myWriteAPIKey);
  } 
  Serial.println();  
 // delay(1000); 
} 
void open1(){ 
  pickServo.write(OPEN_ANGLE);   // Send the command to the servo motor to open the trap door
}
void close1(){ 
  pickServo.write(CLOSE_ANGLE);   // Send te command to the servo motor to close the trap door
}