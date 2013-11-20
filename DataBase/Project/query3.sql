/* task 3 */
/*Управляющий плантации "Мачетес" в день X потерял свой любимый кошелек.
Расследование длилось несколько дней и наконец в день Y выяснилось, 
что кошелек случайно попал в мешок с кофе и поехал в порт. 
В порт сразу же позвонили, но за истекший срок из порта ушло несколько кораблей с кофе и скорее всего кошелек
был в одном из них. Выясните, с кем в Европе надо связаться, чтоб найти кошелек*/

SELECT DISTINCT
	cust."Name"
FROM
	"Plantation" plantation
INNER JOIN "Manager" man ON (
	plantation."IDManager" = man."ID"
)
INNER JOIN "ShipmentToAmericanPort" sap ON (
	sap."IDPlantation" = plantation."ID"
)
INNER JOIN "ShipmentToEuropeanPort" sep ON (
	sep."IDAmericanPort" = sap."IDAmericanPort"
	AND sep."Date" >= '2012-05-01' /* day X */
	AND sep."Date" < '2012-05-30'  /* day Y */
)
INNER JOIN "DeliveryToCustomer" dc ON (dc."IDShipment" = sep."ID")
INNER JOIN "Customer" cust ON (cust."ID" = dc."IDCustomer")
WHERE
	man."Name" = 'Machete'