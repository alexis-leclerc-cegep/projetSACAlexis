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
#include "DHT.h"                                            //Inclure la librairie pour intéragir avec le DHT22
#include <HTTPClient.h>
#include <Wire.h>
#include <WiFiManager.h>
#include <MyOled.h>
MyOled *myOled = NULL;
#include <MyOledViewWorking.h>
MyOledViewWorking *myOledViewWorking = NULL;
#include <MyOledViewWifiAP.h>
MyOledViewWifiAP *myOledViewWifiAP = NULL;


#include <string>

WiFiManager wm;
#define WEBSERVER_H

//Pour la gestion du serveur ESP32
#include "MyServer.h"
MyServer *myServer = NULL;

#define DHTPIN 4
#define DHTTYPE DHT22                                       //On définit le type de DHT comme étant un DHT22  

const char *SSID = "TemperatureESP";
const char *PASSWORD = "CodeSecret";


DHT dht(DHTPIN, DHTTYPE);


std::string CallBackMessageListener(std::string message) {
}

void setup() {
  Serial.begin(115200);
  myOled = new MyOled(&Wire, -1, 64, 128);
  myOled->init();
  myOledViewWorking = new MyOledViewWorking();
  myOledViewWifiAP = new MyOledViewWifiAP();
  //myOledViewWorking->setParams("chepo".c_str(), "chepo".c_str(), "chepo".c_str(), "chepo".c_str());



  delay(100);

  if(!wm.autoConnect(SSID, PASSWORD)){
    myOledViewWifiAP->setNomDuSysteme("SACTemperature"); //mettre variable
    myOledViewWifiAP->setSSIDDuSysteme(SSID);
    myOledViewWifiAP->setPassDuSysteme(PASSWORD); 
    myOled->displayView(myOledViewWifiAP);
    Serial.println("Failed to connect and hit timeout");
    delay(3000);
  };                           //On se connecte au réseau WiFi


  // ----------- Routes du serveur ----------------
  myServer = new MyServer(80);
  myServer->initAllRoutes();
  myServer->initCallback(&CallBackMessageListener);
}

void loop() {
}