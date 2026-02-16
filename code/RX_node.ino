#include<SoftwareSerial.h>
SoftwareSerial ndmcu_srl(D1,D2);
#include "ThingSpeak.h"
#include "ESP8266WiFi.h"
char ssid[] = "TP-Link_2BEB";   
char pass[] = "93287289";  


//----------- Channel Details -------------//
unsigned long Channel_ID = 1540719; // Channel ID
//const int Field_number = 1; // Don't change
const char * WriteAPIKey = "UWRL42M3CQGWHSPL"; // Your write API Key

WiFiClient  client;
float ov=12.29;
float c1=3.97;
float c2=4.06;
float c3=4.17;
float t1=27.83;
float t2=27.83;
int x;
 


void setup() 
{
  Serial.begin(9600);                   // Begins Serial Communication with baud rate 9600  
 // if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    WiFi.mode(WIFI_STA);
    ThingSpeak.begin(client);
    WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
    
    while(WiFi.status() != WL_CONNECTED){
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());    
    delay(1000);
  //}
  
}

void loop() 
{
        
          x=ThingSpeak.writeField(Channel_ID, 1, ov, WriteAPIKey);
          x=ThingSpeak.writeField(Channel_ID, 2, c1, WriteAPIKey);
          x=ThingSpeak.writeField(Channel_ID, 3, c2, WriteAPIKey);
          x=ThingSpeak.writeField(Channel_ID, 4, c3, WriteAPIKey);
          x=ThingSpeak.writeField(Channel_ID, 5, t1, WriteAPIKey);
          x=ThingSpeak.writeField(Channel_ID, 6, t2, WriteAPIKey);
          if(x == 200){
            Serial.println("Channel update successful.");
                    }
        else{
            Serial.println("Problem updating channel. HTTP error code " + String(x));
             }
}
        

        
     
 


        
          
             
       







  
