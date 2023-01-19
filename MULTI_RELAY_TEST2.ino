#include <EEPROM.h>
#include <stdint.h>
#include <DS3231.h>
#include "RTClib.h"                                 // libreries 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3f, 16, 2);


DS3231  rtc(A0, A1);
RTC_DS3231 R;
Time t;

#define Set     4
#define upbtn   5
#define dnbtn   6                                   // gpio declaration
#define rset    7
#define relay_select  8
#define relay1  9
#define relay2  10
#define relay3  11
#define relay4  12

 int HH,MM,Sc,REAL_TIME,START_TIME1,STOP_TIME1,START_TIME2,STOP_TIME2,START_TIME3,STOP_TIME3,START_TIME4,STOP_TIME4;
 int mode,relay_mode=0;
 int ONHH1,ONMM1,OFFHH1,OFFMM1;
 int ONHH2,ONMM2,OFFHH2,OFFMM2;
 int ONHH3,ONMM3,OFFHH3,OFFMM3;                      // variable declaration 
 int ONHH4,ONMM4,OFFHH4,OFFMM4;


 
void setup()
{
  
  pinMode(relay_select,INPUT_PULLUP);
  pinMode(Set,INPUT_PULLUP);
  pinMode(upbtn,INPUT_PULLUP);
  pinMode(dnbtn,INPUT_PULLUP);                  // sets the gpio as HIGH by default 
  pinMode(rset,INPUT_PULLUP);
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  pinMode(relay3,OUTPUT);
  pinMode(relay4,OUTPUT);
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  rtc.begin();
  

  
}


void loop() 
{ 
 
  
  ONHH1=EEPROM.read(1);ONMM1=EEPROM.read(2);
  OFFHH1=EEPROM.read(3);OFFMM1=EEPROM.read(4);   // calls the value of time entered in EEPROM 
  
  ONHH2=EEPROM.read(5);ONMM2=EEPROM.read(6);
  OFFHH2=EEPROM.read(7);OFFMM2=EEPROM.read(8);

  ONHH3=EEPROM.read(9);ONMM3=EEPROM.read(10);
  OFFHH3=EEPROM.read(11);OFFMM3=EEPROM.read(12);

  ONHH4=EEPROM.read(13);ONMM4=EEPROM.read(14);
  OFFHH4=EEPROM.read(15);OFFMM4=EEPROM.read(16);
  relay_mode=EEPROM.read(17);
  
  if(digitalRead(relay_select)== LOW)
  {
   relay_mode=relay_mode+1;
   if(relay_mode>4)
   relay_mode=0;
   EEPROM.write(17,relay_mode);

  }

 if(relay_mode==0)
  {
  Time_display();                                                          // calls the  time  function
  }
  
  if(relay_mode==1)
  {
  Relay1();                                                               // calls the 1st relay time set function
  }

  if(relay_mode==2)
  {
  Relay2();                                                               // calls the 2nd relay time set function
  }

  if(relay_mode==3)
  {
  Relay3();                                                               // calls the 3rd relay time set function
  }

  if(relay_mode==4)                                                       // calls the 4th relay time set function
  {
  Relay4();                                                               // calls the 1st relay time set function
  }

if((digitalRead(upbtn)==LOW)&&(digitalRead(dnbtn)==LOW))
  {
    ONHH1=0;ONMM1=0;OFFHH1=0;OFFMM1=0;
    ONHH2=0;ONMM2=0;OFFHH2=0;OFFMM2=0;
    ONHH3=0;ONMM3=0;OFFHH3=0;OFFMM3=0;
    ONHH4=0;ONMM4=0;OFFHH4=0;OFFMM4=0;
EEPROM.write(13,ONHH4);EEPROM.write(14,ONMM4); 
EEPROM.write(15,OFFHH4);EEPROM.write(16,OFFMM4);
EEPROM.write(9,ONHH3);EEPROM.write(10,ONMM3); 
EEPROM.write(11,OFFHH3);EEPROM.write(12,OFFMM3);
EEPROM.write(5,ONHH2);EEPROM.write(6,ONMM2); 
EEPROM.write(7,OFFHH2);EEPROM.write(8,OFFMM2); 
EEPROM.write(1,ONHH1);EEPROM.write(2,ONMM1); 
EEPROM.write(3,OFFHH1);EEPROM.write(4,OFFMM1);

  }

  
  delay(100);

  
  
}





