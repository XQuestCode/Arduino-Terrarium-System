#include <BH1750FVI.h>   						//library for Intenisty Sensor
//coded by Aditya Parmar
//XQuestCodes
// Create the Lightsensor instance
BH1750FVI LightSensor(BH1750FVI::k_DevModeContLowRes);
#include <WiFiNINA.h>

//please enter your sensitive data in the Secret tab
char ssid[] = "";       //wifi network ssid
char pass[] = "";		//wifi network password

WiFiClient client;

char   HOST_NAME[] = "maker.ifttt.com";
String PATH_NAME   = "/trigger/sunlight_started/with/key/key1";    //URI if sunlight is recieved
String PATH_NAME2   = "/trigger/sunlight_over/with/key/key2";      //URI if sunlight is gone
String queryString = "?value1=57&value2=25";

void connection()                                                   //to initalize connection to the IFTTT server
{
  // connect to web server on port 80:
  if (client.connect(HOST_NAME, 80)) {
    // if connected:
    Serial.println("Connected to server");
  }
  else {// if not connected:
    Serial.println("connection failed");
  }
}
void setup() 
{
// initialize WiFi connection
  WiFi.begin(ssid, pass);   

  Serial.begin(9600);
  while (!Serial);
  LightSensor.begin();  

    // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500);
  
//coded by Aditya Parmar
//XQuestCodes
  
}
bool lights;
int timer =0;
void loop()
{

  uint16_t lux = LightSensor.GetLightIntensity();
  
  Serial.print("Light: ");
  Serial.println(lux);
  Serial.println(timer);
  
  if(lux>100 && !lights) {
  
  timer++;
  
  if(timer>10000) {                            //10000 shows 10 seconds, so morning will triggered if light stays on for 10 seconds 
  morning();
  lights = true;
  timer = 0;
  delay(10000);
  }
  
  } else if(lux<100 && lights) {                    //only will be triggered if light switches on (sunlight recieved)
    timer++;
  if(timer>10000) {                              //10000 shows 10 seconds, so night will triggered if light stays off for 10 seconds 
  night();
    timer = 0;
    lights = false;
    delay(10000);
  }
  }
}
void morning() 
{
  connection();
  // make a HTTP request:
    // send HTTP header
    client.println("GET " + PATH_NAME + queryString + " HTTP/1.1");
    client.println("Host: " + String(HOST_NAME));
    client.println("Connection: close");
    client.println(); // end HTTP header


    while (client.connected()) {
      if (client.available()) {
        // read an incoming byte from the server and print it to serial monitor:
        char c = client.read();
        Serial.print(c);
      }
    }
    // the server's disconnected, stop the client:
    client.stop();
    Serial.println();
    Serial.println("disconnected");

  
}
void night() 
{
  connection();
  // make a HTTP request:
    // send HTTP header
    client.println("GET " + PATH_NAME2 + queryString + " HTTP/1.1");
    client.println("Host: " + String(HOST_NAME));
    client.println("Connection: close");
    client.println(); // end HTTP header


    while (client.connected()) {
      if (client.available()) {
        // read an incoming byte from the server and print it to serial monitor:
        char c = client.read();
        Serial.print(c);
      }
    }
    // the server's disconnected, stop the client:
    client.stop();
    Serial.println();
    Serial.println("disconnected");
}
//coded by Aditya Parmar
//XQuestCodes
