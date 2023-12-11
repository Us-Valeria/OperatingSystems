lab5s: lab5.o liblab5.so
	gcc lab5.o -L. -llab5 -o lab5s
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.	
	clear
	./lab5s
	

liblab5.so: lab5-*.c
	gcc -c -fPIC -Wall lab5-*.c
	gcc -shared lab5-*.o -o liblab5.so

lab5.o: lab5.c
	gcc -c -fPIC -Wall lab5.c

.PHONY: clean
clean:
	rm -f *.o *.so lab5s