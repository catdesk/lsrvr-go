#include <AikoEvents.h>
#include <ArduinoJson.h>
using namespace Aiko;

int             ledGreen = 2;
int             ledBlue = 4;
int             ledRed = 3;

boolean         inputJson;
int             inByte = 0;
String          inString;
int             c;


// Initialize color [currentBrightness, targetBrightness]
int red[]     = {0, 0};
int green[]   = {0, 0};
int blue[]    = {0, 0};

int fadeSpeed = 1;

void setup() {
  Serial.begin(9600);
  Serial.println("Lights Active");
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  pinMode(ledRed, OUTPUT);
  Events.addHandler(userInput, 100);
  Events.addHandler(fade, 25);
}

void loop() {
  Events.loop();
}

void constructString(int c){
  // 123 is ascii for {, which is the start of a json statement
  if(c == 123 || inputJson == true){
    inString += (char) c;
    inputJson = true;
  }
  // 125 is ascii for }, which is the end of a json statement  
  if(c == 125){
     inputJson = false;
     processString(inString);
     inString = "";  
  }
}

void userInput(){
  if (Serial.available() > 0) {
    do{c = Serial.read();}while (c == -1);
    constructString(c);
  }
}

void processString(String inString){
  StaticJsonBuffer<200> jsonBuffer;
  char json[64];
  inString.toCharArray(json, 64);
  JsonObject& root = jsonBuffer.parseObject(inString);
  setColors(root["red"], root["green"], root["blue"]);
  if(root["fadeSpeed"] == 0)
    fadeSpeed = 1;
  else
    fadeSpeed = root["fadeSpeed"];
  printColors();
}

int setColors(int redValue, int greenValue, int blueValue) {
  red[1] = redValue;
  blue[1] = blueValue;
  green[1] = greenValue;
}

void printColors(){
  Serial.print("{\"red\":");
  Serial.print(red[1]);
  Serial.print(",\"green\":");
  Serial.print(green[1]);
  Serial.print(",\"blue\":");
  Serial.print(blue[1]);
  Serial.print(",\"fadeSpeed\":");
  Serial.print(fadeSpeed);
  Serial.print("}\n");
  Serial.flush();
}

void fade(){
  analogWrite(ledRed, red[0]);
  if(red[0] < red[1])
    red[0] += fadeSpeed;
    if((fadeSpeed + red[0]) > red[1])
      red[0] = red[1];
  if(red[0] > red[1])
    red[0] -= fadeSpeed;
    if((fadeSpeed - red[0]) < red[1])
      red[0] = red[1];
  analogWrite(ledGreen, green[0]);
  if(green[0] < green[1])
    green[0] += fadeSpeed;
    if((fadeSpeed + green[0]) > green[1])
      green[0] = green[1];
  if(green[0] > green[1])
    green[0] -= fadeSpeed;
    if((fadeSpeed - green[0]) < green[1])
      green[0] = green[1];
  analogWrite(ledBlue, blue[0]);
  if(blue[0] < blue[1])
    blue[0] += fadeSpeed;
    if((fadeSpeed + blue[0]) > blue[1])
      blue[0] = blue[1];
  if(blue[0] > blue[1])
    blue[0] -= fadeSpeed;
    if((fadeSpeed - blue[0]) < blue[1])
      blue[0] = blue[1];      
}
