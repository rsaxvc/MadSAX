example: example.c main.c madsax_support.c
	gcc main.c -lexpat -o example -g -Wall

example.c: example.gperf
	cat example.gperf | gperf -CtnI --output-file=example.c

example.gperf: example.madsax madsax.py
	./madsax.py example.madsax > example.gperf

clean:
	rm -f example example.c example.gperf
