#include <LiquidCrystal_I2C.h> // подключаем библиотеку для QAPASS 
#include <Wire.h> // библиотека для управления устройствами по I2C 

LiquidCrystal_I2C LCD(0x27,16,2); // присваиваем имя LCD для дисплея

int ayr = 60; //яркость светодиода

long vremay;
long timer;
byte hours, minuts, seconds;
int flag;
int secundomer;
int minutes;
long milisek;
int st;
int st1 = 1;
int i=0;
int el = 1;
int ot = 0;
String Time = "Time";
String Edit_time = "Edit time";
String Menu = "Menu";
String Secundomer = "Secundomer";
unsigned long btnTimer = 0;
int el1;
int to;
int rab=1;
byte strelka_l[8] = {
0b00001,
0b00011,
0b00101,
0b01001,
0b00001,
0b00001,
0b00001,
0b00001
};

byte strelka_r[8] = {
0b10000,
0b11000,
0b10100,
0b10010,
0b10000,
0b10000,
0b10000,
0b10000
};

byte left_l[8] = {
0b00010,
0b00110,
0b01100,
0b11111,
0b11111,
0b01100,
0b00110,
0b00010
};

byte left_r[8] = {
0b00000,
0b00000,
0b00000,
0b11111,
0b11111,
0b00000,
0b00000,
0b00000
};
void setup()
{     
LCD.init(); // инициализация LCD дисплея
LCD.backlight(); // включение подсветки дисплея
Serial.begin(9600);
pinMode(2, INPUT_PULLUP);
pinMode(3, INPUT_PULLUP);
pinMode(4, OUTPUT);
pinMode(5, OUTPUT);
pinMode(6, OUTPUT);
pinMode(7, OUTPUT);
LCD.createChar(1, strelka_l);
LCD.createChar(4, strelka_r);
LCD.createChar(2, left_l);
LCD.createChar(3, left_r);
}

void loop()
{
  if(rab == 1) {
    analogWrite(7,LOW);
    analogWrite(6,ayr);
 el = 1;
 el1 = 0;
 ot =0;
 v_vremeni();
 menu();
 i=0; 
  }
  else {
    LCD.clear();
    LCD.noBacklight(); // выключаем и включаем подсветку экрана
    digitalWrite(6,LOW);
    digitalWrite(7,HIGH);
  }
}

void v_vremeni() {
  if(millis() % 1000 == 0) timer++;
  if((timer % 60) != seconds){
  hours = timer / 3600;
  minuts = (timer % 3600) / 60;
  seconds = timer % 60;
  vuv();
  }
}

