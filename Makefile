main: main.c thready.c
	gcc -o main main.c thready.c

clean:
	rm main