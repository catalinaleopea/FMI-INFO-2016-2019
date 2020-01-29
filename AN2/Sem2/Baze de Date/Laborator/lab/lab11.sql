/* Laboratorul 8 */

/* ex1 */

create table angajati_mcg(
        cod_ang number(3) constraint pk_mcg primary key,
        nume varchar2(20) constraint cnume_mcg not null,
        prenume varchar2(20),
        email char(15),
        data_ang date default sysdate,
        job varchar2(10),
        cod_sef number(4),
        salariu number(8, 2) constraint csalariu_mcg not null,
        cod_dep number(2));
        
desc angajati_mcg;
drop table angajati_mcg;

create table angajati_mcg(
        cod_ang number(3),
        nume varchar2(20) constraint cnume_mcg not null,
        prenume varchar2(20),
        email char(15),
        data_ang date default sysdate,
        job varchar2(10),
        cod_sef number(4),
        salariu number(8, 2) constraint csalariu_mcg not null,
        cod_dep number(2),
        constraint pk_mcg primary key (cod_ang));
        
desc angajati_mcg;

/* ex2 */

insert into angajati_mcg (cod_ang, nume, prenume, data_ang, job, salariu, cod_dep)
            values(100, 'Nume1', 'Prenume1', null, 'Director', 20000, 10);
            
select *
from angajati_mcg;

insert into angajati_mcg
            values(101, 'Nume2', 'Prenume2', 'Nume2', to_date('02-02-2004', 'dd-mm-yyyy'), 
            'Inginer', 100, 10000, 10);

insert into angajati_mcg 
            values(102,'nume3' , 'prenume3', 'nume3',
            to_date('05-06-2000','dd-mm-yyyy'),'Analist', 101, 5000 ,20);
 
insert into angajati_mcg(cod_ang, nume, prenume, data_ang, job, cod_sef, salariu, cod_dep) 
            values(103,'nume4','prenume4',null,'Inginer ',100,9000,20);

insert into angajati_mcg 
            values(104,'nume5', 'prenume5', 'nume5',null,'Analist', 101, 3000 ,30);

select *
from angajati_mcg;

commit;

/* ex3 */

create table angajati10_mcg
             as select * 
             from angajati_mcg
             where cod_dep=10;
             
select *
from angajati10_mcg;

desc angajati10_mcg;

/* ex4 */

alter table angajati_mcg
            add comision number(4,2);

desc angajati_mcg;

select *
from angajati_mcg;

/* Ex6 */

alter table angajati_mcg
            modify (salariu number(6,2)); /*column to be modified must be empty to decrease precision or scale
                                            NU SE POATE IN PLM CA TRE SA FIE NULL SAU GOL CA SA SCAZI */
                                            
alter table angajati_mcg
            modify (salariu number(8,2) default 100);
            
select *
from angajati_mcg;

/* Ex7 */

alter table angajati_mcg
            modify (comision number(8,2), salariu number(10,2));
          
/* Ex8 */

update angajati_mcg
set comision = 0.1
where upper(job) like 'A%';

select *
from angajati_mcg; 

/* Ex9 */

alter table angajati_mcg
            modify (email varchar2(15));

desc angajati_mcg;

/* Ex10 */

alter table angajati_mcg
add (nr_telefon varchar2(10) default '0123456789');

select *
from angajati_mcg;

/* Ex11 */

alter table angajati_mcg
drop column nr_telefon;

select *
from angajati_mcg;

/* Ex12 */

rename angajati_mcg to angajati3_mcg;

desc angajati3_mcg;

/* Ex13 */

select *
from tab;

rename angajati3_mcg to angajati_mcg;

/* Ex14 */

select *
from angajati10_mcg;

truncate  table angajati10_mcg;

rollback;

select *
from angajati10_mcg;

create table departamente_mcg
             (cod_dep number(2),
              nume varchar2(15),
              cod_director number(4));
              
/* Ex16 */

insert into departamente_mcg
values(10, 'Administrator', 100);

insert into departamente_mcg
values(20, 'Administrator', 101);

insert into departamente_mcg
values(30, 'Administrator', 102);

/* Ex17 */

alter table departamente_mcg
add constraint pkey_depart_mcg primary key (cod_dep);

/* Ex18 a */

alter table angajati_mcg
            add constraint fk_depart_mcg foreign key (cod_dep) references departamente_mcg (cod_dep);
            
/* Ex18 b */

drop table angajati_mcg;

create table angajati_mcg(
        cod_ang number(4) constraint pk_mcg primary key,
        nume varchar2(20) constraint cnume_mcg not null,
        prenume varchar2(20),
        email char(15) unique,
        data_ang date default sysdate,
        job varchar2(10),
        cod_sef number(4) constraint sef_ang_mcg references angajati_mcg(cod_ang),
        salariu number(8, 2) constraint csalariu_mcg not null,
        cod_dep number(2) constraint fk_depart_ang_mcg references departamente_mcg(cod_dep),
        comision number(2,2),
        check (cod_dep > 0),
        constraint verificare_salariu_mcg check(salariu > 100 * comision),
        constraint nume_prenume_unique_mcg unique (nume,prenume));
        
        
/* Ex20 */
        
INSERT INTO ANGAJATI_mcg
       VALUES (101,'Nume2','Prenume2','Nume2',TO_DATE('02-02-2004','dd-mm-yyyy'),'Inginer',NULL,10000,10,0.3);
     
INSERT INTO ANGAJATI_mcg
       VALUES (102,'Nume3','Prenume3','Nume3',TO_DATE('02-02-2004','dd-mm-yyyy'),'Inginer',101,10000,20,0.3);
       
COMMIT;

select *
from angajati_mcg;

/* Ex22 */

select constraint_name, constraint_type, table_name
from user_constraints
where lower(table_name) in ('angajati_mcg', 'departamente_mcg');
