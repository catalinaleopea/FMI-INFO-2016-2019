% Calculeaza sin x
function [y] = fsin(x, grafice)
    y=sin(x);
    if(strcmpi(grafice,'DA'))
        figure(1);
        plot(x,y,'--bo');
        hold on;
        xlabel('x','FontName','Times New Roman','FontSize',25);
        ylabel('f(x)');
        %legend('sin(x)','cos(x)','Location','northwest');
        title('titlu');
        hold off;
    end
end