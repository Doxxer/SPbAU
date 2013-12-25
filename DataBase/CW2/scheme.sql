DROP TABLE
IF EXISTS cathegory CASCADE;

CREATE TABLE cathegory (
	ID INTEGER PRIMARY KEY,
	NAME VARCHAR (25) NOT NULL UNIQUE,
	max_members INTEGER NOT NULL CHECK (max_members > 0),
	description TEXT NULL
);

DROP TABLE
IF EXISTS team CASCADE;

CREATE TABLE team (
	ID INTEGER PRIMARY KEY,
	title VARCHAR (25) UNIQUE NOT NULL,
	registration_date DATE NOT NULL,
	is_paid BOOLEAN NOT NULL,
	cathegory_id INTEGER REFERENCES cathegory (ID)
);

DROP TABLE
IF EXISTS team_member CASCADE;

CREATE TABLE team_member (
	team_id INTEGER REFERENCES team (ID),
	NAME VARCHAR (25) NOT NULL
);

DROP TABLE
IF EXISTS control_point CASCADE;

CREATE TABLE control_point (
	ID INTEGER PRIMARY KEY,
	address TEXT NOT NULL,
	legend TEXT NULL,
	cathegory_id INTEGER REFERENCES cathegory (ID)
);

DROP TABLE
IF EXISTS volunteer CASCADE;

CREATE TABLE volunteer (
	first_name VARCHAR (25) NOT NULL,
	second_name VARCHAR (25) NOT NULL,
	control_point_id INTEGER REFERENCES control_point (ID)
);

DROP TABLE
IF EXISTS visited_control_point CASCADE;

CREATE TABLE visited_control_point (
	visit_time TIME NOT NULL,
	control_point_id INTEGER REFERENCES control_point (ID),
	team_id INTEGER REFERENCES team (ID),
	UNIQUE (team_id, control_point_id) --don't visit same control point twice!
);

DROP TABLE
IF EXISTS team_start_schedule CASCADE;

CREATE TABLE team_start_schedule (
	team_id INTEGER REFERENCES team (ID) UNIQUE,
	cathegory_id INT NOT NULL REFERENCES cathegory (ID),
	start_time TIME NOT NULL,
	finish_time TIME NOT NULL,
	UNIQUE (cathegory_id, start_time)
);

