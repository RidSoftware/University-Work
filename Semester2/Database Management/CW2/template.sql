#F28DM CW2

#username = ????

#question 1
SELECT COUNT(*) AS actresses
FROM imdb_actors
WHERE sex = 'female';


#question 2
SELECT MAX(time) AS longest_film
FROM imdb_runningtimes;


#question 3
SELECT COUNT(*) AS films_more_than_5_directors
FROM (
    SELECT movieid, COUNT(*) AS nof_of_directors
    FROM imdb_movies2directors
    GROUP BY movieid
    HAVING no_of_directors > 5
) AS films_with_many_directors;


#question 4
SELECT imdb_movies.title
FROM imdb_movies
JOIN (
    SELECT movieid, COUNT(*) AS no_of_directors
    FROM imdb_movies2directors
    GROUP BY movieid
    ORDER BY no_of_directors DESC
    LIMIT 1
) AS no_of_directors_per_movie ON imdb_movies.movieid = no_of_directors_per_movie.movieid


#question 5
SELECT SUM(imdb_ratings.votes) AS total_votes
FROM imdb_ratings
JOIN imdb_movies2directors ON imdb_ratings.movieid = imdb_movies2directors.movieid
WHERE imdb_movies2directors.genre = 'Thriller';


#question 6
SELECT COUNT(*) AS movies_with_both
FROM (
    SELECT DISTINCT movieid
    FROM imdb_movies2actors
    WHERE actorid IN (
        SELECT actorid
        FROM imdb_actors
        WHERE name = 'Ewan McGregor' OR name = 'Robert Carlyle'
    )
    GROUP BY movieid
    HAVING COUNT(DISTINCT actorid) = 2
) AS movies_with_EwanMcgregor_and_RobertCarlyle


#question 7
SELECT COUNT(*) AS self_directed_actor_director
FROM (
    SELECT directorid
    FROM imdb_movies2directors
    JOIN imdb_movies2actors ON imdb_movies2directors.movieid = imdb_movies2actors.movieid
    WHERE imdb_movies2actors.directorid = imdb_movies2actors.actorid
    GROUP BY directorid
    HAVING COUNT(*) > 4
) AS self_directed;


#question 8
SELECT 
    CONCAT(
        FLOOR(year / 10) * 10, '-', 
        FLOOR(year / 10) * 10 + 9
    ) AS decade,
    COUNT(*) AS no_of_movies
FROM 
    imdb_movies
GROUP BY 
    FLOOR(year / 10)
ORDER BY 
    FLOOR(year / 10)

#question 9
SELECT ...

#question 10
SELECT ...

#question 11
SELECT ...

#question 12
SELECT ...

#question 13
SELECT ...

#question 14
SELECT ...

#question 15
SELECT ...
