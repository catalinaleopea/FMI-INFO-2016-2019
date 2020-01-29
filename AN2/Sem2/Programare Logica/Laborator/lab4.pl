connected(1,2).
connected(3,4).
connected(5,6).
connected(7,8).
connected(9,10).
connected(12,13).
connected(13,14).
connected(15,16).
connected(17,18).
connected(19,20).
connected(4,1).
connected(6,3).
connected(4,7).
connected(6,11).
connected(14,9).
connected(11,15).
connected(16,12).
connected(14,17).
connected(16,19).

path(A,B):-connected(A,B).
path(A,B):-connected(A,X),path(X,B).

successor(L,[x|L]).

plus(L1,L2,Result):-append(L1,L2,Result).

times([],_,[]).
times([_],L,L).
times([_|T],L,Result):-times(T,L,R),plus(R,R,Result).
element_at([],_,_):-false.
element_at([H|_],1,X):-X=H.
element_at([_|T],N,X):-N1 is N-1,element_at(T,N1,X).

% Crossword puzzle

word(abalone,a,b,a,l,o,n,e).
word(abandon,a,b,a,n,d,o,n).
word(enhance,e,n,h,a,n,c,e).
word(anagram,a,n,a,g,r,a,m).
word(connect,c,o,n,n,e,c,t).
word(elegant,e,l,e,g,a,n,t).

crosswd(V1,V2,V3,H1,H2,H3):-word(V1,_,A1,_,B1,_,C1,_),word(V2,_,A2,_,B2,_,C2,_),
    word(V3,_,A3,_,B3,_,C3,_),word(H1,_,A1,_,A2,_,A3,_),word(H2,_,B1,_,B2,_,B3,_),
    word(H3,_,C1,_,C2,_,C3,_).
born(jan, date(20,3,1977)).
born(jeroen, date(2,2,1992)).
born(joris, date(17,3,1995)).
born(jelle, date(1,1,2004)).
born(joan, date(24,12,0)).
born(joop, date(30,4,1989)).
born(jannecke, date(17,3,1993)).
born(jaap, date(16,11,1995)).

year(Y,Person):-born(Person, date(,,Y)).

before(date(,,Y1),date(,,Y2)):-Y1<Y2.
before(date(,M1,),date(,M2,)):-M1<M2.
before(date(D1,_,_),date(D2,_,_)):-D1<D2.

older(Person1,Person2):-born(Person1,date(D1,M1,Y1)),born(Person2,date(D2,M2,Y2)),
    before(date(D1,M1,Y1),date(D2,M2,Y2)).