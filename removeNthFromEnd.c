/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* removeNthFromEnd(struct ListNode* head, int n){

    
    int i;
    int ll_length=1;
    struct ListNode *p;
    struct ListNode *q;
    
    
    if(head == NULL)
        return NULL;
    
    if(head->next == NULL)
    {
        free(head);
        return 0;
    }
    
    
    for(p=head, q=p; p->next != NULL; p = p->next)
        ll_length++;
    
    if(ll_length == n)
    {
        p = head;
        head = head->next;
        free(p);
        return head;
    }
    
    for(i=0, p = head;i<ll_length-n; i++)
    {
        q = p;
        p = p->next;
    }
    
    q->next = p->next;
    free(p);
        
    return head;
    
    
}
