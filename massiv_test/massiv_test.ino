int a[3] = {0, 0, 10};
int x;
int flag;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(calc(x));
  x++;
  delay(1000);
}

int calc(int num) {
  int b[sizeof(a) / sizeof(a[0]) + 1];
  //Serial.println(sizeof(b) / sizeof(b[0]));
  for (int i = 0; i <= sizeof(a) / sizeof(a[0]) - 1; i++) {
    b[i] = a[i];
    //Serial.println(1);
  }

  b[sizeof(b) / sizeof(b[0]) - 1] = 1;

  int a[sizeof(b) / sizeof(b[0])];

  for (int i = 0; i <= sizeof(b) / sizeof(b[0]) - 1; i++) {
    a[i] = b[i];
  }
  for (int i = 0; i <= sizeof(b) / sizeof(b[0]) - 1; i++) {
    a[i] = b[i];
  }
  //Serial.println(sizeof(a) / sizeof(a[0]));// put your main code here, to run repeatedly:
  //Serial.println(sizeof(a) / sizeof(a[0]));
  return a[num];
}
