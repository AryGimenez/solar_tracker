

#include <Servo.h> 
#include <Time.h>


 
Servo servo_Vertical;      // create servo object to control a servo (Vertical)
Servo servo_Horizonal;  // create servo object to control a servo (Horizontal)
int val_Vertical=90;        // variable to read the value from the analog pin 
int val_Horizonal=90;       // variable to read the value from the analog pin 

//===============================================================================
const int referenceVolts = 5;
const float R1 = 51000.0; //Resistor #1 (51K) <?>
const float R2 = 100000.0; //Resistor #2 (100K)
const float Ratio = (R1/R2);
const float resistorFactor = ((referenceVolts/Ratio)/1023.0);  // eq 0.014471088

const int TolarencePin = A4; // Use Potentiometer for Tolarence Settings 
const int solarPin = A5;     // +V from Solar Panel connected to analog pin 
float v = 0;






z<


//  LED del Sensor de Seguimiento Solar -  LED lights of the Solar Tracking Sensor

const int LDR_1_Left = A0;        // LDR connected to Analog Pin 0 Left
const int LDR_2_Right = A1;       // LDR connected to Analog Pin 1 Right
const int LDR_3_Down = A2;        // LDR connected to Analog Pin 2 Down
const int LDR_4_Up = A3;          // LDR connected to Analog Pin 3 Up






//
int LDR_1_Left_val = 0;
int LDR_2_Right_val = 0;
int LDR_4_Up_val = 0;
int LDR_3_Down_val = 0;
//

// Led que indicadores Aun no se vie que hasen supongo que indica Led LDR_1_Left
//LEDs 10=UP; 11=Right; 12=Left; 13=Down
int ledPins[] = {10,11,12,13};
// 
int dtime = 25; 
int Tolarence = 0;

void setup() 
{ 
  servo_Vertical.attach(5);   // attaches the servo on pin 5 (Elevation) to the servo object 
  servo_Horizonal.attach(6);  // attaches the servo on pin 6 (Horizontal) to the servo object
  
  //Setup LED Pins as OUTPUT
  for (int x = 0; x < 4; x++){
      pinMode(ledPins[x], OUTPUT);  
  }
  Serial.begin(9600); 
} 
 
void loop() 
{ 
  reset_leds();
  read_potentiometer();
  read_voltage();   
  read_LDRs();
  adjust_Servos();
  
  display_status();  
  delay(dtime);                           // waits for the servo to move 
} 

//=========================================================================

// Subs....


//=========================================================================
void reset_leds(){
 for (int x = 0; x < 4; x++){
        digitalWrite(ledPins[x], LOW); 
 }
}
//=========================================================================
void read_potentiometer(){
// Use Potentiometer for Tolarence Settings  
  Tolarence = analogRead(TolarencePin)/4;
}

//=========================================================================
void read_voltage(){
 v = analogRead(solarPin); 
 v *= resistorFactor;
} // end read_voltage

//=========================================================================
void read_LDRs(){
// Set the LDRs in an x config and label the LDRs from 1-4 
//    \ 4 /
//    1 X 2
//    / 3 \1
///arduino LDR Pins 10=UP; 11=Right; 12=Left; 13=Down 
 LDR_1_Left_val = analogRead(LDR_1_Left);
 LDR_2_Right_val = analogRead(LDR_2_Right);
 LDR_3_Down_val = analogRead(LDR_3_Down);
 LDR_4_Up_val = analogRead(LDR_4_Up); 
} //end read_LDRs

//=========================================================================
void adjust_Servos(){
 
int avg_Left_Top =     (LDR_1_Left_val +  LDR_4_Up_val) / 2;        // average value Left_Top
int avg_Left_Botton =  (LDR_1_Left_val +  LDR_3_Down_val) / 2;      // average value Left_Botton
int avg_Right_Top =    (LDR_2_Right_val + LDR_4_Up_val) / 2;        // average value Right_Top
int avg_Right_Botton = (LDR_2_Right_val + LDR_3_Down_val) / 2;      // average value Right_Botton

int dvert = (avg_Left_Top + avg_Right_Top) - (avg_Left_Botton + avg_Right_Botton); // check the diffirence of up and down
int dhoriz = (avg_Left_Top + avg_Left_Botton) - (avg_Right_Top + avg_Right_Botton);// check the diffirence og left and rigt

// Using the tolarence value stop servo seeking
// Check Vertical
   if (-1*Tolarence > dvert || dvert > Tolarence){ // check if the diffirence is in the tolerance else change vertical angle
      if ((avg_Left_Top + avg_Right_Top) > (avg_Left_Botton + avg_Right_Botton)){
         //adjust Vertical Servo Down
         digitalWrite(ledPins[3], HIGH); //Blink the Bottom LED
         val_Vertical = ++val_Vertical;
         if (val_Vertical > 179){
             val_Vertical = 179;
         }
      }
      else if ((avg_Left_Top + avg_Right_Top) < (avg_Left_Botton + avg_Right_Botton)){
        //adjust Vertical Servo Up
        val_Vertical= --val_Vertical;
        digitalWrite(ledPins[0], HIGH); //Blink the Top LED
        if (val_Vertical < 1){
            val_Vertical = 1;
         }
      }
      servo_Vertical.write(val_Vertical);
   }
//Check Horizonal
   if (-1*Tolarence > dhoriz || dhoriz > Tolarence){ // check if the diffirence is in the tolerance else change horizontal angle
      if ((avg_Left_Top + avg_Left_Botton) > (avg_Right_Top + avg_Right_Botton)){
         //adjust Horizonal Servo Left
         val_Horizonal = --val_Horizonal;
         digitalWrite(ledPins[1], HIGH); //Blink the Left LED
         if (val_Horizonal < 1){
             val_Horizonal = 1;
         }
      }
      else if ((avg_Left_Top + avg_Left_Botton) < (avg_Right_Top + avg_Right_Botton)){
         //adjust Horizonal Servo Right
         val_Horizonal = ++val_Horizonal;
         digitalWrite(ledPins[2], HIGH); //Blink the Right LED
         if (val_Horizonal > 179){
             val_Horizonal = 179;
         }
      }
      else if ((avg_Left_Top + avg_Left_Botton) == (avg_Right_Top + avg_Right_Botton)){
         // nothing
      }
      servo_Horizonal.write(val_Horizonal);
   }
} // end adjust servos
  
//========================================================================
void display_status(){
 Serial.print("Solar Panel Volts: ");
 Serial.print(v);
 
 Serial.print("  Servo Horizontal: ");
 Serial.print(val_Horizonal);
 Serial.print("  Servo Vertical: ");
 Serial.print(val_Vertical);
 
 Serial.print("  LDR_1_L: ");
 Serial.print(LDR_1_Left_val);
 Serial.print("  LDR_2_R: ");
 Serial.print(LDR_2_Right_val);
 Serial.print("  LDR_3_D: ");
 Serial.print(LDR_3_Down_val);
 Serial.print("  LDR_4_U: ");
 Serial.print(LDR_4_Up_val);
 
 Serial.print("  Tolarence: ");
 Serial.println(Tolarence);
} //end display status
