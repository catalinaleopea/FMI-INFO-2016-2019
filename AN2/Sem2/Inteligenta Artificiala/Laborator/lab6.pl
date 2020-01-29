matrice([[1,2,3],[4,5,6],[7,8,9]]).
matrice4([[1,0,0],[0,1,0],[0,0,1]]).
matrice7([[1,2,3,7,9],[4,5,6,8,7],[7,8,9,6,4]]).

linie(Nr, [H|T]) :- Nr > 1, Nr1 is Nr - 1, linie(Nr1, T); write(H).

coloana(Nr, [H|T]) :- afisare(H, Nr), coloana(Nr, T).
afisare([], 0).
afisare([H|T], Nr) :- Nr > 1, Nr1 is Nr - 1, afisare(T, Nr1); Nr == 1, write(H), write(' ').

%Nu stiu daca merge
%diag_principala([], _).
%diag_principala([_|T], 0) :- diag_principala(T, 1). 
%diag_principala([H|T], Nr) :- afisare1(H, Nr), Nr1 is Nr + 1, diag_principala(T, Nr1). 
%afisare1(_, 0) :- nl.
%afisare1([H|T], Nr) :- Nr > 1, Nr1 is Nr - 1, write(H), write(' '), afisare1(T, Nr1).
%3 Se dă o matrice, M. Afişaţi elementele de sub diagonala principală.
afis_elem_for_diag(_,X,X).
afis_elem_for_diag([H|T],X,Y):-(Y<X->write(H),write(' ');write('')),
								Z is Y+1,afis_elem_for_diag(T,X,Z).

elem_diagonala([H|T]):-elem_diagonala2(T,2,1).

elem_diagonala2([],_,_).
elem_diagonala2([H|T],X,Y):-afis_elem_for_diag(H,X,Y),write('\n'),Z is X+1,
							elem_diagonala2(T,Z,Y).
							
%4 Se dă o matrice. Să se verifice dacă are 1 pe diagonale şi 0 în rest. 
matrice_cu_0_1([], _).
matrice_cu_0_1([H|T], Nr) :- length(H,Lungime),verificare(H, Nr, Nr,Lungime), Nr1 is Nr + 1, matrice_cu_0_1(T, Nr1).
verificare([],_, ,).
verificare([H|T], Nr, Nr1,Lungime) :- (Nr == Nr1 ; Nr + Nr1 == Lungime - 1), H == 1, verificare(T, Nr, Nr1,Lungime); 
							          (Nr \== Nr1 ; Nr + Nr1 \== Lungime - 1),H == 0, verificare(T, Nr, Nr1,Lungime).

%5 Se dă o listă, L1, cu elemente de forma [Element/Clasa | Tail]. Formaţi o nouă listă, L2, care să conţină subliste cu elemente ce fac parte din aceeasi Clasa în L1.
%Exemplu:L1=[mar/fruct, portocala/fruct, caine/animal, cal/animal, narcisa/floare]
%=> L2=[ [mar, portocala], [caine, cal], [narcisa]]       

get_elements_by_a_class(_,[],[]).
get_elements_by_a_class(Class,[H/Class|T],[H|L]):-get_elements_by_a_class(Class,T,L),!.
get_elements_by_a_class(Class,[H/H2|T],L):-get_elements_by_a_class(Class,T,L),!.

list_of_classes([],[]).
list_of_classes([H/Class|T],List):-list_of_classes(T,Listaux),(member(Class,Listaux)->List = Listaux;
									List =[Class|Listaux]).

initiate([]).
initiate([H|T]):-initiate(T).

rez([],_,[]).
rez([Chead|Ctail],[H/Class|T],W):-rez(Ctail,[H/Class|T],W2),get_elements_by_a_class(Chead,[H/Class|T],R),W = [R|W2].

element_class([H/Class|T],L):-list_of_classes([H/Class|T],Clist),rez(Clist,[H/Class|T],L).


%6 Se dă o matrice M1. Obţineţi o matrice M2 care sa fie transpusa lui M1
get_the_n_element([H|T],N,N,H).
get_the_n_element([H|T],N,Contor,Numarul_cautat):-Q is Contor+1,get_the_n_element(T,N,Q,Numarul_cautat).

create_line(_,[],[]).
create_line(N,[H|T],Linian):-create_line(N,T,Linian2),get_the_n_element(H,N,1,Q),
							Linian=[Q|Linian2].

transpune([H|T],M2):-count([H|T],Limitasuperioara),transpune2([H|T],M2,0,Limitasuperioara).

transpune2(_,[],X,X).
transpune2([H|T],M2,N,W):-Q is N+1,transpune2([H|T],Mj2,Q,W),
						create_line(Q,[H|T],Newline),
						M2 = [Newline|Mj2],!.

%7 Se dă o matrice M. Afişaţi o parte din ea:
% ex (LinieStart, LinieStop, ColoanaStart, ColoanaStop)
show_i_j_element([H|T],I,J,Ind1,Ind2):-(Ind1<I->Q is Ind1+1,show_i_j_element(T,I,J,Q,Ind2);get_the_n_element(H,J,1,Q),write(Q),write(' ')).
%afis_minimatrice([H|T],LinieStart,LinieStop,ColoanaStart,ColoanaStop):-afis_second([H|T],LinieStart, LinieStop, ColoanaStart, ColoanaStop,LinieStart,ColoanaStart).
afis_second([H|T],LinieStart, LinieStop, ColoanaStart, ColoanaStop,LinieStop,J):-
    (J < ColoanaStop -> show_i_j_element([H|T], LinieStop, J, 1, 1), Q is J+1, afis_second([H|T], LinieStart, 
                       LinieStop, ColoanaStart, ColoanaStop,LinieStop,Q)).

afis_second([H|T],LinieStart, LinieStop, ColoanaStart, ColoanaStop,I,J):-
    (J =< ColoanaStop -> show_i_j_element([H|T],I,J,1,1),Q is J+1,afis_second([H|T],LinieStart, LinieStop, ColoanaStart, ColoanaStop,I,Q);
																		(I < LinieStop->write('\n'),Nextline is I+1,afis_second([H|T],LinieStart, LinieStop, ColoanaStart, ColoanaStop,Nextline,ColoanaStart);write(''))).