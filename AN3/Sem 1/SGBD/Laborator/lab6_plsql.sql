--1
CREATE OR REPLACE TRIGGER trig1_***
      BEFORE INSERT OR UPDATE OR DELETE ON emp_***
BEGIN
 IF (TO_CHAR(SYSDATE,'D') = 1) 
     OR (TO_CHAR(SYSDATE,'HH24') NOT BETWEEN 8 AND 20)
 THEN
    RAISE_APPLICATION_ERROR(-20001,'tabelul nu poate fi actualizat');
 END IF;
END;
/

DROP TRIGGER trig1_***;

--2
--Varianta 1
CREATE OR REPLACE TRIGGER trig21_***
  BEFORE UPDATE OF salary ON emp_***
  FOR EACH ROW
BEGIN
  IF (:NEW.salary < :OLD.salary) THEN 
     RAISE_APPLICATION_ERROR(-20002,'salariul nu poate fi micsorat');
  END IF;
END;
/

UPDATE emp_***
SET    salary = salary-100;

DROP TRIGGER trig21_***;

--Varianta 2
CREATE OR REPLACE TRIGGER trig22_***
  BEFORE UPDATE OF salary ON emp_***
  FOR EACH ROW
  WHEN (NEW.salary < OLD.salary)
BEGIN
  RAISE_APPLICATION_ERROR(-20002,'salariul nu poate fi micsorat');
END;
/

UPDATE emp_***
SET    salary = salary-100;
DROP TRIGGER trig22_***;

--3
CREATE OR REPLACE TRIGGER trig3_***
  BEFORE UPDATE OF lowest_sal, highest_sal ON job_grades_***
  FOR EACH ROW
DECLARE
  v_min_sal  emp_***.salary%TYPE;
     v_max_sal  emp_***.salary%TYPE;
  exceptie EXCEPTION;
BEGIN
  SELECT MIN(salary), MAX(salary)
  INTO   v_min_sal,v_max_sal
  FROM   emp_***;
  IF (:OLD.grade_level=1) AND  (v_min_sal< :NEW.lowest_sal) 
     THEN RAISE exceptie;
  END IF;
  IF (:OLD.grade_level=7) AND  (v_max_sal> :NEW.highest_sal) 
     THEN RAISE exceptie;
  END IF;
EXCEPTION
  WHEN exceptie THEN
    RAISE_APPLICATION_ERROR (-20003, 'Exista salarii care se gasesc in afara intervalului'); 
END;
/

UPDATE job_grades_*** 
SET    lowest_sal =3000
WHERE  grade_level=1;

UPDATE job_grades_***
SET    highest_sal =20000
WHERE  grade_level=7;

DROP TRIGGER trig3_***;

--4
CREATE OR REPLACE PROCEDURE modific_plati_***
          (v_codd  info_dept_***.id%TYPE,
           v_plati info_dept_***.plati%TYPE) AS
BEGIN
  UPDATE  info_dept_***
  SET     plati = NVL (plati, 0) + v_plati
  WHERE   id = v_codd;
END;
/

CREATE OR REPLACE TRIGGER trig4_***
  AFTER DELETE OR UPDATE  OR  INSERT OF salary ON emp_***
  FOR EACH ROW
BEGIN
  IF DELETING THEN 
     -- se sterge un angajat
     modific_plati_*** (:OLD.department_id, -1*:OLD.salary);
  ELSIF UPDATING THEN 
    --se modifica salariul unui angajat
    modific_plati_***(:OLD.department_id,:NEW.salary-:OLD.salary);  
  ELSE 
    -- se introduce un nou angajat
    modific_plati_***(:NEW.department_id, :NEW.salary);
  END IF;
END;
/

SELECT * FROM  info_dept_*** WHERE id=90;

INSERT INTO emp_*** (employee_id, last_name, email, hire_date, 
                     job_id, salary, department_id) 
VALUES (300, 'N1', 'n1@g.com',sysdate, 'SA_REP', 2000, 90);

SELECT * FROM  info_dept_*** WHERE id=90;

UPDATE emp_***
SET    salary = salary + 1000
WHERE  employee_id=300;

SELECT * FROM  info_dept_*** WHERE id=90;

DELETE FROM emp_***
WHERE  employee_id=300;   

SELECT * FROM  info_dept_*** WHERE id=90;

DROP TRIGGER trig4_***;

--5
CREATE OR REPLACE VIEW v_info_*** AS
  SELECT e.id, e.nume, e.prenume, e.salariu, e.id_dept, 
         d.nume_dept, d.plati 
  FROM   info_emp_*** e, info_dept_*** d
  WHERE  e.id_dept = d.id;

SELECT *
FROM   user_updatable_columns
WHERE  table_name = UPPER('v_info_***');

CREATE OR REPLACE TRIGGER trig5_***
    INSTEAD OF INSERT OR DELETE OR UPDATE ON v_info_***
    FOR EACH ROW
BEGIN
IF INSERTING THEN 
    -- inserarea in vizualizare determina inserarea 
    -- in info_emp_*** si reactualizarea in info_dept_***
    -- se presupune ca departamentul exista
   INSERT INTO info_emp_*** 
   VALUES (:NEW.id, :NEW.nume, :NEW.prenume, :NEW.salariu,
           :NEW.id_dept);
     
   UPDATE info_dept_***
   SET    plati = plati + :NEW.salariu
   WHERE  id = :NEW.id_dept;

