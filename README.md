# The Automated Fish Farm Manager

## Introduction

The Automated Fish Farm Manager is a device that automates fish farm management. It has numerous purposes and greatly simplifies the work of fish farmers. It is a device that assists the fish farmers in monitoring the health of the fish, checking the pH of the water, pumping new water into the tank and removing dirty water, feeding the fish, and alerting the fish farmer if the fish becomes ill. It reduces the number of fish deaths caused by illnesses or in other ways. It can be changed to our preferences and is very flexible and can easily be customized.

Video ADD LATER 

This is our Automated Fish Farm Manager

## Installation Of Arduino IDE

We have used Arduino IDE in running and writing our code for pH meter,  Water Pump and AutoFeeder.We will be Using Arduino IDE to run the code. So if you have not installed Arduino IDE [Click me][IDE]

 [IDE]: <https://support.arduino.cc/hc/en-us/articles/360019833020-Download-and-install-Arduino-IDE>

## AutoFeeder and Water Pump

- The Autofeeder is a part of our model that automates the process of feeding the fish in the fish farm. We designed it such that it feeds the fish at the desired time for a particular amount of time. 
- We have used 2 water pumps in the fish tank, one to pump the water and the other one to remove the dirty water.We have coded the water in such a way that it removes and pumps the water at desired intervals.

### Connection Diagram

