//---КНОПКИ---
#define BUT_L A2  // кнопка лево
#define BUT_C A4  // кнопка центр
#define BUT_R A0  // кнопка право
#define BUT_D A3  // кнопка низ
#define BUT_U A1  // кнопка верх

//---НАСТРОЙКИ---
#define MAX_MENU 5    // количество пунктов в меню

//---ПЕРЕМЕННЫЕ(РАНДОМАЙЗЕР)---
int a;                // счетчик (вместо millis())
byte menu = 1;        // цифра в меню
byte mode;            // режим
byte flag;            // обработка кнопок
byte num;             // рандомное число
byte prev_num = 11;   // предыдущее случайное число (в переборе чисел)
byte prev_num1 = 11;  // предыдущее случайное число (в основном цикле)

//---ПЕРЕМЕННЫЕ(ЗМЕЙКА)---
byte score;                     // счет
byte flag1;                     // подрежимы
boolean flag3;                  // устанавливаем, увеличиваем змейку или нет
byte direct;                    // направление движения (1 - left, 2 - up, 3 - right, 4 - down)
byte prev_direct = 2;           // изначальное направление
byte snake_x[30] = {2, 2, 2};   // координаты змейки (х)
byte snake_y[30] = {6, 5, 4};   // координаты змейки (н)
byte apple[] = {2, 1};          // координаты яблока
byte length_sn = 2;             // длина змейки (+1)
int speed_sn = 1000;            // скорость движения змейки

//---ПЕРЕМЕННЫЕ(ТЕТРИС)---
byte a1;                          // счетчик, количество миганий строки
int8_t x, y;                      // координаты точек фигуры, которую опускаем
byte shape;                       // выбираем случайную фигуру
byte flag2;                       // цикл мигания строки
byte prev_shape = 6;              // предыдущая случайная фигура
boolean count;                    // переменная для мигания строки, которую нужно удалить
byte line_del[7];                 // массив со строками, которые можно удалить
byte num_line_del;                // количество строк, которые можно удалить
byte orient;                      // ориентация фигуры
int speed_t = 1000;               // скорость опускания фигур
int8_t frame[] = {2, -2};         // изначально положение фигуры
byte num_dot[] = {1, 4, 2, 2, 3}; // количество точек в каждой фигуре
byte lower_side[][4] = {          // какие точки надо проверять на низ в каждом положении
  {1, 1, 1, 1},
  {2, 2, 2, 2},
  {2, 2, 2, 2},
  {1, 2, 1, 2},
  {2, 2, 2, 2},
};
boolean figure[][16][2] = {   // фигуры
  { // точка
    {0, 1},
    {0, 1},
    {0, 1},
    {0, 1},
  },
  { // квадрат
    {0, 1}, {1, 1}, {0, 0}, {1, 0},
    {0, 1}, {1, 1}, {0, 0}, {1, 0},
    {0, 1}, {1, 1}, {0, 0}, {1, 0},
    {0, 1}, {1, 1}, {0, 0}, {1, 0},
  },
  { // линия наискосок
    {0, 1}, {1, 0},
    {0, 0}, {1, 1},
    {0, 1}, {1, 0},
    {0, 0}, {1, 1},
  },
  { // линия
    {0, 1}, {0, 0},
    {0, 0}, {1, 0},
    {1, 1}, {1, 0},
    {1, 1}, {0, 1},
  },
  { // угол
    {0, 1}, {1, 1}, {1, 0},
    {0, 1}, {1, 1}, {0, 0},
    {0, 1}, {1, 0}, {0, 0},
    {0, 0}, {1, 1}, {1, 0},
  }
};


//---ПЕРЕМЕННЫЕ(ГРАФИКА)---
byte x_pin[] = {2, 3, 4, 5, 6};             // VCC
byte y_pin[] = {7, 8, 9, 10, 11, 12, 13};   // GND

boolean matrix[][5] = {   // матрица
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
};

void setup() {
  for (int i = 0; i < 5; i++) {   // инициализируем VCC матрицы
    pinMode(x_pin[i], OUTPUT);
  }
  for (int i = 0; i < 7; i++) {   // инициализируем GND матрицы
    pinMode(y_pin[i], OUTPUT);
  }

  pinMode(BUT_U, INPUT_PULLUP);   // инициализируем кнопки
  pinMode(BUT_D, INPUT_PULLUP);
  pinMode(BUT_L, INPUT_PULLUP);
  pinMode(BUT_C, INPUT_PULLUP);
  pinMode(BUT_R, INPUT_PULLUP);

  randomSeed(analogRead(A5));     // инициализируем функцию рандома (A5)
}

