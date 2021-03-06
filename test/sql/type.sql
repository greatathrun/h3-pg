\pset tuples_only on
\set string '\'801dfffffffffff\''
\set hexagon ':string::h3index'
\set pentagon '\'844c001ffffffff\'::h3index'

CREATE TABLE h3_test_type (hex h3index PRIMARY KEY);
INSERT INTO h3_test_type (hex) SELECT * from h3_get_res_0_indexes();

-- Type conversions
SELECT h3_string_to_h3(h3_to_string(:hexagon)) = :hexagon;
SELECT h3_to_string(h3_string_to_h3(:string))::text = :string::text;

--
-- TEST operators
--
SELECT :hexagon = :hexagon;
SELECT NOT :hexagon = :pentagon;
SELECT NOT :hexagon <> :hexagon;
SELECT :hexagon <> :pentagon;

--
-- TEST b-tree operator class
--
SELECT hex = :hexagon FROM (
    SELECT hex FROM h3_test_type WHERE hex = :hexagon
) q;

--
-- TEST hash operator class
--
SELECT COUNT(hex) = 122 FROM (
    SELECT hex FROM h3_test_type WHERE hex IN (SELECT h3_get_res_0_indexes())
) q;