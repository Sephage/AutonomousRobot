CC = g++
CFLAGS = -Wall
GDB = -g

all : clientTest tests

rasp :
	scp -r ../../AutonomousRobot pi@192.168.42.1:/home/pi

clientTest : client.o clientTest.o
	$(CC) -o clientTests.out $^ $(CFLAGS)

tests : tests.o t_functions.o logs.o server.o
	$(CC) -o tests.out $^ $(CFLAGS)

tests.o : tests.c t_functions.c t_functions.h
	$(CC) -o $@ -c $< $(CFLAGS)

t_functions.o : t_functions.c t_functions.h ../src/logs/logs.c ../include/logs/logs.h ../src/rasp/server/server.c ../include/rasp/server/server.h
	$(CC) -o $@ -c $< $(CFLAGS)

logs.o : ../src/logs/logs.c ../include/logs/logs.h
	$(CC) -o $@ -c $< $(CFLAGS)

server.o : ../src/rasp/server/server.c ../include/rasp/server/server.h
	$(CC) -o $@ -c $< $(CFLAGS)

clientTest.o : clientTest.c ../src/controllerComputer/client.c ../include/controllerComputer/client.h
	$(CC) -o $@ -c $< $(CFLAGS)

client.o : ../src/controllerComputer/client.c ../include/controllerComputer/client.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean_logs :
	rm -r ../Logs/

clean :
	rm *.o
	rm *.out
