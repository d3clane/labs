# Деревья

## Наивное дерево поиска

100000 вставок, 50000 удалений для случайного набора элементов и для отсортированных последовательностей:

|     |        |
|:---:                  | :---:        |
| Вставка случайных     | 0.0130482    |
| Удаление случайных    | 0.0042582    |
| Вставка сортированных | 8.6759390    |
| Удаление сортированных| 4.9318496    |

Очевидно, вставка отсортированных работает очень долго, так как получается бамбук, вставка / удаление будут работать за O(n). 

При вставке / удалении случайных элементов работает быстро, так как в среднем на случайных данных высота наивной дерева поиска O(logn).

## AVL дерево

Вставки:

![AVL INSERTS](https://github.com/d3clane/labs/blob/Lab6/Lab6/ReadmeAssets/imgs/AVL_Inserts.png)

Удаления:

![AVL DELETES](https://github.com/d3clane/labs/blob/Lab6/Lab6/ReadmeAssets/imgs/AVL_Deletes.png)

Время работы для отсортированной последовательности из 1млн вставок и 500к удалений:

|             |              |
|:---:        | :---:        |
| Вставка     | 0.0910926    |
| Удаление    | 0.0554774    |

Вообще, работает дольше, чем вставки / удаления случайных. Возможно, из-за того, что в случае отсортированной последовательности балансировка дерева (ротейты) происходит чаще, то есть операций выходит больше на это. Но все равно это не O(n^2), так как дерево всегда балансируется и его высота O(logn). 

## Декартово дерево

Вставки:

![TREAP INSERTS](https://github.com/d3clane/labs/blob/Lab6/Lab6/ReadmeAssets/imgs/TREAP_Inserts.png)

Удаления:

![TREAP DELETES](https://github.com/d3clane/labs/blob/Lab6/Lab6/ReadmeAssets/imgs/TREAP_Deletes.png)

## Splay дерево

Вставки:

![SPLAY INSERTS](https://github.com/d3clane/labs/blob/Lab6/Lab6/ReadmeAssets/imgs/SPLAY_Inserts.png)

Удаления:

![SPLAY DELETES](https://github.com/d3clane/labs/blob/Lab6/Lab6/ReadmeAssets/imgs/SPLAY_Deletes.png)

## Выводы

Сравним Splay, Treap и AVL. Для вставок:

![SPA INSERT](https://github.com/d3clane/labs/blob/Lab6/Lab6/ReadmeAssets/imgs/SPA_Inserts.png)


