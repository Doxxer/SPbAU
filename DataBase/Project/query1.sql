/* task 1 */
/* найти фамилии управляющих, которые заведуют плантациями, когда-либо поставлявшими кофе в заданный порт */
SELECT DISTINCT
	man."Name"
FROM
	"Plantation" plantation
INNER JOIN "Manager" man ON (
	plantation."IDManager" = man."ID"
)
INNER JOIN "ShipmentToAmericanPort" shipment ON (
	shipment."IDPlantation" = plantation."ID"
)
INNER JOIN "AmericanPort" port ON (
	port."ID" = shipment."IDAmericanPort"
)
WHERE
	port."Name" = 'Rio'