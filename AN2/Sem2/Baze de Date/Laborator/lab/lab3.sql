select * from tab;

desc user_tables

select table_name
from user_tables;

desc job_grades

select*
from job_grades;

--39
select grade_level
from job_grades
where 9000 between LOWEST_SAL and HIGHEST_SAL;

--marti instalarile, si intrebari
--34 where dep id is not null and distinct
--36 jobhistory cod angajat scot duplicatele din selec si ord desc dupa cod
--37 where dep id =80 to char extrag form lunar
--38 jobs minsalary max salary
--40 like %l%l%
--41 employees pt caremanager id=93
--42 veit lunar total cond comission<=
--lab 2
--17 
select NEXT_DAY(ADD_MONTHS(sysdate, 3),6) data_viitoare
from dual;
--tochar fm 

--24
select round(avg(salary),2)
from employees;
--ia toti salariatii

select round(avg(COMMISSION_PCT),2) m1,
        round(SUM(COMMISSION_PCT)/COUNT(*),2) m2,--asta e corect
        round(SUM(COMMISSION_PCT)/COUNT(COMMISSION_PCT),2) m3
from employees
--where COMMISSION_PCT is not null;


--lab3
--equijoin
--SELECT last_name, department_name, location_id, e.department_id  --daca sterg e imi da eroare pentru ca acea coloana apare in mai multe tabele
SELECT e.last_name, d.department_name, d.location_id, e.department_id 
FROM   employees e, departments d  --nu merge cu as
WHERE  e.department_id = d.department_id; 

select employee_id, department_id
from employees
where rownum<=5;

select department_id, department_name
from departments
where department_id in (10,20,50);
--nonequijoin
SELECT last_name, salary, grade_level  
FROM   employees, job_grades 
WHERE  salary BETWEEN lowest_sal AND highest_sal;  
---
SELECT e.last_name, d.department_name, d.location_id, e.department_id 
FROM   employees e, departments d  
WHERE  e.department_id = d.department_id(+)  --left outerjoin
ORDER BY 2; 

SELECT e.last_name, d.department_name, d.location_id, e.department_id 
FROM   employees e left outer join departments d  
       on e.department_id = d.department_id  --standard
ORDER BY 2; 
----
SELECT e.last_name, d.department_name, d.location_id, d.department_id 
FROM   employees e, departments d 
WHERE  e.department_id(+) = d.department_id --right outerjoin
ORDER BY 1; 
--plus se pune unde completez adica aduc din afara
SELECT e.last_name, d.department_name, d.location_id, d.department_id 
FROM   employees e right outer join departments d  
       on e.department_id = d.department_id  --standard
ORDER BY 1; 

--full
SELECT employee_id,e.last_name, d.department_name, d.location_id, e.department_id 
FROM   employees e, departments d 
WHERE  e.department_id(+) = d.department_id --right outerjoin
union
SELECT employee_id,e.last_name, d.department_name, d.location_id, d.department_id 
FROM   employees e, departments d 
WHERE  e.department_id = d.department_id(+); --right outerjoin

  --standard
SELECT e.last_name, d.department_name, d.location_id, e.department_id 
FROM   employees e left outer join departments d  
       on e.department_id = d.department_id  --standard
union
SELECT e.last_name, d.department_name, d.location_id, d.department_id 
FROM   employees e right outer join departments d  
       on e.department_id = d.department_id;  --standard
 
--selfjoin
SELECT sef.last_name Sef, angajat.last_name Angajat 
FROM   employees sef, employees angajat  
WHERE  sef.employee_id = angajat.manager_id  
ORDER BY sef.last_name;

--2
SELECT last_name, e.department_id, department_name 
FROM   employees e, departments d 
WHERE  e.department_id = d.department_id
 AND e.COMMISSION_PCT IS NOT NULL 
AND d.location_id = 1700;

select *
from departments;

