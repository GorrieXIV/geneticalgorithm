# Linux (default)
LDFLAGS = 
CFLAGS=-g -Wall -std=c++11
CC=g++
EXEEXT= gamain
RM=rm

PROGRAM_NAME= gamain

run: $(PROGRAM_NAME)
	./$(PROGRAM_NAME)$(EXEXT)

#when adding additional source files, such as boilerplateClass.cpp
#or yourFile.cpp, add the filename with an object extension below
#ie. boilerplateClass.o and yourFile.o
#make will automatically know that the objectfile needs to be compiled
#form a cpp source file and find it itself :)
$(PROGRAM_NAME): gamain.cpp
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

clean:
	$(RM) *.o $(PROGRAM_NAME) $(EXEEXT)
