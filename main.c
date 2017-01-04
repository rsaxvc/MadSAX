#include "example.c"

#include <stdio.h>

int main()
{
  char buf[128];
  int done = 0;
  int depth = 0;  /* nothing magic about this; the sample program tracks depth to know how far to indent. */
                  /* depth is thus going to be the user data for this parser. */

  FILE * fh = fopen( "example.svg", "r" );
  MADSAX_Parser p = MADSAX_ParserCreate(NULL);
  MADSAX_SetUserData(p, &depth);
  do
  {
	size_t len = fread(buf, 1, sizeof(buf), fh);
	done = len != sizeof(buf);
    if (!MADSAX_Parse(p, buf, len, done))
    {
      printf("handle parse error\n");
      return 1;
    }
  } while (!done);
  MADSAX_ParserFree(p);
  fclose( fh );
  return 0;
}

static void handle_tag_start(int * depth, const char * function )
{
printf("Depth:%i:%s\n",*depth,function);
(*depth)++;
}

static void handle_tag_end(int * depth, const char * function )
{
(*depth)--;
printf("Depth:%i:%s\n",*depth,function);
}

/*
These are individual function calls for tag entry/exit/data.
These are equivalent to what EXPAT provides, but MADSAX splits
them up.
*/
static void handle_tag_start__svg(void *data, const char *el, const char **attr){handle_tag_start(data,__func__);}
static void handle_tag_end__svg(void *data, const char *el){handle_tag_end(data,__func__);}
static void handle_tag_data__svg(void *data, const char *content, int length){}
static void handle_tag_start__svg__defs(void *data, const char *el, const char **attr){handle_tag_start(data,__func__);}
static void handle_tag_end__svg__defs(void *data, const char *el){handle_tag_end(data,__func__);}
static void handle_tag_data__svg__defs(void *data, const char *content, int length){}
static void handle_tag_start__svg__defs__linearGradient(void *data, const char *el, const char **attr){handle_tag_start(data,__func__);}
static void handle_tag_end__svg__defs__linearGradient(void *data, const char *el){handle_tag_end(data,__func__);}
static void handle_tag_data__svg__defs__linearGradient(void *data, const char *content, int length){}
static void handle_tag_start__svg__defs__style(void *data, const char *el, const char **attr){handle_tag_start(data,__func__);}
static void handle_tag_end__svg__defs__style(void *data, const char *el){handle_tag_end(data,__func__);}
static void handle_tag_data__svg__defs__style(void *data, const char *content, int length){}
static void handle_tag_start__svg__rect(void *data, const char *el, const char **attr){handle_tag_start(data,__func__);}
static void handle_tag_end__svg__rect(void *data, const char *el){handle_tag_end(data,__func__);}
static void handle_tag_data__svg__rect(void *data, const char *content, int length){}
static void handle_tag_start__svg__circle(void *data, const char *el, const char **attr){handle_tag_start(data,__func__);}
static void handle_tag_end__svg__circle(void *data, const char *el){handle_tag_end(data,__func__);}
static void handle_tag_data__svg__circle(void *data, const char *content, int length){}
static void handle_tag_start__svg__line(void *data, const char *el, const char **attr){handle_tag_start(data,__func__);}
static void handle_tag_end__svg__line(void *data, const char *el){handle_tag_end(data,__func__);}
static void handle_tag_data__svg__line(void *data, const char *content, int length){}
static void handle_tag_start__svg__polyline(void *data, const char *el, const char **attr){handle_tag_start(data,__func__);}
static void handle_tag_end__svg__polyline(void *data, const char *el){handle_tag_end(data,__func__);}
static void handle_tag_data__svg__polyline(void *data, const char *content, int length){}
