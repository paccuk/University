clc
close all
clearvars

wybor = 4;

switch wybor
    case 1
        f = @(x) exp(x - 1) - 2;
        a = -1;
        b = 2;
    case 2
        f = @(x) 2.^(-x) + exp(x) + cos(x) - 6;
        a = 1;
        b = 3;
    case 3
        f = @(x) log(x + 2/3);
        a = -1/2;
        b = 2;
    otherwise
        f = @(x) x.^3 - 2 * x - 5;
        a = 0;
        b = 3;
end

tol = 10^(-5);
ftol = 10^(-4);

[xb, nb] = sieczne(f, a, b, tol, ftol);
[xf, nf] = styczne(f, a, b, tol, ftol);

t = a:0.01:b;
plot(t, f(t))
hold on;
plot(xb, f(xb), 'ro')
plot(xf, f(xf), 'rx')

function [xb, nb] = sieczne(f, a, b, tol, ftol)
    assert(f(a) * f(b) < 0, 'Nie ma pierwiastku!')
    h = 2 ^ (-16);
    n = 0;
    pochodna2 = (f(a + h) - 2 * f(a) + f(a - h)) / h ^ 2;
    if sign(f(a)) == sign(pochodna2)
        x0 = a;
        x1 = b;
    else
        x0 = b;
        x1 = a;
    end
    while 1
        x = x1 - f(x1) * ((x1 - x0) / (f(x1) - f(x0)));
        if abs(f(x)) <= ftol
            xb = x;
            nb = n;
            break;
        end
        x0 = x1;
        x1 = x;
        n = n + 1;
    end
end

function [xb, nb] = styczne(f, a, b, tol, ftol)
    assert(f(a) * f(b) < 0, 'Nie ma pierwiastku!')
    h = 2 ^ (-16);
    n = 0;
    pochodna2 = (f(a + h) - 2 * f(a) + f(a - h)) / h ^ 2;
    if sign(f(a)) == sign(pochodna2)
        x0 = a;
    else
        x0 = b;
    end
    while 1
        pochodna1 = (f(x0 + h) - f(x0 - h)) / (2 * h);
        x = x0 - f(x0) / pochodna1;
        if abs(f(x)) <= ftol
            xb = x;
            nb = n;
            break;
        end
        x0 = x;
        n = n + 1;
    end
end
