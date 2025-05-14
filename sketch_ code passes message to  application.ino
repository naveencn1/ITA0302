#include <ESP8266WiFi.h>
int vibsensorPin=D1;
int ledPin=D6;
int buzzerpin=D0;
int i=0;

const char* ssid = "Shreyas";
const char* password = "1234567890";
boolean theft = false;

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(ledPin, OUTPUT);
  pinMode(buzzerpin, OUTPUT);
  pinMode(vibsensorPin, INPUT);
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
  
  long Alarm = pulseIn(vibsensorPin, HIGH); 
  if (Alarm > 100) 
  {
    theft = true;
    Serial.println(Alarm);
    Serial.println(theft);
  }
 
   
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  // Match the request
  int val;
  if (req.indexOf("/stop/0") != -1)
    val = 0;
  else if (req.indexOf("/start/1") != -1)
    val = 1;
  else {
    Serial.println("invalid request");
    client.stop();
    return;
  }
  
int vib = digitalRead(vibsensorPin);
  if(vib == HIGH)
  {
    for(i=0;i<10;i++)
    {
  digitalWrite(ledPin, HIGH);
  digitalWrite(buzzerpin, HIGH);
  delay(1000);

  digitalWrite(ledPin, LOW);
  digitalWrite(buzzerpin, LOW);
  delay(1000);
  }
  }
  client.flush();

  // Prepare the response
  String s = "HTTP/1.1 200 OK\r\n Content-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n";
  if (theft == true)
   {
    s += "!!!THEFT!!!";
    theft= false;
   }

  else
  {
    s += "safe";
  }

  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disonnected");
}
