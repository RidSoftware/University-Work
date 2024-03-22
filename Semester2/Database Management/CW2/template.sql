#F28DM CW2

#username = cm2103

#question 1
SELECT COUNT(*) AS actresses
FROM imdb_actors
WHERE sex = 'F';


#question 2
SELECT MAX(time1) AS longest_film
FROM imdb_runningtimes;


#question 3
SELECT COUNT(*) AS films_more_than_5_directors
FROM (
    SELECT movieid, COUNT(*) AS no_of_directors
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
) AS no_of_directors_per_movie ON imdb_movies.movieid = no_of_directors_per_movie.movieid;


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
        WHERE name LIKE 'McGregor, Ewan%' OR name LIKE 'Carlyle, Robert%'
    )
    GROUP BY movieid
    HAVING COUNT(DISTINCT actorid) = 2
) AS movies_with_EwanMcgregor_and_RobertCarlyle;


#question 7
SELECT COUNT(*) AS self_directed_actor_director
FROM (
    SELECT directorid
    FROM imdb_movies2directors
    JOIN imdb_movies2actors ON imdb_movies2directors.movieid = imdb_movies2actors.movieid
    WHERE imdb_movies2actors.actorid = imdb_movies2actors.actorid
    GROUP BY directorid
    HAVING COUNT(*) > 4
) AS self_directed;


#question 8
SELECT CONCAT(FLOOR(year / 10) * 10, '-', FLOOR(year / 10) * 10 + 9) AS decade, COUNT(*) AS no_of_movies
FROM imdb_movies
GROUP BY FLOOR(year / 10)
ORDER BY FLOOR(year / 10);


#question 9
SELECT COUNT(*) AS movies_with_more_female_actors
FROM (
    SELECT movieid
    FROM imdb_movies2actors
    JOIN imdb_actors ON imdb_movies2actors.actorid = imdb_actors.actorid
    GROUP BY movieid
    HAVING SUM(CASE WHEN sex = 'F' THEN 1 ELSE 0 END) > SUM(CASE WHEN sex = 'M' THEN 1 ELSE 0 END)
) AS movies_with_more_female_actors;


#question 10
SELECT imdb_movies2directors.genre, AVG(imdb_ratings.rank) AS average_rank
FROM imdb_movies2directors
JOIN imdb_ratings ON imdb_movies2directors.movieid = imdb_ratings.movieid
JOIN (SELECT movieid FROM imdb_ratings WHERE votes >= 10000) AS filtered_ratings ON imdb_movies2directors.movieid = filtered_ratings.movieid
GROUP BY imdb_movies2directors.genre
ORDER BY average_rank DESC
LIMIT 1;


#question 11
SELECT SUBSTRING_INDEX(name, ' ', -1) AS surname
FROM imdb_actors
JOIN imdb_movies2actors ON imdb_actors.actorid = imdb_movies2actors.actorid
JOIN imdb_movies2directors ON imdb_movies2actors.movieid = imdb_movies2directors.movieid
GROUP BY imdb_actors.actorid
HAVING COUNT(DISTINCT imdb_movies2directors.genre) >= 10;


#question 12
SELECT COUNT(DISTINCT imdb_movies2actors.movieid) AS movies_with_actor_writer_director
FROM imdb_movies2actors
JOIN imdb_movies2writers ON imdb_movies2actors.movieid = imdb_movies2writers.movieid
JOIN imdb_movies2directors ON imdb_movies2actors.movieid = imdb_movies2directors.movieid
WHERE imdb_movies2actors.actorid = imdb_movies2writers.writerid AND imdb_movies2actors.actorid = imdb_movies2directors.directorid;


#question 13
SELECT CONCAT(FLOOR(imdb_movies.year / 10) * 10, '-', FLOOR(imdb_movies.year / 10) * 10 + 9) AS decade_start_year,
    AVG(imdb_ratings.rank) AS average_rank
FROM imdb_movies
JOIN imdb_ratings ON imdb_movies.movieid = imdb_ratings.movieid
GROUP BY FLOOR(imdb_movies.year / 10)
ORDER BY AVG(imdb_ratings.rank) ASC
LIMIT 1;


#question 14
SELECT COUNT(*) AS missing_genre_count
FROM imdb_movies2directors
WHERE genre IS NULL;


#question 15
SELECT COUNT(DISTINCT imdb_movies2directors.movieid) AS movies_count
FROM imdb_movies2directors
JOIN imdb_movies2writers ON imdb_movies2directors.movieid = imdb_movies2writers.movieid
LEFT JOIN imdb_movies2actors ON imdb_movies2directors.movieid = imdb_movies2actors.movieid AND imdb_movies2directors.directorid = imdb_movies2actors.actorid
WHERE imdb_movies2writers.writerid = imdb_movies2directors.directorid AND imdb_movies2actors.actorid IS NULL;
