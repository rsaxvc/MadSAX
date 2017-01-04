#include <stdlib.h>
#include <string.h>
#include <expat.h>

typedef struct
	{
	XML_Parser parser;
	void * userData;
	char * buffer;
	size_t buffer_len;
	size_t buffer_max;
	}MADSAX_ParserStruct,* MADSAX_Parser;

#define MADSAX_Char XML_Char
#define MADSAX_SetUserData( p, rValUserData ) (p)->userData = (rValUserData)
#define MADSAX_Parse(p, b, len, done) XML_Parse((p)->parser, (b), (len), (done))
#define MADSAX_ParseBuffer(p, len, done) XML_ParseBuffer((p)->parser, (len), (done))
#define MADSAX_GetBuffer(p, len) XML_GetBuffer((p)->parser, (len)))

const struct tag_handler *
in_word_set (register const char * str, register unsigned int len);

static void MADSAX_StartElementHandler(void *userData, const XML_Char *tag_name, const XML_Char **atts)
{
MADSAX_Parser p = userData;

/*Insert /tag and reterminate*/
size_t len = strlen(tag_name);
size_t len_needed = p->buffer_len + len + 1;/*this +1 is for tag-sep*/
if( len_needed > p->buffer_max )
	{
	p->buffer_max = p->buffer_len + len;
	void * newBuf = XML_MemRealloc( p->parser, p->buffer, len_needed + 1);/*This one is for NULL*/
	if( !newBuf )
		{
		XML_StopParser( p->parser, XML_FALSE );
		return;
		}
	p->buffer = newBuf;
	}
strcpy(p->buffer+p->buffer_len,"/");p->buffer_len += 1;
strcpy(p->buffer+p->buffer_len,tag_name);p->buffer_len += len;

/*Call start-tag handler*/
const struct tag_handler * tag = in_word_set( p->buffer, p->buffer_len );
if( tag )tag->tag_start( p->userData, tag_name, atts );
}

static void MADSAX_EndElementHandler(void *userData, const XML_Char *tag_name)
{
MADSAX_Parser p = userData;

/*Call end-tag handler*/
const struct tag_handler * tag = in_word_set( p->buffer, p->buffer_len );
if( tag )tag->tag_end(p->userData,tag_name);

/*Remove /tag by reterminating*/
p->buffer_len -= strlen(tag_name) + 1;
p->buffer[p->buffer_len] = 0;
}

static MADSAX_Parser MADSAX_ParserCreate(const XML_Char * encoding)
{
MADSAX_Parser p = malloc(sizeof(MADSAX_ParserStruct));
if( p )
	{
	p->parser = XML_ParserCreate(encoding);
	if( p->parser )
		{
		void * buf = XML_MemMalloc( p->parser, 1 );
		if( buf )
			{
			p->buffer = buf;
			p->buffer_len = 0;
			p->buffer_max = 0;
			p->buffer[p->buffer_len] = 0;
			XML_SetElementHandler(p->parser, MADSAX_StartElementHandler,MADSAX_EndElementHandler);
			XML_SetUserData( p->parser, p );
			return p;
		}
		XML_ParserFree( p->parser );
		}
	free(p);
	}
return NULL;
}

static void MADSAX_ParserFree( MADSAX_Parser p )
{
free(p->buffer);
p->buffer = NULL;
p->buffer_len = 0;
p->buffer_max = 0;
XML_ParserFree( p->parser );
free(p);
}
