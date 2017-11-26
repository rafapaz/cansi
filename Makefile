
prog := histogram-length-word

all: ${prog}.o
	gcc ${prog}.o -o ${prog}

${prog}.o: ${prog}.c
	gcc -c ${prog}.c

clean:
	rm *.o ${prog}
