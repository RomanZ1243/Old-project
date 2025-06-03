int size = 10;
int* arr = new int[size];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(sizeof(arr) / sizeof(arr[0]));
  addItemToArray(arr, sizeof(arr) / sizeof(arr[0]), sizeof(arr) / sizeof(arr[0]) + 1);
  delay(1000);
}

int* addItemToArray(int* array, int size, int newItem){
  for (int i = 0; i < size; i++){
    if (newItem == *(array + i)){
      return nullptr;
    }
  }
  int* newArray = new int[size + 1];
  for (int i = 0; i < size; i++){
    *(newArray+i) == *(array + i);
  }
  *(newArray + size + 1) = newItem;
  return newArray;
}
