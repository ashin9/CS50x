SELECT name FROM people p JOIN stars s ON p.id = s.person_id JOIN movies m ON m.id = s.movie_id AND m.year == 2004 ORDER BY birth;
