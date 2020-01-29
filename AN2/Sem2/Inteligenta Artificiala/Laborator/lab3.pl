afis([]).
afis([H|T]) :- write(H), write(' '), afis(T).

afis_invers([]).
afis_invers([H|T]) :- afis_invers(T),write(' '),write(H).

adauga_inceput([], E,[E]).
adauga_inceput([H|T], E,[E,H|T]). %[E|[H|T]] sau R):-R=[E,H|T].
adauga_inceput2(L, E,[E|L]).

adauga_final([], E,[E]).
adauga_final([H|T], E,[H|R]) :- adauga_final(T, E, R).

% 1. Verificati daca un element dat se regaseste intr-o lista.
membru(E,[]) :- E == [].
membru(E,[H|T]) :- H == E; membru(E, T).

% 2. Afisati elementul care se afla pe o anumita pozitie intr-o lista.
elem_poz([H|T], Poz, ElemRez) :- Poz == 1 , ElemRez = H;
								 Poz2 is Poz - 1 , elem_poz(T, Poz2, ElemRez).

% 3. Stergeti elementul care se afla pe o anumita pozitie intr-o lista.
sterge_poz([_|T],1,T).   
sterge_poz([H|T],Poz,[H|R]) :- Poz2 is Poz - 1 , Poz2 > 0, sterge_poz(T, Poz2, R).

%4. Stergeti un element dat dintr-o lista.
%doar prima aparitie
sterge_elem([E|T],E,T).
sterge_elem([H|T],E,[H|R]) :- H \== E, sterge_elem(T,E,R).

%toate aparitiile
sterge_toate_elem([],_,[]).
sterge_toate_elem([H|T],E,[H|L]):- E \== H, sterge_toate_elem(T,E,L).
sterge_toate_elem([H|T],E,L):- E == H, sterge_toate_elem(T,E,L).

% 5. Determinati numarul de elemente ale unei liste.
lungime_lista([], 0).
lungime_lista([_|T], Lung) :- lungime_lista(T, L), Lung is L + 1.