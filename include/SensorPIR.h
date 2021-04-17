#ifndef SensorPIRScope
#define SensorPIRScope

/*
Sensor Pins
VCC : (+5v)
GND : (Ground)
OUT : (Digital Signal HIGH/LOW)
Degree : 120
Range : 7 Meter
*/

#include <HelperPrint.h>
#include <ManagerLights.h>

class PIRSensor
{

private:
    //Module Name For Debug Purpose
    String _MoudleName = "PIRSensor";

    //Module of Printer Serial
    PrinterHelper *_printerHelper;

    //Manager For Lights
    LightsManager *_lightsManager;

    //Store Pin Number For Microcontroller that Connected PIR Sensor Pin Out
    uint8_t _PIRPin;

    //Store PIR Mode , while true:PIR ON , false:PIR off
    bool _PIRMode;

    //Store state of Detection true:mean detect Motion , false:No Detection
    bool _DetectMotion;

    //Light Flag For PIR is Auto Mode
    uint8_t _LightPin;

    //Can Use Light For PIR Flag that its On Auto Mode
    bool _UseLight;

public:
    //Constructors -----------------
    PIRSensor(PrinterHelper *printerHelper, LightsManager *lightsManager)
    {
        _printerHelper = printerHelper;
        _lightsManager = lightsManager;
    }

    //Destructors -------------------
    ~PIRSensor() {}

    //config PIR Settings with default OFF mode
    void Setup(uint8_t pirPin, bool pirMode = false, uint8_t lightPin = 0, bool useLight = false)
    {
        _printerHelper->println(_MoudleName, "Setup", "Start Setup PIR Sensor");

        //config PIR Remote
        _PIRPin = pirPin;

        //Config PIR Pin as Digital Input PULLUP Mean its default is HIGH
        pinMode(_PIRPin, INPUT_PULLUP);
        

        //Set Default Mode For PIR
        _PIRMode = pirMode;

        //Config Light Flag For PIR Mode AutoMode: turn ON Light ManualMode:turn off Light
        if (useLight)
        {
            _UseLight = useLight;
            _LightPin = lightPin;
            pinMode(_LightPin, OUTPUT);
            digitalWrite(_LightPin, LOW);
        }

        _printerHelper->println(_MoudleName, "Setup", "End Setup PIR Sensor");
    }

    //Capture Motions For PIR Sensor
    void DetectMotions()
    {
        //On Auto Mode Mean PIR Sensor Is ON
        if (_PIRMode)
        {
            int pirSensorRead = digitalRead(_PIRPin);

            if (pirSensorRead == HIGH)
            {
                //On Detect Motion Then Sure the Play Mode in Running

                if (_DetectMotion == false)
                {
                    _lightsManager->RunPlayMode();

                    _printerHelper->println(_MoudleName, "PlayMode", "Detect Motion So Run Play Mode");
                }

                _DetectMotion = true;
            }
            else if(pirSensorRead == LOW)
            {
                //No Motion Detected After Delay Time For Sensor (1 Minute) then sure Stop Mode is Running

                if (_DetectMotion == true)
                {
                    _lightsManager->RunStopMode();

                    _printerHelper->println(_MoudleName, "StopMode", "No Motion So Run Stop Mode");
                }

                _DetectMotion = false;
            }
        }
    }

    //Swap PIR Mode From ON/OFF
    void SwapPIRMode()
    {
        if (_PIRMode)
        {
            _PIRMode = false;

            digitalWrite(_LightPin, LOW);

            _printerHelper->println(_MoudleName, "Mode", "Swap PIR Mode To OFF");
        }
        else
        {
            _PIRMode = true;

            digitalWrite(_LightPin, HIGH);

            _printerHelper->println(_MoudleName, "Mode", "Swap PIR Mode To ON");
        }
    }
};

#endif //SensorPIRScope
