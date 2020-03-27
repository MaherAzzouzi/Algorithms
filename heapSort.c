#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

int left_child(int i)
{
    return 2*i;
}

int right_child(int i)
{
    return 2*i + 1;
}

int parent(int i)
{
    return i/2;
}

void max_heapify_I(int heap[], int i, int heapSize)
{
    int largest;
    int l_c;
    int r_c;


    while(1)
    {
        l_c = left_child(i);
        r_c = right_child(i);

        if(l_c <= heapSize && heap[l_c]>heap[i]){
            largest = l_c;
        }
        else
        {
            largest = i;
        }

        if(r_c <= heapSize && heap[r_c]>heap[largest]){
            largest = r_c;
        }

        if(largest == i)
            return;

        swap(&heap[i], &heap[largest]);
        i = largest;
    }

}

void max_heapify_R(int heap[], int i, int heap_size)
{
    int l_c, r_c;
    int largest_index;

    l_c = left_child(i);
    r_c = right_child(i);

    if(l_c <= heap_size && heap[l_c] > heap[i])
        largest_index = l_c;
    else
        largest_index = i;

    if(r_c <= heap_size && heap[r_c] > heap[largest_index])
        largest_index = r_c;

    if(largest_index != i){
        swap(&heap[i] ,&heap[largest_index]);
        max_heapify_R(heap, largest_index, heap_size);
    }

}


void create_heap(int heap[], int heapSize)
{
    for(int i=heapSize/2; i>0; i--)
        max_heapify_I(heap, i, heapSize);

}

int Heapsort(int A[], int ASize)
{
    create_heap(A, ASize);
    for(int i = ASize; i>0; i--){
    swap(&A[1], &A[ASize]);
    ASize--;
    max_heapify_I(A, 1, ASize);

    }
}

int main()
{



    int heap[] = {0,9, 7, 3, 1, 13, 10, 16, 5, 17, 12, 4, 8, 27, 0};
    int heapSize = 14;


    Heapsort(heap, heapSize);

    for(int i=1; i<heapSize; i++)
        printf("%d ", heap[i]);

    return 0;
}
