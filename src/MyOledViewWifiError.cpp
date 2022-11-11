/**
    Gestion d'une VUE pour le OLed : Base pour les écrans de travail
    @file MyOledViewWifiAP.cpp
    @author Alain Dubé
    @version 1.1 20/11/20 
*/
#include <Arduino.h>
#include "MyOledViewWifiError.h"

using namespace std;

void MyOledViewWifiError::init(std::string _id) {
    MyOledView::init(_id);
}

void MyOledViewWifiError::setNomDuSysteme(std::string _nomDuSysteme) {
    nomDuSysteme = _nomDuSysteme;
}

 
void MyOledViewWifiError::update(Adafruit_SSD1306 *adafruit){
    Serial.println("Update my view MyOledViewWifiError");
}

void MyOledViewWifiError::display( Adafruit_SSD1306 *adafruit) {
    Serial.println("MyOledViewWifiError");
    adafruit->setTextColor(WHITE);

    adafruit->clearDisplay();
    adafruit->setTextSize(2);
    adafruit->setCursor(0, 0);
    adafruit->print(nomDuSysteme.c_str());


    adafruit->display();
    }