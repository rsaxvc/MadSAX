#include "example.c"

#include <stdio.h>
#include <expat.h>

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


static void handle_tag_start__svg(void *data, const char *el, const char **attr){}
static void handle_tag_end__svg(void *data, const char *el){}
static void handle_tag_data__svg(void *data, const char *content, int length){}
static void handle_tag_start__svg__defs(void *data, const char *el, const char **attr){}
static void handle_tag_end__svg__defs(void *data, const char *el){}
static void handle_tag_data__svg__defs(void *data, const char *content, int length){}
static void handle_tag_start__svg__defs__linearGradient(void *data, const char *el, const char **attr){}
static void handle_tag_end__svg__defs__linearGradient(void *data, const char *el){}
static void handle_tag_data__svg__defs__linearGradient(void *data, const char *content, int length){}
static void handle_tag_start__svg__defs__style(void *data, const char *el, const char **attr){}
static void handle_tag_end__svg__defs__style(void *data, const char *el){}
static void handle_tag_data__svg__defs__style(void *data, const char *content, int length){}
static void handle_tag_start__svg__rect(void *data, const char *el, const char **attr){}
static void handle_tag_end__svg__rect(void *data, const char *el){}
static void handle_tag_data__svg__rect(void *data, const char *content, int length){}
static void handle_tag_start__svg__circle(void *data, const char *el, const char **attr){}
static void handle_tag_end__svg__circle(void *data, const char *el){}
static void handle_tag_data__svg__circle(void *data, const char *content, int length){}
static void handle_tag_start__svg__line(void *data, const char *el, const char **attr){}
static void handle_tag_end__svg__line(void *data, const char *el){}
static void handle_tag_data__svg__line(void *data, const char *content, int length){}
static void handle_tag_start__svg__polyline(void *data, const char *el, const char **attr){}
static void handle_tag_end__svg__polyline(void *data, const char *el){}
static void handle_tag_data__svg__polyline(void *data, const char *content, int length){}

