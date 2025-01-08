#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node_t;

typedef struct LinkedList
{
    Node_t *head;
    Node_t *tail;
} LinkedList_t;

typedef struct DynamicArray
{
    int *arr;
    int size;
    int capacity;
} DynamicArray_t;

// Declaring functions
void expand(DynamicArray_t *dynArr, int newCapacity);

Node_t *CreateNode(int value)
{
    Node_t *node = malloc(sizeof(Node_t));

    node->data = value;
    node->next = NULL;

    return node;
}

LinkedList_t *CreateList()
{
    LinkedList_t *node = malloc(sizeof(LinkedList_t));

    node->head = NULL;
    node->tail = NULL;

    return node;
}

DynamicArray_t *CreateDynamicArray(int initCapacity)
{
    DynamicArray_t *arr = malloc(sizeof(DynamicArray_t));

    arr->arr = malloc(sizeof(int) * initCapacity);
    arr->size = 0;
    arr->capacity = initCapacity;

    return arr;
}

void EnqueueUnsortedList(LinkedList_t *list, int value)
{
    Node_t *node = CreateNode(value);

    if (list->tail)
    {
        list->tail->next = node;
        list->tail = node;
    }
    else
    {
        list->head = node;
        list->tail = node;
    }
}

int DequeueUnsortedList(LinkedList_t *list)
{
    // Do nothing if the list is empty
    if (list->head == NULL)
    {
        return 0;
    }

    Node_t *minPrev = NULL;
    Node_t *minNode = NULL;

    for (Node_t *prev = NULL, *node = list->head; node; prev = node, node = node->next)
    {
        if (minNode == NULL)
        {
            minPrev = prev;
            minNode = node;
        }
        else if (node->data < minNode->data)
        {
            minPrev = prev;
            minNode = node;
        }
    }

    // Update the head
    if (minPrev == NULL)
    {
        list->head = minNode->next;
    }
    else
    {
        minPrev->next = minNode->next;
    }

    // Update the tail
    if (minNode->next == NULL)
    {
        list->tail = minPrev;
    }

    // Get the value of the minimum node
    int val = minNode->data;

    free(minNode);

    return val;
}

void EnqueueSortedArray(DynamicArray_t *dynArr, int value)
{
    if (dynArr->size == dynArr->capacity)
    {
        expand(dynArr, dynArr->capacity * 2);
    }

    // Start from the end
    for (int i = dynArr->size - 1; i >= 0; i--)
    {
        if (value > dynArr->arr[i])
        {
            // Insert after i^th element
            // Move data
            for (int j = dynArr->size - 1; j > i; j--)
            {
                dynArr->arr[j + 1] = dynArr->arr[j];
            }

            // Insert new value
            dynArr->arr[i + 1] = value;
            dynArr->size++;
            return;
        }
    }

    // Insert at the beginning
    for (int j = dynArr->size - 1; j >= 0; j--)
    {
        dynArr->arr[j + 1] = dynArr->arr[j];
    }

    // Insert new value
    dynArr->arr[0] = value;
    dynArr->size++;
}

int DequeueSortedArray(DynamicArray_t *dynArr)
{
    // Do nothing if empty
    if (dynArr->size == 0)
    {
        return 0;
    }

    // Get the first item
    int head = dynArr->arr[0];

    // Move data
    for (int i = 1; i < dynArr->size; i++)
    {
        dynArr->arr[i - 1] = dynArr->arr[i];
    }
    dynArr->size--;
}

void EnqueueHeap(DynamicArray_t *heap, int value)
{
    if (heap->size == heap->capacity)
    {
        expand(heap, heap->capacity * 2);
    }

    // Insert the new value at the end
    heap->arr[heap->size++] = value;

    // Move the value up to maintain heap property
    for (int i = heap->size - 1; i > 0; i = (i - 1) / 2)
    {
        int p = (i - 1) / 2;

        // Check if value has lower value than parent
        if (value < heap->arr[p])
        {
            // Swap
            heap->arr[i] = heap->arr[p];
            heap->arr[p] = value;
        }
        else
        {
            break;
        }
    }
}

