--ex 3--
create or replace procedure ex3(p_oras turist.oras%type) is
create or replace type coduri is table of turist.id_turist%type;
turisti coduri;
zile number;
nume_t turist.nume%type
begin
	select id_turist bulk collect into turisti
	from turist
	where oras = p_oras;
	
	for turist in turisti loop
		select nume into nume_t
		from turist
		where id_turist = turist;
		dbms_output.put_line('Nume turist: '||nume_t);
		
		for excursie in (select denumire from achizitioneaza join excursie on (cod_excursie=id_excursie) where cod_turist = turist) loop
			dbms_output.put_line('Nume excursie: '||excursie);
		end loop;
		
		zile := -1;
		for data_ex in (select data_inceput from achizitioneaza join excursie on (cod_excursie=id_excursie) where cod_turist = turist) loop
			if data_ex > sysdate then
				if zile = -1 then
					zile = data_ex - sysdate;
				else
					if zile > data_ex - sysdate then
						zile = data_ex - sysdate;
					end if;
				end if;
			end if;
		end loop;
		if zile = -1 then
			dbms_output.put_line('Nu urmeaza nicio excursie');
		else
			dbms_output.put_line('Urmatoarea exucursie in '||zile);
		end if;
		
		---
		select min(data_inceput - sysdate) into zile
		from achizitioneaza join excursie on (cod_excursie=id_excursie) 
		where cod_turist = turist and data_inceput > sysdate;
		
		if SQL%NOT_FOUND then
			dbms_output.put_line('Nu urmeaza nicio excursie');
		else
			dbms_output.put_line('Urmatoarea exucursie in '||zile);
		end if;
		----
		
	end loop;
end;


--ex 2--
create or replace type ex_nr is object ( id_ex excursie.id_excursie%TYPE , nr_zile number);

create or replace type vect_ex_nr is varray(100) of ex_nr;

alter table turist add info vect_ex_nr;

declare 
lista vect_ex_nr;
begin
	for turist in (select id_turist from turist) loop
		select ex_nr(id_excursie, data_sfarsit - data_inceput) bulk collect into lista
		from achizitioneaza join excursie on (cod_excursie=id_excursie) where cod_turist = turist;
		
		update turist
		set info = lista
		where id_turist = turist;
	end loop;
end;

--ex 4--

create or replace function ex4(ag_p agentie.id_agentie%type) return number is nr number;
id_ex excursie.id_excurise%type;
id_tur turist.id_turist%type;
varsta number;
begin

	select count(*) into nr
	from agentie
	where id_agentie = ag_p;
	
	if nr !=1 then
		raise_application_error(-20500,'Agentie invalida');
	end if;
	
	select count(*) into nr
	from excursie join achizitioneaza on (id_excurise = cod_excursie)
	where cod_agentie = ag_p;
	
	if nr<1 then
		raise_application_error(-20501,'Agentia nu are excursii valide');
	end if;
	
	select top 1 id_excurise into id_ex
	from excursie join achizitioneaza on (id_excurise = cod_excursie)
	where pret = (select max(pret)
				from excursie join achizitioneaza on (id_excurise = cod_excursie)
				where cod_agentie = ag_p) and cod_agentie = ag_p;
				
	select top 1 id_turist into id_tur
	from turist join achizitioneaza on (id_turist = cod_turist)
	where cod_excursie = id_ex and data_nasterii = (select max(data_nasterii)
						from turist join achizitioneaza on (id_turist = cod_turist)
						where cod_excursie = id_ex);
	
	select sysdate - data_nasterii into varsta
	from turist
	where id_turist = id_tur;
	
	return varsta;
end;












