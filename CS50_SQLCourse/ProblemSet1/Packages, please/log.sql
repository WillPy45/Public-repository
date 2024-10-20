-- *** The Lost Letter ***
--Según contenido revelado: '%Congratulatory letter%', se tiene coincidencia dentro de la tabla packages en la columna con PK: 384
--(PK) ID: 384, from_address_id: 432, to_address_id: 854
SELECT * FROM packages
WHERE "contents" LIKE '%Congratulatory letter%';


--Solicitamos direccion que encaje con from_address_id: 432
SELECT * FROM addresses
WHERE "ID" = 432;


--Solicitamos direccion que encaje con to_address_id: 854
SELECT * FROM addresses
WHERE "ID" = 854;


--Revelar datos de scans con ID: 384
SELECT * FROM scans WHERE ("package_id" = 384);


--Revelar nombre del conductor
SELECT * FROM drivers
WHERE "id" =
(
    SELECT "driver_id" FROM scans
    WHERE (
        "package_id" = 384
        AND
        "address_id" = 432
    )
);

-------------------------------------------------------------------------------------------------------------
-- *** The Devious Delivery ***
-- Direccion del remitente: No especificado, posiblemente nulo según el cliente.

/* Pista sobre contenido: Es el tipo de paquete que agregaría un poco más... Grazna a la hora del baño de alguien, si me entiendes.
R: Posiblemente un pato */


-- Obtener datos de cualquier columna con from_address_id NULL, en este caso tenemos 1 coincidencia
-- id 5098, contents: Duck debugger, from_address_id: NULL, to_address_id: 50
SELECT * FROM packages
WHERE "from_address_id" IS NULL;

--Obtener direccion de destino
SELECT * FROM addresses
WHERE "id" = (
    SELECT "to_address_id" FROM packages
    WHERE "from_address_id" IS NULL
);

--Obtener resultado de entrega
SELECT * FROM scans
WHERE (
    "package_id" =
    (
        SELECT "id" FROM packages
        WHERE "from_address_id" IS NULL
    )

);

-- Obtener tipo de direccion

SELECT * FROM addresses
WHERE "id" = (
    SELECT "address_id" FROM scans
    WHERE (
        "package_id" =
        (
            SELECT "id" FROM packages
            WHERE "from_address_id" IS NULL
        )

        AND

        "action" = 'Drop'
    )
);


---------------------------------------------------------------------------------------------
-- *** The Forgotten Gift ***

-- Datos del cliente
-- Entregado desde 109 Tileston Street
-- Dirigido a 728 Maple Place.


-- Obtener ID de direccion 109 Tileston Street
SELECT * FROM addresses WHERE "address" = '109 Tileston Street';

-- Obtener packages info segun FK from address id que coincida con PK de address
--Resultados:
-- Contents: Flowers | id: 9523 | from_address_id: 9873 | to_address_id: 4983


SELECT * FROM packages
WHERE "from_address_id" IN ( --Debe coincidir con direccion origen
    SELECT "id"
    FROM addresses
    WHERE "address" = '109 Tileston Street'
)

AND "to_address_id" IN ( --Debe coincidir con direccion de entrega
    SELECT "id"
    FROM addresses
    WHERE "address" = '728 Maple Place'
);






--Obtener estado del pedido.
-- Se ha recibido en address_id 9873, luego se dejó en address_id 7432 y se volvió a recoger de la misma
-- direccion unos días despues (pick of address id 7432)
--Estado de entrega: Posiblemente el conductor se haya quedado con la carga, no hay Drop (dejar) luego del Pick (agarrar)

SELECT * FROM scans
WHERE "package_id" IN (
    SELECT "id" FROM packages
WHERE "from_address_id" IN ( --Debe coincidir con direccion origen
    SELECT "id"
    FROM addresses
    WHERE "address" = '109 Tileston Street'
)

AND "to_address_id" IN ( --Debe coincidir con direccion de entrega
    SELECT "id"
    FROM addresses
    WHERE "address" = '728 Maple Place'
)
);



-- Obtener nombre de la última última persona que obtuvo el paquete (pick)
SELECT * FROM drivers
WHERE "id" IN (
    SELECT "driver_id" FROM scans
WHERE "package_id" IN (
    SELECT "id" FROM packages
WHERE "from_address_id" IN ( --Debe coincidir con direccion origen
    SELECT "id"
    FROM addresses
    WHERE "address" = '109 Tileston Street'
)

AND "to_address_id" IN ( --Debe coincidir con direccion de entrega
    SELECT "id"
    FROM addresses
    WHERE "address" = '728 Maple Place'
)


)
ORDER BY "timestamp" DESC LIMIT 1 -- Ordenamos según fecha para obtener nombre del último conductor resposable del paquete
);

/* Datos recolectados.
Contents: Flowers
From address name: 109 Tileston Street
To address name: 728 Maple Place
Delivery status: Not delivered
Driver: Mikel (Kept the package, communicate with him)
*/


