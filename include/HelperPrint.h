#ifndef HelperLightsScope
#define HelperLightsScope

#include <Arduino.h>

class PrinterHelper
{
private:
unsigned long _serialSpeed;

public:
    //Constructors -----------------
    PrinterHelper()
    {
        _serialSpeed = 9600;
    }
    PrinterHelper(unsigned long speed)
    {
        _serialSpeed=speed;
    }

    //Destructors -------------------
    ~PrinterHelper() {}

    //Methods     -------------------

    //Config Serial Settings
    void Setup()
    {
        Serial.begin(_serialSpeed);
    }
    void Setup(unsigned long speed)
    {
        _serialSpeed=speed;
        
        Serial.begin(_serialSpeed);
    }

    void SetSpeed(unsigned long speed)
    {
        _serialSpeed = speed;

        Serial.end();

        Serial.begin(_serialSpeed);
    }


    static void println(String caption, String msg)
    {
        Serial.println(caption + ":> " + msg);
    }

    static void println(String module,String caption, String msg)
    {
        Serial.println(module+" ("+caption+") " + ":> " + msg);
    }

    static void println(String msg)
    {
        Serial.println(msg);
    }

    static void println(uint8_t msg)
    {
        Serial.println(msg);
    }

    static void println(int32_t msg)
    {
        Serial.println(msg);
    }

    static void println(unsigned long msg)
    {
        Serial.println(msg);
    }

    static void println(float msg)
    {
        Serial.println(msg);
    }

    static void print(String msg)
    {
        Serial.print(msg);
    }

    static void print(uint8_t msg)
    {
        Serial.print(msg);
    }

    static void print(int32_t msg)
    {
        Serial.print(msg);
    }

    static void print(unsigned long msg)
    {
        Serial.print(msg);
    }

    static void print(float msg)
    {
        Serial.print(msg);
    }
};

#endif //HelperLightsScope