clc
close all
clearvars

%============================================================

x = linspace(0, 6, 1000);

fp = @(x) -sin(2*x) * 2;
f = @(x) cos(2*x);

fcs = {
    @(x, h) ((f(x + h) - f(x)) / h),...
    @(x, h) ((f(x + h) - f(x - h)) / (2 * h)),...
    @(x, h) ((-f(x + 2 * h) + 8 * f(x + h) - 8 * f(x - h) + f(x - 2 * h)) / (12 * h))
    };
d = fp(x);
h = [1 0.5 0.25];

m = {'2pkt', '3pkt', '5ptk'};
cnt = 0;
figure
for i = 1:length(fcs)
    for j = 1:length(h)
        p = fcs{i}(x, h(j));
        mse = 1 / length(d) * sum((d - p) .^ 2);
        subplot(3, 3, cnt + j)
        plot(x, p, x, fp(x))
        title(sprintf('%s: h = %e blad: %e',m{i},h(j),mse))
    end
    cnt = cnt + 3;
end

%============================================================

x = linspace(0, 4, 1000);

fp = @(x) cos(x) - 2 * sin(2*x);
f = @(x) sin(x) + cos(2*x);

fcs = {
    @(x, h) (-3 * f(x) + 4 * f(x + h) - f(x + 2 * h)) / (2 * h),...
    @(x, h) (f(x + h) - f(x - h)) / (2 * h),...
    @(x, h) (f(x - 2 * h) - 4 * f(x - h) + 3 * f(x)) / (2 * h)
    };

d = fp(x);
h = [0.5 0.25 0.125];

m = {'2pkt', '3pkt', '5ptk'};
cnt = 0;
figure
for i = 1:length(fcs)
    for j = 1:length(h)
        p = fcs{i}(x, h(j));
        mse = 1 / length(d) * sum((d - p) .^ 2);
        subplot(3, 3, cnt + j)
        plot(x, p, x, fp(x))
        title(sprintf('%s: h = %e blad: %e',m{i},h(j),mse))
    end
    cnt = cnt + 3;
end

%============================================================

x = linspace(0, 5, 1000);

fpp = @(x) -cos(4 * x) * 16;
fp = @(x) -sin(4*x) * 4 - (1/2);
f = @(x) cos(4*x) - ((1/2)*x);

fcs = {
    @(x, h) (f(x + h) - 2 * f(x) + f(x - h)) / (h^2),...
    @(x, h) (-f(x + 2*h) + 16 * f(x + h) - 30 * f(x) + 16 * f(x - h) - f(x - 2*h)) / (12 * (h^2))
    };

d = fp(x);
h = [1 0.5 0.25];

m = {'2pkt', '3pkt', '5ptk'};
cnt = 0;
figure
for i = 1:length(fcs)
    for j = 1:length(h)
        p = fcs{i}(x, h(j));
        mse = 1 / length(d) * sum((d - p) .^ 2);
        subplot(2, 3, cnt + j)
        plot(x, p, x, fpp(x))
        title(sprintf('%s: h = %e blad: %e',m{i},h(j),mse))
    end
    cnt = cnt + 3;
end

%============================================================