/* Тестовые данные в таблицы */

DELETE FROM "ShipmentPrice";
DELETE FROM "DeliveryToCustomer";
DELETE FROM "ShipmentToAmericanPort";
DELETE FROM "ShipmentToEuropeanPort";
DELETE FROM "EuropeanPort";
DELETE FROM "Plantation";
DELETE FROM "AmericanPort";
DELETE FROM "Manager";
DELETE FROM "Ship";
DELETE FROM "Customer";

INSERT INTO "Manager" ("ID", "Name")
VALUES (1, 'Machete'), (2, 'Manager 2'), (3, 'Manager 3'), (4, 'Manager 4');

INSERT INTO "AmericanPort"("ID", "Name")
VALUES (1, 'Rio'), (2, 'AmericanPort2'), (3, 'AmericanPort3');

INSERT INTO "EuropeanPort"("ID", "Name")
VALUES (1, 'Lisbon'), (2, 'EuropeanPort2'), (3, 'EuropeanPort3');

INSERT INTO "Plantation"("ID", "Country", "IDManager", "IDAmericanPort")
VALUES (1, 'Columbia', 1, 1), (2, 'Brazil', 2, 2), (3, 'Brazil', 3, 3), (4, 'Brazil', 4, 3), (5, 'Brazil', 4, 2);

INSERT INTO "Ship"("ID", "Name")
VALUES (1, 'Fastest'), (2, 'Titanic');

INSERT INTO "ShipmentToAmericanPort"("ID", "Date", "Amount", "IDPlantation")
VALUES (1, '2012-05-20', 3, 1), (2, '2012-05-24', 5, 1), (3, '2012-05-22', 1, 1), (4, '2012-05-22', 10, 1), 
(5, '2012-05-20', 3, 2), (6, '2012-05-24', 19, 2), (7, '2012-05-20', 8, 3);

INSERT INTO "ShipmentPrice"("IDAmericanPort", "IDEuropeanPort", "IDShip", "Price")
VALUES
(1, 1, 1, 4), (1, 1, 2, 17),
(1, 2, 1, 7), (1, 2, 2, 40),
(1, 3, 1, 6), (1, 3, 2, 24),
(2, 1, 1, 55), (2, 1, 2, 48),
(2, 2, 1, 46), (2, 2, 2, 64), 
(2, 3, 1, 19), (2, 3, 2, 42), 
(3, 1, 1, 28), (3, 1, 2, 14),
(3, 2, 1, 73), (3, 2, 2, 46), 
(3, 3, 1, 50), (3, 3, 2, 36);

INSERT INTO "Customer"("ID", "Name", "Price")
VALUES (1, 'Tchibo', 7), (2, 'Nescafe', 2), (3, 'Jacobs', 5);

INSERT INTO "ShipmentToEuropeanPort"("ID", "Date", "IDAmericanPort", "IDEuropeanPort", "IDShip")
VALUES (1, '2012-05-21', 1, 1, 1), (2, '2012-05-23', 2, 3, 1), (3, '2012-05-24', 3, 1, 2), 
(4, '2012-05-22', 1, 3, 2), (5, '2012-05-26', 2, 1, 1), (6, '2012-05-28', 1, 2, 2), 
(7, '2012-05-24', 1, 3, 2), (8, '2012-05-28', 1, 2, 2), (9, '2012-05-30', 3, 1, 1);

INSERT INTO "DeliveryToCustomer"("IDShipment", "IDCustomer")
VALUES (1, 1), (2, 2), (3, 2), (4, 3), (5, 3), (6, 2), (7, 1), (8, 2), (9, 1);