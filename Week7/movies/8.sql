SELECT p.name FROM people p, stars s, movies m WHERE p.id = s.person_id AND m.id = s.movie_id AND m.title = "Toy Story";
