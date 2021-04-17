#ifndef ButtonPushScope
#define ButtonPushScope

/*
Button

Pull-up Resistor mean pin state is default HIGH , when Pressed become LOW
Pull-Down Resistor mean pin state is default LOW, when Pressed become HIGH


Start Example: ---------------------------------------------------------------

//Include Header
#include <ButtonPush.h>

//Global Variable
ButtonPush myButton(); 
//or
ButtonPush myButton(&printerHelper);


//Inside Setup Method
myButton.Setup(2,StateMode::HIGH_INTERNAL_State); //For Pull-up Internal Resistor
//or
myButton.Setup(2,StateMode::HIGH_State);          //For Pull-up External Resistor
//or
myButton.Setup(2,StateMode::LOW_State);           //For Pull-Down External Resistor

//Inside Loop Method

//Detect Button State
if (myButton.State() == ButtonState::ON)
  {
    //On Button Pressed
  }
  else
  {
    //On Button Not Pressed
  }

End Example: ---------------------------------------------------------------

*/

#include <Arduino.h>
#include <HelperPrint.h>

enum StateMode
{
    HIGH_INTERNAL_State, //use Pull UP Internal state to make default is HIGH , no need external resistor
    HIGH_State, //use Pull UP Resistor to make state default is HIGH
    LOW_State   //use Pull DOWN Resistor to make state default is LOW
};
enum ButtonState
{
    ON, //mean Button Clicked
    OFF //mean Button Not Clicked
};

class ButtonPush
{

private:

    //Module Name For Debug Purpose
    String _MoudleName = "PushButton";

    //Pointer Reference For Serial Printer Helper
    PrinterHelper *_printerHelper;
    
    //State mode For Button
    StateMode _stateMode;

    //Pin For Button
    uint8_t _buttonPin;

public:
    //Constructors -----------------
    ButtonPush(){}
    
    ButtonPush(PrinterHelper *printerHelper)
    { 
        _printerHelper = printerHelper;
    }

    //Destructors -------------------
    ~ButtonPush(){}

    //Methods     -------------------

    //Config
    void Setup(uint8_t pin,StateMode stateMode)
    {
        _buttonPin = pin;
        _stateMode = stateMode;

        switch (_stateMode)
        {
        case StateMode::HIGH_INTERNAL_State:
            pinMode(_buttonPin, INPUT_PULLUP);
             break;

        case StateMode::HIGH_State:
            pinMode(_buttonPin, INPUT);
            break;

        case StateMode::LOW_State:
            pinMode(_buttonPin, INPUT);
            break;
        }
    }

    //Read Button State
    ButtonState State()
    {
        if (_stateMode == StateMode::HIGH_INTERNAL_State || _stateMode == StateMode::HIGH_State)
        {
            //HIGH Mode the default state of pin is HIGH so when Button Pressed then pin state will be LOW
            if (digitalRead(_buttonPin) == LOW)
            {
                return ButtonState::ON;
            }
            else
            {
                return ButtonState::OFF;
            }
        }
        else
        {
            //LOW Mode the default state of pin is LOW so when Button Presesd then pin state will be HIGH

            if (digitalRead(_buttonPin) == HIGH)
            {
                return ButtonState::ON;
            }
            else
            {
                return ButtonState::OFF;
            }
        }
    }
};

#endif //ButtonPushScope