void loop() {
  if (mode == 0) {  // меню
    if (flag == 0) {  // выводим на матрицу цифру пункта
      full();
      number_mini(menu, 0);
      flag = 1;
    }
    if (flag == 1) {    // если все кнопки не нажаты
      if (digitalRead(BUT_L) == 1 && digitalRead(BUT_C) == 1 && digitalRead(BUT_R) == 1 && digitalRead(BUT_U) == 1 && digitalRead(BUT_D) == 1) {
        flag = 2;
      }
    }
    if (flag == 2) {    // смотрим какая кнопка была нажата
      if (digitalRead(BUT_L) == 0) {  // предыдущий пункт
        menu--;
        if (menu < 1) {
          menu = 1;
        }
        full();
        number_mini(menu, 0);
        flag = 3;
      }
      if (digitalRead(BUT_D) == 0) {  // предыдущий пункт
        menu--;
        if (menu < 1) {
          menu = 1;
        }
        full();
        number_mini(menu, 0);
        flag = 5;
      }
      if (digitalRead(BUT_C) == 0) {  // заходим в выбранный пункт
        clear();
        mode = menu;
        if (mode == 1 || mode == 2) {
          flag = 1;
        }
        else {
          flag = 0;
        }
      }
      if (digitalRead(BUT_R) == 0) {  // следующий пункт
        menu++;
        if (menu > MAX_MENU) {
          menu = MAX_MENU;
        }
        full();
        number_mini(menu, 0);
        flag = 4;
      }
      if (digitalRead(BUT_U) == 0) {  // следующий пункт
        menu++;
        if (menu > MAX_MENU) {
          menu = MAX_MENU;
        }
        full();
        number_mini(menu, 0);
        flag = 6;
      }
    }
    if (flag == 3) {
      if (digitalRead(BUT_L) == 1) {
        flag = 1;
      }
    }
    if (flag == 4) {
      if (digitalRead(BUT_R) == 1) {
        flag = 1;
      }
    }
    if (flag == 5) {
      if (digitalRead(BUT_D) == 1) {
        flag = 1;
      }
    }
    if (flag == 6) {
      if (digitalRead(BUT_U) == 1) {
        flag = 1;
      }
    }
  }

  if (mode == 1 || mode == 2) { // рандомайзер
    if (flag == 0) {  // если все кнопки не нажаты
      if (digitalRead(BUT_L) == 1 && digitalRead(BUT_C) == 1 && digitalRead(BUT_R) == 1 && digitalRead(BUT_U) == 1 && digitalRead(BUT_D) == 1) {
        flag = 1;
      }
    }
    if (flag == 1) {
      if (digitalRead(BUT_L) == 0) {  // выходим в меню
        prev_num1 = 11;
        mode = 0;
        flag = 0;
      }
      if (digitalRead(BUT_C) == 0) {  // выбираем случайное число
        random_number(30, 10, mode - 1);
        if (mode == 1) {
          num = random(0, 10);
          while (num == prev_num1) {
            num = random(0, 10);
          }
          prev_num1 = num;
          number(num, 1);
        }
        else {
          num = random(1, 7);
          while (num == prev_num1) {
            num = random(1, 7);
          }
          prev_num1 = num;
          number_cube(num, 1);
        }
        flag = 2;
      }
    }
    if (flag == 2) {
      if (digitalRead(BUT_C) == 1) {
        flag = 0;
      }
    }
  }

  if (mode == 3 || mode == 4) { // змейка
    if (flag1 == 0) { // первый ход
      if (flag == 0) {  // выводим изначально положение змейки и яблока
        for (int i = 0; i < 3; i++) {
          matrix[snake_y[i]][snake_x[i]] = 1;
        }
        matrix[apple[1]][apple[0]] = 1;
        flag = 1;
      }
      if (flag == 1) {  // если все кнопки не нажаты
        if (digitalRead(BUT_L) == 1 && digitalRead(BUT_C) == 1 && digitalRead(BUT_R) == 1 && digitalRead(BUT_U) == 1 && digitalRead(BUT_D) == 1) {
          flag = 2;
        }
      }
      if (flag == 2) {    // смотрим какая кнопка была нажата
        if (digitalRead(BUT_L) == 0) {  // идем налево
          direct = 1;
          if (abs(prev_direct - direct) != 2) {
            snake_move(abs(3 - mode));
            flag1 = 1;
            flag = 0;
          }
          else {
            direct = prev_direct;
          }
        }
        if (digitalRead(BUT_C) == 0) {  // выходим в меню
          snake_x[0] = 2;
          snake_x[1] = 2;
          snake_x[2] = 2;
          snake_y[0] = 6;
          snake_y[1] = 5;
          snake_y[2] = 4;
          apple[0] = 2;
          apple[1] = 1;
          prev_direct = 2;
          length_sn = 2;
          speed_sn = 1000;
          score = 0;
          a = 0;
          mode = 0;
          flag = 0;
          flag1 = 0;
          flag3 = 0;
        }
        if (digitalRead(BUT_R) == 0) {  // идем направо
          direct = 3;
          if (abs(prev_direct - direct) != 2) {
            snake_move(abs(3 - mode));
            flag1 = 1;
            flag = 0;
          }
          else {
            direct = prev_direct;
          }
        }
        if (digitalRead(BUT_U) == 0) {  // идем наверх
          direct = 2;
          if (abs(prev_direct - direct) != 2) {
            snake_move(abs(3 - mode));
            flag1 = 1;
            flag = 0;
          }
          else {
            direct = prev_direct;
          }
        }
        if (digitalRead(BUT_D) == 0) {  // идем вниз
          direct = 4;
          if (abs(prev_direct - direct) != 2) {
            snake_move(abs(3 - mode));
            flag1 = 1;
            flag = 0;
          }
          else {
            direct = prev_direct;
          }
        }
      }
    }
    if (flag1 == 1) { // последующие ходы змейки
      if (flag == 0) {    // если все кнопки не нажаты
        if (digitalRead(BUT_L) == 1 && digitalRead(BUT_C) == 1 && digitalRead(BUT_R) == 1 && digitalRead(BUT_U) == 1 && digitalRead(BUT_D) == 1) {
          flag = 1;
        }
      }
      if (flag == 1) {    // смотрим какая кнопка была нажата
        if (digitalRead(BUT_L) == 0) {  // идем налево
          direct = 1;
          flag = 2;
        }
        if (digitalRead(BUT_C) == 0) {
          snake_x[0] = 2;
          snake_x[1] = 2;
          snake_x[2] = 2;
          snake_y[0] = 6;
          snake_y[1] = 5;
          snake_y[2] = 4;
          apple[0] = 2;
          apple[1] = 1;
          prev_direct = 2;
          length_sn = 2;
          speed_sn = 1000;
          score = 0;
          a = 0;
          mode = 0;
          flag = 0;
          flag1 = 0;
          flag3 = 0;
        }
        if (digitalRead(BUT_R) == 0) {  // идем направо
          direct = 3;
          flag = 3;
        }
        if (digitalRead(BUT_U) == 0) {  // идем наверх
          direct = 2;
          flag = 4;
        }
        if (digitalRead(BUT_D) == 0) {  // идем вниз
          direct = 4;
          flag = 5;
        }
      }
      if (flag == 2) {
        if (digitalRead(BUT_L) == 1) {
          flag = 0;
        }
      }
      if (flag == 3) {
        if (digitalRead(BUT_R) == 1) {
          flag = 0;
        }
      }
      if (flag == 4) {
        if (digitalRead(BUT_U) == 1) {
          flag = 0;
        }
      }
      if (flag == 5) {
        if (digitalRead(BUT_D) == 1) {
          flag = 0;
        }
      }
      a++;
      if (a % 5 == 0) { // моргаем яблоком
        matrix[apple[1]][apple[0]] = !matrix[apple[1]][apple[0]];
      }
      if (a >= speed_sn / 10) {
        if (abs(prev_direct - direct) == 2) {
          direct = prev_direct;
        }
        snake_move(abs(3 - mode));
        a = 0;
      }
    }
    if (flag1 == 2) { //змейка врезалась
      for (int i = 0; i < 7; i++) { // заполняем весь экран снизу вверх
        for (int j = 0; j < 5; j++) {
          matrix[6 - i][j] = 1;
        }
        while (a <= 10) {
          update();
          a++;
        }
        a = 0;
      }
      for (int i = 0; i < 7; i++) { // очищаем весь экран сверху вниз
        for (int j = 0; j < 5; j++) {
          matrix[i][j] = 0;
        }
        while (a <= 10) {
          update();
          a++;
        }
        a = 0;
      }
      if (score > 9) {  // выводим количество собранных яблоков
        number((score - score % 10) / 10, 1);
        while (a <= 100) {
          update();
          a++;
        }
        a = 0;
        clear();
        number(score % 10, 1);
      }
      else {
        number(0, 1);
        while (a <= 100) {
          update();
          a++;
        }
        a = 0;
        clear();
        number(score, 1);
      }

      while (a <= 100) {
        update();
        a++;
      }
      a = 0;
      snake_x[0] = 2;
      snake_x[1] = 2;
      snake_x[2] = 2;
      snake_y[0] = 6;
      snake_y[1] = 5;
      snake_y[2] = 4;
      apple[0] = 2;
      apple[1] = 1;
      prev_direct = 2;
      speed_sn = 1000;
      length_sn = 2;
      score = 0;
      mode = 0;
      flag = 0;
      flag1 = 0;
      flag3 = 0;
    }
  }

  if (mode == 5) {  // тетрис
    if (flag1 == 0) { // играем в тетрис
      if (flag == 0) {  // выводим новую фигуру
        shape = random(0, 5);
        orient = random(0, 4);
        while (prev_shape == shape) {
          shape = random(0, 5);
        }
        prev_shape = shape;
        if (shape == 3 && orient == 1) {
          frame[1] = -1;
        }
        tetris_down();
        flag = 1;
      }
      if (flag == 1) {    // если все кнопки не нажаты
        if (digitalRead(BUT_L) == 1 && digitalRead(BUT_C) == 1 && digitalRead(BUT_R) == 1 && digitalRead(BUT_U) == 1 && digitalRead(BUT_D) == 1) {
          flag = 2;
        }
      }
      if (flag == 2) {  // смотрим какая кнопка нажата
        if (digitalRead(BUT_L) == 0) {  // двигаем фигуру влево
          tetris_side(0);
          flag = 3;
        }
        if (digitalRead(BUT_C) == 0) {  // выходим в меню
          speed_t = 1000;
          prev_shape = 6;
          num_line_del = 0;
          frame[0] = 2;
          frame[1] = -2;
          score = 0;
          a = 0;
          mode = 0;
          flag = 0;
          flag1 = 0;
        }
        if (digitalRead(BUT_R) == 0) {  // двигаем фигуру вправо
          tetris_side(1);
          flag = 4;
        }
        if (digitalRead(BUT_U) == 0) {  // меняем положение фигуры
          tetris_rotation();
          flag = 5;
        }
        if (digitalRead(BUT_D) == 0) {  // быстро двигаем фигуру вниз
          flag = 6;
        }
      }
      if (flag == 3) {
        if (digitalRead(BUT_L) == 1) {
          flag = 1;
        }
      }
      if (flag == 4) {
        if (digitalRead(BUT_R) == 1) {
          flag = 1;
        }
      }
      if (flag == 5) {
        if (digitalRead(BUT_U) == 1) {
          flag = 1;
        }
      }
      if (flag == 6) {
        if (digitalRead(BUT_D) == 1) {
          flag = 1;
        }
      }
      a++;
      if (flag2 == 1) { // удаляем строки
        if (a % 10 == 0) {  // мигаем строками
          for (int i = 0; i < num_line_del; i++) {
            for (int j = 0; j < 5; j++) {
              matrix[line_del[i]][j] = count;
            }
          }
          count = !count;
          a1++;
        }
        if (a1 == 5) {
          flag2 = 2;
          a1 = 0;
          count = 0;
          check_line();
        }
      }
      if (flag == 6) {
        if (a >= 10) {
          tetris_down();
          a = 0;
        }
      }
      else {
        if (a >= speed_t / 10) {
          tetris_down();
          a = 0;
        }
      }
    }
    if (flag1 == 1) { // заполнили поле до верху (проиграли)
      for (int i = 0; i < 7; i++) { // заполняем матрицу снизу вверх
        for (int j = 0; j < 5; j++) {
          matrix[6 - i][j] = 1;
        }
        while (a <= 10) {
          update();
          a++;
        }
        a = 0;
      }
      for (int i = 0; i < 7; i++) { // очищаем матрицу сверху вниз
        for (int j = 0; j < 5; j++) {
          matrix[i][j] = 0;
        }
        while (a <= 10) {
          update();
          a++;
        }
        a = 0;
      }
      if (score > 9) {  // выводим количество удаленных строк
        number((score - score % 10) / 10, 1);
        while (a <= 100) {
          update();
          a++;
        }
        a = 0;
        clear();
        number(score % 10, 1);
      }
      else {
        number(0, 1);
        while (a <= 100) {
          update();
          a++;
        }
        a = 0;
        clear();
        number(score, 1);
      }

      while (a <= 100) {
        update();
        a++;
      }
      a = 0;
      speed_t = 1000;
      prev_shape = 6;
      num_line_del = 0;
      frame[0] = 2;
      frame[1] = -2;
      score = 0;
      mode = 0;
      flag = 0;
      flag1 = 0;
    }
  }
  update();
}

