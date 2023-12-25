clc
close all
clearvars

x = [1 6 14 21];
y = [13 11 18 15];

X = linspace(min(x), max(x), 1000);
a = wsp(x, y);

Y = wart(a, X, x);
plot(X, Y, x, y, '*');
% ====================
[~, idx] = max(Y);
cal = floor(X(idx));
ulam = (X(idx) - cal) * 100;
odp2 = [cal ulam]
% ====================
godzina = 13;
for i=1:length(X)
    if godzina == X(i)
        temp = Y(i);
    end
end
% ====================

function a = wsp(x, y)
    n = length(x);
    for i=1:n
        p = 1;
        for j=1:n
            if j ~= i
                p = p * (x(i) - x(j));
            end
        end
        q(i) = y(i) / p; 
    end
    a = q;
end

function Y = wart(a, X, x)
    n = length(x);
    w = 0;
    for i=1:n
        p = 1;
        for j=1:n
            if j ~= i
                p = p .* (X - x(j));
            end
        end
        w = w + (a(i) * p);
    end
    Y = w;
end





