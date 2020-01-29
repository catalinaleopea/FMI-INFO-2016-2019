function [] = exemplu_fminunc()

%%% Punct initial al algoritmului folosit de fminunc
x0 = [-1,2]; 

%%% Setari fminunc: specificam ca in objf 
%%% este cuprins si gradientul functiei obiectiv
optiuni = optimset('GradObj','on');

%%% Apel fminunc
[x,fval] = fminunc( @objf , x0);
[f0,grad0] = objf(x0);


%%% Se ploteaza functia obiectiv, punct initial (x0) si 
%%% punct de convergenta produs de fminunc
figure;
plot3(x0(1),x0(2),f0,'-k*','MarkerSize',14);
hold on;
plot3(x(1),x(2),fval,'-m*','MarkerSize',14);
hold on;
ezsurf('x*exp(-x^2 - y^2)',[-4,4],[-4,4]);





end