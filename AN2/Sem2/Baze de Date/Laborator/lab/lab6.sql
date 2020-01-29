--din lab 4

--23. Scrie?i o cerere pentru a afi?a job-ul, salariul total pentru job-ul respectiv pe
departamente si salariul total pentru job-ul respectiv pe departamentele 30, 50, 80.
Se vor eticheta coloanele corespunz?tor. 

--varianta 1 cu decode
SELECT job_id, SUM(DECODE(department_id, 30, salary)) Dep30,
 SUM(DECODE(department_id, 50, salary)) Dep50,
 SUM(DECODE(department_id, 80, salary)) Dep80,
 SUM(salary) Total
FROM employees
GROUP BY job_id;

--varianta 2
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

--24. S? se creeze o cerere prin care s? se afi?eze num?rul total de angaja?i ?i, din
acest total, num?rul celor care au fost angaja?i în 1997, 1998, 1999 si 2000. Denumiti
capetele de tabel in mod corespunzator

select (select count(*) from employees) Total,
       (select count(*) from employees
                              where to_char(hire_date,'yyyy')=1997) An1997,
       (select count(*) from employees
                              where to_char(hire_date,'yyyy')=1998) An1998,
       (select count(*) from employees
                              where to_char(hire_date,'yyyy')=1999) An1999,
       (select count(*) from employees
                              where to_char(hire_date,'yyyy')=2000) An2000
from dual;


--SUBCERERI IN FROM

--25 S? se afi?eze codul, numele departamentului ?i suma salariilor pe departamente. 
SELECT d.department_id, department_name,a.suma
FROM departments d, (SELECT department_id ,SUM(salary) suma
 FROM employees
 GROUP BY department_id) a
WHERE d.department_id =a.department_id; 

select department_id
from employees;

--26
--varianta 1 fara subcerere
select last_name,salary,department_id,avg(salary)
from employees join departments using (department_id)
group by last_name,salary,department_id;

--varianta 2 cu subcerere

select last_name,salary,department_id,SalMediu
from employees join (select avg(salary) SalMediu,department_id
                    from employees
                     GROUP BY department_id)
using(department_id);

--27 Modifica?i cererea anterioar?, pentru a determina ?i listarea num?rului de angaja?i
din departamente. 

select last_name,salary,department_id, SalMediu, NrAng
from employees join(select avg(salary) SalMediu, department_id,
                    count(employee_id) NrAng
                    from employees
                    group by department_id)
using (department_id); 

--ROLLUP exemplu
SELECT department_id, TO_CHAR(hire_date, ‘yyyy’), SUM(salary)
FROM employees
WHERE department_id < 50
GROUP BY ROLLUP(department_id, TO_CHAR(hire_date, ‘yyyy’)); 

--rollup cu union all
SELECT department_id,NULL,SUM(salary)
from employees
WHERE department_id < 50
group by department_id;



--lab5
--1. a) S? se afi?eze numele departamentelor, titlurile job-urilor ?i valoarea medie a salariilor,
pentru:
- fiecare departament ?i, în cadrul s?u pentru fiecare job;
- fiecare departament (indiferent de job);
- întreg tabelul.

select department_name, job_title, AVG(salary)
from departments d join employees e using(department_id)
                  join jobs j using(job_id)
group by rollup(d.department_name,j.job_title);

--b) Analog cu a), afi?ând ?i o coloan? care arat? interven?ia coloanelor department_name,
job_title, în ob?inerea rezultatului. 
--folosim grouping pt a vedea ce coloane au intervenit si ce nu

select department_name, job_title, AVG(salary),
grouping(department_name),grouping(job_title)
from departments d join employees e using(department_id)
                  join jobs j using(job_id)
group by rollup(d.department_name,j.job_title);

--2
select department_name, job_title, AVG(salary),
grouping(department_name),grouping(job_title) --b
from departments d join employees e using(department_id)
                  join jobs j using(job_id)
group by cube(d.department_name,j.job_title);

--3
select department_name,job_title,e.manager_id,max(salary),sum(salary)
from departments d join employees e using(department_id)
                  join jobs j using(job_id)
group by grouping sets ((department_name,job_title),
                        (job_title,e.manager_id),0);

--SUBCERERI SINCRONIZATE
--4  S? se afi?eze informa?ii despre angaja?ii al c?ror salariu dep??e?te valoarea medie a
salariilor colegilor s?i de departament. 
SELECT last_name, salary, department_id
FROM employees e
WHERE salary > (SELECT AVG(salary)
                FROM employees
                WHERE department_id = e.department_id); 

--5. S? se afi?eze numele ?i salariul angaja?ilor al c?ror salariu este mai mare decât salariile
medii din toate departamentele. Se cer 2 variante de rezolvare: cu operatorul ALL sau cu
func?ia MAX. 

--ALL
select last_name,salary
from employees
where salary > ALL(select avg(salary)
                    from employees 
                    group by department_id);

--MAX
select last_name,salary
from employees
where salary > (select MAX(avg(salary))
                    from employees 
                    group by department_id);

--6 Sa se afiseze numele si salariul celor mai prost platiti angajati din fiecare departament.

--Solu?ia 1 (cu sincronizare):
SELECT last_name, salary, department_id
FROM employees e
WHERE salary = (SELECT MIN(salary)
                FROM employees
                WHERE department_id = e.department_id);
                
--Solu?ia 2 (f?r? sincronizare):
SELECT last_name, salary, department_id
FROM employees
WHERE (department_id, salary) IN (SELECT department_id, MIN(salary)
                                  FROM employees
                                  GROUP BY department_id); 

--Solutia 3
SELECT last_name, salary
from employees e join (select min(salary) SalMinim, department_id IdDepartament
                       from employees
                       group by department_id)
                 on (e.department_id = IdDepartament)
where salary = SalMinim; --putem folosi si aliasurile

--7 Sa se obtina numele salariatilor care lucreaza intr-un departament in care exista cel putin 1
angajat cu salariul egal cu salariul maxim din departamentul 30. 
select last_name
from employees e 
where EXISTS (select employee_id
              from employees
              where e.department_id = department_id and 
                    salary =(select max(salary)
                             from employees
                             where department_id = 30)
              );

select last_name
from employees
where salary = 11000;


--8. Sa se obtina numele primilor 3 angajati avand salariul maxim. Rezultatul se va afi?a în ordine
cresc?toare a salariilor. 
--varianta 1 daca actualizam randul nu va lua defapt max
select last_name,salary,rownum
from employees e
where 3 > (select count(salary)
      from employees
      where e.salary < salary)
      and rownum < 4;
update employees set salary = 200 where employee_id = 101;

--varianta 2 rezolvarea problemei
select employee_id,last_name,salary,rownum
from (select employee_id, last_name,salary
      from employees
      order by salary desc)
where rownum < 4;