![GreenwaveProject2023](https://github.com/shirish2010/greenwavesembcorp2023/blob/main/images/ConnectionDiagramAutofeeder.jpeg)

### The Procedure for working of the AutoFeeder and Water Pump

- Connect the Arduino Uno and the computer using an Arduino USB 2.0 cable
- Select the board as Arduino Uno and the port given there
- Run this code in Arduino IDE
 
```c
#include <Servo.h>//Inputs the library Servo.h
Servo myservo;//Names the library's variable "Servo" to myservo

unsigned long StartTime = 1;
unsigned long Interval = 86400000;

const int RELAY_PIN1 = 8;
const int RELAY_PIN2 = 7;

void setup (){
  myservo.attach(9);//The pin where the servo motor is attached on the arduino
  myservo.write(90);//Makes the servo motor stop  

   pinMode(RELAY_PIN1, OUTPUT);
   pinMode(RELAY_PIN2, OUTPUT);
}

void loop()

 {
  if (millis()>StartTime){
    StartTime = millis()+Interval;
    digitalWrite(RELAY_PIN1, HIGH);
    delay(12000);
    digitalWrite(RELAY_PIN1, LOW);
  }

 if (millis()>StartTime){
    StartTime = millis()+Interval;
    digitalWrite(RELAY_PIN2, HIGH);
    delay(12000);
    digitalWrite(RELAY_PIN2, LOW);
  }
  
 myservo.write(45);
 delay(21000);
 myservo.write(90);
 delay(10000);
 myservo.write(45);
 delay(21000);
 myservo.write(90);
 delay(10000);
 myservo.write(45);
 delay(21000);
 myservo.write(90);
 delay(86400000);
}
```
You will see that the AutoFeeder and Water Pump work together.

## pH Meter 

By using a pH meter in our automated fish farm, fish farmers can effectively monitor and control the pH levels. We have used Thingspeak to display the pH levels. In our project, we have used Tiger Barb and its ideal pH level is approximately 6 to 7

### The Procedure for working on the pH meter

- Connect the ESP32 and the computer using an Micro USB Cable with data wires
- Select the board as Arduino Uno and the port given there
- Run this code in Arduino IDE
-Replace the XXX with your Wi-Fi network name and the password

```c
   #include <WiFi.h>//Includes the necessary library for establishing a WiFi connection.
const int potPin = A0;
float ph;//variable that to store the calculated pH value
float Value = 0;


String apiKey = "GLWQU7W7CH5XTU4Z"; //API key from ThingSpeak
const char *ssid = "XXX"; // replace the "XXX" with your Wi-Fi network SSID
const char *password = "XXX"; // replace the "XXX" with your Wi-Fi network password
const char* server = "api.thingspeak.com"; // ThingSpeak server address
WiFiClient client; // Wi-Fi client object for network communication

 
//WiFiClient client;//Used for network communication with the Wi-Fi network and the ThingSpeak server.
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(potPin,INPUT);//Sets the potPin(which is connected to the pH sensor) as an input pin.
  delay(1000);//Delay 1000 millisecond 
 
  Serial.print("Connecting to ");//Prints the message "Connecting to " to the serial monitor.
  Serial.println(ssid);//ssid variable contains the Wi-Fi network SSID specified in the code.
  WiFi.begin(ssid, password);//Initiates the connection to the Wi-Fi network using the provided SSID and password.
  while (WiFi.status() != WL_CONNECTED) {//Starts a loop that waits until the ESP32 successfully connects to the Wi-Fi network.
    delay(2000);//Delay 2000 millisecond
    Serial.print(".");//Continues to loop and print dots "."" to the serial monitor until the connection is established 
  }
  // Print local IP address and start web server
  Serial.println("");//Prints an empty line to the serial monitor.
  Serial.println("WiFi connected.");//Prints the message "WiFi connected." to the serial moniter
  Serial.println("IP address: ");//Prints the message "IP address: " to the serial moniter
  Serial.println(WiFi.localIP());//Retrieves the IP address and prints it to the serial monitor.
  
}
 
void loop() {
  // put your main code here, to run repeatedly:
Value= analogRead(potPin);//Converts the analog voltage on the pin to a digital value.
Serial.print(Value);//Prints the raw analog value (Value) to the serial monitor.
Serial.print(" | ");//Print "|" to the serial monitor 
float voltage=Value*(3.3/4095.0);//multiplies the Value by the ratio of 3.3 divided by 4095.0
//The result is stored in the voltage variable.
ph=(3.3*voltage);// pH value is stored in the ph variable.
Serial.println(ph-2);//Prints the calculated pH value (ph) to the serial monitor.
delay(500);//Delay 500 milliseonds
 
if (client.connect(server, 80)) //Establishes a connection to the ThingSpeak server.
   {
      String postStr = apiKey;//Initializes a string variable postStr with the value of the API key (apiKey)
      postStr += "&field1=";//Represents the field in which the pH value will be stored on the ThingSpeak platform.
      postStr += String(ph-2);//Adds the pH value to the data that will be sent to ThingSpeak.
      postStr += "\r\n";//Separate multiple fields in the POST request
    
      client.print("POST /update HTTP/1.1\n");// Sends a POST request line to the ThingSpeak server
      client.print("Host: api.thingspeak.com\n");//Sends the host header specifying the ThingSpeak server
      client.print("Connection: close\n");//Specifies the connection header as close
      client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");//Sends the ThingSpeak API key as a custom header (X-THINGSPEAKAPIKEY
      client.print("Content-Type: application/x-www-form-urlencoded\n");//Specifies the content type of the request as application/x-www-form-urlencoded
      client.print("Content-Length: ");//Sends the Content-Length header to specify the length of the data being sent.
      client.print(postStr.length());//Sends the length of the postStr data as the value for the Content-Length header.
      client.print("\n\n");//Sends two newline characters to indicate the end of the headers
      client.print(postStr);//Sends the actual data (postStr) in the request body.
    }    
}

```
-Now the data will be displayed in Thingspeak

 [Click me][Thingspeak]
 
  [Thingspeak]: <https://thingspeak.com/channels/2208052>


## The Fish disease detector

The Fish Disease Detector is a part of our Automated Farm Management which uses Machine learning to identify whether the fish is infected or not.

### The Procedure of working with the  Fish Disease Detector 

- Connect the Raspberry Pi to a power socket using a power cord-
- Go to the terminal in Raspberry Pi and type
- Run this code in Python. This code saves the picture of the fish in my drive.
  
  
- Run this code in Google Colab for machine learning to detect infected fishes

  [Click me][Google colab]
  
   [Google colab]: <https://colab.research.google.com/drive/1g0um-qAnciawWCxyagDnQyym5Tt16iOp>
  




