#include "example.c"

#include <stdio.h>
#include <expat.h>

char * tag_buffer;
size_t tag_buffer_len;
size_t tag_buffer_max;

static void tagBufferInit()
{
tag_buffer = malloc(1);
tag_buffer_len = 0;
tag_buffer_max = 0;
tag_buffer[tag_buffer_len] = 0;
}

static void tagBufferDestroy()
{
free(tag_buffer);
tag_buffer = NULL;
tag_buffer_len = 0;
}

static void tagBufferPush(const char * tag, size_t len)
{
if(tag_buffer_len + len > tag_buffer_max )
	{
	tag_buffer_max = tag_buffer_len + len;
	tag_buffer = realloc( tag_buffer, tag_buffer_max + 1);
	}
strcpy(tag_buffer+tag_buffer_len,tag);
tag_buffer_len += len;
}

static void tagBufferPop(const char * tag, size_t len)
{
tag_buffer_len -= len;
tag_buffer[tag_buffer_len] = 0;
}

static void StartElementHandler(void *userData, const XML_Char *name, const XML_Char **atts)
{
tagBufferPush("/", 1 );
tagBufferPush(name, strlen(name) );
printf("StartElementHandler:%s:%s\n",name,tag_buffer);
const struct tag_handler * tag = in_word_set( tag_buffer, tag_buffer_len );
if( tag )tag->tag_start(userData,name,atts);
}

static void EndElementHandler(void *userData, const XML_Char *name)
{
printf("EndElementHandler:%s:%s\n",name,tag_buffer);
const struct tag_handler * tag = in_word_set( tag_buffer, tag_buffer_len );
if( tag )tag->tag_end(userData,name);
tagBufferPop(name, strlen(name) );
tagBufferPop("/", 1 );
}


int main()
{
  char buf[128];
  int done = 0;
  int depth = 0;  /* nothing magic about this; the sample program tracks depth to know how far to indent. */
                  /* depth is thus going to be the user data for this parser. */

  FILE * fh = fopen( "example.svg", "r" );
  tagBufferInit();
  XML_Parser parser = XML_ParserCreate(NULL);
  XML_SetUserData(parser, &depth);
  XML_SetElementHandler(parser, StartElementHandler,EndElementHandler);
  do {
	size_t len = fread(buf, 1, sizeof(buf), fh);
	done = len != sizeof(buf);
    if (!XML_Parse(parser, buf, len, done)) {
      printf("handle parse error\n");
      return 1;
    }
  } while (!done);
  XML_ParserFree(parser);
  tagBufferDestroy();
  fclose( fh );
  return 0;
}
