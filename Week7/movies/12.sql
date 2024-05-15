-- SELECT m.id FROM movies m JOIN stars s ON m.id = s.movie_id JOIN people p ON p.id = s.person_id AND p.name = "Bradley Cooper";
-- SELECT m.id FROM movies m JOIN stars s ON m.id = s.movie_id JOIN people p ON p.id = s.person_id AND p.name = "Jennifer Lawrence";
SELECT title FROM movies m WHERE
    m.id IN (SELECT m.id FROM movies m JOIN stars s ON m.id = s.movie_id JOIN people p ON p.id = s.person_id AND p.name = "Bradley Cooper")
    AND
    m.id IN (SELECT m.id FROM movies m JOIN stars s ON m.id = s.movie_id JOIN people p ON p.id = s.person_id AND p.name = "Jennifer Lawrence")
    ;