void menu() {
   if(digitalRead(2) == 0 && digitalRead(3) == 0) {
   delay(500);
   if(digitalRead(2) == 0 && digitalRead(3) == 0) {
   delay(500);
   if(digitalRead(2) == 0 && digitalRead(3) == 0) {
   LCD.clear();
   mig_Menu(Menu);
   
   LCD.setCursor(0, 0);     // ставим курсор на 1 символ первой строки
   LCD.print("Time");     // печатаем сообщение на первой строlcd
   LCD.setCursor(0, 1);     // ставим курсор на 1 символ первой строки
   LCD.print("Edit time");     // печатаем сообщение на первой строlcd
    for(int a = 0; a < 1;a) {

 
      if(digitalRead(3) == 0) {
       el++;
       if(el >= 3) {
        ot++;
        if(ot == 1) {
          LCD.clear();
          LCD.setCursor(0, 0);     // ставим курсор на 1 символ первой строки
          LCD.print("Secundomer");     // печатаем сообщение на первой строlcd
          LCD.setCursor(0, 1);     // ставим курсор на 1 символ первой строки
          LCD.print("Timer");     // печатаем сообщение на первой строlcd
                      to++;
                      ot = 0;
          for(int k=0;k < 1; k) {


             if(digitalRead(3) == 0) {
              el1++;
              if(el1 >= 3) {
                k++;
              }
              if(el1 > 2) {
                el1 = 1;
              }
              for(int e = 0; e < 1;e) {
                if(digitalRead(3) == 1) {
                  e++;
                }
              }
             }   
   switch(el1) {
        case 1:
   LCD.setCursor(14,1); // ставим курсор на 1 символ первой строки
   LCD.print("  "); // печатаем символ на первой строке
   LCD.setCursor(14,0); // ставим курсор на 1 символ первой строки
   LCD.print(char(2)); // печатаем символ на первой строке
   LCD.setCursor(15,0); // ставим курсор на 1 символ первой строки
   LCD.print(char(3)); // печатаем символ на первой строке
           if(digitalRead(2) == 0) {
            LCD.clear();
            mig_Secondomer(Secundomer);
            mig_Secondomer(Secundomer);
            Secondomer();
            //jejnfsfnjksenjksfnjjneSFnjesNJLSE
            //jejnfsfnjksenjksfnjjneSFnjesNJLSE
            //jejnfsfnjksenjksfnjjneSFnjesNJLSE
            //jejnfsfnjksenjksfnjjneSFnjesNJLSE
            //jejnfsfnjksenjksfnjjneSFnjesNJLSE
            //jejnfsfnjksenjksfnjjneSFnjesNJLSE
            //jejnfsfnjksenjksfnjjneSFnjesNJLSE
            //jejnfsfnjksenjksfnjjneSFnjesNJLSE
            //jejnfsfnjksenjksfnjjneSFnjesNJLSE
            //jejnfsfnjksenjksfnjjneSFnjesNJLSE
            //jejnfsfnjksenjksfnjjneSFnjesNJLSE
            //jejnfsfnjksenjksfnjjneSFnjesNJLSE
            //jejnfsfnjksenjksfnjjneSFnjesNJLSE
            //jejnfsfnjksenjksfnjjneSFnjesNJLSE
            //jejnfsfnjksenjksfnjjneSFnjesNJLSE
            //jejnfsfnjksenjksfnjjneSFnjesNJLSE
            //jejnfsfnjksenjksfnjjneSFnjesNJLSE
            //jejnfsfnjksenjksfnjjneSFnjesNJLSE
            //jejnfsfnjksenjksfnjjneSFnjesNJLSE
            //jejnfsfnjksenjksfnjjneSFnjesNJLSE
            //jejnfsfnjksenjksfnjjneSFnjesNJLSE
            //jejnfsfnjksenjksfnjjneSFnjesNJLSE
            //jejnfsfnjksenjksfnjjneSFnjesNJLSE
            //jejnfsfnjksenjksfnjjneSFnjesNJLSE
            //jejnfsfnjksenjksfnjjneSFnjesNJLSE
            //jejnfsfnjksenjksfnjjneSFnjesNJLSE
            //jejnfsfnjksenjksfnjjneSFnjesNJLSE
           }
        break;

        case 2:
   LCD.setCursor(14,0); // ставим курсор на 1 символ первой строки
   LCD.print("  "); // печатаем символ на первой строке
   LCD.setCursor(14,1); // ставим курсор на 1 символ первой строки
   LCD.print(char(2)); // печатаем символ на первой строке
   LCD.setCursor(15,1); // ставим курсор на 1 символ первой строки
   LCD.print(char(3)); // печатаем символ на первой строке
           if(digitalRead(2) == 0) {
            
           }
        break;
     }
          }
        }
       }
       if(to == 1) {
        LCD.clear();
        LCD.setCursor(0, 0);     // ставим курсор на 1 символ первой строки
        LCD.print("Time");     // печатаем сообщение на первой строlcd
        LCD.setCursor(0, 1);     // ставим курсор на 1 символ первой строки
        LCD.print("Edit time");     // печатаем сообщение на первой строlc
        to=0;
        el1 = 0;
       }
       
        if(el > 2) {
          el = 1;
        }
        for(int p = 0; p < 1; p) {
          if(digitalRead(3) == 1) {
            p++;
          }
        }
      }
      switch(el) {
        case 1:
   LCD.setCursor(14,1); // ставим курсор на 1 символ первой строки
   LCD.print("  "); // печатаем символ на первой строке
   LCD.setCursor(14,0); // ставим курсор на 1 символ первой строки
   LCD.print(char(2)); // печатаем символ на первой строке
   LCD.setCursor(15,0); // ставим курсор на 1 символ первой строки
   LCD.print(char(3)); // печатаем символ на первой строке
           if(digitalRead(2) == 0) {
            a++;
            LCD.clear();
           }
        break;

        case 2:
   LCD.setCursor(14,0); // ставим курсор на 1 символ первой строки
   LCD.print("  "); // печатаем символ на первой строке
   LCD.setCursor(14,1); // ставим курсор на 1 символ первой строки
   LCD.print(char(2)); // печатаем символ на первой строке
   LCD.setCursor(15,1); // ставим курсор на 1 символ первой строки
   LCD.print(char(3)); // печатаем символ на первой строке
           if(digitalRead(2) == 0) {
            remove_time();
            a++;
           }
        break;
     }
    }
   }
  }
 }
}






