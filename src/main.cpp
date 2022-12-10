/* Copyright 2022 Alexis Leclerc
 * 
 * Examen Mi-Session 2022
 * 
 * Cours objet connectés 2022
 * 
 * @file     main.cpp
 * @author   Alexis Leclerc
 * @version  1.0 10/27/22
 * @brief    Programme qui allume la led à une température définie
 * 
 * Historique des versions:
 *  - Version :  0.1
 *  - Date : 10/27/22
 *  - Auteur : Alexis Leclerc
 *  - Description : Première version du logiciel
 *
 *  - Version : 1.0 
 *  - Date : 12/09/22
 *  - Auteur : Alexis Leclerc
 *  - Description : Première version fonctionnelle du logiciel
 * 
 * Contenu du fichier platformio.ini:
 * 
 *  [env:esp32doit-devkit-v1]
 *  platform = espressif32
 *  board = esp32doit-devkit-v1
 *  framework = arduino
 *  monitor_speed = 115200
 *  lib_deps = 
 *     ESPAsyncWebServer-esphome
 *     AsyncTCP-esphome
 *     adafruit/Adafruit Unified Sensor@^1.1.6
 *     adafruit/Adafruit SSD1306@^2.5.7
 *     adafruit/DHT sensor library@^1.4.4
 *     bblanchon/ArduinoJson@^6.19.4
 * 
 */

#include <Arduino.h>                                        //Le framework Arduino
#include "MyFunctions.cpp"
#include <HTTPClient.h>
#include <Wire.h>
#include <WiFiManager.h>
#include <WiFi.h>
#include <MyOled.h>
MyOled *myOled = NULL;
#include <MyOledViewWifiAP.h>
MyOledViewWifiAP *myOledViewWifiAP = NULL;
#include <MyOledViewWorking.h>
MyOledViewWorking *myOledViewWorking = NULL;
#include <MyOledViewWorkingOff.h>
MyOledViewWorkingOff *myOledViewWorkingOff = NULL;
#include <MyOledViewWorkingHeat.h>
MyOledViewWorkingHeat *myOledViewWorkingHeat = NULL;
#include <MyOledViewWorkingCold.h>
MyOledViewWorkingCold *myOledViewWorkingCold = NULL;

#include <TemperatureStub.h>
TemperatureStub *temperatureStub = NULL;


#include <string>

WiFiManager wm;
#define WEBSERVER_H

//Pour la gestion du serveur ESP32
#include "MyServer.h"
MyServer *myServer = NULL;


const char *NOM_SYSTEME = "SAC System";
const char *SSID = "TemperatureESP";
const char *PASSWORD = "CodeSecret";
const char *ID_SYSTEME = "696969";

const int GPIO_PIN_LED_Heat_YELLOW = 27;
const int GPIO_PIN_LED_LOCK_RED = 12;
const int GPIO_PIN_LED_OK_GREEN = 14;

float tempDeclenchement;
float secondesSechage = 0;
float currentTemp = 0;

bool buttonPressed = false;

int timer = 0;
int timerSechage = 0;
int tempFour= 0;

std::string etat = "OFF";
char strTemperature[10];
char strTimer[10];


using namespace std;

std::string CallBackMessageListener(std::string message) {

  if(std::string(getValue(message, '|', 0).c_str()).compare(std::string("startFour")) == 0) { //Je sais j'aurais du prendre une variable pour action, mais ça ne marche pas sinon
    buttonPressed = true;
    return("");
  }

  if(std::string(getValue(message, '|', 0).c_str()).compare(std::string("getTemp")) == 0) {
    char buffer[10];
    sprintf(buffer, "%g °C|%i", currentTemp, timerSechage);
    return(buffer);
  }

  if(std::string(getValue(message, '|', 0).c_str()).compare(std::string("setWoodTemperature")) == 0) {
    const char * arg1 = getValue(message, '|', 1).c_str();
    try{
      tempDeclenchement = stof(arg1);               //On convertit le string en float
    }
    catch (const std::invalid_argument&) { }             //Si la conversion échoue, on ne fait rien
    return("");
  }



  if(std::string(getValue(message, '|', 0).c_str()).compare(std::string("setWoodTemps")) == 0) {
    const char * arg1 = getValue(message, '|', 1).c_str();
    try{
      secondesSechage = stoi(arg1);               //On convertit le string en entier
    }
    catch (const std::invalid_argument&) { }             //Si la conversion échoue, on ne fait rien
    return("");
  }

  return("");
}

