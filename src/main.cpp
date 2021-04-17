//General Modules
#include <Arduino.h>        //Core of Ardunio
#include <HelperPrint.h>    //Helper For Print String over Serial
#include <Potentiometer.h>
#include <PWM.h>


//Sepreated Modules


//General Variables
PrinterHelper  printerHelper;
Potentiometer myPot;
PWM pwmRed;
PWM pwmGreen;
PWM pwmBlue;

void setup()
{

  //Config Helpers -------------------
  printerHelper.Setup(); //Config Serial Communications
  myPot.Setup(A0);
  pwmBlue.Setup(6, true);
  pwmGreen.Setup(5, true);
  pwmRed.Setup(3, true);
}

void loop()
{
  int val = myPot.Value();
  Serial.println(val);

  pwmBlue.Write(val);
  //pwmGreen.Write(val);
  pwmRed.Write(val);
}