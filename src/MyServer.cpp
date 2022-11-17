
/**
    Gestion d'un serveur WEB
    @file MyServer.cpp
    @author Alain Dubé
    @version 1.1 20/11/20 
*/
#include <Arduino.h>
#include "MyServer.h"
#include <ArduinoJson.h>
using namespace std;

typedef std::string (*CallbackType)(std::string);
CallbackType MyServer::ptrToCallBackFunction = NULL;

//Exemple pour appeler une fonction CallBack
//if (ptrToCallBackFunction) (*ptrToCallBackFunction)(stringToSend); 
void MyServer::initCallback(CallbackType callback) {
    ptrToCallBackFunction = callback;
    }

void MyServer::initAllRoutes() { 
    currentTemperature = 3.3f;

    //Initialisation du SPIFF.
    if (!SPIFFS.begin(true)) {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
        }

    //Route initiale (page html)
    this->on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/index.html", "text/html");
        });

    //Route du script JavaScript
    this->on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/script.js", "text/javascript");
        });

this->on("/getAllWoodOptions", HTTP_GET, [](AsyncWebServerRequest *request) {
        Serial.println("getAllWoodOptions... ");

        HTTPClient http;
        String woodApiRestAddress = "http://51.79.84.135:9999/api/woodlist";
        bool beginResult = http.begin(woodApiRestAddress);
        if(!beginResult){
            Serial.println("Erreur de connection au serveur");
        }
        else{
            Serial.println("Connection au serveur réussie");
            http.addHeader("authorization", "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VybmFtZSI6ImFsYSIsImlhdCI6MTY2MTUxNjAzNX0.4eGrq5XuJM1AcFnrxsRLHZp7e7E6v_u8lh6gEVAoU0Q");
            http.GET();
            String response = http.getString();
            Serial.println(response);
            http.end();
        }

/*
        if(response[response.length()-1]==']') response[response.length()-1] = ' ';
        if(response[0]=='[') response[0] = ' ';

        Serial.println(response);
        String tempToSend;
        StaticJsonDocument<2048> doc;
        deserializeJson(doc, response);
        JsonObject obj1 = doc.as<JsonObject>();
        std::string wood;
        String woodName;


      
        for (JsonPair kv1 : obj1) {
            wood = kv1.key().c_str();
            Serial.print("Element : ");Serial.println(wood.c_str());

            JsonObject elem = obj1[wood];
            woodName = elem["name"].as<String>();
            if(tempToSend!="") tempToSend += "&";
            tempToSend +=  String(wood.c_str()) + String("&") + String(woodName.c_str());
           
            Serial.print(woodName);Serial.print(" ");
                          
            //Pour parcourir les éléments de l'objet
            //for (JsonPair kv2 : elem) {
            //    Serial.print("   Sous element : ");Serial.print(kv2.key().c_str());
            //    Serial.print("    :  ");Serial.println(kv2.value().as<char*>());
            //    }
            }
        
        */
        //request->send(200, "text/plain", tempToSend);
        request->send(200, "text/plain", "okgood");
    });






    
    this->begin();
};