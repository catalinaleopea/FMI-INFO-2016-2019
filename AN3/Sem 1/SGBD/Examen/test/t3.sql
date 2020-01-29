drop table sustine;
drop table sponsor;
drop table vestimentatie;
drop table prezentare;


create table prezentare (
cod_pr number(5) primary key,
data date,
oras varchar2(25),
nume varchar2(30));

create table sponsor(
cod_sponsor number(5) primary key,
nume varchar2(30),
info varchar2(50),
tara_origine varchar2(30));

create table sustine(
cod_pr number(5) references prezentare(cod_pr),
cod_sp number(5) references sponsor(cod_sponsor),
suma number(12),
primary key(cod_pr, cod_sp));

create table VESTIMENTATIE( cod_vestimentatie number(6) Primary key, 
denumire varchar2(30), 
valoare number(5), 
cod_prezentare number(5) references prezentare);


insert into prezentare values (4500, TO_DATE('12-05-2002', 'DD-MM-YYYY'), 'Milan', 'Spring 2002');
insert into prezentare values (4501, TO_DATE('2-09-2002', 'DD-MM-YYYY'), 'Paris', 'Automne 2002');
insert into prezentare values (4502, TO_DATE('28-04-2002', 'DD-MM-YYYY'), 'New York', 'Spring 2003');
insert into prezentare values (4503, TO_DATE('2-05-2004', 'DD-MM-YYYY'), 'Rome', 'Spring 2004');
insert into prezentare values (4504, TO_DATE('5-04-2002', 'DD-MM-YYYY'), 'Paris', 'Printemps 2002');
insert into prezentare values (4505, TO_DATE('19-08-2002', 'DD-MM-YYYY'), 'Milan', 'Fall 20025');
insert into prezentare values (4506, TO_DATE('17-04-2005', 'DD-MM-YYYY'), 'Milan', 'Spring 2005');
insert into prezentare values (4507, TO_DATE('2-02-2006', 'DD-MM-YYYY'), 'Milan', 'Spring 2006');

insert into sponsor values(5200, 'Saphire Inc.', 'cosmetics company', 'US');
insert into sponsor values(5201, 'World''s tissues', 'textiles company', 'France');
insert into sponsor values(5202, 'Exotic scents', 'cosmetics company', 'Italy');
insert into sponsor values(5203, 'Natural', 'cosmetics company', 'France');
insert into sponsor values(5204, 'Cover', 'textiles company', 'Italy');
insert into sponsor values(5205, null, 'textiles company', 'Italy');
insert into sponsor values(5206, null, 'textiles company', 'France');

insert into sustine values(4500, 5203, 20000);  
insert into sustine values(4500, 5204, 25000);  
insert into sustine values(4501, 5206, 10000);  
insert into sustine values(4501, 5203, 20000);  
insert into sustine values(4501, 5202, 30000);  
insert into sustine values(4506, 5203, 12000);  
insert into sustine values(4507, 5204, 25000);  
insert into sustine values(4505, 5201, 22000);  
insert into sustine values(4502, 5203, 15000);  
insert into sustine values(4503, 5203, 18000);  
insert into sustine values(4500, 5205, 16000);  

insert into vestimentatie values(6300, 'black dress', 4000, 4504); 
insert into vestimentatie values(6301, 'rain coat', 2200, 4504); 
insert into vestimentatie values(6302, 'red shoes', 1750, 4502); 
insert into vestimentatie values(6303, 'silk scarf', 400, 4507); 
insert into vestimentatie values(6304, 'bride dress', 5000, 4507); 
insert into vestimentatie values(6305, 'black skirt', 2310, 4504); 
insert into vestimentatie values(6306, 'yellow dress', 350, 4507); 
insert into vestimentatie values(6307, 'orange shirt', 1000, 4505); 
insert into vestimentatie values(6308, 'brown boots', 670, 4503); 
insert into vestimentatie values(6309, 'white scarf', 460, 4502); 
insert into vestimentatie values(6310, 'black hat', 1300, 4501);
insert into vestimentatie values(6311, 'blue dress', 1250, 4502); 
insert into vestimentatie values(6312, 'pink skirt', 2100, 4505); 
insert into vestimentatie values(6313, 'bride dress', 4300, 4504); 
insert into vestimentatie values(6314, 'coat', 3000, 4506);
insert into vestimentatie values(6315, 'white dress', 3000, null);  
insert into vestimentatie values(6316, 'RED DRESS', 1300, 4504);
insert into vestimentatie values(6317, 'coat', 560, 4500);  

commit;


