--Leopea Catalina, grupa 343
--6.

DECLARE
    rezultat VARCHAR2(35);
    nr_ang NUMBER(3);
BEGIN
    SELECT department_name INTO rezultat
    FROM employees e, departments d
    WHERE e.department_id = d.department_id
    GROUP BY department_name
    HAVING COUNT(*) = (SELECT MAX(COUNT(*))
                       FROM employees
                       GROUP BY department_id);
    SELECT COUNT(*) INTO nr_ang
    from departments d, employees e
    WHERE e.department_id = d.department_id
    group by department_name
    having department_name = rezultat;
    DBMS_OUTPUT.PUT_LINE('Departamentul '|| rezultat);
    DBMS_OUTPUT.PUT_LINE(nr_ang);
END;

/*
1.
    a) 2
    b) text 2
    c) text 3 adaugat in sub-bloc
    d) 101
    e) text 1 adaugat un blocul principal
    f) text 2 adaugat in blocul principal
*/

SET SERVEROUTPUT ON;

DECLARE
    numar number(3):=100;
    mesaj1 varchar2(255):='text 1';
    mesaj2 varchar2(255):='text 2';
BEGIN
    DECLARE
        numar number(3):=1;
        mesaj1 varchar2(255):='text 2';
        mesaj2 varchar2(255):='text 3';
    BEGIN
        numar:=numar+1;
        mesaj2:=mesaj2||' adaugat in sub-bloc';
        DBMS_OUTPUT.PUT_LINE(numar);
        DBMS_OUTPUT.PUT_LINE(mesaj1);
        DBMS_OUTPUT.PUT_LINE(mesaj2);
    END;
    numar:=numar+1;
    mesaj1:=mesaj1||' adaugat un blocul principal';
    mesaj2:=mesaj2||' adaugat in blocul principal';
    DBMS_OUTPUT.PUT_LINE(numar);
    DBMS_OUTPUT.PUT_LINE(mesaj1);
    DBMS_OUTPUT.PUT_LINE(mesaj2);
END;

--2.

with zile
  as (select trunc(sysdate,'month') + level-1 zi
      from dual
      connect by level <= extract (day from last_day(sysdate)))
select zi, sum(case when to_char(zi,'dd.mm.yyyy') = to_char(book_date,'dd.mm.yyyy') 
                      then 1
                      else 0
              end) nr    
from   zile, rental
where  to_char(book_date,'mm-yyyy') = to_char(sysdate,'mm-yyyy')
group by zi
order by 1;