void Secondomer() {
  milisek=0;
   secundomer=0;
  LCD.clear();
   LCD.setCursor(4,0); // ставим курсор на 1 символ первой строки
   LCD.print("00:00.0"); // печатаем символ на первой строке
   for(int qq=0;qq<1;qq) {
    if(digitalRead(3) == 0) {
                Serial.println("dwkdawmdlawd");
      for(int uy= 0; uy < 1; uy) {
        milisek++;
        for(int kj =0;kj<1;kj) {
          if(digitalRead(3)==1) {
            kj++;
          }
        }


        if(flag==5){
      if(digitalRead(2)==1){
        flag=4;
      }
        }
      if(flag==0){
        flag==5;
        if(digitalRead(3)==1){
          flag==5;
          //запуск секундомера
            flag=1;
              if(flag==1){
                flag==5;
                if(digitalRead(3)==0){
                  flag==5;
                  flag=2;
                
              }           
            }
          }
        }

      if(flag==2){
        flag==5;
        if(digitalRead(3)==1){
          flag==5;
          //стоп секундомер
            flag=3;
              if(flag==3){
                flag==5;
                if(digitalRead(3)==0){
                  flag==5;
                  flag=0;               
              }           
            }
          }
        }
        if(flag==4){
          //все 0 
          flag==0;
        }
      
        
        
        
        delay(84);
        if(milisek >=10) {
          milisek=0;
          secundomer++;
        }
         if(secundomer >=60) {
          minutes++;
          secundomer=0;
        }
        LCD.setCursor(10,0);
        LCD.print(milisek);

        if(minutes < 10) {
        LCD.setCursor(4,0);
        LCD.print("0");
        LCD.setCursor(5,0);
        LCD.print(minutes);
        }
        
        if(minutes >= 10) {
        LCD.setCursor(4,0);
        LCD.print(minutes);
        }
        
        if(secundomer < 10) {
        LCD.setCursor(7,0);
        LCD.print("0");
        LCD.setCursor(8,0);
        LCD.print(secundomer);
        }
        
        if(secundomer >= 10) {
        LCD.setCursor(7,0);
        LCD.print(secundomer);
      }
    }
   }
   
}
}

void remove_time() {
   LCD.clear();
   delay(500);
   mig_Edit_time_up(Edit_time);
   LCD.clear();
   vuv();
   LCD.setCursor(st,1); // ставим курсор на 1 символ первой строки
   LCD.print(char(1)); // печатаем символ на первой строке

    for(i; i < 1; i) {
     if(digitalRead(3) == 0) {
      if(st >= 6) {
       st = 0;
      }
      if(st1 >= 7) {
       st1 = 1;
      }
      else {
       st = st + 3;
       st1 = st1 + 3;
      }
      Exit_Edit_Time();
  LCD.setCursor(0,1); // ставим курсор на 1 символ первой строки
  LCD.print("                "); // печатаем символ на первой строке
      for(int u = 0; u < 1; u) {
        if(digitalRead(3) == 1) {
          u++;
        }
      }
     }

     
   if(digitalRead(2) == 0) {
    switch(st) {
      
     case 0:
       timer = timer + 3600;
       hours++;
       if(hours >= 24) {
        timer = 0;
        hours=0;
        minuts=0;
        seconds=0;
       }
       vuv();
     break;
     
     case 3:
       timer = timer + 60;
       minuts++;
       if(minuts >= 60) {
        minuts=0;
        timer = timer - 3600;
       }
       vuv();
     break;
     
     case 6:
       timer++;
       seconds++;
       if(seconds >= 60) {
        seconds=0;
        timer=timer-60; 
       }
       vuv();
     break;
          
    }
     for(int l = 0; l < 1;l) {
       if(digitalRead(2) == 1) {
         l++;
    }
  }
}   if(i == 0) { 
     LCD.setCursor(st,1); // ставим курсор на 1 символ первой строки
     LCD.print(char(1)); // печатаем символ на первой строке
     LCD.setCursor(st1,1); // ставим курсор на 1 символ первой строки
     LCD.print(char(4)); // печатаем символ на первой строке
}
}
     mig_Time(Time);
     mig_Time(Time);
}   


