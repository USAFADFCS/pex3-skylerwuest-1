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
    struct PageQueue *new_node = (struct PageQueue *)malloc(sizeof(struct PageQueue));
    new_node->head = NULL;
    new_node->tail = NULL;
    new_node->size = 0;
    new_node->maxSize = maxSize;
    return new_node;
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
    PqNode *temp = pq->tail;

    while (temp != NULL && temp->pageNum != pageNum){
        temp = temp->prev;
        depth++;
    }

    if (temp != NULL)  // Page Found
    {
        // Remove the node from its current position and re-insert it at the tail (most recently used)
        //PqNode *current = temp;
        pq = delHead(pq);  // includes a free      
        pq = insertEnd(pq,temp);        
        // Return d.
        return depth;
    }
    
    
    // MISS path (page not found):
    //   - Allocate a new node for pageNum and insert it at the tail.
    //   - If size now exceeds maxSize, evict the head node (free it).
    //   - Return -1.
    PqNode *newNodePNum = (PqNode*)malloc(sizeof(PqNode));  // Allocate new node
    newNodePNum->pageNum = pageNum;
    pq = insertEnd(pq,newNodePNum);  // Give us head of queue as a result
    
    // Check size (make a new variable)
    if (pq->size > pq->maxSize)  // Larger, evict head node
    {   
        delHead(pq); 
        return -1;  // something went wrong
    }
    free(newNodePNum);
    return depth;
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

    // if (queue->head->next == NULL)
    // {
    //     free(queue->head);
    //     return queue;
    // }
    
    // // Go to last node 
    // struct PqNode *curr = queue->head;
    // while (curr->next != NULL)
    // {
    //     curr = curr->next;
    // }

    // // update previous 
    

    // Store in temp for deletion later
    //PqNode *curr = malloc(sizeof(PqNode));
    struct PqNode *temp = queue->head;

    // Move head to the next node
    queue->head->next = queue->head;

    // Set prev of the new head
    if (queue != NULL)
        queue->head->next->prev = NULL;

    // Free memory and return new head
    free(temp);
    queue->size--;  // make it smaller
    return queue;
}

struct PageQueue *insertEnd(struct PageQueue *queue, PqNode *new_node)
{   struct PqNode *curr = queue->head;
    if (curr == NULL)
    {
        curr = new_node;
    }
    else 
    {   
        while (curr->next != NULL)
        {
            curr = curr->next;
        }

        curr->next = new_node;
        new_node->prev = curr;
        queue->size++;  // Add size
    }

    return queue;
}

