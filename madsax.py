def stripComments( line ):
	pos = line.find('#')
	if( pos == -1 ):
		return line
	else:
		return line[:pos]

def process(line):
	print(line)

import fileinput
for line in fileinput.input():
	line = stripComments(line)
	line = line.strip()
	process(line)
