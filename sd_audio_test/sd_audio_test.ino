#include <SD.h>             // необходимо включить SD библиотеку
#include <TMRpcm.h>         // также необходимо включить данную библиотеку...
#include <SPI.h>
// Измените это в соответствии с вашей платой расширения или модулем;
const int chipSelect = 4;
TMRpcm music;   // создать объект для использования в данном скетче
void setup()
{
  // Открыть последовательное соединение и ждать открытия порта:
  Serial.begin(9600);
  Serial.println("Initializing SD card...");
  if (!SD.begin(chipSelect))
  {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
  music.speakerPin = 9; // 11 на Mega, 9 на Uno, Nano и т.д.
  music.setVolume(3);    //   от 0 до 7. Установка уровня громкости
  music.quality(1);        //  1 для 2x передескритезации, 0 for для нормального режима
}
void loop()
{
  music.play("Sound/0002.wav");
  Serial.println("Play 2.wav");
  delay(2000);
  music.play("Sound/0001.wav");
  Serial.println("Play 1.wav");
  delay(2000);
  music.play("Sound/0003.wav");
  Serial.println("Play 3.wav");
  delay(2000);
  music.play("Sound/0004.wav");
  Serial.println("Play 4.wav");
  delay(2000);
  music.play("Sound/0005.wav");
  Serial.println("Play 5.wav");
  delay(2000);
}
