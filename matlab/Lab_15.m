function [] = Lab_15()
    clc
    close
    clearvars

    wybor = 3;

    switch wybor
        case 1
            f = @(x, y) x.^2 + y.^2;
            x1p = -10;
            x1k = 10;
            x2p = -10;
            x2k = 10;
            x10 = 8;
            x20 = -10;
            krok = 1;
        case 2
            f = @(x, y) -cos(x) .* cos(y) .* exp(-((x-pi).^2 + (y-pi).^2));
            x1p = 2;
            x1k = 4;
            x2p = 2;
            x2k = 4;
            x10 = 2;
            x20 = 2;
            krok = 0.1;
        otherwise
            f = @(x, y) (1-8*x + 7*x.^2 - (7/3)*x.^3 + (1/4)*x.^4) .* ((y.^2) .* exp(-y));
            x1p = 0;
            x1k = 5;
            x2p = 0;
            x2k = 5;
            x10 = 5;
            x20 = 5;
            krok = 0.2;
    end

    eps = 0.01;

    [x1, x2, dx1, dx2, it] = sww(f, x10, x20, krok, eps, x1p, x1k, x2p, x2k, 13)

    subplot(2,1,1)
    [x, y] = meshgrid(x1p:0.1:x1k, x2p:0.1:x2k);
    z = f(x, y);
    mesh(x, y, z);
    hold on
    plot3(x1, x2, f(x1, x2), 'r*', 'MarkerSize', 10, 'LineWidth', 3);
    title('3D plot of the function');
    

    subplot(2,1,2);
    [c, h] = contour(x, y, z);
    clabel(c, h);
    hold on
    plot(x10, x20, 'r*', 'MarkerSize', 10, 'LineWidth', 3);
    text(x10, x20, 'START');
    plot(x1, x2, 'r*', 'MarkerSize', 10, 'LineWidth', 3);
    text(x1, x2, 'STOP');
    
    for i = 1:length(dx1)-1
        line([dx1(i), dx1(i+1)], [dx2(i), dx2(i+1)], 'Color', 'k', 'LineWidth', 1);
        plot(dx1(i), dx2(i), 'ko');
    end
    title('Contour plot with the optimization path');
end

function [x1, x2, dx1, dx2, it] = sww(f, x10, x20, krok, eps, x1p, x1k, x2p, x2k, kierunki)
    theta = linspace(0, 2*pi, kierunki);
    e = [cos(theta); sin(theta)];
    dx1 = [x10];
    dx2 = [x20];
    it = 0;
    fx = zeros(1, kierunki);
    f0 = f(x10, x20);
 
    while true
        for i = 1:kierunki
            fx(i) = f(x10 + e(1, i) * krok, x20 + e(2, i) * krok);
        end
        [f1, i] = min(fx);
        
        if f1 < f0
            x10 = x10 + e(1, i) * krok;
            x20 = x20 + e(2, i) * krok;
            f0 = f1;
            it = it + 1;
            dx1(end + 1) = x10;
            dx2(end + 1) = x20;
        else
            krok = krok / 2;
        end
 
        if krok < eps
            break; 
        end
    end
 
    x1 = x10;
    x2 = x20;
end