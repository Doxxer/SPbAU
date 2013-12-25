-- Найдите категорию с максимальным количеством зарегистрированных команд (если таковых несколько, то запрос должен вернуть все)

SELECT cat."name"
FROM
(
	SELECT cathegory_id AS cat, COUNT(team."id") AS cnt
	FROM team
	GROUP BY cathegory_id
) t1
INNER JOIN
(
	SELECT MAX(counts.cnt) AS c_max
	FROM 
	(
		SELECT cathegory_id AS cat, COUNT(team."id") AS cnt
		FROM team
		GROUP BY cathegory_id
	) counts
) t_max ON (t1.cnt = t_max.c_max)
INNER JOIN cathegory cat ON (cat."id" = t1.cat)