//---ГРАФИКА---
void clear() {    // очистить матрицу
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 7; j++) {
      matrix[j][i] = 0;
    }
  }
}

void clear_matrix() {   // очистить матрицу (не обнуляя массив)
  for (int i = 0; i < 5; i++) {
    digitalWrite(x_pin[i], LOW);
  }
  for (int i = 0; i < 7; i++) {
    digitalWrite(y_pin[i], HIGH);
  }
}

void full() {   // зажечь на матрице все светодиоды
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 7; j++) {
      matrix[j][i] = 1;
    }
  }
}

void update() {   // вывести массив на матрицу
  for (int i = 0; i < 5; i++) {
    x_layer(i);
    for (int j = 0; j < 7; j++) {
      digitalWrite(y_pin[j], !matrix[j][i]);
    }
    delay(2);
    for (int i = 0; i < 7; i++) {
      digitalWrite(y_pin[i], HIGH);
    }
  }
}

void dot(byte x, byte y, boolean en) {    // добавляем координаты точки в массив
  matrix[y][x] = en;
}

void lineH(byte y, byte x0, byte x1, boolean en) {    // рисуем горизонтальную линию
  swap(x0, x1);
  for (int x = x0; x <= x1; x++) {
    dot(x, y, en);
  }
}

void lineV(byte x, byte y0, byte y1, boolean en) {    // рисуем вертикальную линию
  swap(y0, y1);
  for (int y = y0; y <= y1; y++) {
    dot(x, y, en);
  }
}

