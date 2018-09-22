-- OPERATORs
CREATE OR REPLACE FUNCTION color_eq(color, color) 
RETURNS boolean LANGUAGE internal IMMUTABLE AS 'int4eq';

CREATE OR REPLACE FUNCTION color_ne(color, color) 
RETURNS boolean LANGUAGE internal IMMUTABLE AS 'int4ne';

CREATE OPERATOR = (
	LEFTARG = color,
	RIGHTARG = color,
	PROCEDURE = color_eq,
	COMMUTATOR = '=',
	NEGATOR = '<>',
	RESTRICT = eqsel,
	JOIN = eqjoinsel
);
COMMENT ON OPERATOR =(color, color) IS 'equals?';

CREATE OPERATOR <> (
	LEFTARG = color,
	RIGHTARG = color,
	PROCEDURE = color_ne,
	COMMUTATOR = '<>',
	NEGATOR = '=',
	RESTRICT = neqsel,
	JOIN = neqjoinsel
);
COMMENT ON OPERATOR <>(color, color) IS 'not equals?';
