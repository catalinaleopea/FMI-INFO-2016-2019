-- 2a
CREATE OR REPLACE TYPE t_actori IS TABLE OF
    VARCHAR2(100);
/

ALTER TABLE spectacol
ADD lista_actori t_actori
NESTED TABLE lista_actori STORE AS t_lista_actori;

DECLARE
    lista t_actori := t_actori();
BEGIN
    FOR spect IN (SELECT id_spectacol id
                  FROM spectacol) LOOP
        SELECT a.nume || ' ' || a.prenume
        BULK COLLECT INTO lista
        FROM joaca j JOIN actor a ON (j.cod_actor = a.id_actor)
        WHERE cod_spectacol = spect.id;
        
        IF lista.EXISTS(1) THEN
            UPDATE spectacol
            SET lista_actori = lista
            WHERE id_spectacol = spect.id;
        END IF;
    END LOOP;
END;
/

SELECT * FROM spectacol;

ALTER TABLE spectacol
DROP COLUMN lista_actori;

-- 3
CREATE OR REPLACE PROCEDURE info_spectacole_OCO(nume_dat actor.nume%TYPE)
AS
    TYPE nume_actori IS VARRAY(100) OF
        actor.nume%TYPE;
    lista_nume_actori nume_actori := nume_actori();
    valoare_totala NUMBER(5);
BEGIN
    FOR spect IN (SELECT s.id_spectacol, s.denumire, j.rol, a.id_actor
                  FROM spectacol s JOIN joaca j ON (s.id_spectacol = j.cod_spectacol)
                                   JOIN actor a ON (j.cod_actor = a.id_actor)
                  WHERE nume = nume_dat) LOOP
        DBMS_OUTPUT.PUT_LINE(spect.denumire);
        SELECT a.nume
        BULK COLLECT INTO lista_nume_actori
        FROM actor a JOIN joaca j ON (a.id_actor = j.cod_actor)
        WHERE j.rol = spect.rol AND a.id_actor != spect.id_actor;
        
        IF lista_nume_actori.EXISTS(1) THEN
            FOR i IN lista_nume_actori.FIRST..lista_nume_actori.LAST LOOP
                DBMS_OUTPUT.PUT_LINE(lista_nume_actori(i));
            END LOOP;
            ELSE DBMS_OUTPUT.PUT_LINE('Nu exista alti actori cu acelasi rol'); 
        END IF;
        
        SELECT SUM(pret)
        INTO valoare_totala
        FROM bilet_vandut
        WHERE cod_spectacol = spect.id_spectacol;
        DBMS_OUTPUT.PUT_LINE('Valoare totala = ' || valoare_totala);
    END LOOP;
END;
/
BEGIN 
    info_spectacole_OCO('Popescu');
END;
/

-- 4
CREATE OR REPLACE FUNCTION top_spectacol (an_dat NUMBER)
    RETURN spectacol.denumire%TYPE
AS
    denumire_spectacol spectacol.denumire%TYPE;
    maxim NUMBER(5);
    
BEGIN
    SELECT MAX(COUNT(id_bilet))
    INTO maxim
    FROM bilet_vandut b JOIN spectacol s ON (b.cod_spectacol = s.id_spectacol)
    WHERE TO_NUMBER(TO_CHAR(data_spectacol, 'YYYY'))=an_dat
    GROUP BY cod_spectacol, denumire;
    
    SELECT denumire
    INTO denumire_spectacol
    FROM (SELECT COUNT(id_bilet) numar, s.denumire
          FROM bilet_vandut b JOIN spectacol s ON (b.cod_spectacol = s.id_spectacol)
          WHERE TO_NUMBER(TO_CHAR(data_spectacol, 'YYYY'))=an_dat
          GROUP BY cod_spectacol, denumire)
    WHERE numar = maxim;
    
    RETURN denumire_spectacol;
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        DBMS_OUTPUT.PUT_LINE('Nu exista spectacole in acel an');
    WHEN TOO_MANY_ROWS THEN
        DBMS_OUTPUT.PUT_LINE('Exista mai multe spectacole care au vandut acelasi numar maxim de bilete in anul dat');
END;
/
BEGIN
    DBMS_OUTPUT.PUT_LINE(top_spectacol(2020));
END;
/

-- 5
SELECT * FROM actor;
SELECT * FROM sala;
SELECT * FROM spectacol;
SELECT * FROM bilet_vandut;
CREATE OR REPLACE TRIGGER trig_OCO
    BEFORE INSERT ON bilet_vandut
    FOR EACH ROW
DECLARE
    numar_locuri_ocupate NUMBER(5);
    numar_locuri_sala NUMBER(5);
BEGIN
    SELECT COUNT(id_bilet)
    INTO numar_locuri_ocupate
    FROM bilet_vandut
    WHERE cod_spectacol = :NEW.cod_spectacol AND data_spectacol = :NEW.data_spectacol;
    
    SELECT numar_locuri
    INTO numar_locuri_sala
    FROM sala s JOIN spectacol sp ON (sp.cod_sala = s.id_sala)
    WHERE sp.id_spectacol = :NEW.cod_spectacol;
    
    IF numar_locuri_ocupate + 1 > numar_locuri_sala
        THEN RAISE_APPLICATION_ERROR(-20001, 'Locuri insuficiente');
    END IF;
END;
/
INSERT INTO bilet_vandut
VALUES (100, 80, 1, TO_DATE('10-APR-2020'), 1, 15);