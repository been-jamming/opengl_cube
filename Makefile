all:
	gcc src/main.c src/glad.c -lglfw -lGL -lX11 -ldl -lm -Wall -o cube