void rect(byte x0, byte y0, byte x1, byte y1, byte fill) {    // рисуем прямоугольник
  swap(x0, x1);
  swap(y0, y1);
  if (fill < 2) {
    lineH(y0, x0 + 1, x1 - 1, fill);
    lineH(y1, x0 + 1, x1 - 1, fill);
    lineV(x0, y0, y1, fill);
    lineV(x1, y0, y1, fill);
  }
  else {
    for (int y = y0; y <= y1; y++) {
      lineH(y, x0, x1, 1);
    }
  }
}

void x_layer(byte x1) {   //включаем один слой (вертикальный (x))
  for (int i = 0; i < 5; i++) {
    digitalWrite(x_pin[i], (x1 == i));
  }
}

void swap(byte & a, byte & b) {   // расставляем координаты попорядку (мин, макс)
  if (a > b) {
    int c = a;
    a = b;
    b = c;
  }
}

void random_number(byte time1, byte sum, boolean type) {    // перечисляем рандомные числа (время показа одного числа, количество чисел)
  byte flag1;
  for (int i = 0; i < sum; i++) {
    if (flag1 == 0) {
      if (!type) {
        num = random(0, 10);
        if (num != prev_num) {
          prev_num = num;
          number(num, 1);
          flag1 = 1;
        }
      }
      else {
        num = random(1, 7);
        if (num != prev_num) {
          prev_num = num;
          number_cube(num, 1);
          flag1 = 1;
        }
      }
    }
    if (flag1 == 1) {
      while (a <= time1 / 10) {
        update();
        a++;
      }
      a = 0;
      flag1 = 0;
      clear();
    }
    if (i == sum - 1) {
      prev_num = 11;
    }
  }
}

