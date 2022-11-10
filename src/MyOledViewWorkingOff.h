#ifndef MYOLEDVIEWWORKINGOFF_H
#define MYOLEDVIEWWORKINGOFF_H
#include "MyOledViewWorking.h"

class MyOledViewWorkingOff: public MyOledViewWorking {
    protected:
        void display( Adafruit_SSD1306 *adafruit);
};
#endif