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
#include <WiFiManager.h>


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
  dht.begin();                                              //Initialisation du capteur DHT
  delay(100);

  wm.autoConnect(SSID, PASSWORD);                           //On se connecte au réseau WiFi

  // ----------- Routes du serveur ----------------
  myServer = new MyServer(80);
  myServer->initAllRoutes();
  myServer->initCallback(&CallBackMessageListener);
}

void loop() {
}