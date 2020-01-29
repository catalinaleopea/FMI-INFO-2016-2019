select *
from employees
where salary + salary * nvl(commission_pct, 0) > 
      (select max(salary + salary * nvl(commission_pct, 0))
      from employees
      where lower(job_id) like '%clerk%')
order by salary desc;

select last_name, department_name, salary
from employees e join departments d on (e.department_id = d.department_id)
where commission_pct is null and e.manager_id in (select manager_id
                                                    from employees
                                                    where commission_pct is not null);

select last_name, department_id, job_id
from employees
where department_id = (select department_id
                      from departments d join locations l on (d.location_id = l.location_id)
                      where lower (city) = 'toronto');
                      
/*
id  nume salariu manager_id
 1 User1    1000          1
 2 User2    1400          1
 3 User3     700          2
 4 User4     300          2
 5 User4    1600          2

select *
from users
where salariu < 1100
group by manager_id; 
manager 1 - id 1 - salariu 1000
manager 2 - id 2 - salariu 700
group by afiseaza doar prima intrare

select *
from users
having salariu > 800 - analog where (nu avem group by)

select *
from users
group by manager_id
having salariu < 1100

prima data executa gruparea
manager_id 1: 1000, 1400
manager_id 2: 700, 300, 1600

urmeaza having
manager_id 1; 1000
manager_id 2: 700
*/

select job_id, employee_id, max (salary) Maxim, min (salary) Minim, sum (salary) Suma, round(avg(salary)) Medie
from employees
group by job_id, employee_id;

select job_id, salary
from employees;

SELECT job_id, COUNT(*) --numara orice e acolo
FROM employees
GROUP BY job_id; 

select count(distinct manager_id) "Numar manager"
from employees;

select max(salary) - min(salary) "Diferenta"
from employees;

select department_name, location_id, count(employee_id), round(avg(salary))
from employees e join departments d on (e.department_id = d.department_id)
group by department_name, location_id;

select employee_id, first_name, last_name
FROM employees
WHERE salary > (SELECT AVG(salary)
                FROM employees)
ORDER BY salary DESC;

select manager_id, min(salary)
from employees
where manager_id is not null
group by manager_id
having min(salary) < 3000
order by 2 desc;

select e.department_id, department_name, max(salary)
from employees e join departments d on (e.department_id = d.department_id)
group by e.department_id, department_name
having max(salary) > 3000;

SELECT MIN(AVG(salary))
FROM employees
GROUP BY job_id;

select round(max(avg(salary)))
from employees
group by department_id;

select j.job_id, job_title, avg(salary)
from employees e join jobs j on (e.job_id = j.job_id)
group by j.job_id, job_title
having avg(salary) = (select min(avg(salary))
                      from employees
                      group by job_id);
                      
select avg(salary)
from employees
having avg(salary) > 2500;

SELECT department_id, job_id, SUM(salary)
FROM employees
where department_id is not null --era unul null
GROUP BY department_id, job_id;

SELECT e.department_id, d.department_name, COUNT(*)
FROM departments d JOIN employees e ON (d.department_id = e.department_id)
WHERE e.department_id IN (SELECT department_id
                          FROM employees
                          GROUP BY department_id
                          HAVING COUNT(*) < 4)
GROUP BY e.department_id, d.department_name;

select e.department_id, d.department_name, count(*)
from departments d join employees e on (d.department_id = e.department_id)
group by e.department_id, d.department_name
having count(employee_id) = (select max(count(employee_id))
                            from employees
                            group by department_id);
                            
select count(count(department_id))
from employees
group by department_id
having count(employee_id) >= 15;
--mai intai se numara nr angajatiilor, apoi departamentele

select department_id, sum(salary)
from employees
where department_id != 30
group by department_id
having count(employee_id) > 10
order by 2;

select employee_id
from job_history
group by employee_id
having count (job_id) >= 2;

select last_name, hire_date
from employees
where to_char(hire_date, 'dd') = (select to_char(hire_date, 'dd')
                                  from employees
                                  group by to_char(hire_date, 'dd')
                                  having count(employee_id)= (select max(count(employee_id))
                                                              from employees
                                                              group by to_char(hire_date, 'dd')
                                                              )
                                  );