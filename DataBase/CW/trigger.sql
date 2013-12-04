SELECT cat."ID"
FROM "Category" cat
	INNER JOIN 
	(
		SELECT cic."IDCategory" AS "idcat", COUNT(cic."IDCommand") AS "count"
		FROM "CommandInCategory" cic
		GROUP BY cic."IDCategory"
	) "counter" ON ("counter".idcat = cat."ID")
WHERE cat."MaxCapacity" < "counter"."count"