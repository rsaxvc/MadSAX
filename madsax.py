#!/usr/bin/python

import sys

def stripComments( line ):
	pos = line.find('#')
	if( pos == -1 ):
		return line
	else:
		return line[:pos]

#def process_header(lineno,line):
def process_header(line):
	tokens = line.split('/')
	#comment = '/*' + str(lineno) + '*/'
	comment  = ''

	function = 'handle_tag_start' + '__'.join(tokens)
	sys.stdout.write( 'static void ' + function + '(void *data, const char *el, const char **attr)'+comment+';\n')

	function = 'handle_tag_end' + '__'.join(tokens)
	sys.stdout.write( 'static void ' + function + '(void *data, const char *el)'                   +comment+';\n')

	function = 'handle_tag_data' + '__'.join(tokens)
	sys.stdout.write( 'static void ' + function + '(void *data, const char *content, int length)'  +comment+';\n')

#def process_gperf(lineno,line):
def process_gperf(line):
	tokens = line.split('/')
	#comment = '/*' + str(lineno) + '*/'
	comment  = ''

	sys.stdout.write(line)
	for prefix in [ 'handle_tag_start','handle_tag_end','handle_tag_data' ]:
		sys.stdout.write( ', ' )
		sys.stdout.write( prefix )
		sys.stdout.write( '__'.join(tokens) )
	sys.stdout.write(comment)
	sys.stdout.write('\n')

import fileinput

lines = []
lineno = 1
for line in fileinput.input():
	line = stripComments(line)
	line = line.strip()
	if( len(line) == 0 ):
		continue
	lines.append(line)
	lineno += 1

#header
sys.stdout.write('''struct tag_handler
{
const char *name;
void (*tag_start)(void *data, const char *el, const char **attr);
void (*tag_end)  (void *data, const char *el);
void (*tag_data) (void *data, const char *content, int length);
};

#include <expat.h>
#include "madsax_support.c"

''')

for line in lines:
	process_header(line)

sys.stdout.write('%%\n')

for line in lines:
	process_gperf(line)
