/**
 * @file MyOledViewWifiError.h
 * @author Alexis Leclerc
 * @brief la vue qui est affichée lorsque le wifi ne peut s'initier
 * @version 0.1
 * @date 2022-11-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef MYOLEDVIEWWIFIERROR_H
#define MYOLEDVIEWWIFIERROR_H
#include "MyOledView.h"
#include <string>


class MyOledViewWifiError: public MyOledView {
    public:
        void init(std::string _id);
        void setNomDuSysteme(std::string nomDuSysteme);
    
    protected:
        void display( Adafruit_SSD1306 *adafruit);
        void update(Adafruit_SSD1306 *adafruit);
        std::string nomDuSysteme;
};
#endif