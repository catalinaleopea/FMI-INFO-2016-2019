create or replace function f_dav (role joaca.rol%type) return number
is
    nr number := 0;
    aux number;
    v_id_act actor.id_actor%type;
    v_data actor.data_nastere%type;
    cursor c is select id_actor, data_nastere from actor;
begin
    open c;
    loop
        fetch c into v_id_act, v_data;        
        exit when c%notfound;
        select count(*) into aux
        from actor a join joaca j on (a.id_actor = j.cod_actor)
        where rol = role
        and extract(year from sysdate) - extract(year from v_data) >= 35
        and v_id_act = a.id_actor;
        nr := nr + aux;
    end loop;
    close c;
    exception when no_data_found then raise_application_error('-20004', 'Rolul respectiv nu exista');
    return nr;
end;
/

set serveroutput on;
begin
dbms_output.put_line(f_dav('Rol principal'));
end;
/

select * from spectacol;

create or replace procedure f_dav (stag spectacol.stagiune%type)
is
    v_denumire spectacol.denumire%type;
    v_pret bilet_vandut.pret%type;
    v_nume actor.nume%type;
    cursor c is select denumire, nume, sum(pret)
    from spectacol s join joaca j on (s.id_spectacol = j.cod_spectacol)
                 join actor a on (j.cod_actor = a.id_actor)
                 join bilet_vandut b on (s.id_spectacol = b.cod_spectacol)
    where stagiune = stag
    group by (denumire, nume);
    
begin
    open c;
        fetch c into v_denumire, v_nume, v_pret;
        dbms_output.put_line('Spectacolul se numeste ' || v_denumire || ' si costul total a fost de ' || v_pret || '.');
        dbms_output.put_line(v_nume);
        loop
            fetch c into v_denumire, v_nume, v_pret;
            exit when c%notfound;
            dbms_output.put_line(v_nume);            
        end loop;        
    close c;
end;
/

set serveroutput on;
begin
    f_dav('Stag1');
end;
/

create or replace trigger trig_dav
    before insert on bilet_vandut
    for each row
declare
    v_nr_locuri sala.numar_locuri%type;
    v_nr_locuri_ocupate sala.numar_locuri%type;
begin
    select numar_locuri, numar_locuri_ocupate into v_nr_locuri, v_nr_locuri_ocupate
    from
    (
        select cod_spectacol, id_sala, numar_locuri, count(cod_spectacol) as numar_locuri_ocupate
        from bilet_vandut bv join spectacol sp on (bv.cod_spectacol = sp.id_spectacol)
                             join sala sa on (sp.cod_sala = sa.id_sala)
        group by (cod_spectacol, id_sala, numar_locuri)
    );
    if v_nr_locuri = v_nr_locuri_ocupate then raise_application_error(-20006, 'Sala este deja plina');
    end if;
end;
/                     