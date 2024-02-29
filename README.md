# labs

## Tests 1-3

|                   |First run  |Second run |Third run  |Average    |
|---                |---        |---        |---        |---        |
|Test1 dynamic array| 0.014707  | 0.014451  | 0.012242  | 0.0138    |
|Test1 list         | 0.176893  | 0.181270  | 0.173365  | 0.177176  |
|Test2 dynamic array| 0.046721  | 0.045926  | 0.046523  | 0.04639   |
|Test2 list         | 0.359699  | 0.357064  | 0.358123  | 0.358295  |
|Test3 dynamic array| 0.016014  | 0.015967  | 0.015781  | 0.015920  |
|Test3 list         | 0.096717  | 0.096046  | 0.096246  | 0.096336  |

## Test4

Файлы со сгенерированными точками:
- [dynamic array stack](Test4Arr.txt)
- [list stack](Test4List.txt)

График:
![graph](https://github.com/d3clane/labs/blob/lab1/ReadmeAssets/imgs/output.png);


## Вывод

Стек на массиве очевидно лучше. Причины:
- Локальность данных в памяти -> cache-friendly
- Меньше вызовов realloc, calloc, которые занимают много времени

Это подтверждается тестами и графиками. Разница в скорости может быть даже десятикратной (test1).
