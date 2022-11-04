/**
    Class MyOledViewWorking : Vue utilisée par MyOled (Affiche la page montrant le système en opération)
    @file MyOledViewWorking.h 
    @author Alain Dubé
    @version 1.1 21/09/20 
    
    Historique des versions   
                            Versions  Date      Auteur      Description
                            1.1      21/09/20   Ald         Première version de la classe
                            
                            
    platform = espressif32
    board = esp32doit-devkit-v1
    framework = arduino
    lib_deps = 
        Aucune
    Autres librairies (à copier dans le répertoire lib)
        Aucune
    
    Exemple d'utilisation 
        #include "MyOledViewWorking.h"
        MyOledViewWorking *myOledViewWorking = NULL;
        myOledViewWorking = new MyOledViewWorking();
        myOledViewWorking->setNomDuSysteme(nomDuSysteme.c_str());
        myOledViewWorking->setIpDuSysteme(WiFi.localIP().toString().c_str());
        myOledViewWorking->setStatusDuSysteme("System OK");
        myOled->displayView(myOledViewWorking);
**/
#ifndef MYOLEDVIEWWIFIAP_H
#define MYOLEDVIEWWIFIAP_H
#include "MyOledView.h"
#include <string>


class MyOledViewWifiAP: public MyOledView {
    public:
        void init(std::string _id);
        void setNomDuSysteme(std::string nomDuSysteme);
        void setSSIDDuSysteme(std::string ssidDuSysteme);
        void setPassDuSysteme(std::string passDuSysteme);
    
    protected:
        void display( Adafruit_SSD1306 *adafruit);
        void update(Adafruit_SSD1306 *adafruit);
        std::string nomDuSysteme;
        std::string ssidDuSysteme;
        std::string passDuSysteme;
};
#endif