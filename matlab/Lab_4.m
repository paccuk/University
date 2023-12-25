clc
close all
clear all

format short
a = 0.2 + 0.2 + 0.2;
a == 0.6;
format default

format long e
x = [exp(1), -pi, sqrt(2), -psi(1), log10(2)];
y = [1486.2497, 878366.9879, -22.37492, 4773714.647, 0.000185049];
r1 = x*y';
r2 = sum(x.*y);

r3 = 0;
for i = 1:5
    r3 = r3 + x(i) * y(i);
end

r4 = 0;
for i = 5:-1:1
    r4 = r4+ x(i) * y(i);
end
%bar([r1, r2, r3, r4])


x = 29/13;        
y = 29 - 13*x;     % dziala jak trzeba
x1 = 29/1300;                   
y1 = 29 - 1300*x1; % gubi liczby po przecinku
%bar([x, y, x1, y1])



k = 4:10;

f = @(x) 1+x.^2;

x = 10.^k;
a = sqrt(f(x));

w1 = x - a;
w2 = -1 / (x + a);

x = single(x);
a = single(a);

w3 = x - a;
w4 = -1 / (x + a);



figure
subplot(1, 2, 1)
plot(x, f1(x), 'r')
title('Algorytm1')
subplot(1, 2, 2)
plot(x, f2(x), 'g')
title('Algorytm2')



d = 10^(-3);
x = linspace(2-d, 2+d, 1000);

f1 = @(x) (x - 2).^4;
f2 = @(x) x.*x.*x.*x + 8.*x.*x.*x + 24.*x.*x + 32.*x + 16;

figure
subplot(1, 2, 1)
plot(x, f1(x), 'r')
title('f1(x)')
subplot(1, 2, 2)
plot(x, f2(x), 'g')
title('f2(x)')


format default



