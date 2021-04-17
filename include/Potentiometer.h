#ifndef PotentiometerScope
#define PotentiometerScope

/*
Potentiometer (Variable Resistor)

Pin Description -------------

(LEG 01) = > +5 Voltage
(LEG 02) = > GND
(LEG 03) = > Analog Pin (A0:A5)

Analog Read From Range (0 : 1023) where 0 is 0 Voltage , 1023 is 5 Voltage

Start Example: ---------------------------------------------------------------

//Include Header
#include <Potentiometer.h>

//Global Variable
Potentiometer myPot;
//or
Potentiometer myPot(&printerHelper);


//Inside Setup Method
myPot.Setup(A0);            //can read the default range for analog (0:1023)
myPot.Setup(A0,true,0,100); //Can Map the range like (0:100)

//Inside Loop Method

//Read Potentiometer Value
int potValue = myPot.Value();

End Example: ---------------------------------------------------------------

*/

#include <Arduino.h>
#include <HelperPrint.h>

class Potentiometer
{

private:

    //Module Name For Debug Purpose
    String _MoudleName = "Potentiometer";

    //Pointer Reference For Serial Printer Helper
    PrinterHelper *_printerHelper;

    //Pin For Potentiometer
    uint8_t _potentiometerPin;

    //Map the Value To Range
    bool _withRange;

    //Range Start From
    int _rangeStart;

    //Range End To
    int _rangeEnd;

public:
    //Constructors -----------------
    Potentiometer() {}

    Potentiometer(PrinterHelper *printerHelper)
    { 
        _printerHelper = printerHelper;
    }

    //Destructors -------------------
    ~Potentiometer() {}

    //Methods     -------------------

    //Config
    void Setup(uint8_t pin,bool withRange=false,int rangeStart=0,int rangeEnd=255)
    {
        _potentiometerPin = pin;

        _withRange = withRange;

        _rangeStart = rangeStart;

        _rangeEnd = rangeEnd;

         pinMode(_potentiometerPin, INPUT);
    }

    //Read Potentiometer Value
    uint16_t Value()
    {
        int readAnalogValue = analogRead(_potentiometerPin);

            if (_withRange)
        {
            //Map Value Inside Range
            return map(readAnalogValue,0,1023,0,100);
        }
        else
        {
            return readAnalogValue;
        }
        
    }
};

#endif //PotentiometerScope