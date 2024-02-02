clc
close all
clearvars

wybor = 3;

switch wybor
    case 1
        f = @(x) cos(x);
        a = 0;
        b = 2;
    case 2
        f = @(x) 2.^(-x) + exp(x) + 2 * cos(x) - 6;
        a = 1;
        b = 3;
    otherwise
        f = @(x) (x + 2).^5;
        a = -3;
        b = 0;
end

tol = 10^(-5);
ftol = 10^(-4);

[xb, nb] = bisekcja(f, a, b, tol, ftol);
[xf, nf] = falsi(f, a, b, tol, ftol);

t = a:0.01:b;
plot(t, f(t))
hold on;
plot(xb, f(xb), 'ro')
plot(xf, f(xf), 'rx')

function [xb, nb] = bisekcja(f, a, b, tol, ftol)
    assert(f(a) * f(b) < 0, 'Nie ma pierwiastku!')
    n = 1;

    while 1
        suma = a + b;
        x0 = suma / 2;
        x = a - (f(a) * (b - a)) / (f(b) - f(a));
        if n > 1
            if abs(f(x)) <= ftol
                xb = x0;
                nb = n;
                break
            end
            if f(a) * f(x0) < 0
                b = x0;
            else
                a = x0;
            end
        end
        n = n + 1;
    end
end

function [xb, nb] = falsi(f, a, b, tol, ftol)
    assert(f(a) * f(b) < 0, 'Nie ma pierwiastku!')
    n = 1;
    
    while 1
        x0 = a - (f(a) * (b - a)) / (f(b) - f(a));

        if n > 1
            if abs(f(x0)) <= ftol
                xb = x0;
                nb = n;
                break
            end
            if f(a) * f(x0) < 0
                b = x0;
            else
                a = x0;
            end
        end
        n = n + 1;
    end
end
















