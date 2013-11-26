-- DROP DATABASE IF EXISTS "Cafe";
-- CREATE DATABASE "Cafe";

DROP TABLE IF EXISTS "ShipmentPrice";
DROP TABLE IF EXISTS "DeliveryToCustomer";
DROP TABLE IF EXISTS "ShipmentToAmericanPort";
DROP TABLE IF EXISTS "ShipmentToEuropeanPort";
DROP TABLE IF EXISTS "AmericanPort";
DROP TABLE IF EXISTS "EuropeanPort";
DROP TABLE IF EXISTS "Plantation";
DROP TABLE IF EXISTS "Manager";
DROP TABLE IF EXISTS "Ship";
DROP TABLE IF EXISTS "Customer";

CREATE TABLE "Manager" (
	"ID" INT PRIMARY KEY,
	"Name" VARCHAR (200) NOT NULL
);

CREATE TABLE "Plantation" (
	"ID" INT PRIMARY KEY,
	"Country" VARCHAR (100) NOT NULL,
	"IDManager" INT NOT NULL,
	FOREIGN KEY ("IDManager") REFERENCES "Manager" ("ID")
);

CREATE TABLE "Ship" (
	"ID" INT PRIMARY KEY,
	"Name" VARCHAR (100) NOT NULL,
    "Payload" INT CHECK ("Payload" >= 0)
);

CREATE TABLE "AmericanPort" (
	"ID" INT PRIMARY KEY,
	"Name" VARCHAR (100) NOT NULL
);

CREATE TABLE "EuropeanPort" (
	"ID" INT PRIMARY KEY,
	"Name" VARCHAR (100) NOT NULL
);

CREATE TABLE "ShipmentPrice" (
    "IDAmericanPort" INT NOT NULL,
    "IDEuropeanPort" INT NOT NULL,
    "IDShip" INT NOT NULL,
    "Price" INT CHECK ("Price" >= 0),    
    FOREIGN KEY ("IDAmericanPort") REFERENCES "AmericanPort" ("ID"),
    FOREIGN KEY ("IDEuropeanPort") REFERENCES "EuropeanPort" ("ID"),
    FOREIGN KEY ("IDShip") REFERENCES "Ship" ("ID")
);

CREATE TABLE "ShipmentToAmericanPort" (
	"ID" INT PRIMARY KEY,
	"Date" DATE NOT NULL,
    "Amount" INT CHECK ("Amount" >= 0),
    "IDAmericanPort" INT NOT NULL,
    "IDPlantation" INT NOT NULL,
    FOREIGN KEY ("IDAmericanPort") REFERENCES "AmericanPort" ("ID"),
    FOREIGN KEY ("IDPlantation") REFERENCES "Plantation" ("ID")
);

CREATE TABLE "ShipmentToEuropeanPort" (
	"ID" INT PRIMARY KEY,
	"Date" DATE NOT NULL,
    "IDAmericanPort" INT NOT NULL,
    "IDEuropeanPort" INT NOT NULL,
    "IDShip" INT NOT NULL,
    FOREIGN KEY ("IDAmericanPort") REFERENCES "AmericanPort" ("ID"),
    FOREIGN KEY ("IDEuropeanPort") REFERENCES "EuropeanPort" ("ID"),
    FOREIGN KEY ("IDShip") REFERENCES "Ship" ("ID")
);

CREATE TABLE "Customer" (
    "ID" INT PRIMARY KEY,
    "Name" VARCHAR(200) NOT NULL,
    "Price" INT CHECK("Price" >= 0)
);

CREATE TABLE "DeliveryToCustomer" (
	"ID" INT PRIMARY KEY,
    "IDShipment" INT NOT NULL,
    "IDCustomer" INT NOT NULL,
    FOREIGN KEY ("IDShipment") REFERENCES "ShipmentToEuropeanPort" ("ID"),
    FOREIGN KEY ("IDCustomer") REFERENCES "Customer" ("ID")
);