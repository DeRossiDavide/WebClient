#include <TimeLib.h>

/*
 Web client

 This sketch connects to a website (http://www.google.com)
 using an Arduino WIZnet Ethernet shield.

 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13

 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe, based on work by Adrian McEwen

 */

#include <SPI.h>
#include <Ethernet.h>
#include <TimeLib.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x08 };

// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
IPAddress server(192, 168, 8, 132);  // numeric IP for Google (no DNS)
//char server[] = "http://localhost:8000";    // name address for Google (using DNS)

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 8, 148);

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

// Variables to measure the speed
unsigned long beginMicros, endMicros;
unsigned long byteCount = 0;
bool printWebData = true;  // set to false for better speed measurement

void setup() {
  getDate();
    
}

void loop() {
  while (!client.connect(server, 8000)) {
  }
  if (client.connect(server, 8000)) {
    Serial.println(second());
    Serial.print("connected to ");
    Serial.println(client.remoteIP());
    String temp = "ftemp=12.21";
    client.println("POST /sendtemperature.php HTTP/1.1");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: ");
    client.println(temp.length());
    client.println();
    client.println(temp);
  }
  delay(1000);
}

void getDate() {

  Serial.begin(9600);
  Serial.println("Inizio");

  Serial.println("Inizialize Ethernet with DHCP");
  Ethernet.begin(mac, ip);
  Serial.println("DHCP assigned IP ");
  Serial.println(Ethernet.localIP());

  delay(1000);
  Serial.print("connecting to ");
  Serial.print(server);
  Serial.println("...");
  while (!client.connect(server, 8000)) {
  }
  if (client.connect(server, 8000)) {
    Serial.print("connected to ");
    Serial.println(client.remoteIP());

    client.println("GET /gettime.php HTTP/1.1");
  } else {
    Serial.println("connection failed");
  }
  Serial.println("SERVER");
  String msg = "";
  while (client.available()) {
    char c = client.read();
    msg = msg + c;
  }

  Serial.println("msg");

  //Isoleted the date
  int i = 0;
  while (msg[i] == '\"') {
    i++;
  }
  i++;
  String data = "";
  Serial.println("Data");  
  while (msg[i] == '\"') {
    data = data + msg[i];
    i++;
  }
  Serial.println("data");
  setTime(data.substring(11, 13).toInt(), data.substring(14, 16).toInt(), data.substring(17, 19).toInt(), data.substring(0, 4).toInt(), data.substring(5, 7).toInt(), data.substring(8, 10).toInt());
}