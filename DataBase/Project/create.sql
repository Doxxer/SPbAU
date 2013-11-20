CREATE SEQUENCE "Customer_ID_seq" INCREMENT 1 START 1 MAXVALUE 9223372036854775807 MINVALUE 1 CACHE 1;
CREATE SEQUENCE "DeliveryToCustomer_ID_seq" INCREMENT 1 START 1 MAXVALUE 9223372036854775807 MINVALUE 1 CACHE 1;
CREATE SEQUENCE "EuropeanPort_ID_seq" INCREMENT 1 START 1 MAXVALUE 9223372036854775807 MINVALUE 1 CACHE 1;
CREATE SEQUENCE "Manager_ID_seq" INCREMENT 1 START 2 MAXVALUE 9223372036854775807 MINVALUE 1 CACHE 1;
CREATE SEQUENCE "Plantation_ID_seq" INCREMENT 1 START 1 MAXVALUE 9223372036854775807 MINVALUE 1 CACHE 1;
CREATE SEQUENCE "Port_ID_seq" INCREMENT 1 START 1 MAXVALUE 9223372036854775807 MINVALUE 1 CACHE 1;
CREATE SEQUENCE "Ship_ID_seq" INCREMENT 1 START 1 MAXVALUE 9223372036854775807 MINVALUE 1 CACHE 1;
CREATE SEQUENCE "ShipmentToAmericanPort_ID_seq" INCREMENT 1 START 1 MAXVALUE 9223372036854775807 MINVALUE 1 CACHE 1;
CREATE SEQUENCE "ShipmentToEuropeanPort_ID_seq" INCREMENT 1 START 1 MAXVALUE 9223372036854775807 MINVALUE 1 CACHE 1;

CREATE TABLE "Manager" (
	"ID" int4 NOT NULL DEFAULT nextval('"Manager_ID_seq"'::regclass),
	"Name" varchar(200)
)

CREATE TABLE "AmericanPort" (
	"ID" int4 NOT NULL DEFAULT nextval('"Port_ID_seq"'::regclass),
	"Name" varchar(100)
)
CREATE TABLE "Plantation" (
	"ID" int4 NOT NULL DEFAULT nextval('"Plantation_ID_seq"'::regclass),
	"Country" varchar(100),
	"IDManager" int4
)
CREATE TABLE "Ship" (
	"ID" int4 NOT NULL DEFAULT nextval('"Ship_ID_seq"'::regclass),
	"Name" varchar(100),
	"Payload" int4
)
CREATE TABLE "ShipmentToAmericanPort" (
	"ID" int4 NOT NULL DEFAULT nextval('"ShipmentToAmericanPort_ID_seq"'::regclass),
	"Date" date,
	"Amount" int4,
	"IDAmericanPort" int4,
	"IDPlantation" int4
)
CREATE TABLE "ShipmentPrice" (
	"IDAmericanPort" int4 NOT NULL,
	"IDEuropeanPort" int4 NOT NULL,
	"IDShip" int4 NOT NULL,
	"Price" int4 NOT NULL
)
CREATE TABLE "EuropeanPort" (
	"ID" int4 NOT NULL DEFAULT nextval('"EuropeanPort_ID_seq"'::regclass),
	"Name" varchar(100)
)
CREATE TABLE "Customer" (
	"ID" int4 NOT NULL DEFAULT nextval('"Customer_ID_seq"'::regclass),
	"Name" varchar(100),
	"Price" int4
)
CREATE TABLE "ShipmentToEuropeanPort" (
	"ID" int4 NOT NULL DEFAULT nextval('"ShipmentToEuropeanPort_ID_seq"'::regclass),
	"Date" date,
	"IDAmericanPort" int4,
	"IDEuropeanPort" int4,
	"IDShip" int4
)
CREATE TABLE "DeliveryToCustomer" (
	"ID" int4 NOT NULL DEFAULT nextval('"DeliveryToCustomer_ID_seq"'::regclass),
	"IDCustomer" int4,
	"IDShipment" int4
)


ALTER SEQUENCE "Customer_ID_seq" OWNED BY "Customer"."ID";
ALTER SEQUENCE "DeliveryToCustomer_ID_seq" OWNED BY "DeliveryToCustomer"."ID";
ALTER SEQUENCE "EuropeanPort_ID_seq" OWNED BY "EuropeanPort"."ID";
ALTER SEQUENCE "Manager_ID_seq" OWNED BY "Manager"."ID";
ALTER SEQUENCE "Plantation_ID_seq" OWNED BY "Plantation"."ID";
ALTER SEQUENCE "Port_ID_seq" OWNED BY "AmericanPort"."ID";
ALTER SEQUENCE "Ship_ID_seq" OWNED BY "Ship"."ID";
ALTER SEQUENCE "ShipmentToAmericanPort_ID_seq" OWNED BY "ShipmentToAmericanPort"."ID";
ALTER SEQUENCE "ShipmentToEuropeanPort_ID_seq" OWNED BY "ShipmentToEuropeanPort"."ID";

ALTER TABLE "Manager" ADD CONSTRAINT "Manager_pkey" PRIMARY KEY ("ID");
ALTER TABLE "AmericanPort" ADD CONSTRAINT "Port_pkey" PRIMARY KEY ("ID");
ALTER TABLE "Plantation" ADD CONSTRAINT "Plantation_pkey" PRIMARY KEY ("ID");
ALTER TABLE "Ship" ADD CONSTRAINT "Ship_pkey" PRIMARY KEY ("ID");
ALTER TABLE "ShipmentToAmericanPort" ADD CONSTRAINT "ShipmentToAmericanPort_pkey" PRIMARY KEY ("ID");
ALTER TABLE "EuropeanPort" ADD CONSTRAINT "EuropeanPort_pkey" PRIMARY KEY ("ID");
ALTER TABLE "Customer" ADD CONSTRAINT "Customer_pkey" PRIMARY KEY ("ID");
ALTER TABLE "ShipmentToEuropeanPort" ADD CONSTRAINT "ShipmentToEuropeanPort_pkey" PRIMARY KEY ("ID");
ALTER TABLE "DeliveryToCustomer" ADD CONSTRAINT "DeliveryToCustomer_pkey" PRIMARY KEY ("ID");

ALTER TABLE "ShipmentPrice" ADD UNIQUE ("IDAmericanPort", "IDEuropeanPort", "IDShip");