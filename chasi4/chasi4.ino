#define kn1 2
#define kn2 3
#define kn3 4
#define CLK 5
#define DIO 6
#define LED 7
#define PISK 8

#include <GyverTM1637.h>//библиотека для 4-разрядного семисегментного индикатора
#include <GyverButton.h>//библиотека для кнопок
GButton butt1(kn1);//кнопка выбора символа //кнопка запуска настроек
GButton butt2(kn2);//кнопка выбора значения //кнопка запуска будильника
GButton butt3(kn3);//enter
GyverTM1637 disp(CLK, DIO);//подключаем 4-разрядный семисегментный индикатор

boolean flag = 1;//индикация точек
boolean flag1;//выбор символа (часы)
boolean flag2 = 1;//вкл/выкл (будильник)
boolean flag4 = 1;//12H/24H (настройка)
int x;//переключение между функциями
int x1;//индикация выбранного символа
int x2;//время
int x3;//задержка
int x4;//задержка звонка
int x5;//будильник
int h;//часы (часы)
int h1;//часы левый символ (часы)
int h2;//часы правый символ (часы)
int h3;//часы (будильник)
int h4;//часы левый символ (будильник)
int h5;//часы правый символ (будильник)
int m;//минуты (часы)
int m1;//минуты левый символ (часы)
int m2;//минуты правый символ (часы)
int m3;//минуты левый символ (будильник)
int m4;//минуты правый символ (будильник)
int m5;//минуты (будильник)

void setup() {
  disp.clear();//очищаем 4-разрядный семисегментный индикатор
  disp.brightness(7);  // яркость, 0 - 7 (минимум - максимум)
  pinMode(LED, OUTPUT);
  pinMode(PISK, OUTPUT);
  pinMode(kn3, INPUT_PULLUP);
  butt1.setTickMode(AUTO);
  butt2.setTickMode(AUTO);
  butt3.setTickMode(AUTO);
  Serial.begin(9600);
}
void loop() {
  if (x == 0) {
    zastavka();
  }
  if (x == 1) {
    nClock();
  }
  if (x == 2) {
    Clock();
  }
  if (x == 3) {
    aClock();
  }
  if (x == 4) {
    settings();
  }
  if (x == 5) {
    bell();
  }
}

void zastavka() {
  disp.twist(8, 8, 8, 8, 50);
  delay(1000);
  disp.clear();
  delay(500);
  x = 1;
}

void nClock() {
  disp.point(1);
  if (butt1.isPress()) {
    flag1 = !flag1;
    x1 = 0;
  }

  if (flag1 == 0) {
    if (x1 == 0) {
      disp.display(0, h1);
      disp.display(1, h2);
      disp.display(2, m1);
      disp.display(3, m2);
      delay(300);
      disp.clear();
      disp.display(2, m1);
      disp.display(3, m2);
      delay(200);
      disp.display(0, h1);
      disp.display(1, h2);
      x1 = 1;
    }

    if (x1 == 1) {
      if (butt2.isHold()) {
        disp.display(0, h1);
        disp.display(1, h2);
        delay(100);
        h2++;
        h++;
        if (h2 > 9) {
          h1++;
          h2 = 0;
        }
        if (h > 23) {
          h1 = 0;
          h2 = 0;
          h = 0;
        }
      }

      if (butt2.isPress()) {
        disp.display(0, h1);
        disp.display(1, h2);
        h2++;
        h++;
        if (h2 > 9) {
          h1++;
          h2 = 0;
        }
        if (h > 23) {
          h1 = 0;
          h2 = 0;
          h = 0;
        }
      }
    }
  }

  if (flag1 == 1) {
    if (x1 == 0) {
      disp.display(0, h1);
      disp.display(1, h2);
      disp.display(2, m1);
      disp.display(3, m2);
      delay(300);
      disp.clear();
      disp.display(0, h1);
      disp.display(1, h2);
      delay(200);
      disp.display(2, m1);
      disp.display(3, m2);
      x1 = 1;
    }

    if (x1 == 1) {
      if (butt2.isHold()) {
        disp.display(2, m1);
        disp.display(3, m2);
        delay(50);
        m2++;
        m++;
        if (m2 > 9) {
          m1++;
          m2 = 0;
        }
        if (m > 59) {
          m1 = 0;
          m2 = 0;
          m = 0;
        }
      }

      if (butt2.isPress()) {
        disp.display(2, m1);
        disp.display(3, m2);
        m2++;
        m++;
        if (m2 > 9) {
          m1++;
          m2 = 0;
        }
        if (m > 59) {
          m1 = 0;
          m2 = 0;
          m = 0;
        }
      }
    }
  }

  if (butt3.isPress()) {
    flag1 = 0;
    disp.clear();
    x = 2;
  }
}

