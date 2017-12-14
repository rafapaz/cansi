
prog := qsort

all: 
	gcc ${prog}.c util.c -o ${prog}

debug:
	gcc ${prog}.c util.c -o ${prog} -g

clean:
	rm *.o ${prog}
