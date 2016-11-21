CC = g++
CFLAGS = -Wall
LDFLAGS=
GDB = -g

tests : tests.o t_logs.o logs.o
	$(CC) -o tests.out $^ $(CFLAGS)

tests.o : tests.c t_logs.c t_logs.h
	$(CC) -o $@ -c $< $(CFLAGS)

t_logs.o : t_logs.c t_logs.h ../src/logs.c ../include/logs.h
	$(CC) -o $@ -c $< $(CFLAGS)

logs.o : ../src/logs.c ../include/logs.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean_logs :
	rm -r ../Logs/

clean :
	rm *.o
	rm *.out
