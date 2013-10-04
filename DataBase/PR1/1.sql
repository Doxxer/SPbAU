-- страны по убыванию отношения площади на человека
SELECT c.surfacearea/c.population as RRR, *
FROM country c
where c.population != 0
ORDER BY (c.surfacearea/c.population) DESC