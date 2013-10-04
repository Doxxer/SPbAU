-- все страны, где всего один город в котором не меньше 90% населения страны
SELECT
	temp1.*,
	c1."name", c1.population
FROM
	(
		SELECT
			C ."name",
			C .code,
			C .population,
			COUNT (cc."id") AS cityCount
		FROM
			country C
		INNER JOIN city cc ON (C .code = cc.countrycode)
		GROUP BY
			C ."name",
			C .code,
			C .population
		HAVING
			COUNT (cc."id") = 1
		ORDER BY
			1
	) temp1
INNER JOIN city c1 ON (temp1.code = c1.countrycode)
WHERE
	c1.population >= 0.9 * temp1.population