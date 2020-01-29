--1
DECLARE 
  v NUMBER;
  CURSOR c IS
      SELECT employee_id FROM employees;
BEGIN

 -- no data found
SELECT employee_id 
INTO v
FROM employees
WHERE 1=0;
-- too many rows
SELECT employee_id
INTO v
FROM employees;
  -- invalid number
SELECT employee_id
INTO v
FROM employees;
WHERE 2='s';
  -- when others
 v := 's';
  -- cursor already open
  open c;
  open c;
EXCEPTION
 WHEN NO_DATA_FOUND THEN 
    DBMS_OUTPUT.PUT_LINE (' no data found: ' ||SQLCODE || ' - ' || SQLERRM);
 WHEN TOO_MANY_ROWS THEN 
    DBMS_OUTPUT.PUT_LINE (' too many rows:  ' ||SQLCODE || ' - ' || SQLERRM);
 WHEN INVALID_NUMBER THEN 
    DBMS_OUTPUT.PUT_LINE (' invalid number: ' ||SQLCODE || ' - ' || SQLERRM);
 WHEN CURSOR_ALREADY_OPEN THEN
    DBMS_OUTPUT.PUT_LINE (' cursor already open: ' ||SQLCODE || ' - ' || SQLERRM);
 WHEN OTHERS THEN 
    DBMS_OUTPUT.PUT_LINE (SQLCODE || ' - ' || SQLERRM);
 END;
/

--2

CREATE TABLE error_***
(cod    NUMBER,
 mesaj  VARCHAR2(100));


--Varianta 1 

DECLARE
  v_cod       NUMBER;
  v_mesaj     VARCHAR2(100);
  x           NUMBER;
  exceptie    EXCEPTION;

BEGIN
 x:=1;
 IF x=1 THEN RAISE exceptie;
 ELSE 
     x:=x/(x-1);
 END IF;
EXCEPTION
 WHEN exceptie THEN    
      v_cod := -20001;
      v_mesaj := 'x=1 determina o impartire la 0';
      INSERT  INTO error_***
      VALUES  (v_cod, v_mesaj);
 END;
/

SELECT *
FROM error_***;

--Varianta 2

DECLARE
  v_cod        NUMBER;
  v_mesaj      VARCHAR2(100);
  x            NUMBER;
BEGIN
 x:=1;
 x:=x/(x-1);
EXCEPTION
WHEN  ZERO_DIVIDE THEN    
      v_cod := SQLCODE;
      v_mesaj := SUBSTR(SQLERRM,1,100); 
      -- mesajul erorii are dimensiune 512
      INSERT  INTO error_***
      VALUES  (v_cod, v_mesaj);
END;
/

SELECT *
FROM error_***;
ROLLBACK;

--3
ACCEPT p_loc PROMPT 'Dati locatia: '

DECLARE
  v_loc      dept_***.location_id%TYPE:= &p_loc;
  v_nume     dept_***.department_name%TYPE;
BEGIN
  SELECT   department_name
  INTO     v_nume
  FROM     dept_***
  WHERE    location_id = v_loc;
  DBMS_OUTPUT.PUT_LINE('In locatia '|| v_loc ||
           ' functioneaza departamentul '||v_nume);
EXCEPTION
  WHEN NO_DATA_FOUND THEN
     INSERT   INTO error_*** 
     VALUES  ( -20002, 'nu exista departamente in locatia data');
     DBMS_OUTPUT.PUT_LINE('a aparut o exceptie ');
  WHEN TOO_MANY_ROWS THEN
     INSERT   INTO error_***
     VALUES   (-20003, 
                'exista mai multe departamente in locatia data');
     DBMS_OUTPUT.PUT_LINE('a aparut o exceptie ');
  WHEN OTHERS THEN
INSERT   INTO error_*** (mesaj)
VALUES   ('au aparut alte erori');
END;
/

--4

ALTER TABLE dept_***
ADD CONSTRAINT c_pr_*** PRIMARY KEY(department_id);

ALTER TABLE emp_***
ADD CONSTRAINT c_ex_*** FOREIGN KEY (department_id) 
    REFERENCES dept_***;

DELETE FROM dept_***
WHERE department_id=10;  --apare eroarea sistem -02292

SET SERVEROUTPUT ON
SET VERIFY OFF
ACCEPT p_cod PROMPT 'Dati un cod de departament ' 
DECLARE
  exceptie  EXCEPTION;
  PRAGMA EXCEPTION_INIT(exceptie,-02292); 
  --   exceptia nu are un nume predefinit, 
       cu PRAGMA EXCEPTION_INIT asociez erorii avand 
  --   codul -02292 un nume
BEGIN
  DELETE FROM dept_***
  WHERE department_id = &p_cod;
EXCEPTION
  WHEN exceptie THEN
    DBMS_OUTPUT.PUT_LINE ('nu puteti sterge un departament in care lucreaza salariati');
END;
/

--5
ACCEPT p_val PROMPT 'Dati valoarea: '
DECLARE
  v_val          NUMBER := &p_val;
  v_numar     NUMBER(7);
  exceptie      EXCEPTION;
BEGIN
  SELECT  COUNT(*)
  INTO    v_numar
  FROM    emp_***
  WHERE   (salary+salary*NVL(commission_pct,0))*12>v_val;
  IF v_numar = 0 THEN
     RAISE  exceptie;
  ELSE 
     DBMS_OUTPUT.PUT_LINE('NR de angajati este '||v_numar);
  END IF;

