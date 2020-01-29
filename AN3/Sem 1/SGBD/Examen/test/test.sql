--1
create or replace package pachet is
  --a)
  cursor carti(autor bookauthor.authorid%type) return bookauthor%rowtype;
  --b)
  function nr_exemplare(titlu books.title%type) return number;
  
  --c)
  
  procedure afisare(nume publisher.name%type);
  
end pachet;
/


create or replace package body pachet is
  --a)
  cursor carti(autor bookauthor.authorid%type) return bookauthor%rowtype is
  (
    select isbn, title, pubdate, pubid, cost, retail, category
    from books join bookauthor using(isbn)
    where autorid = autor
  );
  
  --b)
  function nr_exemplare(titlu books.title%type) return number
  is
    nr number;
  begin
    select sum(quantity)
    into nr
    from books join bookorderitems using(isbn)
    where title = titlu;
    return nr;
  exception
    when NO_DATA_FOUND then
      return 0;
  end nr_exemplare;

  --c)
  procedure afisare(id_autor bookauthor.authorid%type) 
  is
    nr number;
    nr_total number := 0;
  begin
    --c1
    DBMS_OUTPUT.PUT_LINE('Autorul ' || id_autor || ' a publicat:');
    for i in carti(id_autor) loop
      DBMS_OUTPUT.PUT_LINE(i.title);
    end loop;
    
    --c2
    
    DBMS_OUTPUT.PUT_LINE('Clienti ai autorului');
    for i in carti(id_autor) loop
      nr := nr_exemplare(i.title);
      if nr = 0 then
        DBMS_OUTPUT.PUT_LINE('Nu a cumparat nimeni titlul' || i.title);
      else
      
        for j in (select lastname, firstname
                  from books join bookorderitems using(isbn)
                             join bookorders using(order)
                             join bookcust using(customer)
                  where title = i.title) loop
          
          DBMS_OUTPUT.PUT_LINE('Nume: ' || j.lastname || '   prenume: ' || j.firstname);      
        end loop;
        
      end if;
      DBMS_OUTPUT.PUT_LINE('Numar exemplare cumparate: ' || nr);
      nr_total := nr_total + nr;
    end loop;
    
    DMBS_OUTPUT.PUT_LINE('Numar total de exemplare: ' || nr_total);
    
  end afisare;
  
end pachet;
/

--2

begin 
  for autor in (select * from bookauthor) loop
    pachet.afisare(autor.authorid);
  end loop;
end;
/























