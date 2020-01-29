function [f, grad] = objf(x)

f = x(1)*exp(-x(1)^2 - x(2)^2);
grad = [exp(-x(1)^2-x(2)^2)-(2*x(1)^2)*exp(-x(1)^2-x(2)^2) ... 
    -(2*x(1)*x(2))*exp(-x(1)^2-x(2)^2)];

end