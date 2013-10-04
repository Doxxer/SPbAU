-- страны с максимальным количеством различных языков
SELECT
	C ."name",
	cc.cnt,
	ccc."language",
	ccc.percentage
FROM
	(
		SELECT
			C .countrycode,
			COUNT (C ."language") AS cnt
		FROM
			countrylanguage C
		GROUP BY
			C .countrycode
		ORDER BY
			1 DESC
	) AS cc
INNER JOIN country C ON (C .code = cc.countrycode)
INNER JOIN countrylanguage ccc ON (ccc.countrycode = C .code)
WHERE
	cc.cnt = (
		SELECT
			COUNT (C ."language")
		FROM
			countrylanguage C
		GROUP BY
			C .countrycode
		ORDER BY
			1 DESC
		LIMIT 1
	)
ORDER BY
	1,
	4 DESC