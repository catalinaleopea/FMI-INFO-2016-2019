%%
x = linspace(0, 2 * pi, 10)
y = sin(x)
%plot(x, y, 'O')
%plot(x, y, 'Linewidth', 3)
plot(x, y, '--g', 'Linewidth', 3)
grid on
line(xlim , [0 0])
line([0 0], ylim, 'Linewidth', 3)
z = cos(x)
hold on
plot(x, z)
xlabel('variabila x')
ylabel('variabila y')
title('Graficele functiilor sin(x) si cos(x)')

%%
close all %inchide graficele
x = linspace(0, 2*pi, 10) ;
y=sin(x);
z=cos(x);

x0=pi/2; y0=sin(x0); z0=cos(x0);
plot(x,y,'--r*','LineWidth',3)
hold on %Suprapune noile grafice pe primul grafic
plot(x0,y0,'o','MarkerEdgeColor','k','MarkerSize',10,'MarkerFaceColor','r')
plot(x,z,'-y','LineWidth',3)

%fplot('functia',[a, b], 'linia de specificatori')
figure(2)
fplot('sin(x)',[0, 2*pi],'--r*')

figure(1)
xlabel('Axa Ox ','FontAngle','italic', 'FontName','Monotype Corsiva','FontSize',20,'Color','k')
ylabel('Axa Oy ','FontAngle','italic', 'FontName','Monotype Corsiva','FontSize',20,'Color','k')

figure(1)
title('Graficele functiilor sin(x) si cos(x) ','FontAngle','italic', 'FontName','Arial','FontSize',10,'Color','k')

figure(1)
text(3.5,0,'sin(x)','EdgeColor','r','LineWidth',2)
text(1.8,0,'cos(x)','EdgeColor','y','LineWidth',2)

%%
f = inline('x.^2-3*x', 'x')%am pus punct pentru ca avem un interval mai jos
f(2)
g = inline ('x^2+y^2', 'x', 'y')
g(2,2)
x = linspace(-2, 3, 100)
y = Patratica(x)
plot(x, y)

z = Patratica (2)

function [y] = Patratica(x)
    y = x.^2 - 3*x;
end

%%

f = inline('x.^3-7*x.^2+14*x-6', 'x');
x = linspace(0, 4);
df = inline('3*x.^2-14*x+14', 'x');
esp = 10^(-3);
x0 = 0;
m1 = MetNR(f, df, x0, esp);

plot(x, f(x));
line(xlim , [0 0]);
line([0 0], ylim);

hold on;
plot(m1, f(m1), 'o');

x0 = 2;
m2 = MetNR(f, df, x0, esp);

hold on
plot(m2, f(m2), 'o', 'MarkerFaceColor', 'r', 'Markersize', 10);

x0 = 3.5;
m3 = MetNR(f, df, x0, esp);

hold on
plot(m3, f(m3), 'o', 'MarkerFaceColor', 'r', 'Markersize', 10);