void Clock() {
  disp.displayClock(h, m);
  if (flag2 == 0) {
    digitalWrite(LED, HIGH);
  }
  if (flag2 == 1) {
    digitalWrite(LED, LOW);
  }
  if (flag2 == 0) {
    if (h == h5) {
      if (m == m5) {
        x = 5;
      }
    }
  }
  delay(50);
  if (butt1.isPress()) {
    x = 4;

  }
  if (butt2.isPress()) {
    h1 = h / 10;
    h2 = h % 10;
    m1 = m / 10;
    m2 = m % 10;
    if (x5 == 0) {
      h3 = h1;
      h4 = h2;
      m3 = m1;
      m4 = m2;
      h5 = h;
      m5 = m;
    }
    flag1 = 1;
    disp.clear();
    x = 3;
  }
  delay(50);
  if (butt1.isPress()) {
    x = 4;

  }
  if (butt2.isPress()) {
    h1 = h / 10;
    h2 = h % 10;
    m1 = m / 10;
    m2 = m % 10;
    if (x5 == 0) {
      h3 = h1;
      h4 = h2;
      m3 = m1;
      m4 = m2;
      h5 = h;
      m5 = m;
    }
    flag1 = 1;
    disp.clear();
    x = 3;
  }
  x2++;
  if (x2 % 600 == 0) {
    m++;
    if (m == 60) {
      m = 0;
      h++;
    }
    if (h == 24) {
      h = 0;
    }

  }
  if (x2 % 5 == 0) {
    disp.point(flag = !flag);
  }
}

void aClock() {
  x5 = 1;
  disp.point(1);
  if (butt1.isClick()) {
    flag1 = !flag1;
    x1 = 0;
  }

  if (flag1 == 0) {
    if (x1 == 0) {
      disp.display(0, h3);
      disp.display(1, h4);
      disp.display(2, m3);
      disp.display(3, m4);
      delay(300);
      disp.clear();
      disp.display(2, m3);
      disp.display(3, m4);
      delay(200);
      disp.display(0, h3);
      disp.display(1, h4);
      x3++;
      x1 = 1;
    }

    if (x1 == 1) {
      if (butt2.isHold()) {
        disp.display(0, h3);
        disp.display(1, h4);
        delay(100);
        h4++;
        h5++;
        if (h4 > 9) {
          h3++;
          h4 = 0;
        }
        if (h5 > 23) {
          h3 = 0;
          h4 = 0;
          h5 = 0;
        }
      }

      if (butt2.isPress()) {
        disp.display(0, h3);
        disp.display(1, h4);
        h4++;
        h5++;
        if (h4 > 9) {
          h3++;
          h4 = 0;
        }
        if (h5 > 23) {
          h3 = 0;
          h4 = 0;
          h5 = 0;
        }
      }
    }
  }

  if (flag1 == 1) {
    if (x1 == 0) {
      disp.display(0, h3);
      disp.display(1, h4);
      disp.display(2, m3);
      disp.display(3, m4);
      delay(300);
      disp.clear();
      disp.display(0, h3);
      disp.display(1, h4);
      delay(200);
      disp.display(2, m3);
      disp.display(3, m4);
      x3++;
      x1 = 1;
    }

    if (x1 == 1) {
      if (butt2.isHold()) {
        disp.display(2, m3);
        disp.display(3, m4);
        delay(50);
        m4++;
        m5++;
        if (m4 > 9) {
          m3++;
          m4 = 0;
        }
        if (m5 > 59) {
          m3 = 0;
          m4 = 0;
          m5 = 0;
        }
      }

      if (butt2.isPress()) {
        disp.display(2, m3);
        disp.display(3, m4);
        m4++;
        m5++;
        if (m4 > 9) {
          m3++;
          m4 = 0;
        }
        if (m5 > 59) {
          m3 = 0;
          m4 = 0;
          m5 = 0;
        }
      }
    }
  }

  if (butt3.isPress()) {
    flag1 = 0;
    disp.clear();
    x = 2;
    flag2 = 0;
  }
  delay(50);
  if (butt1.isClick()) {
    flag1 = !flag1;
    x1 = 0;
  }

  if (flag1 == 0) {
    if (x1 == 0) {
      disp.display(0, h3);
      disp.display(1, h4);
      disp.display(2, m3);
      disp.display(3, m4);
      delay(300);
      disp.clear();
      disp.display(2, m3);
      disp.display(3, m4);
      delay(200);
      disp.display(0, h3);
      disp.display(1, h4);
      x3++;
      x1 = 1;
    }

    if (x1 == 1) {
      if (butt2.isHold()) {
        disp.display(0, h3);
        disp.display(1, h4);
        delay(100);
        h4++;
        h5++;
        if (h4 > 9) {
          h3++;
          h4 = 0;
        }
        if (h5 > 23) {
          h3 = 0;
          h4 = 0;
          h5 = 0;
        }
      }

      if (butt2.isPress()) {
        disp.display(0, h3);
        disp.display(1, h4);
        h4++;
        h5++;
        if (h4 > 9) {
          h3++;
          h4 = 0;
        }
        if (h5 > 23) {
          h3 = 0;
          h4 = 0;
          h5 = 0;
        }
      }
    }
  }

  if (flag1 == 1) {
    if (x1 == 0) {
      disp.display(0, h3);
      disp.display(1, h4);
      disp.display(2, m3);
      disp.display(3, m4);
      delay(300);
      disp.clear();
      disp.display(0, h3);
      disp.display(1, h4);
      delay(200);
      disp.display(2, m3);
      disp.display(3, m4);
      x3++;
      x1 = 1;
    }

    if (x1 == 1) {
      if (butt2.isHold()) {
        disp.display(2, m3);
        disp.display(3, m4);
        delay(50);
        m4++;
        m5++;
        if (m4 > 9) {
          m3++;
          m4 = 0;
        }
        if (m5 > 59) {
          m3 = 0;
          m4 = 0;
          m5 = 0;
        }
      }

      if (butt2.isPress()) {
        disp.display(2, m3);
        disp.display(3, m4);
        m4++;
        m5++;
        if (m4 > 9) {
          m3++;
          m4 = 0;
        }
        if (m5 > 59) {
          m3 = 0;
          m4 = 0;
          m5 = 0;
        }
      }
    }
  }

  if (butt3.isPress()) {
    flag1 = 0;
    disp.clear();
    x = 2;
    flag2 = 0;
  }
  delay(50);
  x2++;
  if (x2 % 600 == 0) {
    m++;
    if (m == 60) {
      m = 0;
      h++;
    }
    if (h == 24) {
      h = 0;
    }
  }
}

