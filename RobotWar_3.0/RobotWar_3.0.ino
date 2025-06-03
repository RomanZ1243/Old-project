#define CH1 A2 // X ПРАВОГО ДЖОЙСТИКА
#define CH2 A3 // Y ПРАВОГО ДЖОЙСТИКА
#define CH3 A4 // Y ЛЕВОГО ДЖОЙСТИКА
#define CH4 A5 // X ЛЕВОГО ДЖОЙСТИКА
#define CH10 A1
#define CH7 A0
#define CH9 8
#define CH5 3



// #define CH5 6
// #define CH6 7

#define MLF 6
#define MRF 9
#define MLB 10
#define MRB 11
#define Break 2
#define Gun 7
#define Speed1 12
#define Speed3 13

int CH1_value = 0;
int CH11_value = 0;
int CH2_value = 0;
int CH21_value = 0;

bool isGun = 0;
bool isBreak = 0;
bool action = 0;

// cvd - CH10
enum Direction {
  Idle,
  Up,
  Down,
  Left,
  Right,
  UpLeft,
  UpRight,
  DownLeft,
  DownRight,
};

Direction direction;

void setup() {
  Serial.begin(9600);

  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  pinMode(CH3, INPUT);
  pinMode(CH4, INPUT);
  pinMode(CH5, INPUT);
  pinMode(CH9, INPUT);
  pinMode(CH10, INPUT);

  pinMode(MLF, OUTPUT);
  pinMode(MRF, OUTPUT);
  pinMode(MLB, OUTPUT);
  pinMode(MRB, OUTPUT);
  pinMode(Gun, OUTPUT);

  pinMode(Break, OUTPUT);

  pinMode(Speed1, OUTPUT);
  pinMode(Speed3, OUTPUT);

  digitalWrite(MLF, LOW);
  digitalWrite(MRF, LOW);
  digitalWrite(MLB, LOW);
  digitalWrite(MRB, LOW);
}

void loop() {
  // CH4 (x - правый джостик):
  // down 1000
  // up 2000
  // mid 1500
//

  if(pulseIn(CH10, HIGH)<1100) {
    isBreak = 1;
    }
  else isBreak = 0;

  int CH1_value = map(pulseIn(CH1, HIGH), 1500, 2000, 0, 160);// поворот вправо(1 и 4 колесо)
  int CH11_value = map(pulseIn(CH1, HIGH), 980, 1500, 160, 0);//поворот влево(2 и 3 колесо)
  int CH2_value = map(pulseIn(CH2, HIGH), 1500, 2000, 0, 160);//процент хода вперед(1 и 2 колесо)
  int CH21_value = map(pulseIn(CH2, HIGH), 980, 1500, 160, 0);//процент заднего хода(3 и 4 колесо)

  action = 0;
  if(pulseIn(CH1, HIGH)>1600){
    direction = Right;
    action = 1;
  }
  if(pulseIn(CH1, HIGH)<1400){
    direction = Left;
    action = 1;
  }
  if(pulseIn(CH2, HIGH)>1600){
    direction = Up;
    action = 1;
  }
  if(pulseIn(CH2, HIGH)<1400){
    direction = Down;
    action = 1;
  }


  if(pulseIn(CH1, HIGH)>1600 && pulseIn(CH2, HIGH)>1600){
    direction = UpRight;
    action = 1;
  }
  if(pulseIn(CH1, HIGH)<1400 && pulseIn(CH2, HIGH)>1600){
    direction = UpLeft;
    action = 1;
  }
  if(pulseIn(CH1, HIGH)>1600 && (pulseIn(CH2, HIGH)<1400)){
    direction = DownRight;
    action = 1;
  }
  if(pulseIn(CH1, HIGH)<1400 && (pulseIn(CH2, HIGH)<1400)){
    direction = DownLeft;
    action = 1;
  }

  if(action==0)
  direction = Idle;

  switch(direction) {
    case Idle: {
    
      digitalWrite(Break, isBreak);
     

      analogWrite(MLF, 0);
      analogWrite(MRF, 0);
      analogWrite(MLB, 0);
      analogWrite(MRB, 0);

      // Serial.println("ALL WHEEL = 0 ");

      break;
    }
    case Up: {
      analogWrite(MLF, CH2_value);
      analogWrite(MRF, CH2_value);
      analogWrite(MLB, 0);
      analogWrite(MRB, 0);

      digitalWrite(Break, 0);
    

      /* Serial.print("1 WHEEL =");
      Serial.println(CH2_value);
      Serial.print("2 WHEEL =");
      Serial.println(CH2_value);*/

      break; 
    }
    case Right: {
      analogWrite(MLF, CH1_value);
      analogWrite(MRB, CH1_value);
      analogWrite(MRF, 0);
      analogWrite(MLB, 0);

      digitalWrite(Break, 0);

      /* Serial.print("1 WHEEL =");
      Serial.println(CH1_value);
      Serial.print("4 WHEEL =");
      Serial.println(CH1_value); */

      break;
    }
    case Left: {
      analogWrite(MRF, CH11_value);
      analogWrite(MLB, CH11_value);
      analogWrite(MLF, 0);
      analogWrite(MRB, 0);

      digitalWrite(Break, 0);
  

      /* Serial.print("2 WHEEL ="); 
      Serial.println(CH11_value);
      Serial.print("3 WHEEL =");
      Serial.println(CH11_value); */

      break;
    }

    case Down: {
      analogWrite(MLB, CH21_value);
      analogWrite(MRB, CH21_value);
      analogWrite(MLF, 0);
      analogWrite(MRF, 0);

      digitalWrite(Break, 0);
     
      /* Serial.print("3 WHEEL =");
      Serial.println(CH21_value);
      Serial.print("4 WHEEL =");
      Serial.println(CH21_value); */

      break;
    }

    case UpLeft: {
      analogWrite(MRF, CH2_value);
      analogWrite(MLF, 0);
      analogWrite(MLB, 0);
      analogWrite(MRB, 0);

      digitalWrite(Break, 0);
   

      /* Serial.print("2 WHEEL =");
      Serial.println(CH2_value);
      Serial.print("1 WHEEL =");
      Serial.println(0); */

      break;
    }

    case UpRight: {
      analogWrite(MRF, CH2_value);
      analogWrite(MLF, 0);
      analogWrite(MLB, 0);
      analogWrite(MRB, 0);

      digitalWrite(Break, 0);
    

      /* Serial.print("1 WHEEL =");
      Serial.println(CH2_value);
      Serial.print("2 WHEEL =");
      Serial.println(0); */

      break;
    }

    case DownLeft:{
      analogWrite(MRB, CH2_value);
      analogWrite(MLB, 0);
      analogWrite(MLF, 0);
      analogWrite(MRF, 0);

      digitalWrite(Break, 0);
      

      /* Serial.print("4 WHEEL =");
      Serial.println(CH21_value);
      Serial.print("3 WHEEL =");
      Serial.println(0); */

      break;
    }

    case DownRight:{
      analogWrite(MLB, CH2_value);
      analogWrite(MRB, 0);
      analogWrite(MLF, 0);
      analogWrite(MRF, 0);

      digitalWrite(Break, 0);
    

      /* Serial.print("3 WHEEL =");
      Serial.println(CH21_value);
      Serial.print("4 WHEEL =");
      Serial.println(0); */

      break;
    }
  }

     

  if(pulseIn(CH5, HIGH)>1700){
  isGun=1;
  }
  else isGun=0;


  if(pulseIn(CH7, HIGH)>1100 && isGun==1){
    digitalWrite(Gun, HIGH);
  }
  else digitalWrite(Gun,LOW);

  if(pulseIn(CH9, HIGH)<1100 ){
    digitalWrite(Speed1, HIGH);
    digitalWrite(Speed3, LOW);
  }
  if(pulseIn(CH9, HIGH)>1100 && pulseIn(CH9, HIGH)<1800){
    digitalWrite(Speed3, LOW);
    digitalWrite(Speed1, LOW);
  }
 if(pulseIn(CH9, HIGH)>1800){
    digitalWrite(Speed3, HIGH);
    digitalWrite(Speed1, LOW);
  }


  delay(1);
}






