EXCEPTION
  WHEN exceptie THEN
    DBMS_OUTPUT.PUT_LINE('Nu exista angajati pentru care sa se indeplineasca aceasta conditie');

  WHEN OTHERS THEN
    DBMS_OUTPUT.PUT_LINE('Alta eroare');
END;
/

--6
ACCEPT p_cod PROMPT 'Dati codul: '
DECLARE
  v_cod          NUMBER := &p_cod;
BEGIN
UPDATE  emp_***
SET     salary=salary+1000
WHERE   employee_id=v_cod;
IF SQL%NOTFOUND THEN
  RAISE_APPLICATION_ERROR(-20999,'salariatul nu exista');
END IF;
END;
/

--7
ACCEPT p_cod PROMPT 'Dati codul: '
DECLARE
  v_cod    NUMBER := &p_cod;
  v_nume   emp_***.last_name%TYPE;
  v_sal    emp_***.salary%TYPE;
BEGIN  
  SELECT last_name,salary
  INTO   v_nume,v_sal
  FROM   emp_***
  WHERE  employee_id=v_cod;
  DBMS_OUTPUT.PUT_LINE(v_nume||' '||v_sal);
EXCEPTION
  WHEN NO_DATA_FOUND THEN
    RAISE_APPLICATION_ERROR(-20999, 'salariatul nu exista');
END;
/

--8

--Varianta 1 – fiecare comanda are un numar de ordine

DECLARE
  v_localizare  NUMBER(1):=1;
  v_nume  emp_***.last_name%TYPE;
  v_sal    emp_***.salary%TYPE;
  v_job    emp_***.job_id%TYPE;

BEGIN  
v_localizare:=1;
SELECT last_name
INTO   v_nume
FROM   emp_***
WHERE  employee_id=200;
DBMS_OUTPUT.PUT_LINE(v_nume);

v_localizare:=2;
SELECT salary
INTO   v_sal
FROM   emp_***
WHERE  employee_id=455;
DBMS_OUTPUT.PUT_LINE(v_sal);

v_localizare:=3;
SELECT job_id
INTO   v_job
FROM   emp_***
WHERE  employee_id=200;
DBMS_OUTPUT.PUT_LINE(v_job);
EXCEPTION
  WHEN NO_DATA_FOUND THEN
    DBMS_OUTPUT.PUT_LINE('comanda SELECT ' || v_localizare || ' nu returneaza nimic');
END;
/


--Varianta 2 – fiecare comanda este inclusa într-un subbloc

DECLARE
  v_localizare  NUMBER(1):=1;
  v_nume  emp_***.last_name%TYPE;
  v_sal    emp_***.salary%TYPE;
  v_job    emp_***.job_id%TYPE;
BEGIN  


  BEGIN
    SELECT last_name
    INTO   v_nume
    FROM   emp_***
    WHERE  employee_id=200;
     DBMS_OUTPUT.PUT_LINE(v_nume);
  EXCEPTION
    WHEN NO_DATA_FOUND THEN
      DBMS_OUTPUT.PUT_LINE('comanda SELECT1 nu returneaza nimic');
  END;
 
  BEGIN
    SELECT salary
    INTO   v_sal
    FROM   emp_***
    WHERE  employee_id=455;
    DBMS_OUTPUT.PUT_LINE('v_sal');
  EXCEPTION
    WHEN NO_DATA_FOUND THEN
      DBMS_OUTPUT.PUT_LINE('comanda SELECT2 nu returneaza nimic');
  END;

  BEGIN
SELECT job_id
INTO   v_job
FROM   emp_***
WHERE  employee_id=200;
DBMS_OUTPUT.PUT_LINE(v_job);
  EXCEPTION
    WHEN NO_DATA_FOUND THEN
      DBMS_OUTPUT.PUT_LINE('comanda SELECT3 nu returneaza nimic');
  END;

END;
/


--9
DECLARE
  v_comm  NUMBER(4);
BEGIN
  SELECT ROUND(salary*NVL(commission_pct,0))
  INTO   v_comm
  FROM   emp_***
  WHERE  employee_id=455;
<<eticheta>>
  UPDATE  emp_*** 
  SET     salary=salary+v_comm
  WHERE employee_id=200;

EXCEPTION
  WHEN NO_DATA_FOUND THEN 
    v_comm:=5000;
    GOTO eticheta; 
END;
/

--10
DECLARE
  v_comm_val  NUMBER(4);
  v_comm      emp_***.commission_pct%TYPE;
BEGIN
  SELECT NVL(commission_pct,0),
         ROUND(salary*NVL(commission_pct,0))
  INTO   v_comm, v_comm_val
  FROM   emp_***
  WHERE employee_id=200;
  IF v_comm=0 
   THEN 
     GOTO eticheta;
   ELSE 
     UPDATE emp_*** 
     SET salary=salary+ v_comm_val
     WHERE employee_id=200;
  END IF;
<<eticheta>>
   --DBMS_OUTPUT.PUT_LINE('este ok!');
EXCEPTION
  WHEN OTHERS THEN 
     DBMS_OUTPUT.PUT_LINE('este o exceptie!'); 
END;
/





