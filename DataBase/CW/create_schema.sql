DROP TABLE IF EXISTS "CommandInCategory";
DROP TABLE IF EXISTS "Participant";
DROP TABLE IF EXISTS "VolunteerInCP";
DROP TABLE IF EXISTS "CheckList";
DROP TABLE IF EXISTS "CheckPoint";
DROP TABLE IF EXISTS "Category";
DROP TABLE IF EXISTS "Command";
DROP TABLE IF EXISTS "Volunteer";


CREATE TABLE "Command" (
    "ID" INT PRIMARY KEY,
    "Name" VARCHAR (200) NOT NULL,
    "Phone" VARCHAR (20),
    "RegistationDate" DATE NOT NULL,
    "PaymentStatus" BOOLEAN
);

CREATE TABLE "Participant" (
    "ID" INT PRIMARY KEY,
    "IDCommand" INT NOT NULL,
    "FirstName" VARCHAR (200) NOT NULL,
    "SecondName" VARCHAR (200) NOT NULL,
    FOREIGN KEY ("IDCommand") REFERENCES "Command" ("ID")
);

CREATE TABLE "Category" (
    "ID" INT PRIMARY KEY CHECK ("ID" >= 0 AND "ID" <= 8),
    "Name" VARCHAR (200) NOT NULL,
    "MaxCapacity" INT NOT NULL,
    "Rules" VARCHAR(2000)
);

CREATE TABLE "CommandInCategory" (
    "IDCommand" INT PRIMARY KEY,
    "IDCategory" INT NOT NULL,
    "StartTime" INT,    
    "FinishTime" INT,
    FOREIGN KEY ("IDCommand") REFERENCES "Command" ("ID"),
    FOREIGN KEY ("IDCategory") REFERENCES "Category" ("ID"),
    UNIQUE ("IDCategory", "StartTime")
);

CREATE TABLE "CheckPoint" (
    "ID" INT PRIMARY KEY,
    "IDCategory" INT NOT NULL,
    "Address" VARCHAR(200) NOT NULL,
    "Legend" VARCHAR(2000) NOT NULL,    
    FOREIGN KEY ("IDCategory") REFERENCES "Category" ("ID")
);

CREATE TABLE "Volunteer" (
    "ID" INT PRIMARY KEY,
    "FirstName" VARCHAR (200) NOT NULL,
    "SecondName" VARCHAR (200) NOT NULL
);

CREATE TABLE "VolunteerInCP" (
    "IDVolunteer" INT NOT NULL,
    "IDCheckPoint" INT NOT NULL,
    FOREIGN KEY ("IDVolunteer") REFERENCES "Volunteer" ("ID"),
    FOREIGN KEY ("IDCheckPoint") REFERENCES "CheckPoint" ("ID")
);

CREATE TABLE "CheckList" (
    "IDCommand" INT NOT NULL,
    "IDCheckPoint" INT NOT NULL,
    "CheckTime" INT,
    FOREIGN KEY ("IDCommand") REFERENCES "Command" ("ID"),
    FOREIGN KEY ("IDCheckPoint") REFERENCES "CheckPoint" ("ID")
);