void number(byte num, boolean en) {   // рисуем обычные цифры
  switch (num) {
    case 0:
      rect(0, 0, 4, 6, en);
      break;
    case 1:
      lineH(6, 0, 4, en);
      lineV(2, 0, 6, en);
      dot(1, 1, en);
      break;
    case 2:
      lineH(0, 0, 4, en);
      lineH(3, 0, 4, en);
      lineH(6, 0, 4, en);
      lineV(4, 1, 2, en);
      lineV(0, 4, 5, en);
      break;
    case 3:
      lineH(0, 0, 3, en);
      lineH(3, 0, 3, en);
      lineH(6, 0, 3, en);
      lineV(4, 0, 6, en);
      break;
    case 4:
      lineH(3, 0, 3, en);
      lineV(0, 0, 2, en);
      lineV(4, 0, 6, en);
      break;
    case 5:
      lineH(0, 0, 4, en);
      lineH(3, 0, 4, en);
      lineH(6, 0, 4, en);
      lineV(0, 1, 2, en);
      lineV(4, 4, 5, en);
      break;
    case 6:
      rect(0, 3, 4, 6, en);
      lineH(0, 0, 4, en);
      lineV(0, 1, 2, en);
      break;
    case 7:
      lineH(0, 0, 4, en);
      lineV(3, 2, 3, en);
      lineV(2, 4, 6, en);
      dot(4, 1, en);
      break;
    case 8:
      rect(0, 0, 4, 3, en);
      rect(0, 3, 4, 6, en);
      break;
    case 9:
      rect(0, 0, 4, 3, en);
      lineH(6, 0, 4, en);
      lineV(4, 4, 5, en);
      break;
  }
}

