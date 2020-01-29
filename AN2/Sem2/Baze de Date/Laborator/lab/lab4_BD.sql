--continuare lab2 -25
select e.last_name, e.hire_date, sef.last_name, sef.hire_date
from employees e, employees sef
where e.manager_id = sef.employee_id and e.hire_date < sef.hire_date;

--continuare lab3
select last_name, salary, grade_level, lowest_sal,highest_sal
from employees,job_grades
where salary BETWEEN lowest_sal AND highest_sal;
--ia din tabelul job_grades primul interval de salariu si afiseaza din empolyees
--toate salariile care se incadreaza in acel interval,etc. se repeta pt toate intervalele

desc job_grades;
select * from job_grades;

SELECT last_name, e.job_id, job_title 
FROM employees e, jobs j 
WHERE e.job_id = j.job_id;

SELECT last_name, department_name, location_id
FROM employees JOIN departments USING (department_id);

--afisam toti angajati chiar daca au sau nu departament
SELECT last_name, department_name, location_id
FROM employees e JOIN departments d ON (e.department_id = d.department_id);

--1
select e.last_name, to_char(e.hire_date, 'month-yyyy'),gates.employee_id
from employees e JOIN employees gates ON (e.department_id = gates.department_id)
where lower(e.last_name) like '%a%' and lower(e.last_name) != 'gates'
                                    and lower(gates.last_name) = 'gates';
--2
select e.last_name, e.employee_id,e.department_id,department_name
from employees e JOIN employees coleg ON(e.department_id = coleg.department_id)
                JOIN departments d ON(e.department_id = d.department_id)
where lower(coleg.last_name) like '%t%'
order by 2;

--3
select e.last_name,e.salary,job_title,city,country_name
from employees e JOIN employees king ON(e.manager_id = king.employee_id) 
                 JOIN jobs j ON(e.job_id = j.job_id)
                 JOIN departments d ON(d.department_id = e.department_id)
                 JOIN locations l ON(d.location_id = l.location_id)
                 JOIN countries c ON(c.country_id = l.country_id)
where lower(king.last_name)='king';

--4
select d.department_id,department_name,last_name,job_id,to_char(salary,'$99,999.00')
from departments d join employees e ON(d.department_id = e.department_id)
where lower(d.department_name) like '%ti%'
order by 2,3;


--5
select department_name,last_name
from employees e JOIN departments d ON(e.department_id = d.department_id);
--asa arata si departmentele fara angajati 50
select department_name,last_name
from employees e RIGHT JOIN departments d ON(e.department_id = d.department_id);
--107
select department_name,last_name
from employees e LEFT JOIN departments d ON(e.department_id = d.department_id);
--123 fara distinct,121 cu distinct
--full outer join e echivalent cu union
select department_name,last_name
from employees e FULL OUTER JOIN departments d ON(e.department_id = d.department_id);

--6,7
select department_id, department_name from departments
where lower(department_name) like '%re%'
UNION ALL
select department_id ,last_name from employees
where upper(job_id) = 'SA_REP';

--8
SELECT department_id “Cod departament”
FROM departments --codurile tuturor dep(27)
MINUS
SELECT department_id
FROM employees; 
--var 2 toate dep si fara angajati
SELECT department_id
FROM departments
WHERE department_id NOT IN (SELECT DISTINCT NVL(department_id,0)
 FROM employees); 

SELECT department_name,last_name
FROM employees e right join departments d on(e.department_id = d.department_id)
WHERE employee_id is null; --vrem dep cu 0 angajati
--orice col reprezentativa pt anagajat are val null

select department_name, last_name,email,phone_number,employee_id
from employees e right join departments d on(e.department_id = d.department_id)
where department_name = 'NOC';

--9
SELECT department_id "Cod departament" FROM employees
WHERE UPPER(job_id)='HR_REP'
INTERSECT
SELECT department_id FROM departments
WHERE LOWER(department_name) LIKE '%re%'; 

--10
SELECT last_name, hire_date FROM employees
WHERE hire_date > (SELECT hire_date
                   FROM employees
                   WHERE INITCAP(last_name)='Gates');

--11
select department_id
from employees
where lower(last_name)='gates';

select last_name,salary
from employees
where department_id = (select department_id
                      from employees
                      where lower(last_name)='gates')
      and lower(last_name)!='gates';
--sau <>

--12 subcerere pt a selecta seful companiei
select last_name,salary
from employees
where manager_id = (select employee_id
from employees
where manager_id is null);

--13
select last_name,department_id,salary
from employees
where (department_id,salary)in(select department_id,salary
from employees
where commission_pct is not null);

--14
select employee_id,last_name,salary
from employees
where salary > (select AVG(salary) from employees);

--15