void displayGoodScreen(std::string etat , float temp, int timer) {

  sprintf(strTemperature, "%2.2f", temp);
  sprintf(strTimer, "%d", timer);


  if(isEqualString(etat.c_str(), std::string("HEAT"))) myOled->updateCurrentView(myOledViewWorkingHeat);

  if(isEqualString(etat.c_str(), std::string("OFF"))) {
    digitalWrite(GPIO_PIN_LED_LOCK_RED, LOW);
    digitalWrite(GPIO_PIN_LED_OK_GREEN, HIGH);
    digitalWrite(GPIO_PIN_LED_Heat_YELLOW, LOW);
    myOledViewWorkingOff = new MyOledViewWorkingOff();
    myOledViewWorkingOff->setParams("nomDuSysteme", NOM_SYSTEME);
    myOledViewWorkingOff->setParams("idDuSysteme", ID_SYSTEME);
    myOledViewWorkingOff->setParams("ipDuSysteme", WiFi.localIP().toString().c_str());
    myOledViewWorkingOff->setParams("temperature", strTemperature);
    myOled->displayView(myOledViewWorkingOff);
    tempFour = temp;
  }

  if(isEqualString(etat.c_str(), std::string("COLD"))) {
    digitalWrite(GPIO_PIN_LED_LOCK_RED, LOW);
    digitalWrite(GPIO_PIN_LED_OK_GREEN, LOW);
    digitalWrite(GPIO_PIN_LED_Heat_YELLOW, HIGH);
    myOledViewWorkingCold = new MyOledViewWorkingCold();
    myOledViewWorkingCold->setParams("nomDuSysteme", NOM_SYSTEME);
    myOledViewWorkingCold->setParams("idDuSysteme", ID_SYSTEME);
    myOledViewWorkingCold->setParams("ipDuSysteme", WiFi.localIP().toString().c_str());
    myOledViewWorkingCold->setParams("temperature", strTemperature);
    myOled->displayView(myOledViewWorkingCold);
    tempFour = temp;
  }

  if(isEqualString(etat.c_str(), std::string("HEAT"))) {
    digitalWrite(GPIO_PIN_LED_LOCK_RED, HIGH);
    digitalWrite(GPIO_PIN_LED_OK_GREEN, LOW);
    digitalWrite(GPIO_PIN_LED_Heat_YELLOW, LOW);

    myOledViewWorkingHeat = new MyOledViewWorkingHeat();
    myOledViewWorkingHeat->setParams("nomDuSysteme", NOM_SYSTEME);
    myOledViewWorkingHeat->setParams("idDuSysteme", ID_SYSTEME);
    myOledViewWorkingHeat->setParams("ipDuSysteme", WiFi.localIP().toString().c_str());
    myOledViewWorkingHeat->setParams("temperature", strTemperature);
    myOled->displayView(myOledViewWorkingHeat);
    tempFour = temp;
  }
}

void setup() {

  WiFi.disconnect();

  pinMode(GPIO_PIN_LED_LOCK_RED, OUTPUT);
  pinMode(GPIO_PIN_LED_OK_GREEN, OUTPUT);
  pinMode(GPIO_PIN_LED_Heat_YELLOW, OUTPUT);

  Serial.begin(115200);

  temperatureStub = new TemperatureStub();
  temperatureStub->init();

  myOled = new MyOled(&Wire, -1, 64, 128);
  myOled->init();

  myOledViewWifiAP = new MyOledViewWifiAP();

  myOledViewWifiAP->setNomDuSysteme(NOM_SYSTEME); //mettre variable
  myOledViewWifiAP->setSSIDDuSysteme(SSID);
  myOledViewWifiAP->setPassDuSysteme(PASSWORD); 
  myOled->displayView(myOledViewWifiAP);

  wm.autoConnect(SSID, PASSWORD);

  //make it run two times
  for(int i=0; i<2; i++){
    digitalWrite(GPIO_PIN_LED_LOCK_RED, HIGH);
    digitalWrite(GPIO_PIN_LED_OK_GREEN, HIGH);
    digitalWrite(GPIO_PIN_LED_Heat_YELLOW, HIGH);

    delay(500);

    digitalWrite(GPIO_PIN_LED_LOCK_RED, LOW);
    digitalWrite(GPIO_PIN_LED_OK_GREEN, LOW);
    digitalWrite(GPIO_PIN_LED_Heat_YELLOW, LOW);

    delay(500);
  }

  // ----------- Routes du serveur ----------------
  myServer = new MyServer(80);
  myServer->initAllRoutes();
  myServer->initCallback(&CallBackMessageListener);

  // ----------- Affichage de l'IP ----------------
}

void loop() {

  if(timer % 1000 == 0){
    currentTemp = temperatureStub->getTemperature();

    if (!buttonPressed)
    {
      etat = "OFF";
    }
    else 
    {
      if (currentTemp <= tempDeclenchement)
      {
        etat = "COLD";
      }
      else if (currentTemp > tempDeclenchement*0.90 && currentTemp <= tempDeclenchement*1.10)
      {
        if (timerSechage<secondesSechage){
          etat = "HEAT";
          // On incrémente le compteur
          timerSechage++;
        }
        else{
          etat = "OFF";
          buttonPressed = false;
          timerSechage = 0;
        }


      }
      else
      {
        etat = "COLD";
      }

    }

    displayGoodScreen(etat, currentTemp, timerSechage);
  }

  timer += 10;
  delay(10);
}