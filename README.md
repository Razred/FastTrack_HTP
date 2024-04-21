# FastTrack_HTP

## Неделя 3 Fast track в Telecom. Домашняя работа 


## Задание 1


<details>
  <summary>Условие задания</summary>

Задание 1 (15 баллов): на основании кода с вебинара (файл лежит здесь: https://phoenixcs.notion.site/16-04-24-43659f3faac347c0ad1b6efaa85e54ca?pvs=4) 
1. Дополнить решение токенами: max, sqr
2. Добавить все необходимые классы в определение Token
3. Реализовать ParseName, который читает последовательность букв и возвращает токен соответствующей функции или UnknownToken
4. Закончить Tokenize

</details>

1. Исходный код: [ссылка](https://github.com/Razred/FastTrack_HTP/tree/main/DZ_2/src)



**Пояснение**

1.Были добавлены дополнительные токены MaxToken и SqrToken.

```cpp
struct MaxToken {};

struct SqrToken {};
```

2.Также добавил дополнил Token необходимыми классами

```cpp
using Token = std::variant<OpeningBracket, ClosingBracket, Number, UnknownToken, MinToken, AbsToken, Plus, Minus, Multiply, Divide, Modulo, MaxToken, SqrToken>;

```

3. Была реализованна функция ParseName, в которой происходит проверка выражения на валидность, для этого была создана hash_map. В которой записаны все допустимые выражения, сделано это для удобства, чтобы не использовать большое количество if-else.

Функция ParseName.
```cpp
Token ParseName(const std::string& input, size_t& pos) {
    std::string expression;
    while (std::isalpha(static_cast<unsigned char>(input[pos]))) {
        expression += input[pos++];
        if (pos == input.size()) {
            break;
        }
    }
```
Hash-map kExpression2Token.
```cpp
const std::unordered_map<std::string, Token>  kExpression2Token {
        {"min", MinToken{}}, {"max", MaxToken{}}, {"abs", AbsToken{}}, {"sqr", SqrToken{}}};
```

4. Для добавления выражений добавлен специальный else-if в функцию Tokenize:
```cpp
else if (std::isalpha(symbol)) {
            tokens.emplace_back(ParseName(input, pos));
```


## Задание 2

<details>
  <summary>Условие задания</summary>

Задание 2 (30 баллов): Напишите библиотеку, реализующую шаблонный класс для односвязного списка с поддержкой операций вставки, удаления и поиска заданного элемента.

</details>

Был реализован шаблонный класс односвзяного списка, в котором определены 2 конструктора и оператор присваивания:

```cpp
LinkedList() : size_(0), head_(nullptr), tail_(nullptr);

LinkedList(const value_type& item);

LinkedList& operator=(const LinkedList& right);
```

Определены следующие публичные методы:
```cpp
size_t size(); Возвращает размер списка

value_type front(); // Возвращает первый элемент

value_type back(); // Возвращает последний элемент

value_type operator[](size_t index); // Возвращает элемент по индексу

void push_back(const value_type& item) // Добавление в конец

void insert(size_t index, value_type item) // Добавление в произвольное место

value_type pop_back() // Удаление последнего элемента

value_type remove(size_t index) // Удаление произвольно элемента

void clear() // Очищает список
```

Также присутствует единственный приватный метод, который возвращает ноду в произвольном месте списка:
```cpp
ListNode<value_type>* getNode(size_t index);
```


**Реализация**

1. Исходный код: (https://github.com/Razred/FastTrack_HTP/blob/main/DZ_2/src/LinkedList/LinkedList.h)
