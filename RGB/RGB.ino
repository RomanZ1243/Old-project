#include <TFT.h>                 // Подключаем библиотеку TFT  
#include <SPI.h>                 // Подключаем библиотеку SPI
 
#define cs   10                  // Указываем пины cs
#define dc   9                   // Указываем пины dc (A0)
#define rst  8                   // Указываем пины reset
 
TFT TFTscreen = TFT(cs, dc, rst);
 
void setup() 
{
  TFTscreen.begin();
  TFTscreen.background(0, 0, 0); // Очистим экран дисплея
  TFTscreen.setTextSize(2);      // Устанавливаем размер шрифта
}
 
void loop() 
{
/* 
* Установка цвета фона TFTscreen.background ( r , g , b )
* где, r, g и b являются значениями RGB для заданного цвета
*/ 
  TFTscreen.background ( 0 , 0 , 0 );
/*
* Команда установки цвета фона TFTscreen.stroke ( r , g , b )
* где, r, g и b являются значениями RGB для заданного цвета
*/  
  TFTscreen.stroke(255, 0, 0);
/*
 * Вывод текста на дисплей TFTscreen.text("Hello, World!", x, y);
 * где x и y координаты.
*/
  TFTscreen.text("Hello, World!", 6, 47);
  TFTscreen.text("RobotChip", 30, 67);
  delay(500);
}
