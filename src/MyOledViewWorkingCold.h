/**
    Class MyOledViewWorkingCOLD :  Pour la gestion de l'afffichage du mode COLD sur notre écran OLED
    @file MyOledViewWorkingCOLD.h 
    @author Alexis Leclerc
    @version 1.0 18/11/22 
    **/
#ifndef MYOLEDVIEWWORKINGCOLD_H
#define MYOLEDVIEWWORKINGCOLD_H

#include <Adafruit_SSD1306.h>
#include "MyOledViewWorking.h"
#include <string>
#include <vector>
using std::vector;

class MyOledViewWorkingCold : public MyOledViewWorking {
    public:

    private:
        void display( Adafruit_SSD1306 *adafruit);
        void update(Adafruit_SSD1306 *adafruit);
   };
#endif