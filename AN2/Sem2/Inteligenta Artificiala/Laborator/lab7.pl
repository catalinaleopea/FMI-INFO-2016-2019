arbore(t(t(t(t(nil,1,nil),2,t(nil,3,nil)),5,t(t(nil,6,nil),7,t(nil,9,nil))),10,t(t(nil,13,t(nil,14,nil)),15,t(t(nil,17,nil),18,nil)))).

/*NEIMPLEMENTATE
5. Scrieti un predicat cu care sa obtineti media elementelor dintr-un arbore.
8. Extrageti intr-o lista muchiile dintr-un arbore. Exemplu : [(5,2),(2,1),(2,3),(5,6),(6,7)]
*/

%1. Scrieti un predicat cu care sa afisati in preordine, inordine, respectiv postordine arborele de mai sus.

afisPre :- arbore(T),afiseaza(T).
afiseaza(nil).
afiseaza(t(S,R,D)):-write(R),write(' '), afiseaza(S), afiseaza(D).

afisIn(T) :-afiseaza2(T).
afiseaza2(nil).
afiseaza2(t(S,R,D)):- afiseaza2(S),write(R),write(' '), afiseaza2(D).

afisPost :-arbore(T),afiseaza3(T).
afiseaza3(nil).
afiseaza3(t(S,R,D)):- afiseaza3(S), afiseaza3(D),write(R),write(' ').


% 2. Scrieti un predicat cu care sa determinati numarul de frunze din arborele de mai sus. Testati si cu un alt arbore.

frunze(Nr) :- arbore(T), cauta(T,Nr2), Nr is Nr2.
cauta(nil,0).
cauta(t(nil,_,nil),1).
cauta(t(S,_,D),Nr) :- cauta(S,Nr2),cauta(D,Nr3), Nr is Nr2+ Nr3. 


%3. Scrieti un predicat cu care sa obtineti numarul de noduri care au valoarea mai mare decat un numar dat.

noduri(X,Nr) :- arbore(T),cauta2(T,X,Nr2), Nr is Nr2.
cauta2(nil,_,0).
cauta2(t(S,R,D),X,Nr) :- cauta2(S,X,Nr2), cauta2(D,X,Nr3), (R > X -> Nr is 1 + Nr2+ Nr3;
								   Nr is Nr2 + Nr3).


%4. Scrieti un predicat cu care sa obtineti cel mai mic, respectiv cel mai mare element dintr-un arbore.
%M e ultimul maxim gasit NU MERGE
maxim(M) :- arbore(T), cauta3(T,0,M2), M is M2.
cauta3(nil,M,M).
cauta3(t(nil,R,nil),M,Max) :- Max is max(R,M).
cauta3(t(S,R,D),M,Max) :- cauta3(S,M,Max2),cauta2(D,M,Max3), MaxI is max(M,R), MaxJ is max(Max2,Max3),Max is max(MaxI,MaxJ),M is Max.


%6. Scrieti un predicat cu care sa obtineti suma nodurilor de la un anumit nivel intr-un arbore. (Consideram radacina avand nivelul 1.)

sumList([],0).
sumList([H|T],S) :- sumList(T,S2),S is S2 + H.

nivel(t(_,R,_),1,[R]).
nivel(t(S,_,D),N,L) :- N2 is N - 1, nivel(S,N2,L1), nivel(D,N2,L2), 
			 append(L1,L2,L).
nivelN(N,S) :-arbore(T),nivel(T,N,L), sumList(L,S).


% 7. Se da o lista de elemente. Formati un arbore binar de cautare folosind elementele din lista. Ordinea in care elementele apar in lista este ordinea in care vor fi adaugate in arbore.

add(t(nil,R,nil),t(S,R,D),E) :- E > R, S = nil, D = E;
				S = E,D = nil.
add(t(S,R,D),Arb,E) :- E > R, add(D,Arb1,E),Arb = t(S,R,Arb1);
		       add(S,Arb1,E), Arb = t(Arb1,R,D).

add(t(nil,R,D),T,E) :- E =< R,T = t(t(nil,E,nil),R,D);
			add(D,D2,E), T = t(nil,R,D2).

add(t(S,R,nil),T,E) :- E >R, T = t(S,R,t(nil,E,nil));
			add(S,S2,E),T = t(S2,R,nil).

creeazaArbore([],T) :- afisIn(T).
creeazaArbore([H1,H2|Tail],T) :- add(t(nil,H1,nil),T,H2),creeazaArbore(Tail,T).