void number_mini(byte num, boolean en) {    // рисуем маленькие цифры
  switch (num) {
    case 0:
      rect(1, 1, 3, 5, en);
      break;
    case 1:
      lineH(5, 1, 3, en);
      lineV(2, 1, 5, en);
      dot(1, 2, en);
      break;
    case 2:
      lineH(1, 1, 3, en);
      lineH(3, 1, 3, en);
      lineH(5, 1, 3, en);
      dot(3, 2, en);
      dot(1, 4, en);
      break;
    case 3:
      lineH(1, 1, 2, en);
      lineH(3, 1, 2, en);
      lineH(5, 1, 3, en);
      lineV(3, 1, 5, en);
      break;
    case 4:
      lineH(3, 1, 2, en);
      lineV(1, 1, 2, en);
      lineV(3, 1, 5, en);
      break;
    case 5:
      lineH(1, 1, 3, en);
      lineH(3, 1, 3, en);
      lineH(5, 1, 3, en);
      dot(1, 2, en);
      dot(3, 4, en);
      break;
    case 6:
      rect(1, 3, 3, 5, en);
      lineH(1, 1, 3, en);
      dot(1, 2, en);
      break;
    case 7:
      lineH(1, 1, 3, en);
      lineV(2, 3, 5, en);
      dot(3, 2, en);
      break;
    case 8:
      rect(1, 1, 3, 3, en);
      rect(1, 3, 3, 5, en);
      break;
    case 9:
      rect(1, 1, 3, 3, en);
      lineH(5, 1, 3, en);
      dot(3, 4, en);
      break;
  }
}

void number_cube(byte num, boolean en) {    // рисуем цифры с кубика
  switch (num) {
    case 1:
      dot(2, 3, en);
      break;
    case 2:
      dot(1, 2, en);
      dot(3, 4, en);
      break;
    case 3:
      dot(0, 1, en);
      dot(2, 3, en);
      dot(4, 5, en);
      break;
    case 4:
      dot(1, 2, en);
      dot(1, 4, en);
      dot(3, 2, en);
      dot(3, 4, en);
      break;
    case 5:
      dot(0, 1, en);
      dot(0, 5, en);
      dot(2, 3, en);
      dot(4, 5, en);
      dot(4, 1, en);
      break;
    case 6:
      dot(1, 1, en);
      dot(1, 3, en);
      dot(1, 5, en);
      dot(3, 1, en);
      dot(3, 3, en);
      dot(3, 5, en);
      break;
  }
}

