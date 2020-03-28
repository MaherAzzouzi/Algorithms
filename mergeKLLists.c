/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

void swap(int *a, int *b)
{
    int temp;
    
    temp = *a;
    *a = *b;
    *b = temp;
    
}

void max_heapify(int heap[], int i, int heapSize)
{
    int l_c;
    int r_c;
    int largest;
    
    while(1)
    {
        l_c = 2*i;
        r_c = 2*i +1;
        
        if(l_c <= heapSize && heap[l_c] > heap[i])
            largest = l_c;
        else
            largest = i;
        
        if(r_c <= heapSize && heap[r_c] > heap[largest])
            largest = r_c;
        
        if(largest != i)
            swap(&heap[largest], &heap[i]);
        else
            return i;
        
        i = largest;
    }
}

void create_heap(int heap[], int heapSize)
{
    int i;
    
    for( i = heapSize/2; i>0; i--)
        max_heapify(heap, i, heapSize);
}

void Heapsort(int heap[], int heapSize)
{
    int i;
    
    while(heapSize != 1)
    {
        swap(&heap[heapSize], &heap[1]);
        heapSize--;
        max_heapify(heap, 1, heapSize);
    }
}

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize){

    int heap[100000];
    int i;
    int k;

    
    heap[0] = 0;
    
    struct ListNode* p;
    
    for(i=0, k=1; i<listsSize; i++)
    {
        for(p = lists[i]; p; k++,p=p->next)
            heap[k] = p->val;
        
    }
    
    if(k == 1)
        return NULL;

    create_heap(heap, k-1);
    Heapsort(heap, k-1);
    
    struct ListNode *result;
    
    result = (struct ListNode *)malloc(sizeof(struct ListNode));
    result->val = heap[1];
    
    p = result;
    
    for(i=2; i<k; i++)
    {
        p->next = (struct ListNode *)malloc(sizeof(struct ListNode));
        p = p->next;
        p->val = heap[i];
    }
    
    p->next = NULL;
    
    
    for(i=0; i<k; i++)
        printf("%d ", heap[i]);
    
    return result;
}

