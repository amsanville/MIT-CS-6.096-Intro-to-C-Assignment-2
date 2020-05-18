OBJS = mainA2.o 
CC = g++
CFLAGS = -Wall -g
EXEC = output

output: $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

mainA1.o: mainA2.cpp
	g++ -c mainA2.cpp
	
clean: 
	rm -f $(EXEC) *.o