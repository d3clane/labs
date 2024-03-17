# Сравнение сортировок

# Пункт 0

Генерируются тесты, как сказано в условии. Код тестируется, время выполнения каждого теста для конкретной сортировки выписывается в файлы в папке [TestsResults](TestsResults). Затем по этим точкам строятся графики с помощью программы на питоне. Сами тесты на гитхаб не загрузить - они занимают 7.77Гб.

# Пункт 1

Все квадратичные сортировки написаны без каких-либо оптимизаций. Shell sort использует последовательность Кнута. Результат тестирования:
![Quadratic sorts](https://github.com/d3clane/labs/blob/lab2/ReadmeAssets/imgs/Quadratic.png)

Лучше всех, очевидно, отработала Shell sort, как и предполагалось теоретически. Самая близкая к ней - insertion sort. В целом логично, учитывая, что Shell sort - улучшенная ее версия.

# Пункт 2

Для построения кучи используется функция build, которая строит ее за $O(arrSize)$. Затем все выполняется согласно алгоритму. Тестируем разные ранги кучи:

![Heap sort](https://github.com/d3clane/labs/blob/lab2/ReadmeAssets/imgs/HeapSorts.png)

Лучшую скорость показывают кучи с рангом в районе 5-7, далее оптимальным рангом будем считать 6.

# Пункт 3

Логично предположить, что итеративная реализация должна быть чуть быстрее, чем рекурсивная. Проверяем на деле:

![Merge sorts](https://github.com/d3clane/labs/blob/lab2/ReadmeAssets/imgs/Merges.png)

Итеративная реализация действительно быстрее, но разница очень малая.

# Пункт 4 

Согласно теории, ломуто работает медленнее хоара. При этом толстое разбиение должно работать лучше всех остальных, когда в массиве много повторений, так как оно фактически умеет выкидывать за раз какую-то часть массива. Результат на больших массивах:

![Quick sorts partitions](https://github.com/d3clane/labs/blob/lab2/ReadmeAssets/imgs/QuickSortBig.png)

Результат на массивах с большим количеством повторений:

![Quick sorts partitions duplicates](https://github.com/d3clane/labs/blob/lab2/ReadmeAssets/imgs/QuickSortDuplicates.png)

Все, как и ожидалось - разбиение ломуто самое медленное, а толстое разбиение показывает себя лучше всех на массивах с дубликатами. Единственное, что можно отметить - толстое разбиение ведет себя так же, как и ломуто на просто больших массивах без дубликатов.

Тогда, если заранее известно, что в массивах будет много дубликатов, следует выбирать толстое разбиение, иначе предпочтительней использовать разбиение хоара.

Теперь реализуем оптимизацию быстрой сортировки - использование одной ветки рекурсии, когда мы спускаемся всегда в массив с наименьшим размером после разбиения, а другой обрабатываем в цикле. Такая оптимизация позволяет гарантированно ограничить размер рекурсии - это $O(logn)$, так как наименьший из двух массивов всегда хотя бы в два раза меньше исходного. Но, предположительно, выигрыша во времени не ожидается - добавляются действия на организацию циклов (jmp в ассемблере), подсчет длин и их сравнения, которые заменяют просто лишний вызов функции. Проверим на деле:

![One branch qsort](https://github.com/d3clane/labs/blob/lab2/ReadmeAssets/imgs/QuickSortOptimization.png)

Действительно, производительность сортировок абсолютно идентична в пределах погрешности измерений. Далее будем считать самой оптимальной быстрой сортировкой рекурсивную с двумя ветками сортировки и партиционированием хоара. 

# Пункт 5

Теперь изучаем, как ведут себя быстрые сортировки в зависимости от стратегии выбора опорного элемента. Если брать все время центральный элемент, то тогда можно подобрать такой тест, что сортировка скатится в n^2, но в нашем случае этого не должно произойти - тесты генерировались случайно и вероятность такого события неимоверно мала. Посмотрим на зависимость:

![Pivots](https://github.com/d3clane/labs/blob/lab2/ReadmeAssets/imgs/QuickSortPivots.png)

Выбор центрального или медиану трех ведут себя одинаково, а вот выборы, которые используют рандом работают заметно хуже. Возможное объяснение - время, которое тратится на вычисление случайного элемента довольно значительно и тратит много времени. 

Далее постоянный выбор центрального элемента буду считать оптимальным.

# Пункт 6

График сравнения сортировок:

![Quick vs shell](https://github.com/d3clane/labs/blob/lab2/ReadmeAssets/imgs/QuickVsShell.png)

Оптимальный размер блока - 64 инта. Сортировка шелла обгоняет qsort на малых блоках за счет меньшей константы и возможно большей дружелюбности с кешом.

# Пункт 7

Комбинируем shell sort + heap sort + quick sort. Запускаем на тестах big_tests, считаем суммарное время, затраченное на тесты в зависимости от $C$ - константы в рекурсии. График зависимости:

![Intro sort recursion](https://github.com/d3clane/labs/blob/lab2/ReadmeAssets/imgs/IntroSortDepth.png)

По графику видно, что довольно быстро функция выходит на некоторое плато и производительность не меняется. Предполагаю, это следствие того, что heapsort особо не влияет на производительность алгоритма, а основной вклад исходит от комбинации qsort + shell. То есть лучше, когда комбинация просто состоит из qsort + shell, а heapsort вызывается только если очень не повезло с qsort. Тогда примем оптимальный $C = 30$.

Сравнение qsort и introsort:

![Intro vs Qsort](https://github.com/d3clane/labs/blob/lab2/ReadmeAssets/imgs/IntroSortVsQsort.png)

Introsort совсем незначительно обгоняет qsort, предполагаю что этот выигрыш происходит из-за использования сортировки шелла на маленьких блоках, а не из-за использования heapsort.

# Пункт 8

Предположительно, LSD должна работать в разы быстрее любой другой используемой мной сортировкой, про MSD не очень понятно, так как там неприятная рекурсия внутри. Результат:

![Digits sorts](https://github.com/d3clane/labs/blob/lab2/ReadmeAssets/imgs/DigitsSorts.png)

LSD sort работает очень быстро, а MSD, как ни странно, показывает себя почти так же, как и qsort. 

# Пункт 9

Все сравнения сортировок были выполнены без использования оптимизаций компилятора (-O0). Сравнение всех сортировок без использования оптимизаций:

![All sorts](https://github.com/d3clane/labs/blob/lab2/ReadmeAssets/imgs/AllSorts.png)

С использованием оптимизации (-O3):

![All sorts O3](https://github.com/d3clane/labs/blob/lab2/ReadmeAssets/imgs/AllSortsO3.png)

Рассмотрим график без оптимизаций - LSD sort, как и ожидалась, всех обогнал. Догнать qsort из стандартной библиотеки не удалось - она работает чуть быстрее, чем introsort.

Теперь воспользуемся оптимизацией. Удивительно, что Heapsort, которая работала дольше всех без оптимизаций теперь ведет себя так же, как и Introsort. С учетом подобных оптимизаций любая написанная мною сортировка обгоняет стандартный qsort. 

Предполагаю, что библиотечный qsort написан с огромным количеством оптимизаций сам по себе, поэтому без использования оптимизаций компилятора догнать его не удалось. При использовании оптимизаций мои сортировки работают лучше, возможно из-за того, что qsort написан на абстрактных void*, а мои на конкретных интах. 

Introsort лучшая сортировка на сравнениях из всех написанных мною, но на O3 heapsort возможно даже лучше, что удивительно. 

CPU, на котором все исполнялось: M1 pro
