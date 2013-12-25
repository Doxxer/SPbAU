-- Хранимая процедура*
-- Напишите триггер, проверяющий ограничение “число зарегистрированных команд не  превышает максимально возможного в данной категории”
-- и отвергающий изменения, если ограничение нарушено

CREATE TRIGGER "check_max_members" BEFORE INSERT
ON team
EXECUTE PROCEDURE sp_check_max()

-- Сама процедура:
CREATE FUNCTION sp_check_max() RETURNS TRIGGER AS $$
BEGIN
	IF EXISTS (SELECT cat."id"
		FROM cathegory cat
		INNER JOIN 
			(
				SELECT cathegory_id AS cat, COUNT(team."id") AS cnt
				FROM team
				GROUP BY cathegory_id
			) t_cnt ON (t_cnt.cat = cat."id")
		WHERE cat.max_members < t_cnt.cnt)
	THEN RETURN NEW;
	END IF;
	RETURN NULL;
END
$$ LANGUAGE plpgsql;