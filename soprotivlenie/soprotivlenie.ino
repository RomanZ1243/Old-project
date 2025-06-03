int Vin = 5;      // напряжение на выводе 5V arduino
float Vout = 0;   // напряжение на выводе A0 arduino
float R1 = 1000;  // значение известного сопротивления
int R2 = 0;     // значение неизвестного сопротивления

int a2d_data = 0;
float buffer = 0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  a2d_data = analogRead(A1);
  if (a2d_data)
  {
    buffer = a2d_data * Vin;
    Vout = (buffer) / 1024.0;
    buffer = Vout / (Vin - Vout);
    R2 = R1 * buffer;
    if(R2 <= 0 ){
      R2 = 0;
    }
    Serial.println(R2);
    delay(1000);
  }
}
