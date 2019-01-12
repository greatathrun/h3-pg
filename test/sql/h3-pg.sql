\pset tuples_only on

-- neighbouring indexes (one hexagon, one pentagon) at resolution 3
\set hexagon '\'831c02fffffffff\'::h3index'
\set pentagon '\'831c00fffffffff\'::h3index'
\set distance 86.3352698485577
\set epsilon 0.0000000000001

--
-- TEST h3_haversine_distance
--

SELECT h3_haversine_distance(:hexagon, :pentagon) - :distance < :epsilon;

--
-- TEST h3_basecells
--

SELECT COUNT(*) = 122 FROM (SELECT h3_basecells()) q;