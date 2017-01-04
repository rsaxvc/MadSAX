# MADSAX

MADSAX is both a thin shim over expat,
and a program to generate that shim.
The shim uses a perfect hash to map
XML tag patterns to callbacks for
open/close/data.

The following EXPAT APIs are available:

* MADSAX_Char
* MADSAX_SetUserData
* MADSAX_Parse
* MADSAX_ParseBuffer
* MADSAX_GetBuffer
* MADSAX_ParserCreate
* MADSAX_ParserFree

But, parser callbacks are done a little
differently. See example.madsax for an
example. Specific tag patterns are
specified and will be called by MADSAX
as they are encountered by EXPAT.

For an example of how to build MADSAX
into a project, see the Makefile
