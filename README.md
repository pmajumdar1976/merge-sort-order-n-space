# merge-sort-order-n-space (pm_sort)

## Thr problem description

There are many sorting algorithms. When it comes to make a choice, it normally boils down to `merge sort` or `quick sort`. I am not worried too much about very small arrays where complexity of the algorithms doesn't play a very big role. Many times people pick `quick sort` over `merge sort`. This is what bothers me the most.

So I googled `merge sort cons` and found the following.

> **Disadvantages of using merge sort algorithm**
> 1. extra space to store subarrays.
> 2. slow for small arrays.
> 3. the algorithm does the whole process even the array is already sorted.

I personally belive that pont `#3` applies to `quick sort` too. Point `#2` applies to sort arrays. Some `O(n)` algorithm may work much better here.

* So the question is if we can do anything about point `#1`. *
* <ins>I believe we can</ins>

```
This project contains an implementation that'll need only one auxiliary array (of the size same as that of the original input) but no meory allocation for each subarray. When I use it I normally allocate twice the memory that is needed for storing the original input and use last half as the auxiliary array. This reduces one extra memory allocation call
```
<ins>So memory wise it is still worse than `quick sort` but memory complexity wise it should be the same.</ins>
