% 6. Concatenati doua liste.
% exemplu: concat([1,2], [3,4,5], R). => R=[1,2,3,4,5].
concat([], List, List).
concat([H|T], List, [H|R]) :- concat(T, List, R).

% 7. Verificati daca o lista are duplicate.
% multime(Lista)     yes daca nu exista duplicate, daca Lista este multime;
%                    no daca exista elemente duplicate

multime([]).
multime([H|T]) :- verifica(H,T), multime(T).

verifica(_,[]).
verifica(X, [H|T]) :- X \== H, verifica(X, T).

% 8. Eliminati duplicatele dintr-o lista data.
elim_duplicate([],[]).
elim_duplicate([H|T], [H|R]) :- (verifica(H,T),T2 = T;
                                sterge_toate_elem(T,H,T2)),elim_duplicate(T2,R).

%toate aparitiile
sterge_toate_elem([],_,[]).
sterge_toate_elem([H|T],E,[H|L]):- E \== H, sterge_toate_elem(T,E,L).
sterge_toate_elem([H|T],E,L):- E == H, sterge_toate_elem(T,E,L).

% 9. Se da o lista. Daca toate elementele sale sunt mai mici decat 5,obtineti suma acestora

maiMici([],_).
maiMici([H|T], X) :- H =< X, maiMici(T,X).
suma([H|T],X) :- maiMici([H|T], X), suma2([H|T],0).
suma2([],S) :- write(S).
suma2([H|T],S) :- S2 is S + H,suma2(T,S2).

%10
mereSiPortocale([], 0, 0).
mereSiPortocale([H|T], Mere, Portocale):- H == 'mar', mereSiPortocale(T, Mere1, Portocale), Mere is Mere1 + 1;
    H == 'portocala', mereSiPortocale(T, Mere, Portocale1), Portocale is Portocale1 + 1.

parinte(ion,maria).
parinte(ana,maria).
parinte(ana,maria).
parinte(maria,elena).
parinte(maria,radu).
parinte(elena,nicu).
parinte(radu,gigi).
parinte(radu,dragos).