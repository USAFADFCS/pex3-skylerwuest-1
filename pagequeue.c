/** pagequeue.c
 * ===========================================================
 * Name: _______________________, __ ___ 2026
 * Section: CS483 / ____
 * Project: PEX3 - Page Replacement Simulator
 * Purpose: Implementation of the PageQueue ADT — a doubly-linked
 *          list for LRU page replaceme
 *          Head = LRU (eviction end), Tail = MRU end.
 * =========================================================== */
#include <stdio.h>
#include <stdlib.h>

#include "pagequeue.h"

/**
 * @brief Create and initialize a page queue with a given capacity
 */
PageQueue *pqInit(unsigned int maxSize) {
    // TODO: malloc a PageQueue, set head and tail to NULL,
    //       size to 0, maxSize to maxSize, and return the pointer
    struct PageQueue *new_q = (struct PageQueue *)malloc(sizeof(struct PageQueue));
    new_q->head = NULL; 
    new_q->tail = NULL;
    new_q->size = 0;
    new_q->maxSize = maxSize;
    return new_q;
}

/**
 * @brief Access a page in the queue (simulates a memory reference)
 */
long pqAccess(PageQueue *pq, unsigned long pageNum) {  // this is the LRU here
    // HIT path (page found at depth d): tail->head
    //   - Remove the node from its current position and re-insert
    //     it at the tail (most recently used).
    //   - Return d.

    int depth = 0;
    
    if (pq->head != NULL && pq->tail != NULL) // There is something in the queue
    {   
        PqNode *temp = pq->tail;
        while (pq->tail != NULL)
        {   
            if (temp->pageNum == pageNum)
            {
                continue;
            } else{
                temp = temp->prev;
                printf("depth, %d", depth);
                depth++;
            }
        }

        if (temp->pageNum == pageNum)  // Page Found
        {
        // Remove the node from its current position and re-insert it at the tail (most recently used)
        PqNode *current = temp;

        insertEnd(pq,current);  
        delAt(pq,depth);  // includes a free   

        return depth;
        } else {  // Miss, same code as below 
            printf("Miss\n");
            PqNode *newNodePNum = (PqNode*)malloc(sizeof(PqNode));  // Allocate new node
            newNodePNum->pageNum = pageNum;
            insertEnd(pq,newNodePNum);  // Give us head of queue as a result
            return -1;
        }
    }  
    printf("nothing in the queue\n");
    // there is nothing in the queue... auto miss
        // MISS path (page not found):
        //   - Allocate a new node for pageNum and insert it at the tail.
        //   - If size now exceeds maxSize, evict the head node (free it).
        //   - Return -1.
    PqNode *newNodePNum = (PqNode*)malloc(sizeof(PqNode));  // Allocate new node
    newNodePNum->pageNum = pageNum;
    insertEnd(pq, newNodePNum);
    return -1;
}

/**
 * @brief Free all nodes in the queue and reset it to empty
 */
void pqFree(PageQueue *pq) {
    struct PqNode *current = pq->head;
    struct PqNode *toDelete;

    while (current != NULL)  // Free loop
    {
        toDelete = current;
        current = current->next;
        free(toDelete);
        
    }
    free(pq);
}

/**
 * @brief Print queue contents to stderr for debugging
 */
// void pqPrint(PageQueue *pq) {
//     // TODO (optional): Print each page number from head to tail,
//     //                  marking which is head and which is tail.
//     //                  Useful for desk-checking small traces.
//     struct PageQueue *curr = pq;
//     while (curr != NULL)
//     {    
//         printf("%d ", curr->head->pageNum);  // This is wrong all of this code block
//         curr = curr->head->next;
//     }
//     printf("\n");
// }


struct PageQueue *delHead(struct PageQueue *queue) {
  
    // If empty, return NULL
    if (queue == NULL){
        return NULL;
    }

    struct PqNode *temp = queue->head;

    // Move head to the next node
    queue->head->next = queue->head;

    // Set prev of the new head
    if (queue != NULL)
        queue->head->next->prev = NULL;

    // Free memory and return new head
    free(temp);
    printf("decreasing size of q\n");
    queue->size--;  // make it smaller
    return queue;
}

struct PageQueue *insertEnd(struct PageQueue *queue, PqNode *new_node)
{   struct PqNode *curr = queue->head;
    
    if (curr == NULL)
    {
        //printf("yo theres nothing in the queue");
        queue->head = new_node;
        queue->tail = new_node;
    }
    else 
    {   
        while (curr->next != NULL)
        {
            curr = curr->next;
        }
        
        queue->tail = curr->next;
        curr->next = new_node;
        curr->prev = curr;
        //printf("increasing size of q\n");
        queue->size++;  // Add size
    }

    return queue;
}

struct PageQueue *delAt(struct PageQueue *queue, int position) {
  
    // If empty, return NULL
    if (queue == NULL){
        return NULL;
    }
    
    struct PqNode *temp = queue->head;

    // traverse to position
    for (int i = 0; temp != NULL && i < position; ++i)
    {
        temp = temp->next;
    }
    
    if (temp == NULL)
    {
        return queue;
    }

    if (temp->prev != NULL){
        temp->prev->next = temp->next;
    }

    if (temp->next != NULL)
    {
        temp->next->prev = temp->prev;
    }

    if (queue->head == temp)
    {
        temp = temp->next;
    }
    
    free(temp);
    queue->size--;  // make it smaller
    return queue;
}
