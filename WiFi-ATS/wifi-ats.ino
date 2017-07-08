#include <ESP8266WiFi.h>


/////////////////////
// Pin Definitions //
/////////////////////
const int LED_PIN = 16; // Pin DO, green LED




//////////////////////
// WiFi Definitions //
//////////////////////
const char WiFi_Password[] = "iotclass";
const char SSID_name[] = "WiFI-ATS";
String jsonResponse = "";


// create Wifi server object
WiFiServer server(3000);



void setup() {
  
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  Serial.begin(115200); // starts serial port
  WiFi.mode(WIFI_AP);
  WiFi.softAP(SSID_name, WiFi_Password);
  server.begin();
}



void loop() {
  // put your main code here, to run repeatedly:
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  

  if (req.indexOf("/wifiats/nepa") != -1)    
      {
        digitalWrite(LED_PIN, LOW);
        jsonResponse  = "{\"status\": \"NEPA active\"}";
      }
    
  else if (req.indexOf("/wifiats/gen") != -1)
    {
        digitalWrite(LED_PIN, HIGH);
        jsonResponse  = "{\"status\": \"GEN Active\"}";
    }

   else
   {
    // wrong path
    jsonResponse  = "{\"status\": \"invalid route\"}";
   }

  client.flush();

  // Prepare the response. Start with the common header:
    String s = "HTTP/1.1 200 OK\r\n";
    s += "Content-Type: application/json\r\n\r\n";
    s += jsonResponse;
    
    // Send the response to the client
    client.print(s);
    delay(1);
    //Serial.println("Client disonnected");
///////////////// end of loop  main code //////////////////////
}
