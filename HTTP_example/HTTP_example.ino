#include <SPI.h>
#include <Ethernet.h>
 
// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {   0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x0 };
IPAddress ip(109,123,141, 148);
IPAddress gateway(109,123,141, 1);
IPAddress subnet(255, 255, 255, 0);
 
// Initialize the Ethernet server library
// with the IP address and port you want to use 
// (port 80 is default for HTTP):
EthernetServer server(125);

boolean gotAMessage = false; // whether or not you got a message from the client yet
String commandString;
 
void setup() 
{
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial.println("Trying to get an IP address using DHCP");
  //if (Ethernet.begin(mac) == 0) {
  Serial.println("Failed to configure Ethernet using DHCP");
  // initialize the ethernet device not using DHCP:
  Ethernet.begin(mac, ip, gateway, subnet);
  
  // print your local IP address:
  Serial.print("My IP address: ");
  ip = Ethernet.localIP();
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(ip[thisByte], DEC);
    Serial.print("."); 
  }
  Serial.println();
  // start listening for clients
  server.begin();
}
 
void loop() 
{
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    if (!gotAMessage) {
      Serial.println("We have a new client");
      client.println("Hello, client!"); 
      gotAMessage = true;
    }
    
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) 
        {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
	  client.println("Refresh: 30");  // refresh the page automatically every 30 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
 
          // from here we can enter our own HTML code to create the web page
          client.print("<head><title>Office Weather</title></head><body><h1>Office Temperature</h1><p>Temperature - ");
          client.print(" degrees Celsius</p>");
          client.print("<p>Humidity - ");
          client.print(" percent</p>");
          client.print("<p><em>Page refreshes every 30 seconds.</em></p></body></html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}
