run: qpsk.o main.o 
	g++ -o run qpsk.o main.o

qpsk.o: qpsk.c qpsk.h
	g++ -c qpsk.c

main.o: main.c
	g++ -c main.c

clean:
	rm *.o run plot.txt
