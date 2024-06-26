# Custom Interpreter

Этот интерпретатор — простой интерпретатор языка, поддерживающий операции с целыми и логическими значениями, вывод строк, переменные, массивы, условные операторы, циклы и ввод пользователя. Он предназначен для обучения в рамках лабораторной принципам работы интерпретаторов.

## Особенности

- Операции с целыми и логическими значениями
- Вывод строк
- Объявление и присваивание переменных
- Объявление массивов и доступ к элементам
- Условные операторы (`if`/`else`)
- Циклы (`while`)
- Ввод пользователя
- Комментарии
- **Каждый оператор заканчиватся на ;**

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
   ./interpreter -f example.tsu
   ```



## Архитектура

#### Общая архитектура

Программа представляет собой интерпретатор для простого скриптового языка, который состоит из трёх основных компонентов:

1. **Лексер (Lexer)**
2. **Парсер (Parser)**
3. **Абстрактное синтаксическое дерево (AST)**

#### Лексер

Лексер анализирует входной поток текста и преобразует его в последовательность токенов. Токены представляют собой значимые элементы языка, такие как идентификаторы, ключевые слова, числа, операторы. Лексер управляется функцией `gettok()`, которая читает символы, игнорирует пробелы и комментарии, и генерирует соответствующие токены.

#### Парсер

Парсер принимает последовательность токенов от лексера и строит из них AST. Это делается путём рекурсивного спуска, где каждая функция парсера обрабатывает свой уровень грамматики. Например, `ParseExpression()` собирает выражения, `ParseIntDecl()` обрабатывает объявления переменных типа `int`.

#### Абстрактное синтаксическое дерево (AST)

AST является центральной структурой данных в интерпретаторе. Каждый узел дерева представляет собой конструкцию языка, и каждый узел способен самостоятельно вычислять своё значение. Важные классы включают:

- `ExprAST` - базовый класс для всех выражений.
- `NumberExprAST`, `BooleanExprAST`, `StringExprAST` - представляют литералы различных типов.
- `BinaryExprAST` - представляет бинарные операции (+, -, *, /).
- `IfExprAST`, `WhileExprAST` - представляют управляющие структуры.
- `PrintExprAST`, `VariableExprAST` - специальные функции для печати и обработки переменных.

#### Построение и обход AST

1. **Построение AST**: Начинается после того, как парсер получает токены. Парсер читает токены и построенными правилами грамматики создаёт соответствующие узлы AST.
2. **Обход AST**: Выполняется когда программа должна быть интерпретирована. Каждый узел AST может вычислить себя, и, в зависимости от типа узла, может влиять на ход выполнения программы (например, циклы, условные операторы).



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
  };
  ```

  

### Циклы

- Цикл с использованием `while`.

```
while (x < 10) {
    print x;
    x = x + 1;
};
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
};
endl;
```



### Пример 4: Циклы

```
int x = 0;
while (x < 5) {
    print x;
    endl;
    x = x + 1;
};
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
int j = 0;
int temp = 0;

while (i < (n - 1)) {
    j = 0;
    while (j < (n - i - 1)) {
        if (arr[j] > arr[j + 1]) {
            temp = arr[j];
            arr[j] = arr[j + 1];
            arr[j + 1] = temp;
        };
        j = j + 1;
    };
    i = i + 1;
};

# Вывод отсортированного массива

print arr[0];
print arr[1];
print arr[2];
print arr[3];
print arr[4];
```



## Результат

Этот интерпретатор предоставляет базовую функциональность простого языка программирования. Он является отличной отправной точкой для изучения  интерпретаторов и разработки языков. Вы можете расширить язык, добавив  больше функций по мере необходимости.