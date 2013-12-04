SELECT cic."IDCommand", cat."Name", cic."StartTime", "counter".cnt
FROM "CommandInCategory" cic
	INNER JOIN "Command" com ON (com."ID" = cic."IDCommand")
	INNER JOIN "Category" cat ON (cat."ID" = cic."IDCategory")
	INNER JOIN
	(
		SELECT participant."IDCommand" AS "idcom", COUNT (participant."ID") AS "cnt"
		FROM "Participant" participant
		GROUP BY participant."IDCommand"
	) "counter" ON ("counter".idcom = cic."IDCommand")
WHERE
	com."PaymentStatus" = TRUE
ORDER BY cic."StartTime" DESC