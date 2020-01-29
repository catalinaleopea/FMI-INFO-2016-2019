--exemplu
Vrem sa afisam angajatii care lucreaza la toate proiectele care au acelasi manager

--not exists
angajat - lucreaza - proiect
proiect - are - manager

select *
from employees e
where NOT EXISTS(select *
                --toti angajatii care lucreaza pe proiecte cu managerii de mai jos
                 from works_on wo
                 where NOT EXISTS(select *
                                  --proiectele pentru toti managerii
                                  from project p
                                  where e.manager_id = p.project_manager
                                  )
                )

--ex lab 6 PT EXAMEN!! 
Sa se obtina codurile salariatilor atasati tuturor proiectelor pentru care s-a alocat un buget
egal cu 10000.
--Metoda 1 (utilizând de 2 ori NOT EXISTS):
SELECT DISTINCT employee_id
FROM works_on a
WHERE NOT EXISTS 
      (SELECT 1
       FROM project p
       WHERE budget=10000
       AND NOT EXISTS 
           (SELECT 'x'
            FROM works_on b
            WHERE p.project_id=b.project_id
            AND b.employee_id=a.employee_id)
        );
                                  
--Metoda 2 (simularea diviziunii cu ajutorul functiei COUNT):
SELECT employee_id
FROM works_on
WHERE project_id IN
                (SELECT project_id
                 FROM project
                WHERE budget=10000)
GROUP BY employee_id
HAVING COUNT(project_id)=
                         (SELECT COUNT(*)
                          FROM project
                          WHERE budget=10000);
                                  
                                  
--Metoda 3 (operatorul MINUS):
SELECT employee_id
FROM works_on --toti angajatii care lucreaza la proiecte

MINUS --din care eliminam pe cei care lucreaza la proiecte diferite de 10000

SELECT employee_id from
      (SELECT employee_id, project_id
       FROM (SELECT DISTINCT employee_id FROM works_on) t1,
            (SELECT project_id FROM project WHERE budget=10000) t2
             --angajatii care lucreaza la proiecte de 10000
       MINUS --eliminam 
             
       SELECT employee_id, project_id FROM works_on
       )t3; --angajatii care lucreaza la proiecte in general
        -- rezulta anagajatii care lucreaza la proiecte diferite de 10000       
--la final vom obtine angajatii proiectelor de 10000

--Metoda 4 (A include B => B\A = Ø):
SELECT DISTINCT employee_id
FROM works_on a --toti angajatii care lucreaza la proiecte in general
WHERE NOT EXISTS (
                  (SELECT project_id
                   FROM project p
                   WHERE budget=10000) --din toate proiectele cu bugete de 10000
 
MINUS --eliminam
                  
                  (SELECT p.project_id
                   FROM project p, works_on b
                   WHERE p.project_id=b.project_id
                   AND b.employee_id=a.employee_id)
                   --toate proiectele la care ang curent lucreaza
                  );
--obtinem proiecte de 10000 la care nu lucreaza anagajatul

--EXERCITII
--1. Sa se listeze informatii despre angajatii care au lucrat în toate proiectele demarate în primele 6
luni ale anului 2006. 

select employee_id
from works_on
where project_id IN (select project_id
                     from project
                     where start_date >= to_date('01-JAN-06')
                     and start_date <= to_date('01-JUN-06')
                     );

--2. Sa se listeze informatii despre proiectele la care au participat toti angajatii care au detinut alte 2
posturi în firma.

select *
from project
where project_id IN (select project_id
                     from works_on
                     where employee_id IN 
                                       (select employee_id
                                        from job_history
                                        group by employee_id
                                        having count(job_id) = 2) --angajati care au detinut alte doua posturi in firma
                     group by project_id --grupand putem numara cati
                     --angajati sunt pe acelasi id de proiect
                     --si acest numar trebuie sa fie egal cu numarul de angajati care au detinut alte doua posturi in firma
                     having count(*)=(select count(count(*))
                                      from job_history
                                      group by employee_id
                                      having count(job_id)=2
                                      )
                    );

--3. Sa se obtina numarul de angajati care au avut cel putin trei job-uri, luându-se în considerare si
job-ul curent.

select count(employee_id)
from(select employee_id,count(job_id) "Numar job-uri"
     from job_history
     group by employee_id
     )
where "Numar job-uri" >= 2;

--4. Pentru fiecare tara, sa se afiseze numarul de angajati din cadrul acesteia.
select count(employee_id)
from employees e join departments d using(department_id)
                 join locations l using(location_id)
                 join countries c using(country_id)
group by country_id;

--5. Sa se listeze codurile angajatilor si codurile proiectelor pe care au lucrat. Listarea va cuprinde si
angajatii care nu au lucrat pe nici un proiect.

select employee_id,project_id
from employees e left join works_on wo using(employee_id);

--6. Sa se afiseze angajatii care lucreaza în acelasi departament cu cel putin un manager de proiect.
select *
from employees
where department_id in (
                        select distinct department_id
                        from employees e join project p on e.employee_id = p.project_manager
                        );

--7. Sa se afiseze angajatii care nu lucreaza în acelasi departament cu nici un manager de proiect.
select *
from employees
where department_id not in (
                        select distinct department_id
                        from employees e join project p on e.employee_id = p.project_manager
                        );

--8. Sa se determine departamentele având media salariilor mai mare decât un numar dat.
select department_id,round(avg(salary))
from employees
group by DEPARTMENT_ID
HAVING AVG(salary) > &p;--cere o valoare de la tastatura de fiecare data

select &&x--cere o singura data valoarea si o pastreaza pt o perioada de timp
from dual;

select &y
from dual;

undefine x;

select last_name,&x
from employees;

--sa se afiseze numele din 7 in 7 intre doua numere x si y
--level numara pozitia inclusiv pozitia de unde incepem

undefine x;
undefine y;
select &&x+level - 1
from dual
where mod(level,7) = 0
connect by &&x+level < = &&y;

x=1;
x=21;