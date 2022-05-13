run1: client.c msgqueue.c shdmemory.c
	gcc $^ -o $@

client: run1
	./run1

run2: server.c read_write_thread.c msgqueue.c shdmemory.c
	gcc -pthread $^ -o $@

server: run2
	./$^

run3: clear.c msgqueue.c shdmemory.c
	gcc $^ -o $@

clear: run3
	./run3