void bell() {
  disp.displayClock(h, m);
  tone(PISK, 523, 100);
  delay(50);
  if (digitalRead(kn3) == 0) {
    noTone(PISK);
    x = 2;
  }
  delay(50);
  if (digitalRead(kn3) == 0) {
    noTone(PISK);
    x = 2;
  }
  disp.displayClock(h, m);
  x2++;
  if (x2 % 600 == 0) {
    m++;
    if (m == 60) {
      m = 0;
      h++;
    }
    if (h == 24) {
      h = 0;
    }
  }
  if (x2 % 5 == 0) {
    disp.point(flag = !flag);
  }
  delay(50);
  if (digitalRead(kn3) == 0) {
    noTone(PISK);
    x = 2;
  }
  delay(50);
  if (digitalRead(kn3) == 0) {
    noTone(PISK);
    x = 2;
  }
  disp.displayClock(h, m);
  x2++;
  if (x2 % 10 == 0) {
    m++;
    if (m == 60) {
      m = 0;
      h++;
    }
    if (h == 24) {
      h = 0;
    }
  }
  if (x2 % 5 == 0) {
    disp.point(flag = !flag);
  }
}

void settings() {
  disp.point(0);
  if (butt2.isPress()) {
    flag2 = !flag2;
  }
  if (flag2 == 0) {
    x5 = 1;
    digitalWrite(LED, HIGH);
    disp.displayByte(_empty, _empty, _O, _N);
  }
  if (flag2 == 1) {
    digitalWrite(LED, LOW);
    disp.displayByte(_empty, _O, _F, _F);
  }
  if (butt3.isPress()) {
    x = 2;
  }
  delay(50);
  if (butt2.isPress()) {
    flag2 = !flag2;
  }
  if (flag2 == 0) {
    x5 = 1;
    digitalWrite(LED, HIGH);
    disp.displayByte(_empty, _empty, _O, _N);
  }
  if (flag2 == 1) {
    digitalWrite(LED, LOW);
    disp.displayByte(_empty, _O, _F, _F);
  }
  if (butt3.isPress()) {
    x = 2;
  }
  delay(50);
  x2++;
  if (x2 % 600 == 0) {
    m++;
    if (m == 60) {
      m = 0;
      h++;
    }
    if (h == 24) {
      h = 0;
    }
  }
}
