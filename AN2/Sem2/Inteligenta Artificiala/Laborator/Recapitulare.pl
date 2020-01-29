
/* Lab 11

La fiecare ex sa dam si un exemplu de interogare */

%ex1

ex1(M) :- matrice1(M,1).

matrice1([],_).
matrice1([H|T],L) :- afisSpecial(H,L,1), L1 is L+1, matrice1(T,L1).

afisSpecial([],_,_).
afisSpecial([H|T],L,C) :- H =< L+C, write(H), write(' '), C1 is C+1, afisSpecial(T,L,C1).
afisSpecial([H|T],L,C) :- H > L+C, C1 is C+1, afisSpecial(T,L,C1).

/* exexmple:
?- ex1([[1,2,3],[4,5,6],[7,8,9]]). => 1 2 3 yes
?- ex1([[1,2,3],[1,2,3],[1,2,3]]). => 1 2 3 1 2 3 1 2 3 yes
*/

%ex2
/*
?-ex2(t(10,t(5,t(2,t(1,nil,nil),t(3,nil,nil)),t(7,t(6,nil,nil),t(9,nil,nil))),t(15,t(13,nil,t(14,nil,nil)),t(18,t(17,nil,nil),nil))),L). => L = [5,2,1,3,7,6,9,15,14,17] yes */


ex2(Arbore,L) :- el(Arbore,NSt,NDr,L).

% NSt nr nodurilor din subarborele stg
% NDr nr nodurilor din subarborele dr

el(t(R,nil,nil),0,0,[R]). % e frunza

el(t(R,S,D),NSt,NDr,L) :- (S \== nil -> (el(S,NSt1,NDr1,L1), NSt is NSt1+NDr1+1);
										(NSt is 0, L1 = [])),
						  (D \== nil -> (el(D,NSt2,NDr2,L2), NDr is NSt2+NDr2+1);
										(NDr is 0, L2 = [])),
						  (NSt =:= NDr -> (append(L1,L2,L3), L = [R|L3]);
										(append(L1,L2,L))).

















