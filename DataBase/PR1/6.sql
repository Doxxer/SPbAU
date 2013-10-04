-- найти страны (и языки) где язык используется только в этой стране
SELECT
	cl."language" AS "language",
	MIN (C ."name")
FROM
	countrylanguage cl
INNER JOIN country C ON (cl.countrycode = C .code)
GROUP BY
	cl."language"
HAVING
	COUNT (C .code) = 1
ORDER BY
	2