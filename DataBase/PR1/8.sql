-- самые большие страны на континентах
SELECT
	t1.continent,
	cc."name",
	t1.mm,
	cc.headofstate
FROM
	(
		SELECT
			C .continent,
			MAX (C .surfacearea) AS mm
		FROM
			country C
		GROUP BY
			C .continent
	) t1
INNER JOIN country cc ON (
	t1.mm = cc.surfacearea
	AND t1.continent = cc.continent
)
ORDER BY
	2