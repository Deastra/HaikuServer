C_SOURCES :=$(all/wildcard *.c)
C_HEADERS :=$(all/wildcard *.h)

run1: client.c client.h 
	gcc client.c -o run1

client: run1
	./run1

run2: $(C_SOURCES) $(C_HEADERS) 
	gcc -pthread server.c -o run2

server: run2
	./run2
