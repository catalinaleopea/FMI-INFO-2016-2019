--1
CREATE OR REPLACE PROCEDURE sterg_*** (tabel VARCHAR2) IS
BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE ' || tabel;
END;
/

CREATE TABLE tab_*** (col number(4));
EXECUTE sterg_***('tab_***');

--2
CREATE OR REPLACE FUNCTION numar_*** (val NUMBER)
  RETURN NUMBER AS
  sir VARCHAR2(500);
  rezultat  NUMBER;
BEGIN
  sir :=   'SELECT COUNT(*) FROM employees ' || 'WHERE salary >= :x';

  EXECUTE IMMEDIATE sir
        INTO  rezultat
        USING val;
  RETURN rezultat;
END;
/

--3
DECLARE
     sir     VARCHAR2(50);
     bloc  VARCHAR2(500);
BEGIN
  -- creare tabel
  EXECUTE IMMEDIATE
    'CREATE TABLE tab_*** (col VARCHAR2(15))';
  --inserare in tabel  
  FOR i IN 1..10 LOOP
    sir :=  'INSERT INTO tab_*** VALUES (''Contor ' || i || ''')';
    EXECUTE IMMEDIATE sir;
  END LOOP;
  -- tiparire continut tabel 
  bloc :=  'BEGIN
                FOR i IN (SELECT * FROM tab_***) LOOP
                        DBMS_OUTPUT.PUT_LINE (i.col);
                END LOOP;
                END;';
 EXECUTE IMMEDIATE bloc;
  -- stergere tabel
  EXECUTE IMMEDIATE 'DROP TABLE tab_***';
END;
/

--4
CREATE OR REPLACE PACKAGE pachet_*** AS
  	TYPE refcursor  IS REF CURSOR;
  	FUNCTION f1 (sir VARCHAR2) RETURN refcursor;
  	FUNCTION f2 (sir VARCHAR2)  RETURN refcursor;
END pachet_***;
/
CREATE OR REPLACE PACKAGE BODY pachet_*** AS
      FUNCTION f1 (sir VARCHAR2)  RETURN refcursor   IS
                rez  refcursor;
               comanda   VARCHAR2(500);
      BEGIN

          comanda := 'SELECT * FROM employees ' || sir;
          OPEN rez  FOR comanda;
          RETURN rez;
      END;
FUNCTION f2 (sir VARCHAR2) RETURN refcursor IS
              rez  refcursor; 
              comanda   VARCHAR2(500);
      BEGIN
               comanda := 'SELECT * FROM employees WHERE  job_id  = :j';
              OPEN rez FOR comanda USING sir;
              RETURN rez;
      END;
END pachet_***;
/ 
DECLARE
    v_emp     employees%ROWTYPE;
    v_cursor  pachet_***.refcursor;
BEGIN
  -- deschide cursor 
  v_cursor :=  pachet_***.f1 ('WHERE salary >10000');
  -- parcurge cursor si tipareste rezultate
  LOOP
    FETCH v_cursor INTO v_emp;
    EXIT WHEN v_cursor%NOTFOUND;
    DBMS_OUTPUT.PUT_LINE(v_emp.last_name|| ' ' ||v_emp.salary);
  END LOOP;
  CLOSE v_cursor;
  
  DBMS_OUTPUT.PUT_LINE ('*************************************');
  -- deschide cursor 
  v_cursor :=  pachet_***.f2 ('SA_MAN');
   -- parcurge cursor si tipareste rezultate
  LOOP
       FETCH v_cursor INTO v_emp;
       EXIT WHEN v_cursor%NOTFOUND;
       DBMS_OUTPUT.PUT_LINE (v_emp.last_name|| ' ' ||v_emp.job_id);
  END LOOP;
  CLOSE v_cursor;
END;
/

--5
DECLARE
     TYPE  refc IS REF CURSOR;
     TYPE  t_cod IS TABLE OF NUMBER;
     TYPE  t_nume IS TABLE OF VARCHAR2(50);
     cursor_dept  refc;
     cod  t_cod;
     nume  t_nume;
BEGIN

       DBMS_OUTPUT.PUT_LINE ('********* Varianta 1 *******');
       OPEN cursor_dept FOR 'SELECT department_id, department_name FROM departments';
       FETCH cursor_dept BULK COLLECT INTO cod, nume;    
       CLOSE cursor_dept;
       FOR i IN cod.FIRST..cod.LAST LOOP
                  DBMS_OUTPUT.PUT_LINE (cod(i)|| ' ' || nume(i));
        END LOOP;
        
        DBMS_OUTPUT.PUT_LINE ('********* Varianta 2 *******');
        
        EXECUTE IMMEDIATE 'SELECT department_id, department_name FROM departments '
        BULK COLLECT INTO cod, nume;
        FOR i IN cod.FIRST..cod.LAST LOOP
                 DBMS_OUTPUT.PUT_LINE (cod(i)|| ' ' || nume(i));
        END LOOP;
END;
/

--6 
--Exemplul 1
DECLARE
        TYPE tablou IS TABLE OF VARCHAR2(60);
        v_tab    tablou;
        valoare    NUMBER := 1000;
        comanda VARCHAR2(200);
BEGIN
        comanda := 'UPDATE emp_***  SET salary = salary + :a WHERE job_id=''SA_MAN''
                             RETURNING last_name INTO :b';
        EXECUTE IMMEDIATE comanda
        USING valoare RETURNING BULK COLLECT INTO v_tab;
        FOR i IN v_tab.FIRST.. v_tab.LAST LOOP
                 DBMS_OUTPUT.PUT_LINE (v_tab (i));
        END LOOP;
END;
/

--Exemplul 2
DECLARE
     TYPE  t_nr  IS TABLE OF NUMBER;
     TYPE  t_nume  IS TABLE OF VARCHAR2(30);
     nr  t_nr;
     nume  t_nume;
BEGIN
     nr := t_nr(110, 120, 130, 140, 150);
  FORALL i IN 1..5
    EXECUTE IMMEDIATE
       'UPDATE emp_***  SET salary = salary*1.1
        WHERE  employee_id = :1

         RETURNING last_name INTO :2'
     USING nr(i) RETURNING BULK COLLECT INTO nume;
    FOR i IN nume.FIRST..nume.LAST LOOP
                 DBMS_OUTPUT.PUT_LINE (nume (i));
        END LOOP;
END;
/
