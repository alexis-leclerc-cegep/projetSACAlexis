#include "MyOledViewWorkingOff.h"

void MyOledViewWorkingOff::display( Adafruit_SSD1306 *adafruit) {

    MyOledViewWorking::display(adafruit);

    adafruit->setCursor(10, 30);
    adafruit->setTextSize(2);
    adafruit->print(getTag("temperature").c_str());

    adafruit->setCursor(80, 20);
    adafruit->setTextSize(1);
    adafruit->print("Ready");

    adafruit->display();
}