/* ////////////////////////////////////////////////    Time_display   ////////////////////////////////////////////////////////// */

int Time_display()
{
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("TIME " ); // shows the time 
  lcd.print(t.hour);
  lcd.print(":" );
  lcd.print(t.min);
  lcd.print(":" );
  lcd.print(t.sec);
  t = rtc.getTime();

  
  HH=t.hour;
  MM=t.min;
  Sc=t.sec;
  
  REAL_TIME=(HH*3600)+(MM*60)+SS;
  
  START_TIME1=(ONHH1*3600)+(ONMM1*60);
  STOP_TIME1=(OFFHH1*3600)+((OFFMM1)*60);

  START_TIME2=(ONHH2*3600)+(ONMM2*60);
  STOP_TIME2=(OFFHH2*3600)+((OFFMM2)*60);

  START_TIME3=(ONHH3*3600)+(ONMM3*60);
  STOP_TIME3=(OFFHH3*3600)+((OFFMM3)*60);

  START_TIME4=(ONHH4*3600)+(ONMM4*60);
  STOP_TIME4=(OFFHH4*3600)+((OFFMM4)*60);

/* //////////////////////////////////////////////////////////////////////////////////////////////// */

 
 
  if(ONHH1<=OFFHH1)
  {
  if(START_TIME1<=REAL_TIME&&REAL_TIME<=STOP_TIME1)
  {
    digitalWrite(relay1,LOW);
    lcd.setCursor(0,1);
    lcd.print("S1|" );
  }
  else
  {
    digitalWrite(relay1,HIGH);
    lcd.setCursor(0,1);
    lcd.print("S1O" );
  }
  }
  if(ONHH1>OFFHH1)
  {
    if(START_TIME1<=REAL_TIME || REAL_TIME<=STOP_TIME1)
  {
    digitalWrite(relay1,LOW);
     lcd.setCursor(0,1);
   lcd.print("S1|" );
  }
  else
  {
    digitalWrite(relay1,HIGH);
    lcd.setCursor(0,1);
    lcd.print("S1O" );
  }
  }
 
  
/* ///////////////////////// RELAY 2 ///////////////////////////////////////////////////// */ 

   
  if(ONHH2<=OFFHH2)
  {
  if(START_TIME2<=REAL_TIME&&REAL_TIME<=STOP_TIME2)
  {
    digitalWrite(relay2,LOW);
    lcd.setCursor(3,1);
    lcd.print(" S2|" );
  }
  else
  {
    digitalWrite(relay2,HIGH);
    lcd.setCursor(3,1);
    lcd.print(" S2O" );
  }
  }
  if(ONHH2>OFFHH2)
  {
    if(START_TIME2<=REAL_TIME || REAL_TIME<=STOP_TIME2)
  {
    digitalWrite(relay2,LOW);
    lcd.setCursor(3,1);
    lcd.print(" S2|" );
  }
  else
  {
    digitalWrite(relay2,HIGH);
    lcd.setCursor(3,1);
    lcd.print(" S2O" );
  }
  }

/*  /////////////////////////////////// RELAY3  ////////////////////////////////////////////////////// */

   if(ONHH3<=OFFHH3)
  {
  if(START_TIME3<=REAL_TIME&&REAL_TIME<=STOP_TIME3)
  {
    digitalWrite(relay3,LOW);
    lcd.setCursor(7,1);
    lcd.print(" S3|" );
  }
  else
  {
    digitalWrite(relay3,HIGH);
    lcd.setCursor(7,1);
    lcd.print(" S3O" );
  }
  }
  if(ONHH3>OFFHH3)
  {
    if(START_TIME3<=REAL_TIME || REAL_TIME<=STOP_TIME3)
  {
    digitalWrite(relay3,LOW);
     lcd.setCursor(7,1);
    lcd.print(" S3|" );
  }
  else
  {
    digitalWrite(relay3,HIGH);
    lcd.setCursor(7,1);
    lcd.print(" S3O" );
  }
  }

/* ////////////////////////////////////////////////    RELAY4   ////////////////////////////////////////////////////////// */




   if(ONHH4<=OFFHH4)
  {
  if(START_TIME4<=REAL_TIME&&REAL_TIME<=STOP_TIME4)
  {
    digitalWrite(relay4,LOW);
    lcd.setCursor(11,1);
    lcd.print(" S4|" );
  }
  else
  {
    digitalWrite(relay4,HIGH);
    lcd.setCursor(11,1);
    lcd.print(" S4O" );
  }
  }
  if(ONHH4>OFFHH4)
  {
    if(START_TIME4<=REAL_TIME || REAL_TIME<=STOP_TIME4)
  {
    digitalWrite(relay4,LOW);
    lcd.setCursor(11,1);
    lcd.print(" S4|" );
  }
  else
  {
    digitalWrite(relay4,HIGH);
    lcd.setCursor(11,1);
    lcd.print(" S4O" );
  }
  }

  delay(100);
  
  
}



