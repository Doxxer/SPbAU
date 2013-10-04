-- страны отсортированные по отношению сельских ко всем
SELECT c.code, c."name", 1.0*(c.population - SUM(cc.population)) / c.population as Result
FROM country c
	INNER JOIN city cc on (c.code = cc.countrycode)
GROUP BY c.code, c."name"
ORDER BY 3 DESC