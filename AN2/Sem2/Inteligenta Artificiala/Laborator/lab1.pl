%FISIER UPDATAT
parinte(ion,maria).
parinte(ana,maria).
parinte(ana,dan).
parinte(maria,elena).
parinte(maria,radu).
parinte(elena,nicu).
parinte(andrei,gabriela).
parinte(radu,gigi).
parinte(radu,dragos).
parinte(ion,andrei).
bunic(ion):-parinte(ion,andrei),parinte(andrei,gabriela).

femeie(ana).
femeie(ioana).
femeie(alina).
femeie(georgiana).
femeie(claudia).
femeie(andrada).
femeie(sorana).

barbat(vasile).
barbat(sergiu).
barbat(alin).
barbat(florin).
barbat(dan).
barbat(alexandru).
barbat(gheorghe).
barbat(claudiu).
barbat(andrei).
barbat(bogdan).

%casatorit(ea,el).
casatorit(ana,vasile).
casatorit(ioana,sergiu).
casatorit(alina,florin).
casatorit(claudia,alexandru).
casatorit(andrada,gheorghe).
casatorit(sorana,andrei).

%copil(copil,mama,tata).
copil(ioana,ana,vasile).
copil(dan,ana,vasile).
copil(gheorghe,ana,vasile).
copil(alina,ioana,sergiu).
copil(alin,ioana,sergiu).
copil(georgiana,alina,florin).
copil(andrada,claudia,alexandru).
copil(claudiu,andrada,gheorghe).
copil(andrei,andrada,gheorghe).
copil(bogdan,sorana,andrei).

%A fratele lui B
frate(A,B):-barbat(A),copil(A,M,T),copil(B,M,T),A\==B.

%sora,frati,verisor,verisoara
sora(A,B):-femeie(A),femeie(B),copil(A,M,T),copil(B,M,T),A\==B.
frati(A,B):-copil(A,M,T),copil(B,M,T),A\==B.
verisor(A,B):-barbat(A),copil(A,M1,T1),copil(B,M2,T2),(frati(M1,M2);frati(M1,T2);frati(T1,M2);frati(T1,T2)).
verisoara(A,B):-femeie(A),copil(A,M1,T1),copil(B,M2,T2),(frati(M1,M2);frati(M1,T2);frati(T1,M2);frati(T1,T2)).

%unchi,matusa,cumnat,cumnata
%A e unchiul lui B
unchi(A,B):-barbat(A),copil(B,M,T),(frati(A,M);frati(A,T);(casatorit(Femeie,A),(frati(Femeie,M);frati(Femeie,T)))).
matusa(A,B):-femeie(A),copil(B,M,T),(frati(A,M);frati(A,T);(casatorit(A,Barbat),(frati(M,Barbat);frati(Barbat,T)))).
%UPDATE AICI
cumnat(A,B):-(barbat(A),frati(B,X),casatorit(X,A));(barbat(A),frati(A,X),casatorit(X,B)).
cumnata(A,B):-(femeie(A),casatorit(A,X),frati(B,X));(femeie(A),frati(A,X),casatorit(B,X)).

%bunic,bunica,strabunic,strabunica
bunic(A,B):-barbat(A),copil(B,M,T),(copil(M,_,A);copil(T,_,A)).
bunica(A,B):-femeie(A),copil(B,M,T),(copil(M,A,_);copil(T,A,_)).
strabunic(A,B):-barbat(A),copil(B,M,T),(bunic(A,M);bunic(A,T)).
strabunica(A,B):-femeie(A),copil(B,M,T),(bunica(A,M);bunica(A,T)).