
prog := expand

all: ${prog}.o
	gcc ${prog}.o -o ${prog}

${prog}.o: ${prog}.c
	gcc -c ${prog}.c

debug: ${prog}.debug
	gcc ${prog}.o -o ${prog}

${prog}.debug: ${prog}.c
	gcc -c ${prog}.c -g

clean:
	rm *.o ${prog}
