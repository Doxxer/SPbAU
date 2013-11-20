/* task 2 */
/* найти все корабли грузоподъемностью более 1000 тонн,
которые смогут перевезти кофе из Рио-де-Жанейро в Лиссабон
по цене меньше чем 10000 долларов */
/* note: цены хранятся в тысячах долларов, а грузоподъемность в тоннах (ибо так сказано в пророчестве (задании)) */
SELECT
	ship."Name"
FROM
	"Ship" ship
INNER JOIN "ShipmentPrice" price ON (ship."ID" = price."IDShip")
INNER JOIN "EuropeanPort" eport ON (
	eport."ID" = price."IDEuropeanPort"
)
INNER JOIN "AmericanPort" aport ON (
	aport."ID" = price."IDAmericanPort"
)
WHERE
	aport."Name" = 'Lisbon'
AND eport."Name" = 'Rio'
AND price."Price" < 10
AND ship."Payload" > 1000