int i;
int randomColor;

#define of 7
#define red 1
#define yellow 4
#define green 2
#define blue 3
#define ButtonBlue 5
#define ButtonYellow 6
#define ButtonRed 9
#define ButtonGreen 10
void RGB(byte color) {
  switch (color) {
    case red:
      digitalWrite(red, HIGH);
      digitalWrite(blue, LOW);
      digitalWrite(green, LOW);
      break;
    case green:
      digitalWrite(green, HIGH);
      digitalWrite(blue, LOW);
      digitalWrite(red, LOW);
      break;
    case blue:
      digitalWrite(blue, HIGH);
      digitalWrite(green, LOW);
      digitalWrite(red, LOW);
      break;
    case yellow:
      digitalWrite(green, HIGH);
      digitalWrite(blue, LOW);
      digitalWrite(red, HIGH);
      break;
    default:

      break;
   
  }
}

void setup() {
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(ButtonBlue, INPUT_PULLUP);
  pinMode(ButtonYellow, INPUT_PULLUP);
  pinMode(ButtonRed, INPUT_PULLUP);
  pinMode(ButtonGreen, INPUT_PULLUP);
  randomSeed(analogRead(A0));
  Serial.begin(9600);
}

void loop() {


  RGB(random(1,5));
  delay(1000);
digitalWrite(green, LOW);
      digitalWrite(red, LOW);
      digitalWrite(blue, LOW);
 delay(300);

butState - !digitalRead(ButtonBlue) | !digitalRead(ButtonYellow) << 1 | !digitalRead(ButtonRed) << 2 | !digitalRead(ButtonGreen) << 3;

if(batState = 1 & ButtonBlue = 0){//правильно

}
if(batState = 1 & ButtonYellow = 0){//неправильно

}
if(batState = 1 & ButtonRed = 0){//неправильно

}
if(batState = 1 & ButtonGreen = 0){//неправильно

}
if(batState = 2 & ButtonBlue = 0){//правильно

}
if(batState = 2 & ButtonYellow = 0){//неправильно

}
if(batState = 2 & ButtonRed = 0){//неправильно

}
if(batState = 2 & ButtonGreen = 0){//неправильно

}
if(batState = 3 & ButtonBlue = 0){//правильно

}
if(batState = 3 & ButtonYellow = 0){//неправильно

}
if(batState = 3 & ButtonRed = 0){//неправильно

}
if(batState = 3 & ButtonGreen = 0){//неправильно

}
}
