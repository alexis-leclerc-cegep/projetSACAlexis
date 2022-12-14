/**
    Gestion d'une VUE pour le OLed : Base pour les écrans de travail
    @file MyOledViewWifiAP.cpp
    @author Alain Dubé
    @version 1.1 20/11/20 
*/
#include <Arduino.h>
#include "MyOledViewWifiAP.h"

using namespace std;

void MyOledViewWifiAP::init(std::string _id) {
    MyOledView::init(_id);
    }

void MyOledViewWifiAP::setNomDuSysteme(std::string _nomDuSysteme) {
    nomDuSysteme = _nomDuSysteme;
}

void MyOledViewWifiAP::setSSIDDuSysteme(std::string _ssidDuSysteme) {
    ssidDuSysteme = _ssidDuSysteme;
}

void MyOledViewWifiAP::setPassDuSysteme(std::string _passDuSysteme) {
    passDuSysteme = _passDuSysteme;
}

 
void MyOledViewWifiAP::update(Adafruit_SSD1306 *adafruit){
    Serial.println("Update my view MyOledViewWifiAP");
    }

void MyOledViewWifiAP::display( Adafruit_SSD1306 *adafruit) {
    Serial.println("MyOledViewWifiAP");
    adafruit->setTextColor(WHITE);

    adafruit->clearDisplay();
    adafruit->setTextSize(2);
    adafruit->setCursor(0, 0);
    adafruit->print(nomDuSysteme.c_str());

    adafruit->setTextSize(1);
    adafruit->setCursor(0, 20);
    adafruit->print('AP Configuration');

    adafruit->setTextSize(1);
    adafruit->setCursor(0, 30);
    adafruit->print("SSID: ");
    adafruit->print(ssidDuSysteme.c_str());
    
    adafruit->setCursor(0, 40);
    adafruit->print("Password: ");
    adafruit->print(passDuSysteme.c_str());

    adafruit->display();
    }