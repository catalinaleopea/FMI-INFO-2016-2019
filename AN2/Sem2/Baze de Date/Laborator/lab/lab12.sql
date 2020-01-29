/* Lab8 */

/* Ex23 */

desc angajati_mcg;

alter table angajati_mcg
modify (email not null);

desc angajati_mcg;

update angajati_mcg
set email = nume where email is null;

/* Ex24 */

--Nu merge pentru ca nu exista departamentul 50

/* Ex25 */

insert into departamente_mcg
values (60, 'Analiza', null );

commit;

select *
from departamente_mcg;

/* Ex26 */

delete from departamente_mcg
where cod_dep = 20;

select * from angajati_mcg;

SELECT constraint_name, constraint_type, table_name
FROM user_constraints
WHERE lower(table_name) IN ('angajati_mcg', 'departamente_mcg');

alter table angajati_mcg
drop constraint FK_DEPART_ANG_MCG;

alter table angajati_mcg
add constraint FK_DEPART_ANG_MCG foreign key (cod_dep)
references departamente_mcg (cod_dep) on delete cascade;

delete from departamente_mcg
where cod_dep = 20; 

select *
from angajati_mcg;

select *
from departamente_mcg;

/* Ex27 */

delete from departamente_mcg
where cod_dep = 60;

rollback;

/* Ex28 */

--e la 26

/* Ex29 */

--la 26

/* Ex30 */

alter table departamente_mcg
add constraint cod_director_fk_mcg foreign key(cod_director)
references angajati_mcg (cod_ang) on delete set null;

/* Ex31 */

update departamente_mcg
set cod_director = 102
where cod_dep = 30;

select * from departamente_mcg;

select * from angajati_mcg;

DELETE from angajati_mcg where cod_ang = 102;

select * from angajati_mcg;

rollback;

/* Ex32 */

alter table angajati_mcg
add constraint v_sal_mcg check (salariu <= 30000);

update angajati_mcg
set salariu = 25000 --nu putem adauga un salariu mai mare de 30 000, conform noii constrangeri adaugate
where cod_ang = 100;

select * from angajati_mcg;


alter table angajati_mcg disable constraint v_sal_mcg;

update angajati_mcg
set salariu = 40000
where cod_ang = 100;

select * from angajati_mcg;

--fn1 avem id-uri si fiecare e unic
--e pana la fn5

--Explicati fn4 si explicati in limbaj natural

/* Lab 9 */

CREATE TABLE EMP_mcg AS SELECT * FROM employees;
CREATE TABLE DEPT_mcg AS SELECT * FROM departments;
ALTER TABLE emp_mcg
ADD CONSTRAINT pk_emp_mcg PRIMARY KEY(employee_id);
ALTER TABLE dept_mcg
ADD CONSTRAINT pk_dept_mcg PRIMARY KEY(department_id);
ALTER TABLE emp_mcg
ADD CONSTRAINT fk_emp_dept_mcg
 FOREIGN KEY(department_id) REFERENCES dept_mcg(department_id);
ALTER TABLE dept_mcg
ADD CONSTRAINT fk_dept_sef_mcg
 FOREIGN KEY (manager_id) REFERENCES emp_mcg(employee_id);
ALTER TABLE emp_mcg
ADD CONSTRAINT fk_emp_sef_mcg
 FOREIGN KEY (manager_id) REFERENCES emp_mcg(employee_id);
INSERT INTO dept_mcg (department_id, department_name)
VALUES (300, 'Programare');

/* Ex1 */

CREATE OR REPLACE VIEW VIZ_EMP30_mcg AS
 (SELECT employee_id, last_name, email, salary
 FROM emp_mcg
 WHERE department_id = 30
 );

DESC VIZ_EMP30_mcg;
SELECT * FROM VIZ_EMP30_mcg;
INSERT INTO VIZ_EMP30_mcg
 VALUES(559,'last_name','eemail',10000);
 --nu merge, e intentionat
 
/* Ex2 */

CREATE OR REPLACE VIEW VIZ_EMP30_mcg AS
 (SELECT employee_id, last_name, email, salary, hire_date, job_id, department_id
 FROM emp_mcg
 WHERE department_id = 30
 );
DESC VIZ_EMP30_mcg;
SELECT * FROM VIZ_EMP30_mcg;
SELECT * FROM EMP_mcg;
INSERT INTO VIZ_EMP30_mcg
 VALUES(601, 'last_name', 'eemail', 10000, SYSDATE, 'IT_PROG', 30);
SELECT * FROM VIZ_EMP30_mcg;
SELECT * FROM EMP_mcg;

DELETE FROM viz_emp30_mcg
WHERE employee_id = 601;

SELECT * FROM VIZ_EMP30_mcg;
SELECT * FROM EMP_mcg;

commit;

/* Ex3 */

CREATE OR REPLACE VIEW VIZ_EMPSAL50_mcg AS
 SELECT employee_id, last_name, email, job_id, hire_date, salary*12 sal_anual
 FROM emp_mcg
 WHERE department_id = 50;

DESC VIZ_EMPSAL50_mcg;
SELECT * FROM VIZ_EMPSAL50_mcg;

/* Ex4 */
INSERT INTO VIZ_EMPSAL50_mcg(employee_id, last_name, email, job_id, hire_date)
 VALUES(567, 'last_name', 'email000', 'IT_PROG', sysdate);
 
SELECT * FROM VIZ_EMPSAL50_mcg;
 
/* Ex5 */

/* a */

CREATE OR REPLACE VIEW VIZ_EMP_DEP30_mcg AS
SELECT v.*,d.department_name
FROM VIZ_EMP30_mcg v JOIN departments d ON(d.department_id = v.department_id);

SELECT * FROM VIZ_EMP_DEP30_mcg;

/* b */

INSERT INTO VIZ_EMP_DEP30_mcg
 (employee_id,last_name,email,salary,job_id,hire_date,department_id)
 VALUES (358, 'lname', 'email', 15000, 'IT_PROG', sysdate, 30);
SELECT * FROM VIZ_EMP_DEP30_mcg;
SELECT * FROM VIZ_EMP30_mcg;

DELETE FROM VIZ_EMP_DEP30_mcg WHERE employee_id = 358;