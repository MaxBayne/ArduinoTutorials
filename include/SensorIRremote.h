#ifndef SensorIRremoteScope
#define SensorIRremoteScope

/*
Sensor Pins (From Left To Right Pins)
1: (OutPut Signal)
2: (GND)
3: (+5v)
*/

#include <HelperPrint.h>
#include <ManagerLights.h>
#include <IRremote.h>
#include <SensorPIR.h>

enum PrintResultType
{
    AsVariables,
    Minimal,
    RawFormatted,
    Short
};

enum IRRemoteCommand
{
    PlayStop = 0x1,              //Red Button  (Play: turn on Current Lights , Stop: turn off Current Lights)
    Mode = 0x1A,                 //Mode Button (Auto: PIR ON , Manual:PIR OFF)
    ONOFFSmallWhiteLights = 0x2, //|<< Button  (ON: turn on Small White Lights,OFF: turn off Small White Lights)
    ONOFFBigWhiteLights = 0x3,   //>>| Button  (ON: turn on Big White Lights,OFF: turn off Big White Lights)
    ONOFFBigYellowLights = 0x6   //Vol+ Button (ON: turn on Big Yellow Lights,OFF: turn off Big Yellow Lights)
};

class IRremoteSensor
{

private:
    
    //Module Name For Debug Purpose
    String _MoudleName = "IRremoteSensor";

    //Pointer Reference For Serial Printer Helper
    PrinterHelper *_printerHelper;
    
    //Pointer Reference For Lights Manager
    LightsManager *_lightsManager;

    //Pointer Reference For PIR Sensor
    PIRSensor *_pirSensor;

    //Store Pin Number For Microcontroller that Connected IRremote Sensor Pin Out
    uint8_t _IRReceiverPin;

    //Store Timer Duration For IRremote To Recieve Signals and Process it by MileSeconds , Default is Every One Second (1000)
    uint32_t _IRTimerDuration=1000;

    //Store Timer Start by MileSeconds
    unsigned long _IRTimerStart=0;


    //Check if Timer is Valid To Execute Command or Not 
    bool IsValidTimer()
    {
        return millis() - _IRTimerStart >= _IRTimerDuration;
    }

    //Store the Current Millis to be the Start time of Timer
    void RestartTimer()
    {

        _IRTimerStart = millis();
    }



public:
    //Constructors -----------------
    IRremoteSensor(PrinterHelper *printerHelper, LightsManager *lightsManager, PIRSensor *pirSensor)
    {
        _printerHelper = printerHelper;
        _lightsManager = lightsManager;
        _pirSensor = pirSensor;
    }
    IRremoteSensor(PrinterHelper *printerHelper, LightsManager *lightsManager, PIRSensor *pirSensor, uint8_t pin)
    {
        _printerHelper = printerHelper;
        _lightsManager = lightsManager;
        _pirSensor = pirSensor;
        _IRReceiverPin = pin;
    }

    //Destructors -------------------
    ~IRremoteSensor() {}

    //Methods     -------------------

    //config IRremote Settings , Config Timer Settings
    void Setup(uint8_t pin, uint32_t timerDuration = 1000)
    {

        _printerHelper->println(_MoudleName, "Setup", "Start Setup IRremote Sensor");

        //Config Timer
        _IRTimerDuration = timerDuration;

        //config IR Remote
        _IRReceiverPin = pin;

        IrReceiver.begin(_IRReceiverPin);

        _printerHelper->println(_MoudleName, "Setup", "End Setup IRremote Sensor");
    }

    //Capture Signals For IR Remote , and Execute Commands Depend on that Commands
    void ProcessSignals(bool printResult = false, PrintResultType resultType = Short)
    {
        //Check if Timer is Valid
        if (!IsValidTimer()) return;
        

        if (IrReceiver.decode())
        {
            //Print Data over Serial
            if (printResult)
            {
                switch (resultType)
                {
                case AsVariables:
                    IrReceiver.printIRResultAsCVariables(&Serial);
                    break;

                case Minimal:
                    IrReceiver.printIRResultMinimal(&Serial);
                    break;

                case RawFormatted:
                    IrReceiver.printIRResultRawFormatted(&Serial);
                    break;

                case Short:
                    IrReceiver.printIRResultShort(&Serial);
                    break;

                default:
                    break;
                }

                //IrReceiver.printIRResultShort(&Serial);
            }

            //Execute Actions Depend on Command
            ExecuteAction(IrReceiver.decodedIRData.command);

            //Resume Ir Working For Receive Signals
            IrReceiver.resume();
        }

        //Restart Timer
        RestartTimer();
    }

    //Execute Actions
    void ExecuteAction (uint16_t command)
    {
        if (command == IRRemoteCommand::PlayStop || command == 0x45) //playStop Button
        {
            _lightsManager->SwapStartMode();
        }
        else if (command == IRRemoteCommand::Mode || command == 0x47) //Mode Button
        {
            _pirSensor->SwapPIRMode();
        }
        else if (command == IRRemoteCommand::ONOFFSmallWhiteLights || command == 0x44) //|<<
        {
            _lightsManager->SwapLightState(Lights::WhiteLightsSmall);
        }
        else if (command == IRRemoteCommand::ONOFFBigWhiteLights || command == 0x40) //>>|
        {
            _lightsManager->SwapLightState(Lights::WhiteLightsBig);
        }
        else if (command == IRRemoteCommand::ONOFFBigYellowLights || command == 0x43) //Vol+
        {
            _lightsManager->SwapLightState(Lights::YellowLightsBig);
        }
        else if (command == 0x5 || command == 0x46) //Swap All Lights
        {
            _lightsManager->SwapLightState(Lights::WhiteLightsSmall);
            _lightsManager->SwapLightState(Lights::WhiteLightsBig);
            _lightsManager->SwapLightState(Lights::YellowLightsBig);
        }
    }
};

#endif //SensorIRremoteScope