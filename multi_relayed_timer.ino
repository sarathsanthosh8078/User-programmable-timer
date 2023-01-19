#include <EEPROM.h>
#include <stdint.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3f, 16, 2);


#define Set     4
#define upbtn   5
#define dnbtn   6
#define rset    7
#define relay_select  8


 int mode,relay_mode=0;
 int ONHH1,ONMM1,OFFHH1,OFFMM1;
 int ONHH2,ONMM2,OFFHH2,OFFMM2;
 int ONHH3,ONMM3,OFFHH33,OFFMM3;
 int ONHH4,ONMM4,OFFHH4,OFFMM4;

void setup()
{
  pinMode(relay_select,INPUT_PULLUP);
  pinMode(Set,INPUT_PULLUP);
  pinMode(upbtn,INPUT_PULLUP);
  pinMode(dnbtn,INPUT_PULLUP);
  pinMode(rset,INPUT_PULLUP);
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

}


void loop() 
{ 
  ONHH1=EEPROM.read(1);ONMM1=EEPROM.read(2);
  OFFHH1=EEPROM.read(3);OFFMM1=EEPROM.read(4);
  if(digitalRead(relay_select)== LOW)
  {
   relay_mode=relay_mode+1;
   if(relay_mode>4)
   relay_mode=0;
 /*  Serial.print("relay_mode=");
   Serial.print("\n");
   Serial.print(relay_mode);
   Serial.print("\n"); */

  lcd.setCursor(0,0);
  lcd.print("rel_mod=");
  lcd.setCursor(8,0);
  lcd.print(relay_mode);
  
   delay(500);
  }
  if(relay_mode==1)
  {
  Relay1();
  }
}
int Relay1()
{
  /* Serial.print("relay 1 settings");  
   Serial.print("\n");    
  */
  lcd.setCursor(10,0);
  lcd.print("R1");
  {
    if(digitalRead(Set)==LOW)
    mode=mode+1;
    if(mode>4)
    mode=1;
  lcd.setCursor(13,0);
  lcd.print(mode);
  delay(250);
  }
  if((digitalRead(upbtn)==LOW))
{
  if(mode==1)
  {
  ONHH1=ONHH1+1;
  if(ONHH1>23) 
    ONHH1=0;
  lcd.setCursor(0,1);
  lcd.print("ON TIME ");
  lcd.print(ONHH1); lcd.print(":"); lcd.print(ONMM1);
   
  }
  if(mode==2)
  {
  ONMM1=ONMM1+1;
  if(ONMM1>59)
    ONMM1=0;
  lcd.setCursor(0,1);
  lcd.print("ON TIME ");
  lcd.print(ONHH1); lcd.print(":"); lcd.print(ONMM1);
  }
}



if((digitalRead(dnbtn)==LOW))
{
  if(mode==1)
  {
  ONHH1=ONHH1-1;
  if(ONHH1<0)
    ONHH1=23;
  lcd.setCursor(0,1);
  lcd.print("ON TIME ");
  lcd.print(ONHH1); lcd.print(":"); lcd.print(ONMM1);

  }
  if(mode==2)
  {
  ONMM1=ONMM1-1;
  if(ONMM1<0)
    ONMM1=59;
 lcd.setCursor(0,1);
  lcd.print("ON TIME ");
  lcd.print(ONHH1); lcd.print(":"); lcd.print(ONMM1);
  }
}



/************************************************************************************************************************************ */


if((digitalRead(upbtn)==LOW))
{
  if(mode==3)
  {
  OFFHH1=OFFHH1+1;
  if(OFFHH1>23)
    OFFHH1=0;
  lcd.setCursor(0,1);
  lcd.print("OFF TIME ");
  lcd.print(OFFHH1); lcd.print(":"); lcd.print(OFFMM1);

  }
  if(mode==4)
  {
  OFFMM1=OFFMM1+1;
  if(OFFMM1>59)
    OFFMM1=0;
 lcd.setCursor(0,1);
  lcd.print("OFF TIME ");
  lcd.print(OFFHH1); lcd.print(":"); lcd.print(OFFMM1);;
  }
}



if((digitalRead(dnbtn)==LOW))
{
  if(mode==3)
  {
  OFFHH1=OFFHH1-1;
  if(OFFHH1<0)
    OFFHH1=23;
  lcd.setCursor(0,1);
  lcd.print("OFF TIME ");
  lcd.print(OFFHH1); lcd.print(":"); lcd.print(OFFMM1);

  }
  if(mode==4)
  {
  OFFMM1=OFFMM1-1;
  if(OFFMM1<0)
    OFFMM1=59;
 lcd.setCursor(0,1);
  lcd.print("OFF TIME ");
  lcd.print(OFFHH1); lcd.print(":"); lcd.print(OFFMM1);
  }
}

EEPROM.write(1,ONHH1);EEPROM.write(2,ONMM1); 
EEPROM.write(3,OFFHH1);EEPROM.write(4,OFFMM1);

}
