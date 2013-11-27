/* task 1 */
/* найти фамилии управляющих, которые заведуют плантациями, когда-либо поставлявшими кофе в заданный порт */
SELECT DISTINCT
    man."Name"
FROM
    "ShipmentToAmericanPort" sap
    INNER JOIN "Plantation" P ON (P."ID" = sap."IDPlantation")
    INNER JOIN "AmericanPort" port ON (port."ID" = P."IDAmericanPort")
    INNER JOIN "Manager" man ON (P."IDManager" = man."ID")
WHERE
    port."Name" = 'Rio';