-- SELECT m.id FROM people p JOIN stars s ON p.id = s.person_id AND p.name = "Kevin Bacon" AND p.birth = 1958 JOIN movies m ON m.id = s.movie_id;

-- SELECT s.person_id FROM stars s JOIN movies m ON s.movie_id = m.id JOIN people p ON s.person_id = p.id AND p.name = "Kevin Bacon" AND p.birth = 1958

-- SELECT p.id FROM people p WHERE p.name = "Kevin Bacon" AND p.birth = 1958;

-- SELECT m.id FROM movies m JOIN stars s ON m.id = s.movie_id JOIN people p ON s.person_id = p.id AND p.name = "Kevin Bacon" AND p.birth = 1958;

SELECT name FROM people WHERE name != "Kevin Bacon" AND
    id IN (
        SELECT s.person_id FROM stars s JOIN movies m ON s.movie_id IN
            (SELECT m.id FROM movies m JOIN stars s ON m.id = s.movie_id JOIN people p ON s.person_id = p.id AND p.name = "Kevin Bacon" AND p.birth = 1958)
        );
