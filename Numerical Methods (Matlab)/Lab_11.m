clc
close all
clearvars

Xg = [0, 15, 38, 60, 90, 120, 150];
Yg = [0, 25, 18, 20, 5, 40, 0];

fg = griddedInterpolant(Xg, Yg, 'spline');


Xd = [0, 20, 45, 80, 98, 135, 150];
Yd = [0, -30, -5, -20, -3, -25, 0];

fd = griddedInterpolant(Xd, Yd, 'spline');


x = linspace(0, 150, 1000);
plot(x, fg(x), 'r', x, fd(x), 'r')
h = 20;
calka(fg, 0, 150, h)
calka(fd, 0, 150, h)

function S = calka(f, a, b, h)
    S = 0;
    suma = h;
    q = 0;
    for x=a:h:b-h
        S = S + ((f(x) + f(x+h)) * h) / 2;
        patch('Vertices', [x f(x); x+h 0; x+h f(x+h); x 0], ...
            'Faces', [1 3 2 4], ...
            'FaceColor', [0 0.4470, 0.7410], ...
            'FaceAlpha', 0.4, ...
            'Marker', 'o')
        suma = suma + h;
        q = x + h;
    end
    if suma > b
        S = S + ((f(b) + f(q)) * (b - q)) / 2;
        patch('Vertices', [q f(q); b 0; b f(b); q 0], ...
            'Faces', [1 3 2 4], ...
            'FaceColor', [0 0.4470, 0.7410], ...
            'FaceAlpha', 0.4, ...
            'Marker', 'o')
        return
    end
end