void vuv() {
  if(seconds >= 10 && minuts < 10 && hours < 10) {
   LCD.setCursor(0, 0);     // ставим курсор на 1 символ первой строки
   LCD.print("                ");
   LCD.setCursor(0, 0);     // ставим курсор на 1 символ первой строки
   LCD.print("0");
   LCD.setCursor(1, 0);     // ставим курсор на 1 символ первой строки
   LCD.print(hours);
   LCD.setCursor(2, 0);     // ставим курсор на 1 символ первой строки
   LCD.print(":");
   LCD.setCursor(3, 0);     // ставим курсор на 1 символ первой строки
   LCD.print("0");
   LCD.setCursor(4, 0);     // ставим курсор на 1 символ первой строки
   LCD.print(minuts);
   LCD.setCursor(5, 0);     // ставим курсор на 1 символ первой строки
   LCD.print(":");
   LCD.setCursor(6, 0);     // ставим курсор на 1 символ первой строки
   LCD.print(seconds);
  }

  
if(seconds >= 10 && minuts >= 10 && hours < 10) {
   LCD.setCursor(0, 0);     // ставим курсор на 1 символ первой строки
   LCD.print("                ");
   LCD.setCursor(0, 0);     // ставим курсор на 1 символ первой строки
   LCD.print("0");
   LCD.setCursor(1, 0);     // ставим курсор на 1 символ первой строки
   LCD.print(hours);
   LCD.setCursor(2, 0);     // ставим курсор на 1 символ первой строки
   LCD.print(":");
   LCD.setCursor(3, 0);     // ставим курсор на 1 символ первой строки
   LCD.print(minuts);
   LCD.setCursor(5, 0);     // ставим курсор на 1 символ первой строки
   LCD.print(":");
   LCD.setCursor(6, 0);     // ставим курсор на 1 символ первой строки
   LCD.print(seconds);
  }

  if(seconds >= 10 && minuts < 10 && hours >= 10) {
   LCD.setCursor(0, 0);     // ставим курсор на 1 символ первой строки
   LCD.print("                ");
   LCD.setCursor(0, 0);     // ставим курсор на 1 символ первой строки
   LCD.print(hours);
   LCD.setCursor(2, 0);     // ставим курсор на 1 символ первой строки
   LCD.print(":");
   LCD.setCursor(3, 0);     // ставим курсор на 1 символ первой строки
   LCD.print("0");
   LCD.setCursor(4, 0);     // ставим курсор на 1 символ первой строки
   LCD.print(minuts);
   LCD.setCursor(5, 0);     // ставим курсор на 1 символ первой строки
   LCD.print(":");
   LCD.setCursor(6, 0);     // ставим курсор на 1 символ первой строки
   LCD.print(seconds);
  }

  
  if(seconds >= 10 && minuts >= 10 && hours >= 10) {
   LCD.setCursor(0, 0);     // ставим курсор на 1 символ первой строки
   LCD.print("                ");
   LCD.setCursor(0, 0);     // ставим курсор на 1 символ первой строки
   LCD.print(hours);
   LCD.setCursor(2, 0);     // ставим курсор на 1 символ первой строки
   LCD.print(":");
   LCD.setCursor(3, 0);     // ставим курсор на 1 символ первой строки
   LCD.print(minuts);
   LCD.setCursor(5, 0);     // ставим курсор на 1 символ первой строки
   LCD.print(":");
   LCD.setCursor(6, 0);     // ставим курсор на 1 символ первой строки
   LCD.print(seconds);
  }

   if(seconds < 10 && minuts < 10 && hours < 10) {
   LCD.setCursor(0, 0);     // ставим курсор на 1 символ первой строки
   LCD.print("                ");
   LCD.setCursor(0, 0);     // ставим курсор на 1 символ первой строки
   LCD.print("0");
   LCD.setCursor(1, 0);     // ставим курсор на 1 символ первой строки
   LCD.print(hours);
   LCD.setCursor(2, 0);     // ставим курсор на 1 символ первой строки
   LCD.print(":");
   LCD.setCursor(3, 0);     // ставим курсор на 1 символ первой строки
   LCD.print("0");
   LCD.setCursor(4, 0);     // ставим курсор на 1 символ первой строки
   LCD.print(minuts);
   LCD.setCursor(5, 0);     // ставим курсор на 1 символ первой строки
   LCD.print(":");
   LCD.setCursor(6, 0);     // ставим курсор на 1 символ первой строки
   LCD.print("0");
   LCD.setCursor(7, 0);     // ставим курсор на 1 символ первой строки
   LCD.print(seconds);
  }


   if(seconds < 10 && minuts >= 10 && hours < 10) {
   LCD.setCursor(0, 0);     // ставим курсор на 1 символ первой строки
   LCD.print("                ");
   LCD.setCursor(0, 0);     // ставим курсор на 1 символ первой строки
   LCD.print("0");
   LCD.setCursor(1, 0);     // ставим курсор на 1 символ первой строки
   LCD.print(hours);
   LCD.setCursor(2, 0);     // ставим курсор на 1 символ первой строки
   LCD.print(":");
   LCD.setCursor(3, 0);     // ставим курсор на 1 символ первой строки
   LCD.print(minuts);
   LCD.setCursor(5, 0);     // ставим курсор на 1 символ первой строки
   LCD.print(":");
   LCD.setCursor(6, 0);     // ставим курсор на 1 символ первой строки
   LCD.print("0");
   LCD.setCursor(7, 0);     // ставим курсор на 1 символ первой строки
   LCD.print(seconds);
  }

  
  if(seconds >= 10 && minuts >= 10 && hours < 10) {
   LCD.setCursor(0, 0);     // ставим курсор на 1 символ первой строки
   LCD.print("                ");
   LCD.setCursor(0, 0);     // ставим курсор на 1 символ первой строки
   LCD.print("0");
   LCD.setCursor(1, 0);     // ставим курсор на 1 символ первой строки
   LCD.print(hours);
   LCD.setCursor(2, 0);     // ставим курсор на 1 символ первой строки
   LCD.print(":");
   LCD.setCursor(3, 0);     // ставим курсор на 1 символ первой строки
   LCD.print(minuts);
   LCD.setCursor(5, 0);     // ставим курсор на 1 символ первой строки
   LCD.print(":");
   LCD.setCursor(6, 0);     // ставим курсор на 1 символ первой строки
   LCD.print(seconds);
  }

  
   if(seconds < 10 && minuts >= 10 && hours >= 10) {
   LCD.setCursor(0, 0);     // ставим курсор на 1 символ первой строки
   LCD.print("                ");
   LCD.setCursor(0, 0);     // ставим курсор на 1 символ первой строки
   LCD.print(hours);
   LCD.setCursor(2, 0);     // ставим курсор на 1 символ первой строки
   LCD.print(":");
   LCD.setCursor(3, 0);     // ставим курсор на 1 символ первой строки
   LCD.print(minuts);
   LCD.setCursor(5, 0);     // ставим курсор на 1 символ первой строки
   LCD.print(":");
   LCD.setCursor(6, 0);     // ставим курсор на 1 символ первой строки
   LCD.print("0");
   LCD.setCursor(7, 0);     // ставим курсор на 1 символ первой строки
   LCD.print(seconds);
  }


  if(seconds < 10 && minuts < 10 && hours >= 10) {
   LCD.setCursor(0, 0);     // ставим курсор на 1 символ первой строки
   LCD.print("                ");
   LCD.setCursor(0, 0);     // ставим курсор на 1 символ первой строки
   LCD.print(hours);
   LCD.setCursor(2, 0);     // ставим курсор на 1 символ первой строки
   LCD.print(":");
   LCD.setCursor(3, 0);     // ставим курсор на 1 символ первой строки
   LCD.print("0");
   LCD.setCursor(4, 0);     // ставим курсор на 1 символ первой строки
   LCD.print(minuts);
   LCD.setCursor(5, 0);     // ставим курсор на 1 символ первой строки
   LCD.print(":");
   LCD.setCursor(6, 0);     // ставим курсор на 1 символ первой строки
   LCD.print("0");
   LCD.setCursor(7, 0);     // ставим курсор на 1 символ первой строки
   LCD.print(seconds);
  }
}

