#ifndef ManagerLightsScope
#define ManagerLightsScope

/*
Manager For Lights
*/


#include <HelperPrint.h>

//Lights Names
enum Lights
{
    WhiteLightsSmall,
    WhiteLightsBig,
    YellowLightsBig
};

//Lights State ON/OFF
enum LightsStates
{
    ON=HIGH,
    OFF=LOW
};


class LightsManager
{
private:

    //Module Name For Debug Purpose
    String _MoudleName = "LightsManager";

    //Module Of Printer Serial
    PrinterHelper *_PrinterHelper;

    //Pin of Big White Lights
    uint8_t _WhiteLightsBigPin;

    //Pin of Big Yellow Lights
    uint8_t _YellowLightsBigPin;

    //Pin of Small White Lights
    uint8_t _WhiteLightsSmallPin;

    
    //State of Big White Lights (OFF: turn off,ON:turn on)
    LightsStates _WhiteLightsBigState;

    //State of Big Yellow Lights (OFF: turn off,ON:turn on)
    LightsStates _YellowLightsBigState;

    //State of Small White Lights (OFF: turn off,ON:turn on)
    LightsStates _WhiteLightsSmallState;

   
    //store state of Play/Stop button where Play=true,Stop=false
    bool _StartMode;


public:
    //Constructors -----------------
    LightsManager(PrinterHelper *printerHelper) 
    {
        _PrinterHelper = printerHelper;
    }

    //Destructors -------------------
    ~LightsManager() {}


    //Methods     -------------------

    //Config Lights Manager
    void Setup(uint8_t bigWhiteLightsPin = 0, uint8_t smallWhiteLightsPin = 0, uint8_t bigYellowLightsPin = 0, bool startMode = true)
    {
        _PrinterHelper->println(_MoudleName, "Setup", "Start Setup Lights");

        //Config the Output Pins For Lights

        //Config Big white Lights
        if (bigWhiteLightsPin != 0)
        {
            _WhiteLightsBigPin = bigWhiteLightsPin;

            pinMode(_WhiteLightsBigPin, OUTPUT);
        }

        //Config Small white Lights
        if (smallWhiteLightsPin != 0)
        {
            _WhiteLightsSmallPin = smallWhiteLightsPin;

            pinMode(_WhiteLightsSmallPin, OUTPUT);
        }

        //Config Big Yellow Lights
        if (bigYellowLightsPin != 0)
        {
            _YellowLightsBigPin = bigYellowLightsPin;

            pinMode(_YellowLightsBigPin, OUTPUT);
        }

       
        //Turn Off All Lights as Default States
        ChangeLightsState(LightsStates::OFF);

        //Set Default Light When Startup
        ChangeLightState(Lights::WhiteLightsSmall, LightsStates::ON);

        _StartMode = startMode; //Default Mode When MicroController Run First Time

        _PrinterHelper->println(_MoudleName, "Setup", "End Setup Lights");
    }

    //Change the State of Light , state = (ON: mean turn on light,OFF: mean turn off light)
    void ChangeLightState(Lights light, LightsStates state)
    {
        switch (light)
        {
        case Lights::WhiteLightsSmall:
            _WhiteLightsSmallState = state;
            digitalWrite(_WhiteLightsSmallPin,_WhiteLightsSmallState);
            state == ON ? _PrinterHelper->println("LightsManager", "State", "turn ON Small White Lights") : _PrinterHelper->println("LightsManager", "State", "turn OFF Small White Lights");
            break;

        case Lights::WhiteLightsBig:
            _WhiteLightsBigState = state;
            digitalWrite(_WhiteLightsBigPin, _WhiteLightsBigState);
            state == ON ? _PrinterHelper->println("LightsManager", "State", "turn ON Big White Lights") : _PrinterHelper->println("LightsManager", "State", "turn OFF Big White Lights");
            break;

        case Lights::YellowLightsBig:
            _YellowLightsBigState = state;
            digitalWrite(_YellowLightsBigPin, _YellowLightsBigState);
            state == ON ? _PrinterHelper->println("LightsManager", "State", "turn ON Big Yellow Lights") : _PrinterHelper->println("LightsManager", "State", "turn OFF Big Yellow Lights");
            break;

        default:
            break;
        }
    }

    //Change hte State of All Lights , state = (ON: mean turn on light,OFF: mean turn off light)
    void ChangeLightsState(LightsStates state)
    {
        _WhiteLightsSmallState = state;
        digitalWrite(_WhiteLightsSmallPin, _WhiteLightsSmallState);

        _WhiteLightsBigState = state;
        digitalWrite(_WhiteLightsBigPin, _WhiteLightsBigState);

        _YellowLightsBigState = state;
        digitalWrite(_YellowLightsBigPin, _YellowLightsBigState);

        state == ON ? _PrinterHelper->println("LightsManager", "State", "turn ON All Lights") : _PrinterHelper->println("LightsManager", "State", "turn OFF All Lights");
    }

    //Swap the State of Light 
    void SwapLightState(Lights light)
    {
        switch (light)
        {
        case Lights::WhiteLightsSmall:
            _WhiteLightsSmallState == LightsStates::ON ? _WhiteLightsSmallState = LightsStates::OFF : _WhiteLightsSmallState = LightsStates::ON;
            digitalWrite(_WhiteLightsSmallPin, _WhiteLightsSmallState);
            _PrinterHelper->println(_MoudleName, "State", "Swap State of small white lights");
            break;

        case Lights::WhiteLightsBig:
            _WhiteLightsBigState == LightsStates::ON ? _WhiteLightsBigState = LightsStates::OFF : _WhiteLightsBigState = LightsStates::ON;
            digitalWrite(_WhiteLightsBigPin, _WhiteLightsBigState);
            _PrinterHelper->println(_MoudleName, "State", "Swap State of big white lights");
            break;

        case Lights::YellowLightsBig:
            _YellowLightsBigState == LightsStates::ON ? _YellowLightsBigState = LightsStates::OFF : _YellowLightsBigState = LightsStates::ON;
            digitalWrite(_YellowLightsBigPin, _YellowLightsBigState);
            _PrinterHelper->println(_MoudleName, "State", "Swap State of big yellow lights");
            break;

        default:
            break;
        }
    }

    //Swap the state of ON/OFF
    void SwapStartMode()
    {
        _StartMode = !_StartMode;

        if (_StartMode)
        {
            //Play Mode

            RunPlayMode();
        }
        else
        {
            //Stop Mode

            RunStopMode();
        }
    }

    void RunPlayMode()
    {
        _StartMode=true;

        //Play Mode

        ChangeLightState(Lights::WhiteLightsSmall, _WhiteLightsSmallState);
        ChangeLightState(Lights::WhiteLightsBig, _WhiteLightsBigState);
        ChangeLightState(Lights::YellowLightsBig, _YellowLightsBigState);

        _PrinterHelper->println(_MoudleName, "State", "Play Mode running");

    }

    void RunStopMode()
    {
        _StartMode = false;

        //Stop Mode

        digitalWrite(_WhiteLightsSmallPin, LOW);
        digitalWrite(_WhiteLightsBigPin, LOW);
        digitalWrite(_YellowLightsBigPin, LOW);

        _PrinterHelper->println(_MoudleName, "State", "Stop Mode running");

    }
    
    //Get StartMode Value true:Play Mode , false:Stop Mode
    bool GetStartMode()
    {
        return _StartMode;
    }

};

#endif //ManagerLightsScope