ELSIF DELETING THEN
   -- stergerea unui salariat din vizualizare determina
   -- stergerea din info_emp_*** si reactualizarea in
   -- info_dept_***
   DELETE FROM info_emp_***
   WHERE  id = :OLD.id;
     
   UPDATE info_dept_***
   SET    plati = plati - :OLD.salariu
   WHERE  id = :OLD.id_dept;

ELSIF UPDATING ('salariu') THEN
   /* modificarea unui salariu din vizualizare determina 
      modificarea salariului in info_emp_*** si reactualizarea
      in info_dept_***    */
    	
   UPDATE  info_emp_***
   SET     salariu = :NEW.salariu
   WHERE   id = :OLD.id;
    	
   UPDATE info_dept_***
   SET    plati = plati - :OLD.salariu + :NEW.salariu
   WHERE  id = :OLD.id_dept;

ELSIF UPDATING ('id_dept') THEN
    /* modificarea unui cod de departament din vizualizare
       determina modificarea codului in info_emp_*** 
       si reactualizarea in info_dept_***  */  
    UPDATE info_emp_***
    SET    id_dept = :NEW.id_dept
    WHERE  id = :OLD.id;
    
    UPDATE info_dept_***
    SET    plati = plati - :OLD.salariu
    WHERE  id = :OLD.id_dept;
    	
    UPDATE info_dept_***
    SET    plati = plati + :NEW.salariu
    WHERE  id = :NEW.id_dept;
  END IF;
END;
/

SELECT *
FROM   user_updatable_columns
WHERE  table_name = UPPER('v_info_***');

-- adaugarea unui nou angajat
SELECT * FROM  info_dept_*** WHERE id=10;

INSERT INTO v_info_*** 
VALUES (400, 'N1', 'P1', 3000,10, 'Nume dept', 0);

SELECT * FROM  info_emp_*** WHERE id=400;
SELECT * FROM  info_dept_*** WHERE id=10;

-- modificarea salariului unui angajat
UPDATE v_info_***
SET    salariu=salariu + 1000
WHERE  id=400;

SELECT * FROM  info_emp_*** WHERE id=400;
SELECT * FROM  info_dept_*** WHERE id=10;

-- modificarea departamentului unui angajat
SELECT * FROM  info_dept_*** WHERE id=90;

UPDATE v_info_***
SET    id_dept=90
WHERE  id=400;

SELECT * FROM  info_emp_*** WHERE id=400;
SELECT * FROM  info_dept_*** WHERE id IN (10,90);

-- eliminarea unui angajat
DELETE FROM v_info_*** WHERE id = 400;
SELECT * FROM  info_emp_*** WHERE id=400;
SELECT * FROM  info_dept_*** WHERE id = 90;

DROP TRIGGER trig5_***;

--6 
CREATE OR REPLACE TRIGGER trig6_***
  BEFORE DELETE ON emp_***
 BEGIN
  IF USER= UPPER('grupa***') THEN
     RAISE_APPLICATION_ERROR(-20900,'Nu ai voie sa stergi!');
  END IF;
 END;
/

DROP TRIGGER trig6_***;

--7
CREATE TABLE audit_***
   (utilizator     VARCHAR2(30),
    nume_bd        VARCHAR2(50),
    eveniment      VARCHAR2(20),
    nume_obiect    VARCHAR2(30),
    data           DATE);
CREATE OR REPLACE TRIGGER trig7_***
  AFTER CREATE OR DROP OR ALTER ON SCHEMA
BEGIN
  INSERT INTO audit_***
  VALUES (SYS.LOGIN_USER, SYS.DATABASE_NAME, SYS.SYSEVENT, 
          SYS.DICTIONARY_OBJ_NAME, SYSDATE);
END;
/

CREATE INDEX ind_*** ON info_emp_***(nume);
DROP INDEX ind_***;
SELECT * FROM audit_***;

DROP TRIGGER trig7_***;

--8
CREATE OR REPLACE PACKAGE pachet_***
AS
	smin emp_***.salary%type;
	smax emp_***.salary%type;
	smed emp_***.salary%type;
END pachet_***;
/

CREATE OR REPLACE TRIGGER trig81_***
BEFORE UPDATE OF salary ON emp_***
BEGIN
  SELECT MIN(salary),AVG(salary),MAX(salary)
  INTO pachet_***.smin, pachet_***.smed, pachet_***.smax
  FROM emp_***;
END;
/

CREATE OR REPLACE TRIGGER trig82_***
BEFORE UPDATE OF salary ON emp_***
FOR EACH ROW
BEGIN
IF(:OLD.salary=pachet_***.smin)AND (:NEW.salary>pachet_***.smed) 
 THEN
   RAISE_APPLICATION_ERROR(-20001,'Acest salariu depaseste valoarea medie');
ELSIF (:OLD.salary= pachet_***.smax) 
       AND (:NEW.salary<  pachet_***.smed) 
 THEN
   RAISE_APPLICATION_ERROR(-20001,'Acest salariu este sub valoarea medie');
END IF;
END;
/

SELECT AVG(salary)
FROM   emp_***;

UPDATE emp_*** 
SET    salary=10000 
WHERE  salary=(SELECT MIN(salary) FROM emp_***);

UPDATE emp_*** 
SET    salary=1000 
WHERE  salary=(SELECT MAX(salary) FROM emp_***);

DROP TRIGGER trig81_***;
DROP TRIGGER trig82_***;
