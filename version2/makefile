run1: haiku_reader.c haiku_reader.h msgqueue.c
	gcc haiku_reader.c -pthread -o run1

run2: haiku_writer.c haiku_writer.h msgqueue.c
	gcc haiku_writer.c -pthread -o run2

read: run1
	./run1

write: run2
	./run2