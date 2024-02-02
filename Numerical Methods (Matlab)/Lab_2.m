clc
close all
clear all

f = @(x) 8*sin(x)-2*x;
g = @(x) abs(8*sin(x)-2*x);

x1 = linspace(0, 10, 100);
x2 = linspace(0, 10, 20);

% f(x1)
% g(x2)

%figure
%plot(x1, f(x1), 'r', x2, g(x2), 'g.')
%title('Two functions')
%legend('f(x)', 'g(x)')
%xlabel('')
%ylabel('')

f = @(x) sin(x);
g = @(x) round(x);

x1 = -5 : 0.5 : 5;
x2 = -3 : 0.2 : 6;

figure
subplot(1, 2, 1)
plot(x1, f(x1), 'r')
title('f(x) = sin(x)')
subplot(1, 2, 2)
plot(x2, g(x2), 'g')
title('g(x) = round(x)')



clc
close all
clear all

x1 = -5 : 0.5 : 5;

figure

subplot(2, 4, [1 2])
f = @(x) sin(x);
plot(x1, f(x1), 'b')
title('f(x) = sin(x)')

subplot(2, 4, [3 4])
f = @(x) cos(x);
plot(x1, f(x1), 'g')
title('f(x) = cos(x)')

subplot(2, 4, 5)
f = @(x) tan(x);
plot(x1, f(x1), 'k')
title('f(x) = tan(x)')

subplot(2, 4, [6 7])
f = @(x) abs(x);
plot(x1, f(x1), 'r')
title('f(x) = abs(x)')

subplot(2, 4, 8)
f = @(x) x;
plot(x1, f(x1), 'm')
title('f(x) = x')

clc
close all
clear all

f = @(x) sin(x) + 0.2 * rand(size(x));

x1 = -4 : 0.1 : 6;
x2 = 2 : 0.01 : 4;

figure
axes('Position', [0 0 0.8 0.8], 'Box', 'off')
plot(x1, f(x1), 'b')
axes("Position", [0.65 0.65 0.28 0.28], 'Box', 'on')
plot(x2, f(x2), 'b')

clc
close all
clear all

[X,Y] = meshgrid(-10:0.5:10,-5:0.5:5);
Z = X.^2 + Y.*Y;

mesh(X,Y,Z)
hold on
plot3(0, 0, 0, 'Marker', '.', 'MarkerSize', 20, 'Color', 'k')

clc
close all
clear all

[X,Y] = meshgrid(200 : 500);
Z = 418.9829 * 2 - X * sin(sqrt(abs(X))) - Y * sin(sqrt(Y));
contour(X, Y, Z)