void mig_Time(String x) {
  LCD.setCursor(0, 0);        // ставим курсор на 1 символ второй строки
  LCD.print(x);   // печатаем сообщение на первой строке
  delay(500);
  LCD.setCursor(0, 0);        // ставим курсор на 1 символ второй строки
  LCD.print("                ");   // печатаем сообщение на первой строке
  delay(500);
  LCD.setCursor(0, 0);        // ставим курсор на 1 символ второй строки
  LCD.print(x);   // печатаем сообщение на первой строке
}

void mig_Secondomer(String w) {
  LCD.setCursor(0, 0);        // ставим курсор на 1 символ второй строки
  LCD.print(w);   // печатаем сообщение на первой строке
  delay(500);
  LCD.setCursor(0, 0);        // ставим курсор на 1 символ второй строки
  LCD.print("                ");   // печатаем сообщение на первой строке
  delay(500);
  LCD.setCursor(0, 0);        // ставим курсор на 1 символ второй строки
  LCD.print(w);   // печатаем сообщение на первой строке
}

void mig_Edit_time(String y) {
  LCD.setCursor(0, 1);        // ставим курсор на 1 символ второй строки
  LCD.print(y);   // печатаем сообщение на первой строке
  delay(500);
  LCD.setCursor(0, 1);        // ставим курсор на 1 символ второй строки
  LCD.print("                ");   // печатаем сообщение на первой строке
  delay(500);
  LCD.setCursor(0, 1);        // ставим курсор на 1 символ второй строки
  LCD.print(y);   // печатаем сообщение на первой строке
}

