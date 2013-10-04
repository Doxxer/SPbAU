-- найти страны без городов
SELECT C."name", C.code, C.continent
FROM country C
	LEFT JOIN city cc ON (C.code = cc.countrycode)
WHERE cc."id" IS NULL
ORDER BY 1