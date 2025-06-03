#include <Servo.h>
Servo myservo;
#define red 10
#define green 9
#define blue 8
int z = 0;
int xx = 0;
int x = 5;
String y;
String y1;
int a = 0;
int b = 0;
int c = 0;
int d = 0;

void setup() {
pinMode(2,INPUT_PULLUP);  // put your setup code here, to run once:
pinMode(3,INPUT_PULLUP);
pinMode(4,INPUT_PULLUP);
pinMode(5,INPUT_PULLUP);
pinMode(6,INPUT_PULLUP);
pinMode(8,OUTPUT);
pinMode(9,OUTPUT);
pinMode(10,OUTPUT);
myservo.attach(11);
Serial.begin(9600);
}

void loop() {
digitalWrite(blue, HIGH);
if(z == 0){
  myservo.write(110); //open
  z = 1;
}
xx = 0;
if(xx == 0){
  if(x == 5){    
    delay(500);
    Serial.println("Введите число 1");
    x = 0;
  }
  if(x == 0){
    if (digitalRead(2) == 0){
      a = 1;
      delay(500);
      Serial.println("Введите число 2");
      x = 1;
    }
    if (digitalRead(3) == 0){
      a = 2;
      delay(500);
      Serial.println("Введите число 2");
      x = 1;
    }
    if (digitalRead(4) == 0){
      a = 3;
      delay(500);
      Serial.println("Введите число 2");
      x = 1;
     }
    if (digitalRead(5) == 0){
      a = 4;
      delay(500);
      Serial.println("Введите число 2");
      x = 1;
    }  
  }

  if(x == 1){
    if (digitalRead(2) == 0){
      b = 1;
      delay(500);
      Serial.println("Введите число 3");
      x = 2;
    }
    if (digitalRead(3) == 0){
      b = 2;
      delay(500);
      Serial.println("Введите число 3");
      x = 2;
    }
    if (digitalRead(4) == 0){
      b = 3;
      delay(500);
      Serial.println("Введите число 3");
      x = 2;
     }
    if (digitalRead(5) == 0){
      b = 4;
      delay(500);
      Serial.println("Введите число 3");
      x = 2;
    }   
  }

  if(x == 2){
    if (digitalRead(2) == 0){
      c = 1;
      delay(500);
      Serial.println("Введите число 4");
      x = 3;
    }
    if (digitalRead(3) == 0){
      c = 2;
      delay(500);
      Serial.println("Введите число 4");
      x = 3;
    }
    if (digitalRead(4) == 0){
      c = 3;
      delay(500);
      Serial.println("Введите число 4");
      x = 3;
     }
    if (digitalRead(5) == 0){
      c = 4;
      delay(500);
      Serial.println("Введите число 4");
      x = 3;
    }    
  }

  if(x == 3){
    if (digitalRead(2) == 0){
      d = 1;
      x = 4;
    }
    if (digitalRead(3) == 0){
      d = 2;
      x = 4;
    }
    if (digitalRead(4) == 0){
      d = 3;
      x = 4;
     }
    if (digitalRead(5) == 0){
      d = 4;
      x = 4;
    }  
  }


if (x == 4){
  Serial.println(a);
  Serial.println(b);
  Serial.println(c);
  Serial.println(d); 
  String myStr = String(a);
  String myStr1 = String(b);
  String myStr2 = String(c);
  String myStr3 = String(d);
  y = myStr + myStr1 + myStr2 + myStr3;
  Serial.println(y); 
  digitalWrite(blue,LOW);
  delay(200);
  digitalWrite(blue,HIGH);
  delay(200);
  digitalWrite(blue,LOW); 
  delay(200); 
  digitalWrite(blue,HIGH);
  delay(200);
  digitalWrite(blue,LOW); 
  a = 0;
  b = 0;
  c = 0;
  d = 0;
  myservo.write(15); //lock
  x = 6;
  xx = 1;
}
}


if(xx = 1){ 
  if(x == 6){
    delay(500);
    Serial.println("Введите число 1");
    x = 7;
  }
  if(x == 7){
    if (digitalRead(2) == 0){
      a = 1;
      delay(500);
      Serial.println("Введите число 2");
      x = 8;
    }
    if (digitalRead(3) == 0){
      a = 2;
      delay(500);
      Serial.println("Введите число 2");
      x = 8;
    }
    if (digitalRead(4) == 0){
      a = 3;
      delay(500);
      Serial.println("Введите число 2");
      x = 8;
     }
    if (digitalRead(5) == 0){
      a = 4;
      delay(500);
      Serial.println("Введите число 2");
      x = 8;
    }    
  }

  if(x == 8){
    if (digitalRead(2) == 0){
      b = 1;
      delay(500);
      Serial.println("Введите число 3");
      x = 9;
    }
    if (digitalRead(3) == 0){
      b = 2;
      delay(500);
      Serial.println("Введите число 3");
      x = 9;
    }
    if (digitalRead(4) == 0){
      b = 3;
      delay(500);
      Serial.println("Введите число 3");
      x = 9;
     }
    if (digitalRead(5) == 0){
      b = 4;
      delay(500);
      Serial.println("Введите число 3");
      x = 9;
    }    
  }

  if(x == 9){
    if (digitalRead(2) == 0){
      c = 1;
      delay(500);
      Serial.println("Введите число 4");
      x = 10;
    }
    if (digitalRead(3) == 0){
      c = 2;
      delay(500);
      Serial.println("Введите число 4");
      x = 10;
    }
    if (digitalRead(4) == 0){
      c = 3;
      delay(500);
      Serial.println("Введите число 4");
      x = 10;
     }
    if (digitalRead(5) == 0){
      c = 4;
      delay(500);
      Serial.println("Введите число 4");
      x = 10;
    }    
  }

  if(x == 10){
    if (digitalRead(2) == 0){
      d = 1;
      x = 11;
    }
    if (digitalRead(3) == 0){
      d = 2;
      x = 11;
    }
    if (digitalRead(4) == 0){
      d = 3;
      x = 11;
     }
    if (digitalRead(5) == 0){
      d = 4;
      x = 11;
    }    
  }

if (x == 11){
  Serial.println(a);
  Serial.println(b);
  Serial.println(c);
  Serial.println(d); 
  String myStr = String(a);
  String myStr1 = String(b);
  String myStr2 = String(c);
  String myStr3 = String(d);
  y1 = myStr + myStr1 + myStr2 + myStr3;
  Serial.println(y1); 
  digitalWrite(blue,LOW);
  delay(300);
  digitalWrite(blue,HIGH);
  delay(300);
  digitalWrite(blue,LOW);  
  a = 0;
  b = 0;
  c = 0;
  d = 0;
  x = 12;
  xx = 2;
}
}
if(xx == 2){
  if(y == y1){
    digitalWrite(green,HIGH);
    myservo.write(110); //open
    delay(1000);
    digitalWrite(green,LOW);
    z = 2;
    if(digitalRead(2) == 0 && digitalRead(5) == 0){
      xx = 0;      
    }
    if(digitalRead(6) == 0){
      myservo.write(15); //lock
    xx = 1;  
    }
  }
  else{
  digitalWrite(red,HIGH);
  delay(100);
  digitalWrite(red,LOW);
  delay(100);
  digitalWrite(red,HIGH);
  delay(100);
  digitalWrite(red,LOW);
  x = 6;
  xx = 1;    
  }
}
if(z == 2){
    if(digitalRead(5) == 0){
      xx = 0;
      x = 5;  
      z = 3;    
    }
    if(digitalRead(2) == 0){
      myservo.write(15); //lock
      xx = 1; 
      x = 6;
      z = 3; 
    }
  }
}
