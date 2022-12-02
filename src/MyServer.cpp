
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
        Serial.println("Dans la route /");
        request->send(SPIFFS, "/index.html", "text/html");
        });

    //Route du script JavaScript
    this->on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/script.js", "text/javascript");
        });

    

    this->on("/setWoodTemperature", HTTP_GET, [](AsyncWebServerRequest *request) {
        if(request->hasParam("temp")){
            request->send(200, "text/plain",  "Temperature changed");
            String action = "setWoodTemperature" ;

            char buffer[40];

            String inputTemp = request->getParam("temp")->value();
            sprintf(buffer, "%s|%s", action.c_str(), inputTemp.c_str());
            if(ptrToCallBackFunction)(*ptrToCallBackFunction)(buffer);
        }
        else{
            request->send(400, "text/plain", "Temperature not changed");
        }
    });

    this->on("setWoodTemps", HTTP_GET, [](AsyncWebServerRequest *request) {
        if(request->hasParam("temps")){
            request->send(200, "text/plain",  "Temperature changed");
            String action = "setWoodTemps" ;

            char buffer[40];

            String inputTemp = request->getParam("temps")->value();
            sprintf(buffer, "%s|%s", action.c_str(), inputTemp.c_str());
            if(ptrToCallBackFunction)(*ptrToCallBackFunction)(buffer);
        }
        else{
            request->send(400, "text/plain", "Temps de séchage not changed");
        }
    });

    this->on("/lireTemp", HTTP_GET, [](AsyncWebServerRequest *request) {
        std::string repString = "";
        if (ptrToCallBackFunction) repString = (*ptrToCallBackFunction)("getTemp");
        request->send(200, "text/plain", repString.c_str());
    });

    this->on("/getWoodDetails", HTTP_GET, [](AsyncWebServerRequest *request) {
        if(request->hasParam("id")){
            AsyncWebParameter* p = request->getParam("id");
            HTTPClient http;
            String woodApiRestAddress = "http://51.79.84.135:2223/api/drying?id=" + p->value();
            String response = "Error";
            bool beginResult = http.begin(woodApiRestAddress);
            if(!beginResult){
                Serial.println("Erreur de connection au serveur");
            }
            else{
                Serial.println("Connection au serveur réussie");
                http.addHeader("authorization", "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VybmFtZSI6ImFsYSIsImlhdCI6MTY2MTUxNjAzNX0.4eGrq5XuJM1AcFnrxsRLHZp7e7E6v_u8lh6gEVAoU0Q");
                http.GET();
                response = http.getString();
                //if(response[response.length()-1]==']') response[response.length()-1] = ' ';
                //if(response[0]=='[') response[0] = ' ';
                Serial.println(response);
                http.end();
            }

            request->send(200, "text/plain", response);
        }
        else{
            request->send(400, "text/plain", "Error: Missing params");
        };
    });

    this->on("/getWoodName", HTTP_GET, [](AsyncWebServerRequest *request) {
        Serial.println("getWoodName... ");

        HTTPClient http;
        String woodApiRestAddress = "http://51.79.84.135:2223/api/woodlist";
        String response = "Error";
        bool beginResult = http.begin(woodApiRestAddress);
        if(!beginResult){
            Serial.println("Erreur de connection au serveur");
        }
        else{
            Serial.println("Connection au serveur réussie");
            http.addHeader("authorization", "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VybmFtZSI6ImFsYSIsImlhdCI6MTY2MTUxNjAzNX0.4eGrq5XuJM1AcFnrxsRLHZp7e7E6v_u8lh6gEVAoU0Q");
            http.GET();
            response = http.getString();
            //if(response[response.length()-1]==']') response[response.length()-1] = ' ';
            //if(response[0]=='[') response[0] = ' ';
            Serial.println(response);
            http.end();
        }

        request->send(200, "text/plain", response);
    });

    this->begin();
};