//---ЗМЕЙКА---
void snake_move(boolean snake_up) {   // движение змейки (0 - не увеличиваем змейку, 1 - увеличиваем)
  if (flag3 == 0) {
    matrix[snake_y[0]][snake_x[0]] = 0;
    for (int i = 0; i < length_sn; i++) {
      snake_x[i] = snake_x[i + 1];
      snake_y[i] = snake_y[i + 1];
    }
  }
  switch (direct) {
    case 1:
      snake_x[length_sn] = snake_x[length_sn] - 1;
      break;
    case 2:
      snake_y[length_sn] = snake_y[length_sn] - 1;
      break;
    case 3:
      snake_x[length_sn] = snake_x[length_sn] + 1;
      break;
    case 4:
      snake_y[length_sn] = snake_y[length_sn] + 1;
      break;
  }
  prev_direct = direct;
  if (flag3 == 1) {
    flag3 = 0;
  }

  if (snake_x[length_sn] == apple[0] && snake_y[length_sn] == apple[1]) {
    if (snake_up) {
      flag3 = 1;
      length_sn++;
      snake_x[length_sn] = apple[0];
      snake_y[length_sn] = apple[1];
    }
    boolean flag2 = 0;
    score++;
    speed_sn -= 5;
    if (speed_sn < 500) {
      speed_sn = 500;
    }
    while (flag2 == 0) {
      apple[0] = random(0, 5);
      apple[1] = random(0, 7);
      flag2 = 1;
      for (int i = 0; i <= length_sn; i++) {
        if (apple[0] == snake_x[i] && apple[1] == snake_y[i]) {
          flag2 = 0;
        }
      }
    }
    matrix[apple[1]][apple[0]] = 1;
  }
  matrix[apple[1]][apple[0]] = 0;
  if (flag3 == 0 && snake_up == 1 && matrix[snake_y[length_sn]][snake_x[length_sn]] == 1) {
    flag1 = 2;
  }
  if (snake_x[length_sn] > 4 || snake_x[length_sn] < 0 || snake_y[length_sn] > 6 || snake_y[length_sn] < 0) {
    flag1 = 2;
  }
  else {
    matrix[snake_y[length_sn]][snake_x[length_sn]] = 1;
  }
  matrix[apple[1]][apple[0]] = 1;
}

//---ТЕТРИС---
void tetris_down() {  // опускаем фигуру вниз
  if (check_down()) {
    check_line();
  }

  if (!check_down()) {
    for (int i = 0; i < num_dot[shape]; i++) {
      x = figure[shape][orient * num_dot[shape] + i][0] + frame[0];
      y = figure[shape][orient * num_dot[shape] + i][1] + frame[1];
      if (y >= 0) {
        matrix[y][x] = 0;
      }
    }
    frame[1] += 1;

    for (int i = 0; i < num_dot[shape]; i++) {
      x = figure[shape][orient * num_dot[shape] + i][0] + frame[0];
      y = figure[shape][orient * num_dot[shape] + i][1] + frame[1];
      if (y >= 0) {
        matrix[y][x] = 1;
      }
    }
  }
  else {
    flag = 0;
    frame[0] = 2;
    frame[1] = -2;
    a = 0;
    flag = 0;
  }
}

void tetris_rotation() {  // поворачиваем фигуру
  for (int i = 0; i < num_dot[shape]; i++) {
    x = figure[shape][orient * num_dot[shape] + i][0] + frame[0];
    y = figure[shape][orient * num_dot[shape] + i][1] + frame[1];
    if (y >= 0) {
      matrix[y][x] = 0;
    }
  }

  check_rotation();
  for (int i = 0; i < num_dot[shape]; i++) {
    x = figure[shape][orient * num_dot[shape] + i][0] + frame[0];
    y = figure[shape][orient * num_dot[shape] + i][1] + frame[1];
    if (y >= 0) {
      matrix[y][x] = 1;
    }
  }
}

void tetris_side(boolean side) {  // двигаем фигуру в сторону (0 - влево, 1 - вправо)
  for (int i = 0; i < num_dot[shape]; i++) {
    x = figure[shape][orient * num_dot[shape] + i][0] + frame[0];
    y = figure[shape][orient * num_dot[shape] + i][1] + frame[1];
    if (y >= 0) {
      matrix[y][x] = 0;
    }
  }
  if (!side) {
    frame[0] -= check_side(side);
  }
  else {
    frame[0] += check_side(side);
  }

  for (int i = 0; i < num_dot[shape]; i++) {
    x = figure[shape][orient * num_dot[shape] + i][0] + frame[0];
    y = figure[shape][orient * num_dot[shape] + i][1] + frame[1];
    if (y >= 0) {
      matrix[y][x] = 1;
    }
  }
}

