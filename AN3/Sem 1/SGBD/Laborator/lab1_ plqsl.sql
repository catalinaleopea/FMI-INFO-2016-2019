-- plsql lab1

--2.	Se dã urmãtorul enun?: Pentru fiecare zi a lunii octombrie (se vor lua în considerare ?i zilele din lunã în care nu au fost realizate împrumuturi) 
--      ob?ine?i numãrul de împrumuturi efectuate.
--a.	Încerca?i sã rezolva?i problema în SQL fãrã a folosi structuri ajutãtoare.
--b.	Defini?i tabelul octombrie_*** (id, data). Folosind PL/SQL popula?i cu date acest tabel. Rezolva?i în SQL problema datã.

--a 
select ziua, (select count(*) from rental where to_char(book_date,'dd.mm.yyyy') = to_char(ziua,'dd.mm.yyyy')) as nr
from  (select trunc(sysdate,'month') + level-1 ziua
       from   dual
       connect by level<=extract (day from last_day(sysdate)));

--b
drop table octombrie_prof;

create table octombrie_prof (id number, data date);

insert into octombrie_prof 
select level, trunc(sysdate,'month') + level-1 ziua
       from   dual
       connect by level<=extract (day from last_day(sysdate));
select * from octombrie_prof;

rollback;

declare
   d date := trunc(sysdate,'month');
   n number := extract(day from last_day(sysdate));
begin
   for i in 1..n loop
      insert into octombrie_prof
      values (i, d);
      --dbms_output.put_line(i || ' ' ||d);
      d := d+1;
  end loop;
end;
/

select * from octombrie_prof;
commit;

--3.Defini?i un bloc anonim în care sã se determine numãrul de filme (titluri) împrumutate de un membru al cãrui nume este introdus de la tastaturã. 
--Trata?i urmãtoarele douã situa?ii: nu existã nici un membru cu nume dat; existã mai mul?i membrii cu acela?i nume.
select last_name from member order by 1;

declare
   v_nume member.last_name%type := initcap('&nume_membru');
   nr    number;
begin
   select count(distinct title) into nr
   from   rental r, member m, title tc
   where  r.member_id = m.member_id
   and    r.title_id = tc.title_id
   and    last_name = v_nume;
   dbms_output.put_line(nr);
end;
/

declare
   v_nume member.last_name%type := initcap('&nume_membru');
   v_id   member.member_id%type;
   nr     number;
begin
   select member_id into v_id from member where last_name=v_nume; 
   
   select count(distinct title) into nr
   from   rental r, title tc
   where  r.member_id = v_id
   and    r.title_id = tc.title_id;
   
   dbms_output.put_line(nr);
exception
   when no_data_found then dbms_output.put_line('Nu exista membrul cu numele dat');
   when too_many_rows then dbms_output.put_line('Exista mai multi membrii cu acelasi nume');
   when others then dbms_output.put_line('alta eroare');
end;
/


--4. Modifica?i problema anterioarã astfel încât sã afi?a?i ?i urmãtorul text:
---	Categoria 1 (a împrumutat mai mult de 75% din titlurile existente)
---	Categoria 2 (a împrumutat mai mult de 50% din titlurile existente)
---	Categoria 3 (a împrumutat mai mult de 25% din titlurile existente)
---	Categoria 4 (altfel)



   