/* ////////////////////////////////////////////////    RELAY1   ////////////////////////////////////////////////////////// */

int Relay1()                                                               // 1st relay time set function 
{
 
  lcd.setCursor(0,0);
  lcd.print("SW 1");
  lcd.print(" PRESS MODE ");
  lcd.setCursor(0,1);
  lcd.print("                ");
  
  {
   if(digitalRead(Set)==LOW)                                               //active when set button is pressed 
      mode=mode+1;
   if(mode>4)
      mode=1;

  
  lcd.setCursor(4,0); 
  if(mode==1)
  {
    lcd.print("  ON HOUR  ");
    lcd.setCursor(0,1);
    lcd.print("ON TIME ");
    printDigits(ONHH1); lcd.print(":");  printDigits(ONMM1);
    delay(100);
  }
  if(mode==2)
  {
    lcd.print("  ON MNUT  ");
    lcd.setCursor(0,1);
    lcd.print("ON TIME ");
    printDigits(ONHH1); lcd.print(":");  printDigits(ONMM1);
    delay(100);
  }

  if(mode==3)
  {
    lcd.print(" OFF HOUR  ");
    lcd.setCursor(0,1);
    lcd.print("OFF TIME ");
    printDigits(OFFHH1); lcd.print(":");  printDigits(OFFMM1);
    delay(100);
  }
  if(mode==4)
  {
    lcd.print(" OFF MNUT  ");
    lcd.setCursor(0,1);
    lcd.print("OFF TIME ");
    printDigits(OFFHH1); lcd.print(":");  printDigits(OFFMM1);
    delay(100);
  }
  delay(100);
  }
  if((digitalRead(upbtn)==LOW))                                              // time up function 
{  
  if(mode==1)
  {
  ONHH1=ONHH1+1;
  if(ONHH1>23)                                                               // on hour up loop
    ONHH1=0;

  //lcd.clear();  
  lcd.setCursor(0,1);
  lcd.print("ON TIME ");
  printDigits(ONHH1); lcd.print(":");  printDigits(ONMM1);
   
  }
  if(mode==2)
  {
  ONMM1=ONMM1+1;
  if(ONMM1>59)                                                             // on mint up loop 
    ONMM1=0; 

 // lcd.clear();  
  lcd.setCursor(0,1);
  lcd.print("ON TIME ");
   printDigits(ONHH1); lcd.print(":");  printDigits(ONMM1);
  }
  
}



if((digitalRead(dnbtn)==LOW))
{
  if(mode==1)
  {
  ONHH1=ONHH1-1;
  if(ONHH1<0)
    ONHH1=23;  // on hour down loop

 // lcd.clear();  
  lcd.setCursor(0,1);
  lcd.print("ON TIME ");
   printDigits(ONHH1); lcd.print(":");  printDigits(ONMM1);

  }
  if(mode==2)
  {
  ONMM1=ONMM1-1;
  if(ONMM1<0)
    ONMM1=59; // on mint down loop

  //lcd.clear();  
  lcd.setCursor(0,1);
  lcd.print("ON TIME ");
  printDigits(ONHH1); lcd.print(":");  printDigits(ONMM1);
  }
}

if((digitalRead(upbtn)==LOW))
{
  if(mode==3)
  {
  OFFHH1=OFFHH1+1;
  if(OFFHH1>23)
    OFFHH1=0;                                                               //off hour up loop

  //lcd.clear();  
  lcd.setCursor(0,1);
  lcd.print("OFF TIME ");
  printDigits(OFFHH1); lcd.print(":");  printDigits(OFFMM1);

  }
  if(mode==4)
  {
  OFFMM1=OFFMM1+1;                                                         //off mint up loop
  if(OFFMM1>59)
    OFFMM1=0;

  //lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("OFF TIME ");
  printDigits(OFFHH1); lcd.print(":");  printDigits(OFFMM1);
  }
}



if((digitalRead(dnbtn)==LOW))
{
  if(mode==3)
  {
  OFFHH1=OFFHH1-1;
  if(OFFHH1<0)
    OFFHH1=23;                                                                 // off hour down loop
 
  lcd.setCursor(0,1);
  lcd.print("OFF TIME ");
  printDigits(OFFHH1); lcd.print(":");  printDigits(OFFMM1);

  }
  if(mode==4)
  {
  OFFMM1=OFFMM1-1;                                                            // off mint down loop 
  if(OFFMM1<0)
    OFFMM1=59;
  //lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("OFF TIME ");
 printDigits(OFFHH1); lcd.print(":");  printDigits(OFFMM1);
  }
}

EEPROM.write(1,ONHH1);EEPROM.write(2,ONMM1); 
EEPROM.write(3,OFFHH1);EEPROM.write(4,OFFMM1);                               // saves the values of time entered to EEPROM 

}


