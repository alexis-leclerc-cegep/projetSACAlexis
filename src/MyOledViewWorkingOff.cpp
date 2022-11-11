#include "MyOledViewWorkingOff.h"

void MyOledViewWorkingOff::display( Adafruit_SSD1306 *adafruit) {
    Serial.println("MyOledViewWorkingOff");
    adafruit->setTextColor(WHITE);

    adafruit->clearDisplay();
    adafruit->setTextSize(2);
    adafruit->setCursor(0, 0);
    //ajouter des choses

    adafruit->setTextSize(1);
    adafruit->setCursor(0, 20);
    adafruit->print("Working Off");

    adafruit->display();
}