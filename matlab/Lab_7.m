clc
close all
clearvars

xg = [0, 10, 90, 120, 195, 260, 270];
yg = [35, 40, 50, 75, 70, 50, 40];

xd = [5, 40, 45, 50, 55, 60, 65, 75, 190, 195, 200, 210, 220, 230, 260, 265, 270];
yd = [20, 15, 5, 1, 0, 1, 5, 15, 12, 5, 1, 0, 3, 15, 16, 30, 40];

x1 = linspace(0, max(xg), 1000);
x2 = linspace(0, max(xd), 1000);

%==============================
int1 = interp1(xg, yg, x1, 'linear');
subplot(2, 2, 1)
plot(xg, yg, 'k*', x1, int1, 'r')
daspect([1, 1, 1])

hold on

int2 = interp1(xd, yd, x2, 'linear');
plot(xd, yd, 'k*', x2, int2, 'r')
daspect([1, 1, 1])
%==============================
int1 = interp1(xg, yg, x1, 'nearest');
subplot(2, 2, 2)
plot(xg, yg, 'k*', x1, int1, 'r')
daspect([1, 1, 1])

hold on

int2 = interp1(xd, yd, x2, 'nearest');
plot(xd, yd, 'k*', x2, int2, 'r')
daspect([1, 1, 1])
%==============================
int1 = interp1(xg, yg, x1, 'pchip');
subplot(2, 2, 3)
plot(xg, yg, 'k*', x1, int1, 'r')
daspect([1, 1, 1])

hold on

int2 = interp1(xd, yd, x2, 'pchip');
plot(xd, yd, 'k*', x2, int2, 'r')
daspect([1, 1, 1])
%==============================
int1 = interp1(xg, yg, x1, 'spline');
subplot(2, 2, 4)
plot(xg, yg, 'k*', x1, int1, 'r')
daspect([1, 1, 1])

hold on

int2 = interp1(xd, yd, x2, 'spline');
plot(xd, yd, 'k*', x2, int2, 'r')
daspect([1, 1, 1])
%==============================




x = linspace(-3, 3, 5)';
y = abs(x);
V = [];

for i=1:length(x)
    V(i, 1) = 1;
    for j=2:length(x)
        V(i, j) = x(i)^(j-1);
    end
end
a = V\y;
X = linspace(-3, 3, 1000);
Y = 0;
for i=1:length(a)
    Y = Y + a(i)*X.^(i-1);
end
int1 = interp1(x, y, Y, "linear");
subplot(2, 2, 1)
plot(x, y, 'k*', Y, int1, 'r')
%==============================
x = linspace(-3, 3, 10)';
y = abs(x);
V = [];

for i=1:length(x)
    V(i, 1) = 1;
    for j=2:length(x)
        V(i, j) = x(i)^(j-1);
    end
end
a = V\y;
X = linspace(-3, 3, 1000);
Y = 0;
for i=1:length(a)
    Y = Y + a(i)*X.^(i);
end
int1 = interp1(x, y, Y, "linear");
subplot(2, 2, 2)
plot(x, y, 'k*', Y, int1, 'r')
%==============================
x = linspace(-3, 3, 15)';
y = abs(x);
V = [];

for i=1:length(x)
    V(i, 1) = 1;
    for j=2:length(x)
        V(i, j) = x(i)^(j-1);
    end
end
a = V\y;
X = linspace(-3, 3, 1000);
Y = 0;
for i=1:length(a)
    Y = Y + a(i)*X.^(i);
end
int1 = interp1(x, y, Y, 'linear');
subplot(2, 2, 3)
plot(x, y, 'k*', Y, int1, 'r')
