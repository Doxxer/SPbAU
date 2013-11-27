/* View-2 */
/*Тем же аналитикам для каждого европейского порта хочется знать распределение доставленного в него кофе по покупателям.
Что-то в духе "50% кофе, доставленного в Гамбург, покупает "Чибо", 25% "Нескафе" и 25% "Якобс".
В Марселе 70% покупает "Нескафе", а "Чибо" и "Якобс" по 15%. */

DROP VIEW IF EXISTS CustomerDistribution;

CREATE VIEW CustomerDistribution AS
SELECT
    eport."Name" AS port_name,
    cust."Name" AS customer_name,
    round(port_customer_sum.summ * 100.0 / total_port_sum.TotalRevenue, 2) AS precentage
FROM
    (
        SELECT
            sep."IDEuropeanPort",
            dc."IDCustomer",
            SUM (ship."Payload") AS summ
        FROM
            "ShipmentToEuropeanPort" sep
        INNER JOIN "DeliveryToCustomer" dc ON (dc."IDShipment" = sep."ID")
        INNER JOIN "Ship" ship ON (ship."ID" = sep."IDShip")
        GROUP BY sep."IDEuropeanPort", dc."IDCustomer"
    ) port_customer_sum
    INNER JOIN (
        SELECT
            sep."IDEuropeanPort",
            SUM (ship."Payload") AS TotalRevenue
        FROM
            "ShipmentToEuropeanPort" sep
        INNER JOIN "DeliveryToCustomer" dc ON (dc."IDShipment" = sep."ID")
        INNER JOIN "Ship" ship ON (ship."ID" = sep."IDShip")
        GROUP BY sep."IDEuropeanPort"
    ) total_port_sum ON (port_customer_sum."IDEuropeanPort" = total_port_sum."IDEuropeanPort")
    INNER JOIN "EuropeanPort" eport ON (eport."ID" = port_customer_sum."IDEuropeanPort")
    INNER JOIN "Customer" cust ON (cust."ID" = port_customer_sum."IDCustomer")
ORDER BY 1, 2