culoare(rosu).
culoare(galben).
culoare(alb).
frunze(alterne).
frunze(mari).
frunze(nervuri_paralele).
petale(multepetale).
petale(petalegalbene).
petale(grupate_trompeta).
fl(trandafir, rosu, alterne, multepetale).
fl(floarea_soarelui, galben, mari, petalegalbene).
fl(crin, alb, nervuri_paralele, grupate_trompeta).
floare(A, X, Y, Z):-culoare(X), frunze(Y), petale(Z), fl(A,X,Y,Z).

getX('X1').
getZ('Z1').
getX('X2').
getZ('Z2').
wr:-getX(X), getZ(Z), wrXZ(X, Z).
wrXZ(X, Z):-write(X), write(' '), write(Z), write(' '), nl.

f1(X,Y) :- X =< 3,Y is 0;
		  X > 3, X =< 6, Y is 2;
		  X > 6, Y is 4.

f2(X,Y) :- X=<3, Y is 0, ! ;
           X =<6, Y is 2, ! ;
           Y is 4.
fact(X) :- factorial(X,1).
factorial(0,F) :- write(F).
factorial(A,F) :- A2 is A - 1,F2 is F * A,factorial(A2,F2).

%extrage(71) -> (7, sapte); (1, unu).
cifra(0):- write('(0,zero)').
cifra(1):- write('(1,unu)').
cifra(2):- write('(2,doi)').
cifra(3):- write('(3,trei)').
cifra(4):- write('(4,patru)').
cifra(5):- write('(5,cinci)').
cifra(6):- write('(6,sase)').
cifra(7):- write('(7,sapte)').
cifra(8):- write('(8,opt)').
cifra(9):- write('(9,noua)').

extrage(X) :- X > 9, X2 is mod(X,10), X3 is X//10, extrage(X3),write(';'), cifra(X2).
extrage(X) :- X =< 9, cifra(X).

bradut(0).
bradut(X):- X > 0, Y is X - 1, bradut(Y), nl, bradoi(Y).
bradoi(0):- write('*').
bradoi(Y):- Y > 0, Y2 is Y - 1, write('*'), write(' '), bradoi(Y2).