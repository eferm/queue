#include "queue.h"

struct qelemstruct
{										// typen för ett köelement
	struct qelemstruct *next, *prev;	// pekare till nästa och föregående
	int prio;							// anger prioritet
	DATA *data;							// pekare till dataelement
};

struct qstruct
{										// typen för en prioritetskö
	struct qelemstruct *head;			// pekare till startelementet i listan
	int length;							// antal dataelement i kön
};

struct qiteratorstruct
{										// typen för en iterator
	struct qstruct *q;					// pekare till kön
	struct qelemstruct *curr;			// pekare till aktuellt element
};

Queue new_queue()
{
	return 0;
}

void delete_queue(Queue q)
{
	;
}

void clear(Queue q)
{
	;
}

int size(Queue q)
{
	return 0;
}

void add(Queue q, int priority, DATA *d)
{
	;
}

DATA *get_first(Queue q)
{
	return 0;
}

void remove_first(Queue q)
{
	;
}

Iterator new_iterator(Queue q)
{
	return 0;
}

void delete_iterator(Iterator it)
{
	;
}

void go_to_first(Iterator it)
{
	;
}

void go_to_last(Iterator it)
{
	;
}

void go_to_next(Iterator it)
{
	;
}

void go_to_previous(Iterator it)
{
	;
}

DATA *get_current(Iterator it)
{
	return 0;
}

void change_current(Iterator it, DATA *d)
{
	;
}

void remove_current(Iterator it)
{
	;
}

void find(Iterator it, DATA *d)
{
	;
}
