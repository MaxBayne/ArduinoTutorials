#ifndef PWMScope
#define PWMScope

/*
PWM (Pulse Width Modulation) Simulation For Analog Writer

Pin Description -------------

Any Digital Pin with ~ can use To Generate PWM

Analog Writer Range (0:255)


Start Example: ---------------------------------------------------------------

//Include Header
#include <PWM.h>

//Global Variable
PWM pwm;
//or
PWM pwm(&printerHelper);


//Inside Setup Method
pwm.Setup(6);            //can write the default range for analog (0:255)
//or
pwm.Setup(6,true);      //will map the input to range 0:255

//Inside Loop Method

//Write PWM Value (Analog Value using PWM Range 0:255)
pwm.write(value);

End Example: ---------------------------------------------------------------

*/

#include <Arduino.h>
#include <HelperPrint.h>

class PWM
{

private:

    //Module Name For Debug Purpose
    String _MoudleName = "PWM";

    //Pointer Reference For Serial Printer Helper
    PrinterHelper *_printerHelper;

    //Pin For PWM
    uint8_t _pwmPin;

    //Map the Value To Range (0:255)
    bool _withRange;

public:
    //Constructors -----------------
    PWM() {}

    PWM(PrinterHelper *printerHelper)
    { 
        _printerHelper = printerHelper;
    }

    //Destructors -------------------
    ~PWM() {}

    //Methods     -------------------

    //Config
    void Setup(uint8_t pin,bool withRange=false)
    {
        _pwmPin = pin;

        _withRange = withRange;

        pinMode(_pwmPin, OUTPUT);
    }

    //Write Analog PWM Value
    void Write(int value)
    {
        if (_withRange)
        {
            //Map Value Inside Range
            analogWrite(_pwmPin, map(value, 0, 1023, 0, 255));
        }
        else
        {
            analogWrite(_pwmPin,value);
        }
    }
};

#endif //PWMScope