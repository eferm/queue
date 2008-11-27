OBJECTS = qtest.o queue.o

qtest.out: $(OBJECTS)
	gcc $(OBJECTS) -o qtest.out

qtest.o: qtest.c

queue.o: queue.h