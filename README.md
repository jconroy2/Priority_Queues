# Priority_Queues
This program creates an interactive priority queue where lower values have higher priority. Users can choose one of three implementations—an unsorted linked list, a sorted dynamic array, or a min heap—to manage the priority queue. The program provides a hands-on demonstration of different data structures for priority queue operations.

Write an interactive program to create a priority queue, where a lower value has a higher priority.
The user will select the implementation (unsorted linked list, sorted dynamic array, min heap).
A description of the program is provided below.
Structure definitions and function prototypes are provided below.
Several sample runs of the program are provided below.
Program description:
1. Prompt the user to select the implementation for the priority queue.
Select the data structure:
1. Unsorted Linked List
2. Sorted Dynamic Array
3. Heap
Select an option:
2. Prompt the user to select an operation.
Select the operation to perform:
1. Enqueue a value
2. Dequeue a value
3. Exit
Select an option:
3. Perform the selected operation.
4. Output the contents of the data structure.
5. Repeat steps 2 – 4 until the user selects “exit”.

Program Requirements:
• Your program must use the structures defined below.
• Your program must include the functions listed below.
• Your program may include other functions. However, no additional functions are required.
• You should set the initial capacity of the dynamic array to four.
• When expanding the dynamic array, you should double its capacity.
Structure definitions for “Linked List” and “Node”:
typedef struct LinkedList { typedef struct Node {
 Node_t *head; int data;
 Node_t *tail; struct Node *next;
} LinkedList_t; } Node_t;
Structure definition for “Dynamic Array”:
typedef struct DynamicArray {
 int arr*;
 int size;
 int capacity;
} DynamicArray_t;
Function prototypes:
1. Node_t* CreateNode(int value);
2. LinkedList_t* CreateList();
3. DynamicArray_t* CreateDynamicArray(int initCapacity);
4. void EnqueueUnsortedList(LinkedList_t* list, int value);
5. int DequeueUnsortedList(LinkedList_t* list);
6. void EnqueueSortedArray(DynamicArray_t* dynArr, int value);
7. int DequeueSortedArray(DynamicArray_t* dynArr);
8. void EnqueueHeap(DynamicArray_t* heap, int value);
9. int DequeueHeap(DynamicArray_t* heap);
10. void printUnsortedList(LinkedList_t* list);
11. void printSortedArray(DynamicArray_t* dynArr);
12. void printHeap(DynamicArray_t* heap);
13. void expand(DynamicArray_t* dynArr, int newCapacity);

Sample run of program #1:
Select the data structure:
1. Unsorted Linked List
2. Sorted Dynamic Array
3. Heap
Select an option: 1
Select the operation to perform:
1. Enqueue a value
2. Dequeue a value
3. Exit
Select an option: 1
Enter a value (lower value has higher priority): 6
[6]
 Select the operation to perform:
1. Enqueue a value
2. Dequeue a value
3. Exit
Select an option: 1
Enter a value (lower value has higher priority): 3
[6][3]
Select the operation to perform:
1. Enqueue a value
2. Dequeue a value
3. Exit
Select an option: 1
Enter a value (lower value has higher priority): 4
[6][3][4] 