/* ////////////////////////////////////////////////    RELAY2   ////////////////////////////////////////////////////////// */


int Relay2()                                                               // 2nd relay time set function 
{
  lcd.setCursor(0,0);
  lcd.print("SW 2");
  lcd.print(" PRESS MODE ");
  lcd.setCursor(0,1);
  lcd.print("                ");
  {
    if(digitalRead(Set)==LOW)                                               //active when set button is pressed 
      mode=mode+1;
   if(mode>4)
      mode=1;

  
  lcd.setCursor(4,0); 
  if(mode==1)
  {
    lcd.print("  ON HOUR  ");
    lcd.setCursor(0,1);
    lcd.print("ON TIME ");
    printDigits(ONHH2); lcd.print(":");  printDigits(ONMM2);
    delay(100);
  }
  if(mode==2)
  {
    lcd.print("  ON MNUT  ");
    lcd.setCursor(0,1);
    lcd.print("ON TIME ");
    printDigits(ONHH2); lcd.print(":");  printDigits(ONMM2);
    delay(100);
  }

  if(mode==3)
  {
    lcd.print(" OFF HOUR  ");
    lcd.setCursor(0,1);
    lcd.print("OFF TIME ");
    printDigits(OFFHH2); lcd.print(":");  printDigits(OFFMM2);
    delay(100);
  }
  if(mode==4)
  {
    lcd.print(" OFF MNUT  ");
    lcd.setCursor(0,1);
    lcd.print("OFF TIME ");
    printDigits(OFFHH2); lcd.print(":");  printDigits(OFFMM2);
    delay(100);
  }
  delay(100);
  }
  if((digitalRead(upbtn)==LOW))                                              // time up function 
{  
  if(mode==1)
  {
  ONHH2=ONHH2+1;
  if(ONHH2>23)                                                               // on hour up loop
    ONHH2=0;
  //lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("ON TIME ");
  printDigits(ONHH2); lcd.print(":");  printDigits(ONMM2);
   
  }
  if(mode==2)
  {
  ONMM2=ONMM2+1;
  if(ONMM2>59)                                                             // on mint up loop 
    ONMM2=0; 
 // lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("ON TIME ");
  printDigits(ONHH2); lcd.print(":");  printDigits(ONMM2);
  }
}



if((digitalRead(dnbtn)==LOW))
{
  if(mode==1)
  {
  ONHH2=ONHH2-1;
  if(ONHH2<0)
    ONHH2=23;                                                               // on hour down loop

  lcd.setCursor(0,1);
  lcd.print("ON TIME ");
  printDigits(ONHH2); lcd.print(":");  printDigits(ONMM2);

  }
  if(mode==2)
  {
  ONMM2=ONMM2-1;
  if(ONMM2<0)
    ONMM2=59;                                                              // on mint down loop

  lcd.setCursor(0,1);
  lcd.print("ON TIME ");
  printDigits(ONHH2); lcd.print(":");  printDigits(ONMM2);
  }
}


if((digitalRead(upbtn)==LOW))
{
  if(mode==3)
  {
  OFFHH2=OFFHH2+1;
  if(OFFHH2>23)
    OFFHH2=0;                                                               //off hour up loop
    
  lcd.setCursor(0,1);
  lcd.print("OFF TIME ");
  printDigits(OFFHH2); lcd.print(":");  printDigits(OFFMM2);

  }
  if(mode==4)
  {
  OFFMM2=OFFMM2+1;                                                         //off mint up loop
  if(OFFMM2>59)
    OFFMM2=0;
 
  lcd.setCursor(0,1);
  lcd.print("OFF TIME ");
  printDigits(OFFHH2); lcd.print(":");  printDigits(OFFMM2);
  }
}



if((digitalRead(dnbtn)==LOW))
{
  if(mode==3)
  {
  OFFHH2=OFFHH2-1;
  if(OFFHH2<0)
    OFFHH2=23;                                                                 // off hour down loop
  
  lcd.setCursor(0,1);
  lcd.print("OFF TIME ");
  printDigits(OFFHH2); lcd.print(":");  printDigits(OFFMM2);

  }
  if(mode==4)
  {
  OFFMM2=OFFMM2-1;                                                            // off mint down loop 
  if(OFFMM2<0)
    OFFMM2=59;
  
  lcd.setCursor(0,1);
  lcd.print("OFF TIME ");
  printDigits(OFFHH2); lcd.print(":");  printDigits(OFFMM2);
  }
}

EEPROM.write(5,ONHH2);EEPROM.write(6,ONMM2); 
EEPROM.write(7,OFFHH2);EEPROM.write(8,OFFMM2);                               // saves the values of time entered to EEPROM 

}

