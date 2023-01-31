APP = pong
GCC = gcc

COMMANDS = -O1 -Wall -std=c99 -Wno-missing-braces
INCLUDES = -I src/includes/ -L src/libs/
RAYLIB =  -lraylib -lopengl32 -lgdi32 -lwinmm


main: main.o app.o
	$(GCC) $^ -o $(APP) $(COMMANDS) $(INCLUDES) $(RAYLIB)

main.o: main.c
	$(GCC) -c $^

app.o: src/app.c
	$(GCC) -c $^

.PHONY: clean
clean:
	rm *.exe *.o