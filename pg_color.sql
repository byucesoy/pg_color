-- complain if script is sourced in psql, rather than via CREATE EXTENSION
\echo Use "CREATE EXTENSION pg_color" to load this file. \quit

-- IO UDFs
CREATE OR REPLACE FUNCTION color_in(cstring)
RETURNS color
AS '$libdir/pg_color'
LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION color_out(color)
RETURNS cstring
AS '$libdir/pg_color'
LANGUAGE C IMMUTABLE STRICT;

CREATE TYPE color (
  INPUT = color_in,
  OUTPUT = color_out,
  LIKE = int4,
  CATEGORY = 'N'
);
COMMENT ON TYPE color IS 'Color data type for PostgreSQL';

