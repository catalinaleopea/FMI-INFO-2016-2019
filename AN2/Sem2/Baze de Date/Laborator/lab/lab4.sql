select ang.last_name, ang.hire_date, sef.last_name, sef.hire_date
from employees ang, employees sef
where ang.manager_id = sef.manager_id and ang.hire_date < sef.hire_date;

select *
from job_grades;

SELECT last_name, salary, grade_level, lowest_sal, highest_sal  
FROM employees, job_grades  
WHERE salary BETWEEN lowest_sal AND highest_sal;

select ang.last_name, to_char(ang.hire_date, 'month-yyyy'), gates.employee_id Gates
from employees ang join employees gates on (ang.department_id = gates.department_id)
where lower(ang.last_name) like '%a%' and lower(ang.last_name) != 'gates'and lower(gates.last_name) = 'gates';

select e.employee_id, e.last_name, d.department_id, d.department_name
from employees e join employees ang on (e.department_id = ang.department_id) 
                   join departments d on (e.department_id = d.department_id)
where lower(ang.last_name) like '%t%'
order by 2;

select e.last_name, e.salary, king.employee_id, job_title, city, country_name
from employees e join employees king on (e.manager_id = king.employee_id)
                 join jobs j on (e.job_id = j.job_id)
                 join departments d on (e.department_id = d.department_id)
                 join locations l on (d.location_id = l.location_id)
                 join countries c on (l.country_id = c.country_id)
where lower(king.last_name) = 'king';

select d.department_id, department_name, last_name, job_id, to_char(salary, '$99,999.99')
from employees e join departments d on (e.department_id = d.department_id)
where lower(department_name) like '%ti%'
order by department_name, last_name;

select department_name, last_name
from employees e 
right join departments d on (e.department_id = d.department_id)

union

select department_name, last_name
from employees e 
left join departments d on (e.department_id = d.department_id);

select distinct department_name, last_name
from employees e 
full outer join departments d on (e.department_id = d.department_id);

select department_id
from departments
where lower(department_name) like '%re%'

union

select department_id
from employees
where upper(job_id) = 'SA_REP';

--union ia elementele comune si necomune o singura data
--full outer join o sa ia toate elementele de cate ori se gasesc (distinct)

SELECT department_id "Cod departament"
FROM departments --toate departamente

MINUS

SELECT department_id
FROM employees; --departamentele care au angajati

select d.department_id
from employees e right join departments d on (e.department_id = d.department_id)
where email is null;

--daca un departament nu are angajati, atunci orice coloana reprezentativa are valoarea null


SELECT department_id "Cod departamen"
FROM employees
WHERE UPPER(job_id)='HR_REP'

INTERSECT

SELECT department_id
FROM departments
WHERE LOWER(department_name) LIKE '%re%';

select department_id
from departments
where department_id not in (select distinct NVL(department_id, 0)
                            from employees);
                             
--subcererea returneaza departamentul in care lucreaza cineva

SELECT last_name, hire_date
FROM employees
WHERE hire_date > (SELECT hire_date
                    FROM employees
                    WHERE INITCAP(last_name) = 'Gates');
                    
--subcerere departamentul lui Gates = 50

select department_id
from employees
where lower (last_name) = 'gates';

select last_name, salary
from employees
where department_id = (select department_id
                        from employees
                        where lower (last_name) = 'gates')
and lower(last_name) != 'gates'; --merge si <> (diferit)

select last_name, salary
from employees
where department_id in (select department_id
                        from employees
                        where lower (last_name) = 'king')
and lower(last_name) != 'king';

--subcerere King

select employee_id
from employees
where manager_id is null;

select last_name, salary
from employees
where manager_id in (select employee_id
                    from employees
                    where manager_id is null);

select last_name, department_id, salary
from employees
where (department_id, salary) in (select department_id, salary
                                  from employees
                                  where commission_pct is not null);
                                
select employee_id, last_name, salary
from employees
where salary > (select avg(salary)
                from employees);--avg medie salariu (average)