/* ////////////////////////////////////////////////    RELAY3   ////////////////////////////////////////////////////////// */

int Relay3()                                                               // 2nd relay time set function 
{
  lcd.setCursor(0,0);
  lcd.print("SW 3");
  lcd.print(" PRESS MODE ");
  lcd.setCursor(0,1);
  lcd.print("                ");
  {
    if(digitalRead(Set)==LOW)                                               //active when set button is pressed 
    mode=mode+1;
    if(mode>4)
    mode=1;
  
  lcd.setCursor(4,0); 
  if(mode==1)
  {
    lcd.print("  ON HOUR  ");
    lcd.setCursor(0,1);
    lcd.print("ON TIME ");
    printDigits(ONHH3); lcd.print(":");  printDigits(ONMM3);
    delay(100);
  }
  if(mode==2)
  {
    lcd.print("  ON MNUT  ");
    lcd.setCursor(0,1);
    lcd.print("ON TIME ");
    printDigits(ONHH3); lcd.print(":");  printDigits(ONMM3);
    delay(100);
  }

  if(mode==3)
  {
    lcd.print(" OFF HOUR  ");
    lcd.setCursor(0,1);
    lcd.print("OFF TIME ");
    printDigits(OFFHH3); lcd.print(":");  printDigits(OFFMM3);
    delay(100);
  }
  if(mode==4)
  {
    lcd.print(" OFF MNUT  ");
    lcd.setCursor(0,1);
    lcd.print("OFF TIME ");
    printDigits(OFFHH3); lcd.print(":");  printDigits(OFFMM3);
    delay(100);
  }
  }
  if((digitalRead(upbtn)==LOW))                                              // time up function 
{  
  if(mode==1)
  {
  ONHH3=ONHH3+1;
  if(ONHH3>23)                                                               // on hour up loop
    ONHH3=0;
  
  lcd.setCursor(0,1);
  lcd.print("ON TIME ");
  printDigits(ONHH3); lcd.print(":");  printDigits(ONMM3);
   
  }
  if(mode==2)
  {
  ONMM3=ONMM3+1;
  if(ONMM3>59)                                                             // on mint up loop 
    ONMM3=0; 
 
  lcd.setCursor(0,1);
  lcd.print("ON TIME ");
  printDigits(ONHH3); lcd.print(":");  printDigits(ONMM3);
  }
}



if((digitalRead(dnbtn)==LOW))
{
  if(mode==1)
  {
  ONHH3=ONHH3-1;
  if(ONHH3<0)
    ONHH3=23;                                                               // on hour down loop
  
  lcd.setCursor(0,1);
  lcd.print("ON TIME ");
  printDigits(ONHH3); lcd.print(":");  printDigits(ONMM3);

  }
  if(mode==2)
  {
  ONMM3=ONMM3-1;
  if(ONMM3<0)
    ONMM3=59;                                                              // on mint down loop

  lcd.setCursor(0,1);
  lcd.print("ON TIME ");
  printDigits(ONHH3); lcd.print(":");  printDigits(ONMM3);
  }
}


if((digitalRead(upbtn)==LOW))
{
  if(mode==3)
  {
  OFFHH3=OFFHH3+1;
  if(OFFHH3>23)
    OFFHH3=0;                                                               //off hour up loop
  lcd.clear();  
  lcd.setCursor(0,1);
  lcd.print("OFF TIME ");
  printDigits(OFFHH3); lcd.print(":");  printDigits(OFFMM3);

  }
  if(mode==4)
  {
  OFFMM3=OFFMM3+1;                                                         //off mint up loop
  if(OFFMM3>59)
    OFFMM3=0;
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("OFF TIME ");
  printDigits(OFFHH3); lcd.print(":");  printDigits(OFFMM3);
  }
}



if((digitalRead(dnbtn)==LOW))
{
  if(mode==3)
  {
  OFFHH3=OFFHH3-1;
  if(OFFHH3<0)
    OFFHH3=23;                                                                 // off hour down loop
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("OFF TIME ");
  printDigits(OFFHH3); lcd.print(":");  printDigits(OFFMM3);

  }
  if(mode==4)
  {
  OFFMM3=OFFMM3-1;                                                            // off mint down loop 
  if(OFFMM3<0)
    OFFMM3=59;
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("OFF TIME ");
  printDigits(OFFHH3); lcd.print(":");  printDigits(OFFMM3);
  }
}

EEPROM.write(9,ONHH3);EEPROM.write(10,ONMM3); 
EEPROM.write(11,OFFHH3);EEPROM.write(12,OFFMM3);                               // saves the values of time entered to EEPROM 

}

