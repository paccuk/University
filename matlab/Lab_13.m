clc
close all
clearvars

wybor = 4;

switch wybor
    case 1
        f = @(x) x .^2 - x;
        a = 0.25;
        b = 0.75;
    case 2
        f = @(x) (1/3) .* x.^2 - (13/7) .* x + 11;
        a = -10;
        b = 10;
    case 3
        f = @(x) x.^4 - 12 .* x.^3 + x + 4;
        a = -2;
        b = 2;
    otherwise
        f = @(x) -x.^3 + 3 .* x.^2 - 3 .*x;
        a = -2;
        b = -1;
end

eps = 1e-4;
% do zmierzenia czasu wykorzystaj polecenia tic i toc
[x1 , n1 ] = m_polowienia(f , a , b , eps )

% do zmierzenia czasu wykorzystaj polecenia tic i toc
[x2 , n2 ] = m_zlotego_podzialu(f , a , b , eps )

% rysowanie wykresu funkcji f na przedzial [a,b] i zaznaczenie na ich znalezionych rozwiazan
t = a :0.01: b;
plot (t , f (t) )
hold on ;
plot ( x1 , f( x1 ) , 'ro ')
plot ( x2 , f( x2 ) , 'rx ')


function [x1, n1] = m_polowienia(f , a , b , eps)
    xm = (a+b) / 2;
    
    lt = f(a);
    av = f(xm);
    
    cnt = 0;
    while b - a >= eps
        L = b - a;
        xl = a + 0.25 * L; % [a, Xm]
        xr = b - 0.25 * L; % [Xm, b]

        xlt = f(xl);
        xrt = f(xr);
        
        if lt < xlt || xlt < av
            [a, xm]
            
            b = xm;
            xm = xl;
            av = xlt;

        elseif av < xrt
            [xl, xr]

            a = xl;
            b = xr;
        else
            [xm, b]

            a = xm;
            xm = xr;
            lt = av;
            av = xrt;
        end
        cnt = cnt + 1;
    end
    x1 = xm;
    n1 = cnt;
end

function [x2, n2] = m_zlotego_podzialu(f , a , b , eps)
    phi = (sqrt(5)-1) / 2;

    xl = b - phi * (b - a);
    xr = a + phi * (b - a);

    xlt = f(xl);
    xrt = f(xr);
    
    cnt = 0;
    while b - a >= eps
        if xlt < xrt
            [a, xr]

            b = xr;
            xr = xl;
            xl = b - phi * (b - a);

            xrt = xlt;
            xlt = f(xl);
        else
            [xl, b]

            a = xl;
            xl = xr;
            xr = a + phi * (b - a);
            
            xlt = xrt;
            xrt = f(xr);
        end
        cnt = cnt + 1;
    end
    x2 = (xl+xr) / 2;
    n2 = cnt;
end

