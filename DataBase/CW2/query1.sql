-- Найдите все команды, взявшие КП номер 42

SELECT DISTINCT t."id", t.title
FROM
	visited_control_point vcp
	INNER JOIN team t ON t."id" = vcp.team_id
WHERE vcp.control_point_id = 42