--4
SELECT last_name, job_id, department_name 
FROM   employees e, departments d, locations s 
WHERE  e.department_id = d.department_id 
AND    d.location_id = s.location_id 
AND    city = 'Seattle';
-- afisez angajatii care lucreaaza in seattle fara--job_id, department_name 

--6,7,8, sunt facute mai sus
--9
SELECT last_name, job_id, department_name, grade_level
FROM employees e, departments d,job_grades j
WHERE  e.department_id = d.department_id(+) --plus il baga si pe cel care nu are depratament
AND    salary BETWEEN j.LOWEST_SAL AND j.HIGHEST_SAL
order by 1,4;

desc job_grades
--

--11
SELECT a.employee_id "CodAng", a.last_name "NumeAng",
        b.employee_id "CodMgr", b.last_name "NumeMgr1"  
        c.employee_id "CodMgr2", c.lsat_name "NumeMgr2"
FROM   employees a, employees b,employees c
WHERE  a.manager_id = b. employee_id(+)
AND b.manager_id=c.employee_id;--plus nu e pus bine si nu arata nimic

SELECT a.employee_id "CodAng", a.last_name "NumeAng",
        b.employee_id "CodMgr", b.last_name "NumeMgr1", 
        c.employee_id "CodMgr2", c.last_name "NumeMgr2"
FROM   employees a, employees b,employees c
WHERE  a.manager_id = b. employee_id(+)
AND  b.manager_id =c.employee_id(+);--trebuie sa ii punem in fiecare conditie--este outerjoin

--14
SELECT last_name, hire_date 
FROM   employees 
WHERE  hire_date > (SELECT hire_date                     
                    FROM   employees 
                    WHERE  last_name = 'Fay'); 
--sistemul proceseaza intai subcererea apoi compara mai departe
                    
--15
SELECT a.last_name, a.hire_date 
FROM   employees a, employees b 
WHERE  UPPER(b.last_name)= 'FAY' 
AND    a.hire_date>b.hire_date;

--16
SELECT  last_name, salary,department_id 
FROM    employees 
WHERE   last_name <> 'Fay' 
AND     department_id = (SELECT department_id
                         FROM employees
                         WHERE last_name = 'Fay');
                         
SELECT  last_name, salary,department_id 
FROM    employees 
WHERE   last_name <> 'King' 
AND     department_id in (SELECT department_id
                         FROM employees
                         WHERE last_name = 'King')
order by 3; 
select last_name
from employees
order by 1;

--17
SELECT last_name, salary 
FROM   employees 
WHERE  manager_id = (SELECT employee_id                      
                    FROM   employees                     
                    WHERE  UPPER(last_name) =initcap('KING')
                    AND    UPPER(first_name) = initcap('sTEVEN')); 
                   
                   --e o pb dar nu stiu care            
select last_name
from employees;

--20
SELECT last_name, job_id, department_id 
FROM   employees   
WHERE  department_id IN           
                 (SELECT department_id           
                FROM   departments           
                 WHERE  location_id = (SELECT location_id                                
                                         FROM   locations                                  
                                        WHERE  city = 'Seattle'));
                                        
SELECT last_name, job_id, department_name 
FROM   employees e, departments d, locations s 
WHERE  e.department_id = d.department_id 
AND    d.location_id = s.location_id 
AND    city = 'Seattle';
--mai bun cel de jos cu join decat cel cu subcerere

--22
SELECT last_name, salary, commission_pct, department_id 
FROM   employees  
WHERE (salary, commission_pct) IN      --trebuie sa fie pereche in ambele parti  
        (SELECT salary, commission_pct       
        FROM   employees e, departments d        
        WHERE  e.department_id = d.department_id        
        AND    department_name = 'Sales') 
AND    department_id = (SELECT department_id
                        FROM   departments 
                        WHERE  department_name = 'Sales'); 

--23 alta forma
SELECT last_name, salary, job_id 
FROM   employees 
WHERE  salary > all(SELECT salary                
                FROM   employees                  
                WHERE  job_id LIKE '%CLERK')                 
ORDER BY salary DESC; 




