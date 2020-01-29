/* Laborator 4 */

/* Exercitiul 23 */

SELECT job_id, SUM(DECODE(department_id, 30, salary)) Dep30,
       SUM(DECODE(department_id, 50, salary)) Dep50,
       SUM(DECODE(department_id, 80, salary)) Dep80,
       SUM(salary) Total
FROM employees
GROUP BY job_id; 

/* sau */

SELECT job_id, (SELECT SUM(salary)
                FROM employees
                WHERE department_id = 30
                AND job_id = e.job_id) Dep30,
       (SELECT SUM(salary)
        FROM employees
        WHERE department_id = 50
        AND job_id = e.job_id) Dep50,
       (SELECT SUM(salary)
        FROM employees
        WHERE department_id = 80
        AND job_id = e.job_id) Dep80,
        SUM(salary) Total
FROM employees e
GROUP BY job_id;

/* Exercitiul 24 */

SELECT DISTINCT (SELECT COUNT(*)
                 FROM employees) Total,
                (SELECT COUNT(*)
                 FROM employees
                 WHERE TO_CHAR(hire_date,'YYYY') = 1997) An1997,
                (SELECT COUNT(*)
                 FROM employees
                 WHERE TO_CHAR(hire_date,'YYYY') = 1998) An1998,
                (SELECT COUNT(*)
                 FROM employees
                 WHERE TO_CHAR(hire_date,'YYYY') = 1999) An1999,
                (SELECT COUNT(*)
                 FROM employees
                 WHERE TO_CHAR(hire_date,'YYYY') = 2000) An2000
FROM employees;

/* Exercitiul 25 */

SELECT d.department_id, department_name, a.suma
FROM departments d, (SELECT department_id, SUM(salary) suma
                     FROM employees
                     GROUP BY department_id) a
WHERE d.department_id = a.department_id; 

/* Exercitiul 26 */

SELECT d.department_id, department_name, last_name, salary, AVG(salary)
FROM employees e
JOIN departments d ON (d.department_id = e.department_id)
GROUP BY d.department_id, department_name, last_name, salary;

/* sau */

SELECT last_name, salary, department_id, SalMediu
FROM employees
JOIN (SELECT AVG(salary) SalMediu, department_id
      FROM employees
      GROUP BY department_id)
USING (department_id);

/* Exercitiul 27 */

SELECT last_name, salary, department_id, SalMediu, NrAng
FROM employees 
JOIN (SELECT AVG(salary) SalMediu, department_id, COUNT(employee_id) NrAng
      FROM employees
      GROUP BY department_id)
USING (department_id);

/* Exemplu ROLLUP */

SELECT department_id, TO_CHAR(hire_date,'YYYY'), SUM(salary)
FROM employees
WHERE department_id < 50
GROUP BY ROLLUP(department_id, TO_CHAR(hire_date,'YYYY')); 

/* sau (cu UNION ALL) */

SELECT department_id, TO_CHAR(hire_date,'YYYY'), SUM(salary)
FROM employees
WHERE department_id < 50
GROUP BY department_id, TO_CHAR(hire_date,'YYYY')

UNION ALL

SELECT department_id, NULL, SUM(salary)
FROM employees
WHERE department_id < 50
GROUP BY department_id

UNION ALL

SELECT NULL, NULL, SUM(salary)
FROM employees
WHERE department_id < 50
GROUP BY department_id;

/* Laborator 5 */

/* Exercitiul 1 */

/* a) */

SELECT department_name, job_title, ROUND(AVG(salary))
FROM departments JOIN employees USING (department_id)
                 JOIN jobs USING (job_id)
GROUP BY ROLLUP(department_name, job_title);

/* b) */

SELECT department_name, job_title, ROUND(AVG(salary)), 
       GROUPING(department_name), GROUPING(job_title)
FROM departments JOIN employees USING (department_id)
                 JOIN jobs USING (job_id)
GROUP BY ROLLUP(department_name, job_title);

/* Exercitiul 2 */

SELECT department_name, job_title, ROUND(AVG(salary)), 
       GROUPING(department_name), GROUPING(job_title)
FROM departments JOIN employees USING (department_id)
                 JOIN jobs USING (job_id)
GROUP BY CUBE(department_name, job_title);

/* Exercitiul 3 */

SELECT department_name, job_title, e.manager_id, MAX(salary), SUM(salary)
FROM employees e JOIN departments d ON (e.department_id=d.department_id)
                 JOIN jobs j USING(job_id)
GROUP BY GROUPING SETS((department_name,job_title),(job_title,e.manager_id),());

/* Exercitiul 4 */

/* a) */

SELECT last_name, salary, department_id
FROM employees e
WHERE salary > (SELECT AVG(salary)
                FROM employees
                WHERE department_id = e.department_id); 

/* b) */

SELECT last_name, salary, e.department_id, department_name, sal_med, nr_sal
FROM employees e, departments d, (SELECT department_id, AVG(salary) sal_med,
                                         COUNT(*) nr_sal
                                  FROM employees
                                  GROUP BY department_id) sm
                                  WHERE e.department_id = d.department_id
                                        AND d.department_id = sm.department_id
                                        AND salary > (SELECT AVG(salary)
                                                      FROM employees
                                                      WHERE department_id = e.department_id); 			
													  
/* Exercitiul 5 */

SELECT last_name, salary
FROM employees
WHERE salary > ALL(SELECT AVG(salary)
                   FROM employees
				   GROUP BY department_id);
				
/* sau */

SELECT last_name, salary
FROM employees
WHERE salary > (SELECT MAX(AVG(salary))
                FROM employees
				GROUP BY department_id);
				
