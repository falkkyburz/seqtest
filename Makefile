all: run

run: seqtest
	./seqtest

seqtest: seqtest.c
	gcc -Wall -o $@ $^

clean:
	rm -f seqtest
