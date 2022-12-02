/**
    Class MyOledViewWorkingHEAT :  Pour la gestion de l'afffichage du mode HEAT sur notre écran OLED
    @file MyOledViewWorkingHEAT.h 
    @author Alexis Leclerc
    @version 1.0 12/2/2022
    
**/
#ifndef MYOLEDVIEWWORKINGHEAT_H
#define MYOLEDVIEWWORKINGHEAT_H

#include <Adafruit_SSD1306.h>
#include "MyOledViewWorking.h"
#include <string>
#include <vector>
using std::vector;

class MyOledViewWorkingHeat : public MyOledViewWorking {
    public:

    private:
        void display( Adafruit_SSD1306 *adafruit);
        void update(Adafruit_SSD1306 *adafruit);
   };
#endif