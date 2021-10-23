#	Created a make file for easier compiling
#	Inputting 'make' or 'make groupC' should make executable for the program
#	Use command ./groupC to run program

#	-g adds debugging info 
#	-Wall activates compiler warning
CC = gcc
CFLAGS = -g -Wall

default: groupC

#	put all files into 1 file for easier compiling
groupC: MessagePassing.o MiniProject_Cook_Isabell.o main.o clientDriver.o serverDriver.o
	$(CC) $(CFLAGS) -o groupC main.o MessagePassing.o MiniProject_Cook_Isabell.o clientDriver.o serverDriver.o -lpthread

#	compile main and header file
main.o: main.c MessagePassing.h clientHelper.h HunterHolstead.h
	$(CC) $(CFLAGS) -c main.c

#	compile MessagePassing.c file
MessagePassing.o: MessagePassing.c MessagePassing.h
	$(CC) $(CFLAGS) -c MessagePassing.c

#	compile MiniProject_Cook_Isabell.c file
MiniProject_Cook_Isabell.o: MiniProject_Cook_Isabell.c clientHelper.h
	$(CC) $(CFLAGS) -c MiniProject_Cook_Isabell.c -lpthread

#	compile ProcessB_ThreadManagement.c file
ProcessB_ThreadManagement.o: ProcessB_ThreadManagement.c 
	$(CC) $(CFLAGS) -c ProcessB_ThreadManagement.c

#	compile HunterHolstead.c file
HunterHolstead.o: HunterHolstead.c HunterHolstead.h
	$(CC) $(CFLAGS) -c HunterHolstead.c

#	compile serverDriver.c file
serverDriver.o: serverDriver.c 
	$(CC) $(CFLAGS) -c serverDriver.c

#	compile clientDriver.c file
clientDriver.o: clientDriver.c 
	$(CC) $(CFLAGS) -c clientDriver.c

#	clean file
clean:
	rm groupC *.o