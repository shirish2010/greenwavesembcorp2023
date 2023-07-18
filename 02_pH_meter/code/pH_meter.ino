#include <WiFi.h>//Includes the necessary library for establishing a WiFi connection.
const int potPin = A0;
float ph;//variable that to store the calculated pH value
float Value = 0;


String apiKey = "XXX"; // Replace the "XXX" with the API key from ThingSpeak
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
Serial.println(ph);//Prints the calculated pH value (ph) to the serial monitor.
delay(500);//Delay 500 milliseonds
 
if (client.connect(server, 80)) //Establishes a connection to the ThingSpeak server.
   {
      String postStr = apiKey;//Initializes a string variable postStr with the value of the API key (apiKey)
      postStr += "&field1=";//Represents the field in which the pH value will be stored on the ThingSpeak platform.
      postStr += String(ph);//Adds the pH value to the data that will be sent to ThingSpeak.
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
