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
    //if (pq->head != NULL && pq->tail != NULL) // There is something in the queue
    if (pq->size != 0)
    {   
        PqNode *temp = pq->tail;
        
        printf("Page NUM %ld\n", temp->pageNum);
        printf("TAIL Page NUM %ld\n", pq->tail->pageNum);

        while (pq->tail != NULL && temp->pageNum != pageNum)  // Will get Depth of page if found 
        {   
            temp = temp->prev;
            printf("depth, %d", depth);
            depth++;
        }
        if (temp->pageNum == pageNum)  // Page Found
        {
            // Remove the node from its current position and re-insert it at the tail (most recently used)
            // INSERT AT END (No longer helper function)
            struct PqNode *curr = pq->head;
            
                // Edge Case #1 - Empty Queue 
            if (curr == NULL)
            {
                printf("I made it here5\n");
                pq->head = temp;
                pq->tail = temp;
                pq->size++;
            }
            else {   
                // Edge Case #2 - Single Node in Queue 
                printf("I made it here6\n");
                if (pq->size == 1)
                {
                    pq->head->next = temp;
                    pq->tail = pq->head->next;
                    pq->size++;
                } else {  // Multiple Pages in Queue
                    printf("I made it here7\n");
                    // The Traversal
                    while (curr->next != NULL)
                    {
                        curr = curr->next;
                    }
                    pq->tail = curr->next;
                    curr->next = temp; // tail 
                    curr->prev = curr;
                    pq->size++;  // Add size
                }
            }
            // END OF INSERT AT END --------
            
            // DELETE AT DEPTH depth (No longer helper function) -------
                // Edge Case #1 - Empty Queue (this wont happen) 
                // Edge Case #2 - Single Node in Queue 
            if (pq->size == 1)
            {
                pq->head = NULL;
                pq->tail = NULL;
                pq->size--;
            }
                // Edge Case #3 - Hit @ head of queue 
            else if (pq->head == temp)  // USE TEMP FROM EARLIER SINCE IT IS ALREADY IN THE DEPTH SPOT
            {
                pq->head = temp->next;
                temp = NULL;
                pq->size--;
            }
                // Edge Case #4 - Hit @ tail of queue
            else if (pq->tail == temp)  // since it got added to the tail there are two in a row
                // This temp is where we left off in the depth, not where we inserted (! +1)
            {
                pq->tail = temp->prev;
                // im just going to delete the last one that was the prev tail even though 
                // they are both the same this way is just easier
                temp = NULL;
                pq->size--;
            }
            else {
            // ELSE 
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                temp = NULL;
                pq->size--;
            }
            // END OF DELETE AT DEPTH depth -------
            return depth;

        } else {  // MISS PAGE NEVER FOUND
            PqNode *newNodePNum = (PqNode*)malloc(sizeof(PqNode));  // Allocate new node
            newNodePNum->pageNum = pageNum;

            // INSERT AT END (No longer helper function) --------
            struct PqNode *curr = pq->head;
            
                // Edge Case #1 - Empty Queue 
            if (curr == NULL)
            {
                pq->head = newNodePNum;
                pq->tail = newNodePNum;
                pq->size++;
                return -1;
            }
            else {   
                // Edge Case #2 - Single Node in Queue 
                if (pq->size == 1)
                {
                    pq->head->next = newNodePNum;
                    pq->tail = pq->head->next;
                    pq->size++;
                    return -1;
                } else {  // Multiple Pages in Queue
                    // The Traversal
                    while (curr->next != NULL)
                    {
                        curr = curr->next;
                    }
                    pq->tail = curr->next;
                    curr->next = newNodePNum;
                    curr->prev = curr;
                    pq->size++;  // Add size
                    return -1;
                }
            }
            // END OF INSERT AT END --------
            return -1;  // Fault 
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
    // INSERT AT END (No longer helper function) --------
            struct PqNode *curr = pq->head;
                // Edge Case #1 - Empty Queue (it is already empty or should be)
            if (pq->size == 0)
            {
                pq->head = newNodePNum;
                pq->tail = newNodePNum;
                pq->size++;
                return -1;
            }
            else {   
                // Edge Case #2 - Single Node in Queue 
                if (pq->size == 1)
                {
                    pq->head->next = newNodePNum;
                    pq->tail = newNodePNum;
                    pq->size++;
                    return -1;
                } else {  // Multiple Pages in Queue
                    // The Traversal
                    while (curr->next != NULL)
                    {
                        curr = curr->next;
                    }
                    curr->next = newNodePNum;
                    pq->tail = newNodePNum;
                    curr->prev = curr;
                    pq->size++;  // Add size
                    return -1;
                }
            }
            // END OF INSERT AT END --------
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
