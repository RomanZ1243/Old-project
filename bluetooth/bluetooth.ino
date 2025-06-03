String val;
float val1;
int flag;
float Kp;
float Ki;
float Kd;
float Kk;

void setup()
{
  Serial.begin(9600);
  Serial.setTimeout(100);
}

void loop() {
  if (flag == 0) {
    if (Serial.available()) {
      val = Serial.readString();
      val.trim();
      if (val.equals("kp")) {
        flag = 1;
      }
      if (val.equals("ki")) {
        flag = 2;
      }
      if (val.equals("kd")) {
        flag = 3;
      }
      if (val.equals("kk")) {
        flag = 4;
      }
      if(val.equals("clean")){
        Kp = 0;
        Ki = 0;
        Kd = 0;
        Kk = 0;
        Serial.write("OK");
      }
    }
  }
  if (flag > 0 && flag <= 4) {
    if (Serial.available()) {
      val1 = Serial.parseFloat();
      if (flag == 1) {
        Kp = val1;
        flag = 5;
      }
      if (flag == 2) {
        Ki = val1;
        flag = 5;
      }
      if (flag == 3) {
        Kd = val1;
        flag = 5;
      }
      if (flag == 4) {
        Kk = val1;
        flag = 5;
      }
    }
  }
  if (flag == 5) {
    Serial.write("Kp = ");
    Serial.println(Kp);
    Serial.write("Ki = ");
    Serial.println(Ki);
    Serial.write("Kd = ");
    Serial.println(Kd);
    Serial.write("Kk = ");
    Serial.println(Kk);
    Serial.println(" ");
    delay(100);
    flag = 0;
    }
}
