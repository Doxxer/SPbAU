/* SP */
/*У вас в неком южноамериканском порту K лежит некий груз кофе ­­ X тонн.
У вас есть два покупателя A и B.
Покупатель A согласен приехать за кофе в европейский порт L, а покупатель B согласен приехать в порт M.
Посчитайте, кому из них выгоднее везти ваш кофе и на каком корабле. */

DROP FUNCTION CalculateProfit(VARCHAR(200), INT, VARCHAR(200), VARCHAR(200), VARCHAR(200), VARCHAR(200));

CREATE FUNCTION CalculateProfit(VARCHAR(200), INT, VARCHAR(200), VARCHAR(200), VARCHAR(200), VARCHAR(200)) RETURNS SETOF TEXT AS $$
-- ALIASES
DECLARE k_american_port ALIAS FOR $1;
DECLARE x_my_coffee ALIAS FOR $2;
DECLARE a_customer1 ALIAS FOR $3;
DECLARE b_customer2 ALIAS FOR $4;
DECLARE l_customer1_port ALIAS FOR $5;
DECLARE m_customer2_port ALIAS FOR $6;

-- LOCAL VARIABLES
DECLARE maximal_profit INT; -- maximal profit, query 1
DECLARE best record; -- best records in query 2

BEGIN
    -- select max profit
    SELECT
        INTO maximal_profit MAX(cust."Price" * 1000 * x_my_coffee - sp."Price" * 1000)
    FROM
        "ShipmentPrice" sp INNER JOIN "Ship" ship ON (ship."ID" = sp."IDShip")
        INNER JOIN "AmericanPort" aport ON (aport."ID" = sp."IDAmericanPort")
        INNER JOIN "EuropeanPort" eport ON (eport."ID" = sp."IDEuropeanPort"),
        "Customer" cust
    WHERE
        aport."Name" = k_american_port
        AND ((eport."Name" = l_customer1_port AND cust."Name" = a_customer1)
            OR (eport."Name" = m_customer2_port AND cust."Name" = b_customer2))
        AND ship."Payload" >= x_my_coffee;
    
    -- select port and ship with that profit
FOR best IN
    SELECT
        eport."Name" AS port, ship."Name" AS ship, cust."Name" AS cust
    FROM
        "ShipmentPrice" sp
        INNER JOIN "AmericanPort" aport ON (aport."ID" = sp."IDAmericanPort")
        INNER JOIN "EuropeanPort" eport ON (eport."ID" = sp."IDEuropeanPort")
        INNER JOIN "Ship" ship ON (ship."ID" = sp."IDShip"),        
        "Customer" cust
    WHERE
        aport."Name" = k_american_port
        AND ((eport."Name" = l_customer1_port AND cust."Name" = a_customer1)
            OR (eport."Name" = m_customer2_port AND cust."Name" = b_customer2))
        AND ship."Payload" >= x_my_coffee
        AND (cust."Price" * 1000 * x_my_coffee - sp."Price" * 1000) = maximal_profit
LOOP
    RETURN NEXT 'Best port is ' || best.port || '. There is "' || best.cust || '" in the port. Also, order the "' || best.ship || '" ship. Your profit will be $' || maximal_profit;
END LOOP;

END;
$$ LANGUAGE plpgsql;


-- Пример. Параметры по порядку:
-- Американский порт Х (наш)
-- Сколько кофе лежит у нас в порту: X
-- Покупатель А (имя)
-- Покупатель B (имя)
-- Порт покупателя А (имя)
-- Порт покупателя B (имя)
SELECT CalculateProfit('Rio', 15, 'Tchibo', 'Nescafe', 'Lisbon', 'EuropeanPort2');