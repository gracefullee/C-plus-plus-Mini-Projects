###Student Information
  + Name: Yoo Jin Lee
  + USC Email: yoojinl@usc.edu
  + USC ID: 3272884875

###Compile Instruction
> $ make
>>to compile all QuickSort, Grading, and MaxHeap

>$ make qsort
>>to compile Problem 2: QuickSort

>$ make grading
>>to compile Problem 3: Grading Curve

>$ make heap_test
>>to compile Problem 5: MaxHeap

###Graph Explanation
>QuickSort (QuickSort.pdf)
> 
>>Quicksort picks a pivot, then moves the location of pivot to the "correct" location, such that all values lower will be on its left while all values higher than the pivot will be located on its right.

>>As you can see from the graph, runtime of picking the pivot from the back decreases as the array becomes more "randomized" This is because QuickSort's Worst Case is when the pivot is either max or min Item, which runs theta(n^2). As the array is more randomized, there's less chance for the pivot to be either max or min value, which explains the decrease in runtime for picking pivot from the back.

>>For picking pivot randomly from the array, it significantly increases its chance of avoiding the worst case scenario of picking the pivot, which is either max or min value of the array. Therefore, runtime for Rand pivot does not vary as much as Back pivot does.



>MaxHeap (MaxHeap.pdf)

>>Runtime for Insert in D-ary Max Heap decreases as d increases, because its insert runtime essentially depends on its height of the tree since the item is inserted at the end and travels up the tree. The height of the tree is decreases for n ntries as d increases, log d (n). So necessarily, insert runtime decreases for higher d.

>>Runtime for Remove function on the other hand increases as d increases, because although the removing a node also travels down the tree, it makes more comparisons of each item at the same height under the same parent. For 2-ary Heap, it would only compare two items at each height. But for higher d heaps, such as 100-dary, it would have to make 100 comparions to find the highest value out of its siblings. Therefore, runtime significantly increases as d increases.

