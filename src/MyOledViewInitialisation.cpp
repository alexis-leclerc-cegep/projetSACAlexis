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

}