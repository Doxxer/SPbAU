-- Представление
-- В соревнованиях побеждает команда, взявшая больше всех КП.
-- Если несколько команд взяли одинаковое число КП то лучшей считается та, которая потратила меньше времени.
-- Сделайте представление, показывающее тройку призеров в каждой категории.

DROP VIEW IF EXISTS Winners;

CREATE VIEW Winners AS
SELECT cat."name", tm.title
FROM cathegory cat
INNER JOIN
(
SELECT cp_cnt."id", cp_cnt.cathegory_id, cp_cnt.cpcnt, temp_time.ttime,
	RANK() OVER (PARTITION BY cp_cnt."id", cp_cnt.cathegory_id ORDER BY cp_cnt.cpcnt DESC, temp_time.ttime DESC)  AS rang
FROM
(
	SELECT team."id", team.cathegory_id, COUNT(vcp.control_point_id) AS cpcnt
	FROM team
	INNER JOIN visited_control_point vcp ON (vcp.team_id = team."id")
	GROUP BY team."id", team.cathegory_id
) cp_cnt
INNER JOIN
(
	SELECT shed.team_id, shed.cathegory_id, shed.finish_time - shed.start_time AS ttime
	FROM team_start_schedule shed
	WHERE shed.finish_time > shed.start_time
) temp_time ON (cp_cnt."id" = temp_time.team_id AND cp_cnt.cathegory_id = temp_time.cathegory_id)
) res ON (cat."id" = res.cathegory_id AND res.rang <= 3)
INNER JOIN team tm ON (tm."id" = res."id")