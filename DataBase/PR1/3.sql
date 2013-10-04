-- язык - количество людей говорящих на нем
SELECT cl."language", floor(SUM(C.population * cl.percentage / 100.0))
FROM countrylanguage cl
	INNER JOIN country C ON (cl.countrycode = C.code)
GROUP BY cl."language"
ORDER BY 2 DESC