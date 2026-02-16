#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
#include<SoftwareSerial.h>
SoftwareSerial SUART(10, 11);//DPin-10 = SRX; DPin-11 = STX
float data[3];
float Vout = 0.00;
float Vin = 0.00;
float R1 = 100000.00; // resistance of R1 (100K) 
float R2 = 10000.00; // resistance of R2 (10K) 
float temp1;
int val = 0;
float valt,valtt;
float c1,c2,c3;

void setup()
{
  pinMode(A3, INPUT);
  pinMode(A2, INPUT);
  pinMode(A1, INPUT);
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);
  pinMode(13,OUTPUT); // for relay control
  Serial.begin(9600); 
  SUART.begin(9600); 
  
  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(7,0);
  lcd.print("BMS");
  
}

void loop()
{ 
  valt = analogRead(A6);
  valtt = analogRead(A7);
  float mv = ( valt/1024.0)*5000;
  float cel = mv/10;
  float mv1 = ( valtt/1024.0)*5000;
  float cel1 = mv/10; 
  
  Serial.print("T1 = ");
  Serial.print(cel);
  Serial.print("*C");
  Serial.println();
  Serial.print("T2 = ");
  Serial.print(cel1);
  Serial.print("*C");
  Serial.println();
  
  delay(1000);
  
   lcd.clear();
   val = analogRead(A3);
   Vout = (val * 5.00) / 1024.00; 
   Vin = Vout / (R2/(R1+R2)); 
   data[0]=Vin;
   if (Vin<0.09)
   {
     Vin=0.00;
  } 
  c1=Vin;
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("C1");
  lcd.setCursor(0,1);
  lcd.print(c3);
  SUART.print(data[0], 1);
  SUART.print(',');
  // for charging on off
  if(Vin>12.6)
  {
    digitalWrite(13,LOW);

  if(Vin<10.5)
  {
    digitalWrite(13,HIGH);
    
  }
  
  
// for cell 2 
  val = analogRead(A2);
   Vout = (val * 5.00) / 1024.00; 
   Vin = Vout / (R2/(R1+R2)); 
   data[1]=Vin;
   if (Vin<0.09)//condition 
   {
     Vin=0.00;
  } 
  c2=Vin;
  
  lcd.setCursor(8,0);
  lcd.print("C2");
  lcd.setCursor(7,1);
  c2=c2/2;
  lcd.print(c2);

  
  SUART.print(data[1], 1);
  SUART.print(',');
  
 
// for cell 3

  val = analogRead(A1);
   Vout = (val * 5.00) / 1024.00; 
   Vin = Vout / (R2/(R1+R2)); 
   data[2]=Vin;
   if (Vin<0.09) 
   {
     Vin=0.00;
  } 
  c3=Vin;
  
  lcd.setCursor(13,0);
  lcd.print("C3");
  lcd.setCursor(12,1);
  c1=c1/3;
  lcd.print(c1);
  
  
  SUART.print(data[2], 1);
  SUART.print(',');
  delay(1500);

// for Temperatures
  

  
  
  

  
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("T1");
  lcd.setCursor(0,1);
  lcd.print(cel);
  lcd.setCursor(12,0);
  lcd.print("T2");
  lcd.setCursor(10,1);
  lcd.print(cel1);
  delay(800);
  
  
}
