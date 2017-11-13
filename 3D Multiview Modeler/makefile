LDFLAGS = -lfreeglut -lglu32 -lopengl32
CFLAGS=-g -Wall -std=c++11
CC=g++
EXEEXT=.exe
RM=rm

PROGRAM_NAME= main

#run target to compile and build, and then launch the executable
run: $(PROGRAM_NAME)
	./$(PROGRAM_NAME)$(EXEEXT)

$(PROGRAM_NAME): $(PROGRAM_NAME).o PopUpMenu.o Keyboard.o Mouse.o Window.o Drawing.o Rendering.o Camera.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

clean:
	$(RM) -f *.o $(PROGRAM_NAME)$(EXEEXT) *.obj