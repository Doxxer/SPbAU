INSERT INTO "CheckList"("IDCommand", "IDCheckPoint")
SELECT cic."IDCommand", cp."ID"
FROM "CommandInCategory" cic
	INNER JOIN "CheckPoint" cp ON (cic."IDCategory" = cp."IDCategory")