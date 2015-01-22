#include <Ethernet.h>
#include <SPI.h>

byte mac[] = {   0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x0 };
IPAddress ip(109,123,141, 148);
//IPAddress gateway(109,123,141, 1);
//IPAddress subnet(255, 255, 255, 0);
byte server[] = { 109,123,141, 137 }; // Google
int rep=-5;

EthernetClient client;

void setup()
{
  Ethernet.begin(mac, ip);
  Serial.begin(9600);

  Serial.print("My IP address: ");
  ip = Ethernet.localIP();
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(ip[thisByte], DEC);
    Serial.println("."); 
  }
  delay(1000);

  Serial.println(rep);

  Serial.println("connecting...");

  rep = client.connect(server, 80);
  Serial.println(rep);
  if (rep == 1) {
    Serial.println("connected");
    client.println("GET /search?q=arduino HTTP/1.0");
    client.println();
  } 
  else {
    Serial.println(rep);
    Serial.println("connection failed");
  }
  
  delay(1000);

  Serial.println("connecting...");

  rep = client.connect(server, 80);
  Serial.println(rep);
  if (rep == 1) {
    Serial.println("connected");
    client.println("GET /search?q=arduino HTTP/1.0");
    client.println();
  } 
  else {
    Serial.println(rep);
    Serial.println("connection failed");
  }
}

void loop()
{
  if(!client.connected())
    {
        if (client.connect(server, port))
        {
            ...
            client.disconnect();
        }
        else
            Serial.println("Server not found");
    }
    else
        client.disconnect();
    delay(1000);
}
