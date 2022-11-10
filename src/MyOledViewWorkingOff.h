/**
 * @file MyOledViewWorkingOff.h
 * @author Alexis Leclerc
 * @brief Vue qui est affichée lorsque le système est en mode veille
 * @version 0.1
 * @date 2022-11-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef MYOLEDVIEWWORKINGOFF_H
#define MYOLEDVIEWWORKINGOFF_H
#include "MyOledViewWorking.h"

class MyOledViewWorkingOff: public MyOledViewWorking {
    protected:
        void display( Adafruit_SSD1306 *adafruit);
};
#endif