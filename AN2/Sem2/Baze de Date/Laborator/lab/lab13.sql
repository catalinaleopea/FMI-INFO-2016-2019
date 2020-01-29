/* Lab 9 */

/* Ex 7 */

CREATE OR REPLACE VIEW VIZ_EMP30_MCG AS
 (SELECT employee_id, last_name, email, salary, hire_date, job_id, department_id
 FROM emp_mcg
 WHERE department_id = 30)
WITH READ ONLY CONSTRAINT verific_mcg;
INSERT INTO VIZ_EMP30_MCG
 VALUES(600, 'last_name', 'eemail', 10000, SYSDATE, 'IT_PROG', 50);

/* Ex 8 */

SELECT view_name, text
FROM user_views
WHERE view_name LIKE '%MCG';

/* Ex 9 */

select last_name, salary, department_id, (select max(salary)
                                          from employees
                                          where department_id = e.department_id) max_salary
from employees e;

/* Ex 10 */

CREATE OR REPLACE VIEW VIZ_SAL_MCG AS
 (SELECT last_name, department_name, salary, city
 FROM employees JOIN departments USING(department_id)
 JOIN LOCATIONS USING(location_id)
 );
SELECT * FROM VIZ_SAL_MCG;

/* sau (on in loc de using), folosesti on cand ai chei externe diferite, using cand sunt la fel */

CREATE OR REPLACE VIEW VIZ_SAL_MCG AS
 (SELECT last_name, department_name, salary, city
 FROM employees JOIN departments D USING(department_id)
 JOIN LOCATIONS L ON (D.location_id = L.location_id)
 );
SELECT * FROM VIZ_SAL_MCG;

/* Ex 11 */

alter table emp_mcg
add constraint nume_ang_mcg
check (upper(last_name) not like 'WX%');

/* Ex 12 */

select *
from dept_mcg;

create sequence seq_dept_mcg
increment by 10
start with 400
maxvalue 10000
nocycle
nocache;

insert into dept_mcg
values(seq_dept_mcg.nextval, 'DepartamentSEQ', null, null);

select *
from dept_mcg;

insert into dept_mcg
values(seq_dept_mcg.nextval, 'DepartamentSEQ', null, null);

select *
from dept_mcg;

/* Ex 13 */

delete from dept_mcg
where department_id = 400;

delete from dept_mcg
where department_id = 410;

select *
from dept_mcg;

/* Ex 14 */

create index emp_dept_mcg
on emp_mcg (department_id);

select employee_id, department_name
from emp_mcg join dept_mcg using (department_id);

drop index emp_dept_mcg;

/* Ex 15 */

create index dept_index_mcg
on dept_mcg upper(department_name);

create index emp_index_mcg
on emp_mcg lower(last_name);

select employee_id
from emp_mcg
where lower(last_name) = 'king';

drop index emp_index_mcg;

/* Ex 4 recapitulare */

select last_name, salary, commission_pct, d.department_id, department_name
from employees e join departments d on e.department_id = d.department_id
where (salary, commission_pct) in (select salary, commission_pct
                                  from employees em join departments dep
                                  on em.department_id = dep.department_id
                                  where lower(department_name) = 'sales')
and lower(department_name) != 'sales';

/* Ex 3 recapitulare */

select employee_id, city
from (select employee_id, round(sysdate - hire_date) zile, department_id
      from employees
      
      union all
      
      select employee_id, end_date - start_date zile, department_id
      from job_history)
join departments d using (department_id)
join locations using (location_id)
where (employee_id, zile) in (select employee_id, max(zile)
                              from (select employee_id, round(sysdate - hire_date) zile
                                    from employees
      
                                    union all
      
                                    select employee_id, end_date - start_date
                                    from job_history)
                              group by employee_id);