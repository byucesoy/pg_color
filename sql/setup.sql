-- Test creating the extension
CREATE EXTENSION pg_color VERSION '1.0';

-- Test upgrading the extension from v1.0 to v1.1
ALTER EXTENSION pg_color UPDATE TO '1.1';
