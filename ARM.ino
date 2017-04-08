//This example drives a robot in left and right arcs, driving in an overall wiggly course.
//  It demonstrates the variable control abilities. When used with a RedBot chassis,
//  each turn is about 90 degrees per drive.
//
//  Pin 8 can be grounded to disable motor movement, for debugging.

#include <Arduino.h>
#include <stdint.h>
#include "SCMD.h"
#include "SCMD_config.h" //Contains #defines for common SCMD register names and values
#include "Wire.h"

SCMD myMotorDriver; //This creates the main object of one motor driver and connected slaves.

int input[2];

void setup()
{
  pinMode(8, INPUT_PULLUP); //Use to halt motor movement (ground)

  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);

  Serial.begin(9600);
  Serial.println("Starting sketch.");

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
    Serial.println( "ID mismatch, trying again" );
    delay(500);
  }
  Serial.println( "ID matches 0xA9" );

  //  Check to make sure the driver is done looking for slaves before beginning
  Serial.print("Waiting for enumeration...");
  while ( myMotorDriver.ready() == false );
  Serial.println("Done.");
  Serial.println();

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

void Hammer(){
  myMotorDriver.setDrive(0,0,150);
  myMotorDriver.setDrive(1,0,150);
  delay(200);
  myMotorDriver.setDrive(0,0,0);
  myMotorDriver.setDrive(1,0,0);
  delay(500);
  myMotorDriver.setDrive(0,1,150);
  myMotorDriver.setDrive(1,1,150);
  delay(220);
  myMotorDriver.setDrive(0,0,0);
  myMotorDriver.setDrive(1,0,0);
}

void Wrist(int angle){
  int count=0;
  myMotorDriver.setDrive(1,0,50);
  while (count<angle/2){
    if(digitalRead(2) == 1){
      count++;
    }
  }
  myMotorDriver.setDrive(1,0,0);
}

void Return(int angle, int angle2){
  int count=0;
  myMotorDriver.setDrive(1,1,50);
  while (count<angle/2){
    if(digitalRead(2) == 1){
      count++;
    }
  }
  myMotorDriver.setDrive(1,0,0);

  if(angle>0){
    myMotorDriver.setDrive(2,1,50);
    while (count<abs(angle)/2){
      if(digitalRead(4) == 1){
        count++;
      }
    }
    myMotorDriver.setDrive(2,0,0);
  }
  else{
    myMotorDriver.setDrive(2,0,50);
    while (count<angle/2){
      if(digitalRead(4) == 1){
        count++;
      }
    }
    myMotorDriver.setDrive(2,0,0);
  }
}

void Rotate(int angle){
  int count=0;
  if(angle<0){
    myMotorDriver.setDrive(2,1,50);
    while (count<abs(angle)/2){
      if(digitalRead(4) == 1){
        count++;
      }
    }
    myMotorDriver.setDrive(2,0,0);
  }
  else{
    myMotorDriver.setDrive(2,0,50);
    while (count<angle/2){
      if(digitalRead(4) == 1){
        count++;
      }
    }
    myMotorDriver.setDrive(2,0,0);
  }
}

void loop()
{
  //pass setDrive() a motor number, direction as 0(call 0 forward) or 1, and level from 0 to 255
 
  while (digitalRead(8) == 0); //Hold if jumper is placed between pin 8 and ground

  //***** Operate the Motor Driver *****//
  //  This walks through all 34 motor positions driving them forward and back.
  //  It uses .setDrive( motorNum, direction, level ) to drive the motors.

//  myMotorDriver.setDrive( Arm, 1, 50); 
//  myMotorDriver.setDrive( Wrist, 1, 20);
//  delay(200);
//  myMotorDriver.setDrive( Arm, 0, 0); 
//  myMotorDriver.setDrive( Wrist, 0, 0);
//  delay(1000);
//  myMotorDriver.setDrive( Arm, 0, 20); 
//  myMotorDriver.setDrive( Wrist, 0, 20);
//  delay(200);
//  myMotorDriver.setDrive( 2, 0, 200);

  //SOMEHOW GET DATA INTO input[]

  Wrist(input[1]);
  Rotate(input[2]);
  Hammer();
  Return(input[1],input[2]);
  delay(500);
}

