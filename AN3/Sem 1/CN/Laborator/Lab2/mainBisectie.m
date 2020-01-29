f = @(x) sqrt(x)-cos(x);
A=0; B=1; epsilon = 10^(-5);

[xaprox,N]=MetBisectie(f,A,B,epsilon);

X=linspace(A,B,10); %Discretizarea intervalului [A,B]
Y=f(X);

figure(1)
plot(X,Y,'--r*')
hold on
plot(xaprox, f(xaprox), 'b*')
hold off
xlabel('x');
ylabel('f(x)');
title('Graficul functiei f');
legend('y = f(x)', 'xNumeric', 'Location', 'NorthWest');
xlim([0.6,0.7])

disp('Valoarea apxorimat a lui xNumeric este')
disp(xaprox)
disp('Iteratia de oprire')
disp(N)