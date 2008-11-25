/*
 * Machine oriented programming
 * Chalmers University of Technology
 * Lab 4
 * Implement a priority queue with a linked list
 * 
 * Author: 	Emanuel Ferm
 * 			emanuelf @ student.chalmers.se
 * Date:	25 November 2008
 */

#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

/*
 * Queue, the type for a priority queue
 */
struct qstruct
{
	struct qelemstruct *head;			// pointer to starting element in queue
	int length;							// number of elements in the queue
};

/*
 * Element, the type for a queue element
 */
struct qelemstruct
{
	struct qelemstruct *next;			// pointer to next element
	struct qelemstruct *prev;			// pointer to previous element
	signed prio;						// priority (increasing scale)
	DATA *data;							// pointer to data element
};

/*
 * Iterator, the type for the queue iterator
 */
struct qiteratorstruct
{
	struct qstruct *q;					// pointer to the Queue
	struct qelemstruct *curr;			// pointer to current Element
};

typedef struct qelemstruct *Element;

/*
 * Allocates memory and initializes Queue and starting Element
 */
Queue new_queue()
{
	Element p_element = (Element) malloc(sizeof(Element));
	Element element = p_element;
	element->next = element;			// points to itself
	element->prev = element;			// points to itself
	element->prio = 0;
	element->data = 0;
	
	Queue p_queue = (Queue) malloc(sizeof(Queue));
	Queue queue = p_queue;
	queue->head = element;				// head always points to start element
	queue->length = 0;
	
	return queue;
}

/*
 * Frees Queue-pointer
 */
void delete_queue(Queue q)
{
	free(q);
}

/*
 * Frees all Element-pointers
 */
void clear(Queue q)
{
	Iterator it = new_iterator(q);
	
	while (size(q))
	{
		remove_current(it);
		go_to_first(it);
	}
	delete_iterator(it);
}

/*
 * Returns number of elements in the queue
 */
int size(Queue q)
{
	return q->length;
}

/*
 * Adds an element to the queue according to FIFO principle
 */
void add(Queue q, int priority, DATA *d)
{
	Element p_element = (Element) malloc(sizeof(Element));
	Element element = p_element;
	element->prio = priority;
	element->data = d;
	
	Iterator it = new_iterator(q);
	
	// point to first element with smaller or equal prio than given prio
	while (it->curr->prio > element->prio)
		go_to_next(it);

	// if equal prio, but greater than 0, points to first smaller
	if (element->prio != 0)
	{
		while (it->curr->prio == element->prio)
			go_to_next(it);
		go_to_previous(it);
	}
	else
	{
		// if 0
		go_to_last(it);
	}
	
	it->curr->next->prev = element;			// connect element with "next"
	element->next = it->curr->next;			// connect element with "next"
	
	element->prev = it->curr;				// connect "this" with element
	it->curr->next = element;				// connect "this" with element

	// increment queue length
	q->length++;
	
	delete_iterator(it);
}

/*
 * Returns the data of the first element
 */
DATA *get_first(Queue q)
{
	return q->head->next->data;
}

/*
 * Frees pointer to first element
 */
void remove_first(Queue q)
{
	Iterator it = new_iterator(q);
	remove_current(it);
	delete_iterator(it);
}

/*
 * Allocates memory and intializes an iterator connected to a given queue
 */
Iterator new_iterator(Queue q)
{
	Iterator p_it = (Iterator) malloc(sizeof(Iterator));
	Iterator it = p_it;
	it->q = q;
	it->curr = q->head->next;
	
	return it;
}

/*
 * Frees pointer to iterator
 */
void delete_iterator(Iterator it)
{
	free(it);
}

/*
 * Set iterator to first element
 */
void go_to_first(Iterator it)
{
	it->curr = it->q->head->next;
}

/*
 * Set iterator to last element
 */
void go_to_last(Iterator it)
{
	go_to_first(it);
	int i;
	for (i = 0; i < (size(it->q) - 1); i++)
	{
		go_to_next(it);
	}
}

/*
 * Point iterator to next element (if not starting element)
 */
void go_to_next(Iterator it)
{
	if (it->curr != it->q->head)
		it->curr = it->curr->next;
}

/*
 * Point iterator to previous element (if not starting element)
 */
void go_to_previous(Iterator it)
{
	if (it->curr != it->q->head)
		it->curr = it->curr->prev;
}

/*
 * Returns data of by iterator currently pointed element
 */
DATA *get_current(Iterator it)
{
	return it->curr->data;
}

/*
 * Replace data in by iterator currently pointed element (if not starting elem)
 */
void change_current(Iterator it, DATA *d)
{
	if (it->curr != it->q->head)
		it->curr->data = d;
}

/*
 * If not starting element; frees pointer of current and decrements length
 */
void remove_current(Iterator it)
{
	if (it->curr != it->q->head)
	{
		it->curr->next->prev = it->curr->prev;
		it->curr->prev->next = it->curr->next;

		free(it->curr);

		it->q->length--;
	}
}

/*
 * Points iterator to element that contains given data. If unsuccess, points 0
 */
void find(Iterator it, DATA *d)
{
	go_to_first(it);
	
	int i;
	for (i = 0; i < (size(it->q) - 1); i++)
	{
		if (get_current(it) == d)
			break;
		else
			go_to_next(it);
	}
	
	if (get_current(it) != d)
		it->curr = 0;
}
