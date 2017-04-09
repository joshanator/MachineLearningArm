
//This example drives a robot in left and right arcs, driving in an overall wiggly course.
//  It demonstrates the variable control abilities. When used with a RedBot chassis,
//  each turn is about 90 degrees per drive.
//
//  Pin 8 can be grounded to disable motor movement, for debugging.

#include <Arduino.h>
#include <stdint.h>
#include "CmdMessenger.h"
#include "SCMD.h"
#include "SCMD_config.h" //Contains #defines for common SCMD register names and values
#include "Wire.h"

SCMD myMotorDriver; //This creates the main object of one motor driver and connected slaves.

//int input[2] = {300, 200};

enum{
  Wrist,
  Hammer,
  Rotate,
  Return,
};

CmdMessenger c = CmdMessenger(Serial,',',';','/');

void attach_callbacks(){
  c.attach(Wrist,onWrist);
  c.attach(Hammer,onHammer);
  c.attach(Rotate,onRotate);
  c.attach(Return,onReturn);
}

void setup()
{

  attach_callbacks();
  
  //pinMode(8, INPUT_PULLUP); //Use to halt motor movement (ground)

  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);

  Serial.begin(9600);
  //Serial.println("Starting sketch.");

  //***** Configure the Motor Driver's Settings *****//
  //  .commInter face can be I2C_MODE or SPI_MODE
  myMotorDriver.settings.commInterface = I2C_MODE;
  //myMotorDriver.settings.commInterface = SPI_MODE;

  //  set address if I2C configuration selected with the config jumpers
  myMotorDriver.settings.I2CAddress = 0x5A; //config pattern "0101" on board for address 0x5A

  //  set chip select if SPI selected with the config jumpers
  myMotorDriver.settings.chipSelectPin = 10;

  //*****initialize the driver get wait for idle*****//
  while ( myMotorDriver.begin() != 0xA9 ) //Wait until a valid ID word is returned
  {
    //Serial.println( "ID mismatch, trying again" );
    delay(500);
  }
  //Serial.println( "ID matches 0xA9" );

  //  Check to make sure the driver is done looking for slaves before beginning
  //Serial.print("Waiting for enumeration...");
  while ( myMotorDriver.ready() == false );
  //Serial.println("Done.");
  //Serial.println();

  delay(2500);



  //*****Set application settings and enable driver*****//

  //Uncomment code for motor 0 inversion
  //while( myMotorDriver.busy() );
  //myMotorDriver.inversionMode(0, 1); //invert motor 0

  //Uncomment code for motor 1 inversion
  while ( myMotorDriver.busy() ); //Waits until the SCMD is available.
  myMotorDriver.inversionMode(1, 1); //invert motor 1

  while ( myMotorDriver.busy() );
  myMotorDriver.enable(); //Enables the output driver hardware

  myMotorDriver.setDrive( 0, 0, 0); //Stop motor
  myMotorDriver.setDrive( 1, 0, 0); //Stop motor

}

void onHammer(){
  myMotorDriver.setDrive(0,1,150);
  myMotorDriver.setDrive(1,0,160);
  delay(350);
  myMotorDriver.setDrive(0,0,0);
  myMotorDriver.setDrive(1,0,0);
  delay(500);
  myMotorDriver.setDrive(0,0,170);
  myMotorDriver.setDrive(1,1,160);
  delay(380);
  myMotorDriver.setDrive(0,0,0);
  myMotorDriver.setDrive(1,0,0);
}

void onWrist(void){
  int angle = c.readBinArg<int>();
  //int count=0;
  myMotorDriver.setDrive(1,0,50);
//  while (count<angle/2){
//    //Serial.println(digitalRead(2));
//    for(int i=0; i; i++){
//      pulseIn(2, HIGH);
//      Serial.println(i);
//    }
//  }
  delay(angle);
  myMotorDriver.setDrive(1,0,0);
}

void onReturn(void){
  int angle = c.readBinArg<int>();
  int angle2 = c.readBinArg<int>();
  //int count=0;
  myMotorDriver.setDrive(1,1,80);
//  while (count<angle/2){
//    if(digitalRead(3) == 1){
//      count++;
//    }
//  }
  delay(angle);
  myMotorDriver.setDrive(1,0,0);


    myMotorDriver.setDrive(2,0,75);
//    while (count<abs(angle)/2){
//      if(digitalRead(4) == 1){
//        count++;
//      }
//    }
    delay(angle2+30);
    myMotorDriver.setDrive(2,0,0);
}

void onRotate(void){
  int angle = c.readBinArg<int>();
  int count=0;
    myMotorDriver.setDrive(2,1,75);
//    while (count<abs(angle)/2){
//      if(digitalRead(4) == 1){
//        count++;
//      }
//    }
  delay(angle);
    myMotorDriver.setDrive(2,0,0);
  
}

void loop()
{

  c.feedinSerialData();
  
  //pass setDrive() a motor number, direction as 0(call 0 forward) or 1, and level from 0 to 255
 
//  while (digitalRead(8) == 0); //Hold if jumper is placed between pin 8 and ground

  //***** Operate the Motor Driver *****//
  //  This walks through all 34 motor positions driving them forward and back.
  //  It uses .setDrive( motorNum, direction, level ) to drive the motors.


//  input[0] = (int) Serial.parseInt();
//  delay(10);
//  input[1] = (int) Serial.parseInt();
//
//  Wrist(input[0]);
//  Serial.println("Wrist");
//  delay(100);
//  Rotate(input[1]);
//  Serial.println("Rotate");
//  delay(100);
//  Hammer();
//  Serial.println("Hammer");
//  delay(100);
//  Return(input[0],input[1]);
//  Serial.println("Return");
//  delay(1000);

//myMotorDriver.setDrive(2,1,100);
//delay(500);
//myMotorDriver.setDrive(2,0,0);
//delay(500);
}

