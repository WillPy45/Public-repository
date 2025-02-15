/*In 12.sql, write a SQL query to list the titles of all movies in which both Bradley Cooper 
and Jennifer Lawrence starred.
Your query should output a table with a single column for the title of each movie.
You may assume that there is only one person in the database with the name Bradley Cooper.
You may assume that there is only one person in the database with the name Jennifer Lawrence. */

SELECT movies.title
FROM movies
JOIN stars st1 ON movies.id = st1.movie_id
JOIN people p1 ON st1.person_id = p1.id
JOIN stars st2 ON movies.id = st2.movie_id
JOIN people p2 ON st2.person_id = p2.id
WHERE p1.name = 'Bradley Cooper'
AND p2.name = 'Jennifer Lawrence';
