/** pagequeue.c
 * ===========================================================
 * Name: _______________________, __ ___ 2026
 * Section: CS483 / ____
 * Project: PEX3 - Page Replacement Simulator
 * Purpose: Implementation of the PageQueue ADT — a doubly-linked
 *          list for LRU page replacement.
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
    return NULL;
}

/**
 * @brief Access a page in the queue (simulates a memory reference)
 */
long pqAccess(PageQueue *pq, unsigned long pageNum) {  // this is the LRU here
    // TODO: Search the queue for pageNum (suggest searching tail->head
    //       so you naturally count depth from the MRU end).
    //
    // HIT path (page found at depth d):
    //   - Remove the node from its current position and re-insert
    //     it at the tail (most recently used).
    //   - Return d.
    //
    // MISS path (page not found):
    //   - Allocate a new node for pageNum and insert it at the tail.
    //   - If size now exceeds maxSize, evict the head node (free it).
    //   - Return -1.
    int depth = 0;
    PageQueue *temp = pq;

    while (depth <= temp->size)
    {   
        depth++;

        if (pageNum == temp->tail->prev->pageNum)
        {
            return depth;
        }

        temp = temp->tail->prev;
    }
    
    // Miss
    PqNode* newNodePNum = malloc(sizeof(PageQueue));  // Allocate new node
    newNodePNum->pageNum = pageNum;
    pq->tail = newNodePNum;
    pq->size++;

    // Check size (make a new variable)

    if (pq->size > pq->maxSize)  // Larger, evict head node
    {
        free(pq->head);
        pq->size--;  // Make size smaller since we are removing
        return -1;
    }
    
    return depth;
}

/**
 * @brief Free all nodes in the queue and reset it to empty
 */
void pqFree(PageQueue *pq) {
    // TODO: Walk from head to tail, free each node, then free
    //       the PageQueue struct itself.
}

/**
 * @brief Print queue contents to stderr for debugging
 */
void pqPrint(PageQueue *pq) {
    // TODO (optional): Print each page number from head to tail,
    //                  marking which is head and which is tail.
    //                  Useful for desk-checking small traces.
}
