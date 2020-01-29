
x=0:0.1:4*pi;
y=sin(x);
z=cos(x);
hold on;
figure(1);
plot(x,y,'--b*');
plot(x,z);
xlabel('x','FontName','Times New Roman','FontSize',25);
ylabel('f(x)');
legend('sin(x)','cos(x)','Location','northwest');
title('titlu');
hold off;
