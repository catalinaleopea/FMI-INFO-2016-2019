concat_lists([], List, List).
concat_lists([Elem|List1], List2, [Elem|List3]):- 
	concat_lists(List1, List2, List3).
	
all_a([]).
	all_a([H|T]) :- H == a, all_a(T).

trans_a_b([], []).
trans_a_b([a|T1], [b|T2]) :- trans_a_b(T1, T2).

scalarMult(_, [], []).
scalarMult(X, [H|T], [H2|T2]) :- H2 is X * H, scalarMult(X, T, T2).

dot([], [], 0).
dot([H1|T1], [H2|T2], Rez) :- dot(T1, T2, Rez1), Rez is Rez1 + H1 * H2.

max([], 0).
max([H|T], R) :- max(T, R2),(H > R2 -> (R is H);(R is R2)).

rev([], L, L).
rev([H|T], X, L) :- rev(T, X, [H|L]).

palindrome([H|T]):- rev([H|T], [H|T], []).

remove_dublicates([], []).
remove_dublicates([H|T], T2) :- member(H, T), remove_dublicates(T, T2).
remove_dublicates([X|R1], [X|R2]) :- remove_dublicates(R1, R2).
