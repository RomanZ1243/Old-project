// analog pin connected to keypad
#define KEYPAD_PIN 0
 
// milliseconds to wait, to make sure key is pressed
#define TIME_TO_WAIT 50
 
void setup()
{
    Serial.begin(9600);
}
 
void loop()
{
    // reading once
    int r1 = analogRead(KEYPAD_PIN) / 10;
    // waiting
    delay(TIME_TO_WAIT);
    // reading 2nd time - to make sure key is pressed for at least TIME_TO_WAIT milliseconds
    int r2 = analogRead(KEYPAD_PIN) / 10;
    if (r1 == r2) {
        switch (r1) {
        case 350: Serial.println("0"); break;
        case 270: Serial.println("1"); break;
        case 360: Serial.println("2"); break;
        case 120: Serial.println("3"); break;
        case 210: Serial.println("4"); break;
        case 330: Serial.println("5"); break;
        case 0  : Serial.println("6"); break;
        case 240: Serial.println("7"); break;
        case 340: Serial.println("8"); break;
        case 50 : Serial.println("9"); break;
        case 250: Serial.println("*"); break;
        case 80 : Serial.println("#"); break;
        }
    }
}