/* ////////////////////////////////////////////////    RELAY4   ////////////////////////////////////////////////////////// */

int Relay4()                                                               // 2nd relay time set function 
{
  
lcd.setCursor(0,0);
  lcd.print("SW 4");
  lcd.print(" PRESS MODE ");
  lcd.setCursor(0,1);
  lcd.print("                ");
  {
    if(digitalRead(Set)==LOW)                                               //active when set button is pressed 
    mode=mode+1;
    if(mode>4)
    mode=1;
 
  
  lcd.setCursor(4,0); 
  if(mode==1)
  {
    lcd.print("  ON HOUR  ");
    lcd.setCursor(0,1);
    lcd.print("ON TIME ");
    printDigits(ONHH4); lcd.print(":");  printDigits(ONMM4);
    delay(100);
  }
  if(mode==2)
  {
    lcd.print("  ON MNUT  ");
    lcd.setCursor(0,1);
    lcd.print("ON TIME ");
    printDigits(ONHH4); lcd.print(":");  printDigits(ONMM4);
    delay(100);
  }

  if(mode==3)
  {
    lcd.print(" OFF HOUR  ");
    lcd.setCursor(0,1);
    lcd.print("OFF TIME ");
    printDigits(OFFHH4); lcd.print(":");  printDigits(OFFMM4);
    delay(100);
  }
  if(mode==4)
  {
    lcd.print(" OFF MNUT  ");
    lcd.setCursor(0,1);
    lcd.print("OFF TIME ");
    printDigits(OFFHH4); lcd.print(":");  printDigits(OFFMM4);
    delay(100);
  }
  delay(250);
  }
  if((digitalRead(upbtn)==LOW))                                              // time up function 
{  
  if(mode==1)
  {
  ONHH4=ONHH4+1;
  if(ONHH4>23)                                                               // on hour up loop
    ONHH4=0;
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("ON TIME ");
  printDigits(ONHH4); lcd.print(":");  printDigits(ONMM4);
   
  }
  if(mode==2)
  {
  ONMM4=ONMM4+1;
  if(ONMM4>59)                                                             // on mint up loop 
    ONMM4=0; 
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("ON TIME ");
  printDigits(ONHH4); lcd.print(":");  printDigits(ONMM4);
  }
}



if((digitalRead(dnbtn)==LOW))
{
  if(mode==1)
  {
  ONHH4=ONHH4-1;
  if(ONHH4<0)
    ONHH4=23;                                                               // on hour down loop
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("ON TIME ");
  printDigits(ONHH4); lcd.print(":");  printDigits(ONMM4);

  }
  if(mode==2)
  {
  ONMM4=ONMM4-1;
  if(ONMM4<0)
    ONMM4=59;                                                              // on mint down loop
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("ON TIME ");
  printDigits(ONHH4); lcd.print(":");  printDigits(ONMM4);
  }
}


if((digitalRead(upbtn)==LOW))
{
  if(mode==3)
  {
  OFFHH4=OFFHH4+1;
  if(OFFHH4>23)
    OFFHH4=0;                                                               //off hour up loop
  lcd.clear();  
  lcd.setCursor(0,1);
  lcd.print("OFF TIME ");
  printDigits(OFFHH4); lcd.print(":");  printDigits(OFFMM4);
  }
  if(mode==4)
  {
  OFFMM4=OFFMM4+1;                                                         //off mint up loop
  if(OFFMM4>59)
    OFFMM4=0;
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("OFF TIME ");
   printDigits(OFFHH4); lcd.print(":");  printDigits(OFFMM4);
  }
}



if((digitalRead(dnbtn)==LOW))
{
  if(mode==3)
  {
  OFFHH4=OFFHH4-1;
  if(OFFHH4<0)
    OFFHH4=23;                                                                 // off hour down loop
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("OFF TIME ");
   printDigits(OFFHH4); lcd.print(":");  printDigits(OFFMM4);

  }
  if(mode==4)
  {
  OFFMM4=OFFMM4-1;                                                            // off mint down loop 
  if(OFFMM4<0)
    OFFMM4=59;
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("OFF TIME ");
  printDigits(OFFHH4); lcd.print(":"); printDigits(OFFMM4);
  }
}

EEPROM.write(13,ONHH4);EEPROM.write(14,ONMM4); 
EEPROM.write(15,OFFHH4);EEPROM.write(16,OFFMM4);                               // saves the values of time entered to EEPROM 

}
int printDigits(int digits)  
{
  if(digits < 10) 
  {
    lcd.print("0");
    lcd.print(digits);
  }
  else
  {
    lcd.print(digits);
  }
}
