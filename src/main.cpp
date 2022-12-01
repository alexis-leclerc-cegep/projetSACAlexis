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
 *  - Version : 1.0 
 *  - Date : 10/27/22
 *  - Auteur : Alexis Leclerc
 *  - Description : Première version du logiciel
 * 
 * Contenu du fichier platformio.ini:
 * 
 *  [env:esp32doit-devkit-v1]
 *  platform = espressif32
 *  board = esp32doit-devkit-v1
 *  framework = arduino
 *  monitor_speed = 115200
 *  lib_deps = 
 *  	adafruit/Adafruit Unified Sensor@^1.1.6
 *  	adafruit/DHT sensor library@^1.4.4
 * 
 */

#include <Arduino.h>                                        //Le framework Arduino
#include "MyFunctions.cpp"
#include "DHT.h"                                            //Inclure la librairie pour intéragir avec le DHT22
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


#include <string>

WiFiManager wm;
#define WEBSERVER_H

//Pour la gestion du serveur ESP32
#include "MyServer.h"
MyServer *myServer = NULL;

#define DHTPIN 4
#define DHTTYPE DHT22                                       //On définit le type de DHT comme étant un DHT22  

const char *NOM_SYSTEME = "SAC System";
const char *SSID = "TemperatureESP";
const char *PASSWORD = "CodeSecret";

float tempDeclenchement;

DHT dht(DHTPIN, DHTTYPE);


std::string CallBackMessageListener(std::string message) {
  const char * action = getValue(message, '|', 0).c_str();

  Serial.println(action);

  if(std::string(action).compare(std::string("getTemp")) == 0) {
    Serial.println("la tempereature");
    float t = dht.readTemperature();
    char buffer[10];
    sprintf(buffer, "%g °C", t);
    return(buffer);
  }

  if(std::string(action).compare(std::string("setTemp")) == 0) {
    const char * arg1 = getValue(message, '|', 1).c_str();
    try{
      tempDeclenchement = std::stof(arg1);               //On convertit le string en float
    }
    catch (const std::invalid_argument&) { }             //Si la conversion échoue, on ne fait rien
    return("");
  }
}

void setup() {
  WiFi.disconnect();
  Serial.begin(115200);
  Serial.println("dans le nouveau programme");
  myOled = new MyOled(&Wire, -1, 64, 128);
  myOled->init();
  myOledViewWifiAP = new MyOledViewWifiAP();
  //myOledViewWorking->setParams("chepo".c_str(), "chepo".c_str(), "chepo".c_str(), "chepo".c_str());

  myOledViewWifiAP->setNomDuSysteme(NOM_SYSTEME); //mettre variable
  myOledViewWifiAP->setSSIDDuSysteme(SSID);
  myOledViewWifiAP->setPassDuSysteme(PASSWORD); 
  myOled->displayView(myOledViewWifiAP);

  wm.autoConnect(SSID, PASSWORD);

  myOledViewWorkingOff = new MyOledViewWorkingOff();

  // ----------- Routes du serveur ----------------
  myServer = new MyServer(80);
  myServer->initAllRoutes();
  myServer->initCallback(&CallBackMessageListener);
}

void loop() {


  float t = dht.readTemperature();
  char buffer[10];
  sprintf(buffer, "%g C", t);
  Serial.println(buffer);
  myOledViewWorkingOff->setParams("temperature", buffer);
  myOledViewWorkingOff->setParams("nomSysteme", NOM_SYSTEME);
  myOledViewWorkingOff->setParams("ipDuSysteme", WiFi.localIP().toString().c_str());
  myOled->displayView(myOledViewWorkingOff);

/*
  if(t > tempDeclenchement) {
    myOled->displayView(myOledViewWorking);
  }

  else {
    */

//  }

  delay(1000);

}