void mig_Edit_time_up(String t) {
  LCD.setCursor(0, 0);        // ставим курсор на 1 символ второй строки
  LCD.print(t);   // печатаем сообщение на первой строке
  delay(500);
  LCD.setCursor(0, 0);        // ставим курсор на 1 символ второй строки
  LCD.print("                ");   // печатаем сообщение на первой строке
  delay(500);
  LCD.setCursor(0, 0);        // ставим курсор на 1 символ второй строки
  LCD.print(t);   // печатаем сообщение на первой строке
}

void mig_Menu(String u) {
  LCD.setCursor(0, 0);        // ставим курсор на 1 символ второй строки
  LCD.print(u);   // печатаем сообщение на первой строке
  delay(500);
  LCD.setCursor(0, 0);        // ставим курсор на 1 символ второй строки
  LCD.print("                ");   // печатаем сообщение на первой строке
  delay(500);
  LCD.setCursor(0, 0);        // ставим курсор на 1 символ второй строки
  LCD.print(u);   // печатаем сообщение на первой строке
  delay(500);
  LCD.setCursor(0, 0);        // ставим курсор на 1 символ второй строки
  LCD.print("                ");   // печатаем сообщение на первой строке
  delay(500);
}
void Exit_Edit_Time() {
     if(digitalRead(3) == 0){
    delay(250);
     if(digitalRead(3) == 0){
      delay(250);
       if(digitalRead(3) == 0){
        for(int q = 0; q < 1000; q) {
         if(digitalRead(3) == 0) {
          q++;
         }
    else {
          i=0;
         }
        delay(1);
       }
       i++;
       LCD.clear();
      }
    }
  }
 }
