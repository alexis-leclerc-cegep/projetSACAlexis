/**
 * @file MyOledViewInitialisation.h
 * @author alexis leclerc 
 * @brief Vue qui est affichée pendant l'initialisation du système
 * @version 0.1
 * @date 2022-11-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef MYOLEDVIEWINITIALISATION_H
#define MYOLEDVIEWINITIALISATION_H
#include "MyOledView.h"

class MyOledViewInitialisation: public MyOledView{
    public:
        std::string nomDuSysteme;
        std::string idDuSysteme;
        std::string SensibiliteBoutonAction;
        std::string SensibiliteBoutonReset;
        void setNomDuSysteme(std::string _nomDuSysteme);
        void setIdDuSysteme(std::string _idDuSysteme);
        void setSensibiliteBoutonAction(std::string _SensibiliteBoutonAction);  
        void setSensibiliteBoutonReset(std::string _SensibiliteBoutonReset);

    protected:
        void display( Adafruit_SSD1306 *adafruit);
        void update(Adafruit_SSD1306 *adafruit);
};
#endif