int DequeueHeap(DynamicArray_t *heap)
{
    // Do nothing if empty
    if (heap->size == 0)
    {
        return 0;
    }

    int min = heap->arr[0];

    // Swap with the last item
    heap->arr[0] = heap->arr[--heap->size];

    for (int i = 0; i < heap->size; )
    {
        // Move down
        // Save current lowest value
        int j = i;

        // Get left child
        int l = 2 * i + 1;
        if (l < heap->size)
        {
            if (heap->arr[l] < heap->arr[j])
            {
                j = l;
            }
        }

        // Get right child
        int r = 2 * i + 2;
        if (r < heap->size)
        {
            if (heap->arr[r] < heap->arr[j])
            {
                j = r;
            }
        }

        // Swap i and j
        if (j != i)
        {
            int tmp = heap->arr[i];
            heap->arr[i] = heap->arr[j];
            heap->arr[j] = tmp;

            i = j;
        }
        else
        {
            break;
        }
    }

    return min;
}

//prints the unsorted list
void printUnsortedList(LinkedList_t *list)
{
    for (Node_t *node = list->head; node != NULL; node = node->next)
    {
        printf("[%d]", node->data);
    }
    printf("\n");
}

//Prints the sorted array
void printSortedArray(DynamicArray_t *dynArr)
{
    printf("[");
    for (int i = 0; i < dynArr->capacity; i++)
    {
        if (i > 0)
        {
            printf(",");
        }

        if (i < dynArr->size)
        {
            printf("%d", dynArr->arr[i]);
        }
        else
        {
            printf(" ");
        }
    }
    printf("]\n");
}

// Prints the heap
void printHeap(DynamicArray_t *heap)
{
    printf("[");
    for (int i = 0; i < heap->capacity; i++)
    {
        if (i > 0)
        {
            printf(" ");
        }

        if (i < heap->size)
        {
            printf("%d", heap->arr[i]);
        }
        else
        {
            printf(" ");
        }
    }
    printf("]\n");
}

void expand(DynamicArray_t *dynArr, int newCapacity)
{
    // Check new capacity
    if (newCapacity <= dynArr->capacity)
    {
        return;
    }

    // Realloc
    dynArr->arr = realloc(dynArr->arr, sizeof(int) * newCapacity);
    dynArr->capacity = newCapacity;
}

// Gets the operation from the user to preform
int getOperation()
{
    printf("\nSelect the operation to perform:\n\n");
    printf("1. Enqueue a value\n");
    printf("2. Dequeue a value\n");
    printf("3. Exit\n\n");
    printf("Select an option: ");

    int op = 0;
    scanf("%d", &op);
    return op;
}

// Gets the data structure from the user to create
int getDataStructure()
{
    printf("Select the data structure:\n\n");
    printf("1. Unsorted Linked List\n");
    printf("2. Sorted Dynamic Array\n");
    printf("3. Heap\n\n");
    printf("Select an option: ");

    int st = 0;
    scanf("%d", &st);
    return st;
}

int enterValue()
{
    printf("\nEnter a value (lower value has a higher priority): ");

    int v = 0;
    scanf("%d", &v);
    return v;
}

int main()
{
    int st = getDataStructure();
    int op = 0;

    // If the first option is selected, a link list is created
    if (st == 1)
    {
        LinkedList_t *list = CreateList();

        for (;;)
        {
            op = getOperation();

            if (op == 1)
            {
                EnqueueUnsortedList(list, enterValue());
                printf("\n");
                printUnsortedList(list);
            }
            else if (op == 2)
            {
                DequeueUnsortedList(list);
                printf("\n");
                printUnsortedList(list);
            }
            else if (op == 3)
            {
                break;
            }
        }
    }
    // If the second option is selected, a dynamic array is created
    else if (st == 2)
    {
        DynamicArray_t *dynArr = CreateDynamicArray(4);

        for (;;)
        {
            op = getOperation();

            if (op == 1)
            {
                EnqueueSortedArray(dynArr, enterValue());
                printf("\n");
                printSortedArray(dynArr);
            }
            else if (op == 2)
            {
                DequeueSortedArray(dynArr);
                printf("\n");
                printSortedArray(dynArr);
            }
            else if (op == 3)
            {
                break;
            }
        }
    }

    // If the third option is selected, a heap is created
    else if (st == 3)
    {
        DynamicArray_t *heap = CreateDynamicArray(4);

        for (;;)
        {
            op = getOperation();

            if (op == 1)
            {
                EnqueueHeap(heap, enterValue());
                printf("\n");
                printHeap(heap);
            }
            else if (op == 2)
            {
                DequeueHeap(heap);
                printf("\n");
                printHeap(heap);
            }
            else if (op == 3)
            {
                break;
            }
        }
    }

    printf("\nGood bye.\n");

    return 0;
}
