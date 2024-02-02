function [] = Lab_14()
clc
close
clearvars

wybor = 1;

switch wybor
    case 1
        f = @(x1, x2) -x1.^2 - x2.^2;
        x1p = -10;
        x1k = 10;
        x2p = -10;
        x2k = 10;
        x10 = 8;
        x20 = -10;
        krok = 1;

    case 2
        f = @(x1, x2) cos(x1).*cos(x2).*exp(-((x1-pi).^2+(x2-pi).^2));
        x1p = 2;
        x1k = 4;
        x2p = 2;
        x2k = 4;
        x10 = 2;
        x20 = 2;
        krok = 0.1;

    otherwise
        f =@(x1, x2) -(1-8*x1 + 7*x1.^2 - (7/3)*x1.^3 + (1/4)*x1.^4) .* ((x2.^2) .* exp(-x2));
        x1p = 0;
        x1k = 5;
        x2p = 0;
        x2k = 5;
        x10 = 5;
        x20 = 5;
        krok = 0.2;
end

[x1, x2, dx1, dx2, it] = sww(f, x10, x20, krok, 0.01, x1p, x1k, x2p, x2k)

subplot(2,1,1)
[x, y] = meshgrid(x1p:0.05:x1k, x2p:0.05:x2k);
mesh(x,y,f(x,y));
hold on

plot3(x1, x2, f(x1, x2), 'r'); 
subplot(2,1,2);
z = f(x, y);
[c, h] = contour(x, y, z);
clabel(c, h);
hold on

plot(x10, x20, 'r*');
text(x10, x20, 'START');
plot(x1, x2, 'r*');
text(x1, x2, 'STOP');

for i=1:length(dx1)-1
    line(dx1, dx2, 'Color', 'k', 'Linewidth', 1);
    contour(x,y,z,[f(dx1(i), dx2(i)), f(dx1(i), dx2(i))]);
end
end

function [x1, x2, dx1, dx2, it] = sww(f, x10, x20, krok, eps, x1p, x1k, x2p, x2k)
    e = [1 0 -1 0
        0 1 0 -1];

    x1 = x10;
    x2 = x20;
    dx1 = [];
    dx2 = [];

    it = 0;
    while true
        dx1 = [dx1, x1];
        dx2 = [dx2, x2];

        h = 10^-5;
        pochodna = (f(x1+h, x2) -f(x1-h, x2)) / (2*h);
        pochodna = [pochodna, (f(x1, x2+h) -f(x1, x2-h)) / (2*h)];

        if ((abs(pochodna(1)) < eps && abs(pochodna(2)) < eps))
            break
        end

        it = it + 1;
        pX = [x1, x1 + krok, x1, x1 - krok];
        pY = [x2 + krok, x2, x2 - krok, x2];
        punkty = f(pX, pY);

        while true
        [maxP, idx] = min(punkty);
            if pY(idx) < x2p || pY(idx) > x2k || pX(idx) < x1p || pX(idx) > x1k
                punkty(index) = -abs(maxP);
            else
                x1 = pX(idx);
                x2 = pY(idx);
                break
            end
        end
    end
end