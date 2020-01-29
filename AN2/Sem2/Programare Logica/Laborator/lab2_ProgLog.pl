parent_of(rickardStark,eddardStark).
parent_of(rickardStark,lyannaStark).
parent_of(lyarraStark,eddardStark).
parent_of(lyarraStark,lyannaStark).
parent_of(aerysTargaryen,rhaegarTargaryen).
parent_of(rhaellaTargaryen,rhaegarTargaryen).
parent_of(rhaegarTargaryen,jonSnow).
parent_of(lyannaStark,jonSnow).

ancestor_of(X,Y) :- parent_of(X,Y).
ancestor_of(X,Y) :- parent_of(X,Z), ancestor_of(Z,Y).

distance((X1, Y1), (X2, Y2), D) :-
    D is sqrt((X2 - X1) * (X2 - X1) + (Y2 - Y1) * (Y2 - Y1)).

afisLinie(X,_) :- X < 1, nl.
afisLinie(X, Y) :- X > 0, write(Y), X2 is X - 1, afisLinie(X2, Y).

afis(Nr,Nr2,Y) :- Nr2 > 0, afisLinie(Nr, Y),Nr3 is Nr2 -1,afis(Nr, Nr3, Y). 
square(X, Y) :- X > 0, afis(X, X, Y).

fib2(N, Result) :- N < 0 , write('Invalid');
    (N == 0; N == 1),Result is 1;
    N1 is N - 1, N2 is N - 2, fib2(N1, Result1), fib2(N2, Result2), Result is Result1 + Result2.
/*de refacut fibonacci*/