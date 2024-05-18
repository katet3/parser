# Custom Interpreter

Этот интерпретатор — это простой интерпретатор языка, поддерживающий операции с целыми и логическими значениями, вывод строк, переменные, массивы, условные операторы, циклы и ввод пользователя. Он предназначен для обучения принципам работы интерпретаторов.

## Особенности

- Операции с целыми и логическими значениями
- Вывод строк
- Объявление и присваивание переменных
- Объявление массивов и доступ к элементам
- Условные операторы (`if`/`else`)
- Циклы (`while`)
- Ввод пользователя
- Комментарии

## Сборка интерпретатора

Для сборки интерпретатора вам понадобится компилятор C++. Следующие шаги показывают, как скомпилировать и запустить интерпретатор с использованием `g++`, либо с использование Visual Studio.

```sh
g++ -o interpreter interpreter.cpp
```



## Запуск интерпретатора

Вы можете запустить интерпретатор в двух режимах:

1. **Интерактивный режим**: Запустите интерпретатор без аргументов, чтобы войти в интерактивный режим, где вы можете вводить выражения по одному.

   ```sh
   ./interpreter
   ```

2. **Режим работы с файлом**: Запустите интерпретатор с опцией `-f`, за которой следует имя файла, чтобы выполнить код из файла.

   ```sh
   ./interpreter -f example.txt
   ```



## Синтаксис

### Комментарии

- Комментарии начинаются с `#` и продолжаются до конца строки.

### Переменные

- Объявление целочисленной переменной: `int <name> = <value>;`
- Объявление массива: `int <name>[<size>];`
- Присваивание значения переменной или элементу массива: `<name> = <value>;` или `<name>[<index>] = <value>;`

```cpp
int x = 5;
int arr[10];
arr[0] = 1;
```

### Ввод

- Чтение ввода от пользователя: `input <variable>;`

```cpp
input x;
```

### Вывод

- Вывод значения или переменной: `print <expression>;`
- Перевод строки: `endl;`

```
print x;
print "Hello, world!";
endl;
```

### Условные операторы

- Условные операторы с использованием `if` и `else`.

  ```
  if (x < 10) {
      print "x меньше 10";
  } else {
      print "x 10 или больше";
  }
  ```

  

### Циклы

- Цикл с использованием `while`.

```
while (x < 10) {
    print x;
    x = x + 1;
}
```



### Поддерживаемые операторы

- Арифметические: `+`, `-`, `*`, `/`
- Сравнения: `==`, `!=`, `<`, `<=`, `>`, `>=`
- Логические: `&&`, `||`



## Примеры

### Пример 1: Базовые операции

```
# Объявление и присваивание переменных

int a = 10;
int b = 20;

# Выполнение арифметических операций

int sum = a + b;
int product = a * b;

# Вывод результатов

print sum;
endl;
print product;
endl;
```



### Пример 2: Использование массивов

```
# Объявление массива

int arr[5];

# Присваивание значений элементам массива

arr[0] = 1;
arr[1] = 2;
arr[2] = 3;
arr[3] = 4;
arr[4] = 5;

# Вывод элементов массива

print arr[0];
endl;
print arr[1];
endl;
```



### Пример 3: Условные операторы

```
int x = 5;
if (x < 10) {
    print "x меньше 10";
} else {
    print "x 10 или больше";
}
endl;
```



### Пример 4: Циклы

```
int x = 0;
while (x < 5) {
    print x;
    endl;
    x = x + 1;
}
```



### Пример 5: Ввод пользователя

```
print "Введите число: ";
input x;
print "Вы ввели: ";
print x;
endl;
```



### Тест 1. Арифметические выражения.

```
# Проверка арифметических операций

# Объявление и инициализация переменных

int a = 10;
int b = 5;

# Сложение

int sum = a + b;
print "Сложение: ";
print sum; # Ожидаемый результат: 15
endl;

# Вычитание

int difference = a - b;
print "Вычитание: ";
print difference; # Ожидаемый результат: 5
endl;

# Умножение

int product = a * b;
print "Умножение: ";
print product; # Ожидаемый результат: 50
endl;

# Деление

int quotient = a / b;
print "Деление: ";
print quotient; # Ожидаемый результат: 2
endl;

# Проверка операций сравнения

# Равно

bool isEqual = (a == b);
print "Равно (10 == 5): ";
print isEqual; # Ожидаемый результат: 0 (false)
endl;

# Не равно

bool isNotEqual = (a != b);
print "Не равно (10 != 5): ";
print isNotEqual; # Ожидаемый результат: 1 (true)
endl;

# Меньше

bool isLess = (a < b);
print "Меньше (10 < 5): ";
print isLess; # Ожидаемый результат: 0 (false)
endl;

# Меньше или равно

bool isLessOrEqual = (a <= b);
print "Меньше или равно (10 <= 5): ";
print isLessOrEqual; # Ожидаемый результат: 0 (false)
endl;

# Больше

bool isGreater = (a > b);
print "Больше (10 > 5): ";
print isGreater; # Ожидаемый результат: 1 (true)
endl;

# Больше или равно

bool isGreaterOrEqual = (a >= b);
print "Больше или равно (10 >= 5): ";
print isGreaterOrEqual; # Ожидаемый результат: 1 (true)
endl;

# Проверка логических операций

bool trueValue = true;
bool falseValue = false;

# Логическое И

bool andResult = trueValue && falseValue;
print "Логическое И (true && false): ";
print andResult; # Ожидаемый результат: 0 (false)
endl;

# Логическое ИЛИ

bool orResult = trueValue || falseValue;
print "Логическое ИЛИ (true || false): ";
print orResult; # Ожидаемый результат: 1 (true)
endl;

# Проверка вывода строки

print "Проверка вывода строки: Hello, world!";
endl;
```



### Тест 2. Сортировка пузырьком.

```
# Объявляем массив и инициализируем его значениями

int arr[5];
arr[0] = 5;
arr[1] = 3;
arr[2] = 8;
arr[3] = 4;
arr[4] = 1;

# Получаем размер массива

int n = 5;

# Пузырьковая сортировка

int i = 0;
while (i < n - 1) {
    int j = 0;
    while (j < n - i - 1) {
        if (arr[j] > arr[j + 1]) {
            # Обмен значениями
            int temp = arr[j];
            arr[j] = arr[j + 1];
            arr[j + 1] = temp;
        }
        j = j + 1;
    }
    i = i + 1;
}

# Вывод отсортированного массива

int k = 0;
while (k < n) {
    print arr[k];
    endl;
    k = k + 1;
}
```



## Результат

Этот интерпретатор предоставляет базовую функциональность простого языка программирования. Он является отличной отправной точкой для изучения  интерпретаторов и разработки языков. Вы можете расширить язык, добавив  больше функций по мере необходимости.