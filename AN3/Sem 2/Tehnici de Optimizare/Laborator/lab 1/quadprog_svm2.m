function basic_SVM(n,D,S,C)


% This function shows how simple is to train one of the simplest 
% Support Vector Machines, by using Matlab function for 
% quadratic programming (quadprog).
%
% First of all the dataset of n points in 2D is generate, as the union 
% of two subsets of random numbers generated according to two gaussian 
% distributions centered in (-D,-D) and in (+D,+D), respectively,
% with the same standard deviation S.
% Then a SVM is trained, using C as soft margin.
%
% Inputs
%
% n: total number of points (n/2 belongs to each of the two classes)
% D: controls the distance between the two classes.
% S: is the standard deviation of the two gaussian distributions
% C: soft margin of the SVM ( C=0 if the two class are linearly separable )
%
% % Example
% basic_SVM(160,3,1,2);
%
% See also ClassificationSVM, fitcsvm
% This code is just a simple adaptation of the one provided by ali raj:
% https://it.mathworks.com/matlabcentral/fileexchange/51248-svm
% Copyright Marco Cococcioni, 2018-07-17



if nargin < 1, n = 160; end
if nargin < 2, D = 4; end
if nargin < 3, S = 3; end
if nargin < 4, C = 2; end



%% Generate Data
x = [ D + S*randn(n/2,2); 
     -D + S*randn(n/2,2)]';
 
y = [  ones(n/2,1); 
      -ones(n/2,1)  ]';
ClassA = find( y == +1 );
ClassB = find( y == -1 );


%% Design SVM - using only quadprog function
H = zeros(n,n);
for i=1:n
    for j=i:n
        H(i,j) = y(i)*y(j)*x(:,i)'*x(:,j);
        H(j,i) = H(i,j);
    end
end
f = -ones(n,1);
Aeq=y;
beq=0;
lb=zeros(n,1);
ub=C*ones(n,1);
Alg{1}='trust-region-reflective';
Alg{2}='interior-point';
options=optimset('Algorithm',Alg{2},...
    'Display','off',...
    'MaxIter',20);
alpha=quadprog(H,f,[],[],Aeq,beq,lb,ub,[],options)';
AlmostZero=(abs(alpha)<max(abs(alpha))/1e5);
alpha(AlmostZero)=0;
S=find(alpha>0 & alpha<C);
w=0;
for i=S
    w=w+alpha(i)*y(i)*x(:,i);
end
b=mean(y(S)-w'*x(:,S));
%% Plot Results
Line = @(x1,x2) w(1)*x1+w(2)*x2+b;
LineA = @(x1,x2) w(1)*x1+w(2)*x2+b+1;
LineB = @(x1,x2) w(1)*x1+w(2)*x2+b-1;
figure;
plot(x(1,ClassA),x(2,ClassA),'ro');
hold on;
plot(x(1,ClassB),x(2,ClassB),'bs');
plot(x(1,S),x(2,S),'ko','MarkerSize',12);
x1min = min(x(1,:));
x1max = max(x(1,:));
x2min = min(x(2,:));
x2max = max(x(2,:));
handle = ezplot(Line,[x1min x1max x2min x2max]);
set(handle,'Color','k','LineWidth',2);
handleA = ezplot(LineA,[x1min x1max x2min x2max]);
set(handleA,'Color','k','LineWidth',1,'LineStyle',':');
handleB = ezplot(LineB,[x1min x1max x2min x2max]);
set(handleB,'Color','k','LineWidth',1,'LineStyle',':');
legend('Class A','Class B');