void check_rotation() { // проверяем, можно ли повернуть фигуру. Если можно поворачиваем
  //byte flag = 0;
  //byte prev_orient = orient;
  if (shape == 3) {
    if (orient == 0 && frame[0] == 4) {
      frame[0] = 3;
      orient = 2;
    }
    if (orient == 2 && frame[0] == -1) {
      frame[0] = 0;
      orient = 0;
    }
  }
  orient++;
  if (orient > 3) {
    orient = 0;
  }
  /*prev_orient++;
    if (prev_orient > 3) {
    prev_orient = 0;
    }
    for (int j = 0; j < 4; j++) {
    if (flag == 0) {
      for (int i = 0; i < num_dot[shape]; i++) {
        x = figure[shape][prev_orient * num_dot[shape] + i][0] + frame[0];
        y = figure[shape][prev_orient * num_dot[shape] + i][1] + frame[1];
        if (matrix[y][x] == 1) {

          flag = 1;
        }

      }
      if (flag = 0) {
        orient = prev_orient;
        flag = 1;
      }
      else {
        prev_orient++;
        if (prev_orient > 3) {
          prev_orient = 0;
        }
        flag = 0;
      }
    }
    }*/
}

boolean check_side(boolean side1) { // проверяем, можно ли подвинуть фигуру в сторону (0 - нельзя, 1 - можно)
  boolean err = 1;
  byte prev_frame = frame[0];
  if (!side1) {
    prev_frame -= 1;
  }
  else {
    prev_frame += 1;
  }
  for (int i = 0; i < num_dot[shape]; i++) {
    x = figure[shape][orient * num_dot[shape] + i][0] + prev_frame;
    if (x < 0 || x > 4) {
      err = 0;
    }
  }
  return err;
}

boolean check_down() {  // проверяем, можно ли опустить фигуру (0 - можно, 1 - нельзя)
  boolean err = 0;
  for (int i = 0; i < lower_side[shape][orient]; i++) {
    x = figure[shape][orient * num_dot[shape] + i][0] + frame[0];
    y = figure[shape][orient * num_dot[shape] + i][1] + frame[1];
    if (y >= 0) {
      if (y + 1 > 6 || matrix[y + 1][x] == 1) {
        err = 1;
      }
    }
  }
  if (err == 1) {
    for (int i = 0; i < num_dot[shape]; i++) {
      y = figure[shape][orient * num_dot[shape] + i][1] + frame[1];
      if (y <= 0) {
        flag1 = 1;
        flag = 0;
        a = 0;
      }
    }
  }
  return err;
}

boolean check_line() {  // проверяем, если ли полностью заполненные строки
  byte num = 0;
  if (flag2 == 0) {
    for (int i = 0; i < 7; i++) {
      for (int j = 0; j < 5; j++) {
        if (matrix[i][j] == 1) {
          num++;
        }
      }
      if (num == 5) {
        line_del[num_line_del] = i;
        num_line_del++;
      }
      num = 0;
    }
    if (num_line_del > 0) {
      score += num_line_del;
      speed_t -= 5;
      if (speed_t < 500) {
        speed_t = 500;
      }
      flag2 = 1;
    }
  }
  if (flag2 == 2) {
    for (int i = 0; i < num_dot[shape]; i++) {
      x = figure[shape][orient * num_dot[shape] + i][0] + frame[0];
      y = figure[shape][orient * num_dot[shape] + i][1] + frame[1];
      if (y >= 0) {
        matrix[y][x] = 0;
      }
    }
    for (int i2 = 0; i2 < num_line_del; i2++) {
      for (int i1 = line_del[i2]; i1 >= 1; i1--) {
        for (int j = 0; j < 5; j++) {
          matrix[i1][j] = matrix[i1 - 1][j];
        }
      }
    }
    for (int i = 0; i < num_dot[shape]; i++) {
      x = figure[shape][orient * num_dot[shape] + i][0] + frame[0];
      y = figure[shape][orient * num_dot[shape] + i][1] + frame[1];
      if (y >= 0) {
        matrix[y][x] = 1;
      }
    }
    flag2 = 0;
    num_line_del = 0;
  }
}
