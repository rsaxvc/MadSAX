example: main.c example.c madsax_support.c
	gcc $< -lexpat -o $@ -g -Wall

example.c: example.gperf
	gperf -CtnI $^ --output-file=$@

example.gperf: example.madsax madsax.py
	./madsax.py $< > $@

clean:
	rm -f example example.c example.gperf
