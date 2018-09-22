/*
 * pg_color: Color data type for PostgreSQL
 *
 * Author: Burak Yucesoy <burak@citusdata.com>
 */

#include "postgres.h"

#include "utils/elog.h"
#include "utils/palloc.h"
#include "utils/builtins.h"
#include "libpq/pqformat.h"

#ifndef PG_VERSION_NUM
#error "Unsupported too old PostgreSQL version"
#endif

#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif

#define COLOR_LENGTH 6
#define MAX_COLOR_VALUE 16777215

typedef int32 color;

static inline
int hex_to_binary(char h)
{
	if (h >= '0' && h <= '9')
	{
		return h - '0';
	}
	else if (h >= 'A' && h <= 'F')
	{
		return h + 10 - 'A';
	}
	else
	{
		elog(ERROR, "value '%c' is not a valid digit for type color.", h);
	}

	return 0;
}

static inline
char binary_to_hex(int b)
{
	char lookup_table[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

	if (b < 0 || b > 15)
	{
		elog(ERROR, "value '%d' is not a valid binary representation of a hex character", b);
	}

	return lookup_table[b];
}

static inline
color color_from_str(const char *str)
{
  int i = 0;
  color c = 0;

  if(strlen(str) != COLOR_LENGTH)
  {
    ereport(ERROR,
			(errcode(ERRCODE_NUMERIC_VALUE_OUT_OF_RANGE),
			 errmsg("value \"%s\" is out of range for type color", str)));
  }

  for(i = 0; i < COLOR_LENGTH; i++) {
    c <<= 4;
	c |= hex_to_binary(str[i]);
  }

  return c;
}

static inline
char *color_to_str(color c)
{
  int i = 0;
  char *str = palloc0((COLOR_LENGTH + 1) * sizeof(char));

  if(c > MAX_COLOR_VALUE)
  {
    ereport(ERROR,
			(errcode(ERRCODE_NUMERIC_VALUE_OUT_OF_RANGE),
			 errmsg("value \"%d\" is out of range for type color", c)));
  }

  for(i = COLOR_LENGTH - 1; i >= 0; i--)
  {
    str[i] = binary_to_hex(c & 15);
	c >>= 4;
  }

  return str;
}

Datum color_in(PG_FUNCTION_ARGS);
Datum color_out(PG_FUNCTION_ARGS);

PG_FUNCTION_INFO_V1(color_in);
Datum
color_in(PG_FUNCTION_ARGS)
{
    char *str = PG_GETARG_CSTRING(0);
    PG_RETURN_INT32(color_from_str(str));
}

PG_FUNCTION_INFO_V1(color_out);
Datum
color_out(PG_FUNCTION_ARGS)
{
  color c = PG_GETARG_INT32(0);
  PG_RETURN_CSTRING(color_to_str(c));
}
