%Leopea Catalina,grupa 243,numarul 1

%1.1
%p1(Lista,X,ListaRez).
p1([],_,[]).
p1([H|T],X,[H,H|R]):- H >= X, p1(T,X,R).
p1([H|T],X,[H|R]):- p1(T,X,R).

%1.2
%p2(Lista,ListaRez).
p2([],[]).
p2([_],[]).
p2([_,H2|T],[H2|R]):- p2(T,R).

%1.3
%p3(Lista,NrPare).
p3([],0).
p3([H|T],Nr):- H mod 2 =:= 0 -> p3(T,Nr2), Nr is Nr2 + 1 ; p3(T,Nr2),Nr is Nr2.

%2
%adun(ListaNr1,ListaNr2,ListaSuma).
adun([],[],[]).
adun([],T,T).
adun(T,[],T).
%mai intai verific daca este instantiat elementul din lista si daca este cifra,apoi il prelucrez
adun([H1|T1],[H2|T2],[R1|R2]):- member(H1,[0,1,2,3,4,5,6,7,8,9]),
								member(H2,[0,1,2,3,4,5,6,7,8,9]),
								R1 is H1 + H2, adun(T1,T2,R2).
adun([H1|T1],[H2|T2],[R1|R2]):- member(R1,[0,1,2,3,4,5,6,7,8,9]),
								member(H2,[0,1,2,3,4,5,6,7,8,9]),
								H1 is R1 - H2, adun(T1,T2,R2).
adun([H1|T1],[H2|T2],[R1|R2]):- member(R1,[0,1,2,3,4,5,6,7,8,9]),
								member(H1,[0,1,2,3,4,5,6,7,8,9]),
								H2 is R1 - H1, adun(T1,T2,R2).