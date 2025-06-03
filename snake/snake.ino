#define BUT1 4
#define BUT2 5
#define BUT3 6
#define BUT4 7
#include <TroykaOLED.h>

TroykaOLED oled(0x3C);

int8_t x[19] = {64, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int8_t y[19] = {32, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int8_t pX, pY, pXp, pYp;

int8_t lineTraffic = 0, longSnake = 0, xa, ya;
uint16_t eatApple = 0;

boolean apple = true;
boolean go = true; 
boolean fb1, fb2, fb3, fb4, retur1, retur2, retur3, retur4;



void setup() {
oled.begin();
oled.autoUpdate(false);
oled.setCoding(Encoding::UTF8);

pinMode(BUT1, INPUT_PULLUP);
pinMode(BUT2, INPUT_PULLUP);
pinMode(BUT3, INPUT_PULLUP);
pinMode(BUT4, INPUT_PULLUP);

pXp = 126;
pX = oled.getWidth() / 2;
pY = oled.getHeight() / 2;


}

void loop() {
oled.setFont(alphabet6x8);
oled.clearDisplay();

// Куда едет змейка

if (but1() && lineTraffic != 3) {
  but1(); 
  lineTraffic = 1;  
} else if (but2() && lineTraffic != 4) {
  but2();
  lineTraffic = 2;
} else if (but3() && lineTraffic != 1) {
  but3();
  lineTraffic = 3;
} else if (but4() && lineTraffic != 2) {
  but4();
  lineTraffic = 4;
} 






if (x[0] < 0 || x[0] > 126 || y[0] < 0 || y[0] > 62) {
go = false;
}

if (go) {
// Движение змеи
for (int i = longSnake; i > 0; i--) {
  x[i] = x[i - 1];
  y[i] = y[i - 1];
}

  
if (lineTraffic == 1) {
x[0] -= 2;
} else if (lineTraffic == 2) {
y[0] -= 2;  
} else if (lineTraffic == 3) {
x[0] += 2;  
} else if (lineTraffic == 4) {
y[0] += 2;
}


if (apple) {
xa = random(4, 122);
ya = random(4, 58);
apple = false;  
}
// eat apple
if ((x[0] - xa >= 0 && x[0] - xa <= 2 || xa - x[0] >= 0 && 
xa - x[0] <= 2) && (y[0] - ya >= 0 &&
y[0] - ya <= 2 || ya - y[0] >= 0 && ya - y[0] <= 2)) {
  
  longSnake++;
  eatApple++;
  if (longSnake > 18) {longSnake = 18;}
  apple = true;
  
}


// Draw snake
for (int i = 1; i < 19; i++) {
 if (x[i] != -1 && y[i] != -1) {
  oled.drawRect(x[i], y[i], x[i] + 2, y[i] + 2);   

 }
}
 

oled.drawRect(x[0], y[0], x[0] + 2, y[0] + 2);
oled.drawRect(xa, ya, xa + 2, ya + 2);
//oled.print(eatApple, OLED_CENTER, OLED_TOP);
oled.update();  


} else {



oled.print(eatApple, OLED_CENTER, OLED_TOP);
oled.print("Game Over", OLED_CENTER, OLED_CENTER); 
oled.update();


 }
}

// Обработчик кнопок

boolean but1() {
if (!digitalRead(BUT1) && fb1) {
  retur1 = true;
}
fb1 = digitalRead(BUT1);
if (retur1) {
  retur1 = false;
  return true;
}
}

boolean but2() {
if (!digitalRead(BUT2) && fb2) {
  retur2 = true;
}
fb2 = digitalRead(BUT2);
if (retur2) {
  retur2 = false;
  return true;
 }
}
boolean but3() {
if (!digitalRead(BUT3) && fb3) {
  retur3 = true;
}
fb3 = digitalRead(BUT3);
if (retur3) {
  retur3 = false;
  return true;
 }
}

boolean but4() {
if (!digitalRead(BUT4) && fb4) {
  retur4 = true;
}
fb4 = digitalRead(BUT4);
if (retur4) {
  retur4 = false;
  return true;
  
 }
}
