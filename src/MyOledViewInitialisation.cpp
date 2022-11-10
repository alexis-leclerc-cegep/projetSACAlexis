/**
 * @file MyOledViewInitialisation.cpp
 * @author alexis leclerc 
 * @brief Vue qui est affichée pendant l'initialisation du système
 * @version 0.1
 * @date 2022-11-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Arduino.h"
#include "MyOledViewInitialisation.h"

using namespace std;

void MyOledViewInitialisation::setNomDuSysteme(std::string _nomDuSysteme) {
    nomDuSysteme = _nomDuSysteme;
}

void MyOledViewInitialisation::setIdDuSysteme(std::string _idDuSysteme) {
    idDuSysteme = _idDuSysteme;
}

void MyOledViewInitialisation::setSensibiliteBoutonAction(std::string _SensibiliteBoutonAction) {
    SensibiliteBoutonAction = _SensibiliteBoutonAction;
}

void MyOledViewInitialisation::setSensibiliteBoutonReset(std::string _SensibiliteBoutonReset) {
    SensibiliteBoutonReset = _SensibiliteBoutonReset;
}

void MyOledViewInitialisation::update(Adafruit_SSD1306 *adafruit){
    Serial.println("Update my view MyOledViewInitialisation");
}

void MyOledViewInitialisation::display(Adafruit_SSD1306 *adafruit){
    adafruit->clearDisplay();

    adafruit->setTextSize(2);
    adafruit->setTextColor(WHITE);
    adafruit->setCursor(0,0);
    adafruit->print(nomDuSysteme.c_str());

    adafruit->setTextSize(1);
    adafruit->setCursor(0,20);
    adafruit->print("INITIALISATION");

    adafruit->setCursor(0,30);
    adafruit->print("Bouton action: ");
    adafruit->print(SensibiliteBoutonAction.c_str());

    adafruit->setCursor(0,40);
    adafruit->print("Bouton reset: ");
    adafruit->print(SensibiliteBoutonReset.c_str());



}