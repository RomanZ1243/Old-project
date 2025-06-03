void setup() {
    Serial.begin(9600);

    const int capacity = 10; // Максимальная вместимость массива
    int arr1[capacity] = {10, 20, 30, 40, 50};
    int arr_size1 = 5; // Текущее количество значимых элементов в массиве

    Serial.print("Исходный массив: ");
    for (int i = 0; i < arr_size1; ++i) {
        Serial.print(arr1[i]);
        Serial.print(" ");
    }
    Serial.println();

    int indexToRemove = 2; // Индекс элемента, который нужно удалить
    removeElementAtIndex(arr1, arr_size1, indexToRemove);

    Serial.print("Массив после удаления элемента: ");
    for (int i = 0; i < arr_size1; ++i) {
        Serial.print(arr1[i]);
        Serial.print(" ");
    }
    Serial.println();
}

void loop() {
    // Основной цикл остается пустым
}

void removeElementAtIndex(int arr[], int& arr_size, int index) {
    for (int i = index; i < arr_size - 1; ++i) {
        arr[i] = arr[i + 1];
    }

    --arr_size;
}
