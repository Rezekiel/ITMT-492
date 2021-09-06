
#include "raysays.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#ifndef STASSID
#define STASSID "MTE-ZEKE"
#define STAPSK  "OjuOwiwi96"
#endif

const char *ssid = STASSID;
const char *password = STAPSK;


ESP8266WebServer server(80);

int highscore = 10;

/*const int buzzerPin = 14;
const int redButtonPin = 2;     // the number of the pushbutton pin
const int redLedPin =  16;      // the number of the LED pin
const int greenButtonPin = 0;     
const int greenLedPin =  15;      
const int yellowButtonPin = 13;    
const int yellowLedPin =  12;      
//tones assigned to each color
const int redTone = 165;
const int greenTone = 196;
const int yellowTone = 220;

//=============================//
int level = 1;
int patternArray[10]= { }; //array with 10 elements. Initialized and assigned 0 for each element
int ctrArray[3]={ 1, 1, 1 }; //array that keeps track of the total number of times each button was pressed throughout the program 


// variable for reading the pushbutton status
int redButtonState = 0;
int greenButtonState = 0;
int yellowButtonState = 0;
boolean correctPattern=false;
*/

void handleRoot() {
  char temp[400];
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;

  snprintf(temp, 400,

 "<html>\
  <head>\
    <meta http-equiv='refresh' content='5'/>\
    <title>ESP8266 Demo</title>\
    <style>\
      body { background-color: #e9ebe4; font-family: Arial, Helvetica, Sans-Serif; Color: #44444d; }\
    </style>\
  </head>\
  <body>\
    <h1>Hello from ESP8266!</h1>\
    <h3>Highscores:%02d</h3>\
    <p>Uptime: %02d:%02d:%02d</p>\
    <img src=\"/test.svg\" />\
  </body>\
</html>",
          highscore, hr, min % 60, sec % 60);
  server.send(200, "text/html", temp);
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);
}

void drawGraph() {
  String out;
  out.reserve(2600);
  char temp[70];
  out += "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"400\" height=\"150\">\n";
  out += "<rect width=\"400\" height=\"150\" fill=\"rgb(250, 230, 210)\" stroke-width=\"1\" stroke=\"rgb(0, 0, 0)\" />\n";
  out += "<g stroke=\"black\">\n";
  int y = rand() % 130;
  for (int x = 10; x < 390; x += 10) {
    int y2 = rand() % 130;
    sprintf(temp, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke-width=\"1\" />\n", x, 140 - y, x + 10, 140 - y2);
    out += temp;
    y = y2;
  }
  out += "</g>\n</svg>\n";

  server.send(200, "image/svg+xml", out);
}

void setup(void) {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to Wifi...");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }
  server.on("/", handleRoot);
  server.on("/test.svg", drawGraph);
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");

  // initialize LED pins as an output:
  pinMode(buzzerPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  // initialize pushbutton pin as an input:
  pinMode(redButtonPin, INPUT);
  pinMode(greenButtonPin, INPUT);
  pinMode(yellowButtonPin, INPUT);
  Serial.println("------- Start Serial Monitor ------");
  genNextPatternKey(); //Initializes the first
}

void loop(void) {
  server.handleClient();
  MDNS.update();

//main program loop starts here
  if( startGame==0){
    startGame = pressToStart();
    //secondThreadLed();
    //digitalWrite(redLedPin,);
  }
  
  //lampMode();
  if(startGame == 1){
    displayPattern();
    showPatternOnTerminal();
    levelCleared = userInputAndValidation();
    if( levelCleared == true ){
      letsGo();
      level++;
      genNextPatternKey();
      Serial.println("Level Cleared is: " + (String)levelCleared);
    } else if ( levelCleared == false){
       highscore = level;
      youLose();
      resetGame();
    }
  }
} //end loop method