/*
  int joyLeftY = pulseIn(CH1, HIGH);
  int joyLeftX = pulseIn(CH2, HIGH);

 /* analogWrite( , CH1_value );
  analogWrite( , CH1_value );
  analogWrite( , CH1_value );
  analogWrite( , CH1_value );
  

Serial.print((joyLeftY - 1500) + (joyLeftX - 1500));
Serial.print(" ");
Serial.println( joyLeftY - 1500 );
Serial.print(1);
Serial.print(" ");
Serial.println( 1);
Serial.println("");

Serial.println(' ');
*/


/*
  if(CH1_value >0){
    Serial.print("1 WHEEL ="); 
    Serial.println(CH1_value);
    Serial.print("4 WHEEL =");
    Serial.println(CH1_value);
  }
  if(CH11_value <1500){
    Serial.print("2 WHEEL ="); 
    Serial.println(CH11_value);
    Serial.print("3 WHEEL =");
    Serial.println(CH11_value);
  }
  if(CH2_value >1500){
    Serial.print("1 WHEEL =");
    Serial.println(CH2_value);
    Serial.print("2 WHEEL =");
    Serial.println(CH2_value);
  }
  if(CH21_value <1500){
    Serial.print("3 WHEEL =");
    Serial.println(CH21_value);
    Serial.print("4 WHEEL =");
    Serial.println(CH21_value);
  }
*/
/*
int PWM3_value = map(, 0, 255, 0, 100);

  bool idle1 = false;
  if(pulseIn(CH2, HIGH) >= 1700) {
    direction = forward;
    idle1 = false;
    Serial.println("Forward");
  } else if(pulseIn(CH2, HIGH) <= 1200) {
    direction = backward;
    idle1 = false;
    Serial.println("Backward");
  } else {
    idle1 = true;
  }

  bool idle2 = false;
  if(pulseIn(CH1, HIGH) <= 1200) {
    direction = left;
    idle2 = false;
    Serial.println("Left");
  } else if(pulseIn(CH1, HIGH) >= 1700) {
    direction = right;
    idle2 = false;
    Serial.println("Right");
  } else {
    idle2 = true;
  }

  if(idle1 && idle2) {
    direction = idle;
    Serial.println("Idle");
  }

  switch(direction) {
    case idle: {
      digitalWrite(MLF, LOW);
      digitalWrite(MRF, LOW);
      digitalWrite(MLB, LOW);
      digitalWrite(MRB, LOW);
      break;
    }
    case forward: {
      digitalWrite(MLF, HIGH);
      digitalWrite(MRF, HIGH);
      break;
    }
  }
*/
