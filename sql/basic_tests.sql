CREATE TABLE colors(color color);

-- INSERT different color values
INSERT INTO colors VALUES('000000'), ('FFFFFF'), ('FF0000'), ('00FF00'), ('0000FF');

-- Display INSERTed values
SELECT * FROM colors;

-- Try INSERTing invalid colors
INSERT INTO colors VALUES('0');
INSERT INTO colors VALUES('0000000');
INSERT INTO colors VALUES('GGGGGG');

-- Test equality operator
SELECT * FROM colors WHERE color = '000000';

-- Test inequality operator
SELECT * FROM colors WHERE color <> '000000';

-- Test JOIN with our new type
SELECT * FROM colors c1 JOIN colors c2 ON (c1.color = c2.color);