/* Exercitiul 6 */

SELECT last_name, salary, department_id
FROM employees e
WHERE salary = (SELECT MIN(salary)
 FROM employees
 WHERE department_id = e.department_id); 
 
 /* sau */
 
SELECT last_name, salary, department_id
FROM employees
WHERE (department_id, salary) IN (SELECT department_id, MIN(salary)
FROM employees
GROUP BY department_id); 
 
/* sau */
 
select last_name, salary
from employees e join (select min(salary) MinSal, department_id dep_id
                      from employees
                      group by department_id)
on(e.department_id = dep_id)
where salary = MinSal;

/* ex7 */

select last_name
from employees e
where exists (select employee_id
              from employees
              where department_id = e.department_id
              and salary = (select max(salary)
                            from employees
                            where department_id = 30));
                            
/* ex8 */

select last_name, salary, rownum
from employees e
where 3 > (select count(salary)
          from employees
          where e.salary < salary)
      and rownum < 4;
      
--sortam in from

select employee_id, last_name, rownum
from (select employee_id, salary, last_name
      from employees
      order by salary desc)
where rownum < 4;

/* ex9 */

select sef.employee_id, sef.last_name, sef.first_name
from employees sef
where 1 < (select count(employee_id)
          from employees
          where sef.employee_id = manager_id);
          
/* ex10 */

--Exist

select loc.location_id
from locations loc
where exists(select department_id
            from departments
            where loc.location_id = location_id);
            
--In

select location_id
from locations loc
where location_id in (select location_id
                      from departments
                      where loc.location_id = location_id);
                      
/* ex11 */

--Not exists

SELECT department_id, department_name
FROM departments d
WHERE NOT EXISTS (SELECT 'x'
                  FROM employees
                  WHERE department_id = d.department_id); 
            
--Not in subcerere sincronizata

select department_id, department_name
from departments d
where department_id not in (select department_id
                            from employees
                            where department_id = d.department_id); 

--Not in subcerere nesincronizata

select department_id, department_name
from departments d
where department_id not in (select department_id
                            from employees
                            where department_id is not null);

--Minus

select department_id
from departments --din toate departamentele existente

minus

select department_id
from employees; --din departamentele cu angajati

/* Ex12 */

--a

select employee_id, last_name, hire_date, salary, manager_id
from employees
where manager_id = (select employee_id
                   from employees
                   where lower(last_name) = 'de haan');
                   
--b

/*
select
from
where
start with
connect by
group by
having
order by
*/

SELECT employee_id, last_name, hire_date, salary, manager_id
FROM employees
START WITH manager_id = (SELECT employee_id
                        FROM employees
                        WHERE LOWER(last_name)='de haan')
CONNECT BY manager_id = PRIOR employee_id; 

/* Ex13 */

select employee_id, last_name
from employees
start with employee_id = 114
connect by manager_id = prior employee_id;

/* Ex 14 */

select employee_id, manager_id, last_name, level
from employees
where level < 3
start with manager_id = (SELECT employee_id
                        from employees
                        where LOWER(last_name)='de haan')
connect by manager_id = prior employee_id;


/* ex 15 */

select employee_id, manager_id, level, last_name
from employees
connect by employee_id  = prior manager_id
order by level;

/* ex 16 */

--v 1.0

select employee_id, last_name, salary, LEVEL, manager_id
from employees
start with salary = (select max(salary)
                    from employees)
connect by prior employee_id = manager_id and salary > 5000;

--v 1.1

select employee_id, last_name, salary, level,manager_id
from employees
where salary > 5000
start with salary = (select max(salary) 
                    from employees)
connect by prior employee_id = manager_id;

/* Ex 17 */

WITH val_dep AS (SELECT department_name, SUM(salary) AS total
                FROM departments d, employees e
                WHERE d.department_id = e.department_id
                GROUP BY department_name),
val_medie AS (SELECT SUM(total)/COUNT(*) AS medie
              FROM val_dep)
              
SELECT *
FROM val_dep
WHERE total > (SELECT medie
              FROM val_medie)
ORDER BY department_name; 

with subordonat as (select employee_id, hire_date
                    from employees
                    where manager_id = (select employee_id
                                        from employees
                                        where lower(last_name || first_name) = 'kingsteven')),
                                        
    vechime as (select employee_id
                from subordonat
                where hire_date = (select min(hire_date)
                                  from subordonat))
                                  
select employee_id, last_name || first_name "Nume si prenume", job_id, hire_date
from employees
where to_char(hire_date, 'yyyy') != 1970
start with employee_id in (select employee_id
                          from vechime)
connect by prior employee_id = manager_id;

/* Ex19 */

with platit as (select last_name, salary
                from employees
                order by 1 desc)

select last_name, rownum, salary
from platit
where rownum <= 10;

select 'Departamentul ' || department_name || ' este condus de ' || nvl(to_char(manager_id), 'nimeni') || ' si ' ||
      case
      when (select count(employee_id)
            from employees
            where department_id = d.department_id) = 0
      then 'nu are salariati'
      else 'are numarul de salariati' || (select count(employee_id)
                                          from employees
                                          where department_id = d.department_id)
      end DETALII
from departments d;

/* Ex23 */

select job_id
case 
when (lower(job_id) like 's%')
then (select sum(salary)
      from employees
      where j.job_id = job_id)
when (job_id = (select job_id
                from employees
                where salary = (select max(salary)
                                from employees))
then (select avg(salary)
      from employees)
else (select min(salary)
      from employees
      where job_id = j.job_id)
end joburi
from jobs j;