// динамическое создание и опрос компонентов интерфейса

#define AP_SSID "zuba08"
#define AP_PASS "ro110608ma"

#include <GyverPortal.h>
GyverPortal ui;
#include <Servo.h>

Servo myservo;

int a;
int b;
boolean c;

void build() {
  GP.BUILD_BEGIN();
  GP.THEME(GP_DARK);

  // ОБНОВЛЕНИЯ
  String s;


  // КЛИКИ
  // создём слайдеры с именами sld/0, sld/1 ...

  GP.SLIDER("L1");
  GP.SLIDER("servo");

  // создём кнопки с именами btn/0, btn/1 ...
  GP.BUTTON(String("L2"), String("LED"));

  GP.BUILD_END();
}

void action() {
  if (ui.click()) {
    if (ui.clickSub("servo")) {   // начинается с sld
      a = map(ui.getInt(), 0, 100, 0, 180);
      Serial.println(a);
      myservo.write(a);
    }
    if (ui.clickSub("L1")) {   // начинается с sld
      b = map(ui.getInt(), 0, 100, 0, 255);
      Serial.println(b);
      analogWrite(13, b);
    }
    if (ui.clickSub("L2")) {   // начинается с btn
      c = ! c;
      digitalWrite(14, c);
      Serial.println(c);
    }
  }
}

void setup() {
  pinMode(14, OUTPUT);
  pinMode(13, OUTPUT);
  myservo.attach(16);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(AP_SSID, AP_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());

  ui.attachBuild(build);
  ui.attach(action);
  ui.start();
}

void loop() {
  ui.tick();
}
