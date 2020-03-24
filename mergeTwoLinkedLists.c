/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2){

    struct ListNode *return_val;
    struct ListNode *p;
    struct ListNode *q;
    struct ListNode *linker;
    
    if(l1 == NULL && l2 == NULL)
        return NULL;
    
    if(l1 == NULL && l2 != NULL)
        return l2;
    
    if(l2 == NULL && l1 != NULL)
        return l1;
    
    p = l1;
    q = l2;
    
    if(l1->val < l2->val)
    {
        linker = l1;
        p = linker->next;

    }
    else{
        linker = l2;
        q = linker->next;

    }
    
    return_val = linker;
    
    while(p && q)
    {
        if(p->val < q->val)
        {
            linker->next = p;
            linker = p;
            p = linker->next;
        }
        else
        {
            linker->next = q;
            linker = q;
            q = linker->next;
        }     
    }

    if(!p)
        linker->next = q;
    
    if(!q)
        linker->next = p;

   return return_val;
}

