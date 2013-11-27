/* View */
/*Аналитикам хочется знать "товарооборот" между каждой парой европейских и южноамериканских портов.
Товарооборот -- это суммарный вес перевезенного кофе между двумя портами.
Напишите им простенькое представление, показывающее эти цифры */

DROP VIEW IF EXISTS GrossRevenue;

CREATE VIEW GrossRevenue AS
SELECT
    ap."Name" AS American_port,
    ep."Name" AS European_port,
    SUM(ship."Payload") AS "Gross Revenue"
FROM
    "ShipmentToEuropeanPort" sep
    INNER JOIN "Ship" ship ON (sep."IDShip" = ship."ID")
    INNER JOIN "AmericanPort" ap ON (ap."ID" = sep."IDAmericanPort")
    INNER JOIN "EuropeanPort" ep ON (ep."ID" = sep."IDEuropeanPort")
GROUP BY
    ap."Name", ep."Name"
ORDER BY ap."Name", ep."Name"