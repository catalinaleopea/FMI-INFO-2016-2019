/* Lab6 */

/* Ex9 */

select employee_id
from works_on
where project_id in (select project_id
                    from projects
                    where project_manager=102)
group by employee_id
having count(project_id) <= (select count(project_id)
                            from projects
                            where project_manager=102);
                            
/* Ex10a */

select employee_id, last_name, first_name
from employees e  join works_on w using(employee_id)
where project_id in (select employee_id
                    from works_on
                    where employee_id=200) --selectam proiectele la care a lucrat 200
group by employee_id, last_name, first_name
having count(project_id) >= (select count(employee_id)
                            from works_on
                            where employee_id=200) --trebuie ca fiecare angajat sa lucreze la toate proiectele la care a lucrat angajatul 200
--cel putin inseamna ca a lucrat la aceleasi proiecte ca si angajatul 200, dar poate sa aiba si allte proiecte in afara de 200     
                            
/* Ex10b */

--cel mult inseamna ca a lucrat la oricare din proiectele ca si angajatul 200
--sau maxim la toate, dar nu la altele

select employee_id, last_name, first_name
from employees e  join works_on w using (employee_id)
where project_id in (select employee_id
                    from works_on
                    where employee_id=200) --selectam proiectele la care a lucrat 200
group by employee_id, last_name, first_name
having count(project_id) <= (select count(employee_id)
                            from works_on
                            where employee_id=200);
--facem minus si eliminam proiectele la care nu lucreaza 200

minus

select employee_id, last_name, first_name
from employees e  join works_on w using (employee_id)
where project_id in (select distinct project_id
                    from works_on --din toate proiectele la care au lucrat angajati
                    
                    minus
                    
                    select distinct project_id
                    from works_on
                    where employee_id=200)
                    --in where trebuie sa obtinem proiectele la care nu lucreaza 200
                    
group by employee_id, last_name, first_name;


/* Lab 7 */

/* ex1 */

create table EMP_mcg as select * from employees
create table DEPT_mcg as select * from departments

/* ex2 */

desc employees
desc emp_mcg

desc departments
desc dept_mcg

/* ex3 */

select * from emp_mcg
select * from employees

/* ex4 */

ALTER TABLE emp_mcg
ADD CONSTRAINT pk_emp_mcg PRIMARY KEY(employee_id);

ALTER TABLE dept_mcg
ADD CONSTRAINT pk_dept_mcg PRIMARY KEY(department_id);

ALTER TABLE emp_mcg
ADD CONSTRAINT fk_emp_dept_mcg
 FOREIGN KEY(department_id) REFERENCES dept_mcg(department_id); 
 
--manager_id departament trebuei sa fie un angajat pentru a pastra intehritatea 

ALTER TABLE dept_mcg
ADD CONSTRAINT fk_dept_sef_mcg
 FOREIGN KEY(manager_id) REFERENCES emp_mcg(employee_id);
 
 --adaugam in emp cheia externa manager_id, deoarece daca adaugam un sef pentru angajat, acel sef trebuie sa existe si as fie sef la randul lui
 
alter table emp_mcg
add constraint fk_emp_sef_mcg
foreign key(manager_id) references emp_mcg(employee_id);

/* Ex5 */

--incorect
INSERT INTO DEPT_mcg
VALUES (300, 'Programare');

INSERT INTO DEPT_mcg (department_id, department_name)
 VALUES (300, 'Programare');

--incorect
INSERT INTO DEPT_mcg (department_name, department_id)
 VALUES (300, 'Programare');
 
INSERT INTO DEPT_mcg (department_id, department_name, location_id)
 VALUES (300, 'Programare', null);

--incorect
INSERT INTO DEPT_mcg (department_name, location_id)
 VALUES (‘Programare’, null); 

select * from dept_mcg;
 
rollback;--anuleaza tot ce s-a facut in sesiunea curenta (de la conectarea pe server sau de la ultimul commit)
 --commit salveaza toate modificarile din tranzactia curenta
 
select * from dept_mcg;
 
commit;

/* ex6 */

desc emp_mcg;

insert into emp_mcg
values (300, 'Vasile', 'Pielosu', 'vasilepielosu@hotmail.com', null, sysdate, 'IT prog', null, null, null, 300);

commit;

/* ex7 */

INSERT INTO emp_mcg (hire_date, job_id, employee_id, last_name, email, department_id)
VALUES (sysdate, 'sa_man', 278, 'nume_278', 'email_278', 300);
COMMIT ;

select *
from emp_mcg;

INSERT INTO emp_mcg (employee_id, last_name, email, hire_date, job_id, salary,
 commission_pct)
VALUES (252, 'Nume252', 'nume252@emp.com',SYSDATE, 'SA_REP', 5000, NULL);

SELECT employee_id, last_name, email, hire_date, job_id, salary, commission_pct
FROM emp_pnu
WHERE employee_id=252;

rollback;

insert into
 (select employee_id, last_name, hire_date, job_id, email
 from emp_mcg)
values ((select max(employee_id) + 1 from emp_mcg), 'nume', sysdate, 'ss_man', 'email');

/* ex9 */

create table emp1_mcg as select * from employees;

delete from emp1_mcg;

insert into emp1_mcg 
select *
from employees
where commission_pct > 0.25;

select *
from emp1_mcg;

rollback;--create, drop si alter fac commit automat

select *
from emp1_mcg;

/* ex10 */

INSERT INTO emp_mcg
 SELECT 0,USER,USER, 'TOTAL', 'TOTAL',SYSDATE,
 'TOTAL', SUM(salary), ROUND(AVG(commission_pct)), null, null
 FROM employees;
 
SELECT * FROM emp_mcg;

ROLLBACK;

SELECT * FROM emp_mcg;