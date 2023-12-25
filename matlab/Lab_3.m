clc
close all
clear all


%info = zad_1('kajak')
%info = zad_1_2('oppo')
%sorted_vector = sort_vector([5,1,7,3,9,4,3,6,9,4,2,7,8,4,3,0,5,6,1,-4])
f_zerowe = f0(3, 5, 2)
board = [
    1 0 -1;
    0 1 0;
    -1 0 1
    ];
%check_winner(board)



function info = zad_1(s)
    n = length(s);

    for i = 1:n
        if s(i) ~= s(n-i+1)
            fprintf('Nie jest polindrom!\n')
            info = 0;
            return
        end
    end
    info = 1;
    return 
end

function info = zad_1_2(s)
    n = length(s);
    if n <= 1
        info = 1;
    elseif s(1) == s(n)
        info = zad_1_2(s(2:n-1))
    else
        info = 0;
    end
end

function sorted_vector = sort_vector(vector)
    n = length(vector);
    for i = 1:n-1
        for j = n:-1:i+1
            if vector(i) > vector(j)
                buffer = vector(i);
                vector(i) = vector(j);
                vector(j) = buffer;
            end
        end
        plot(vector, '*')
        pause(0.01)
    end
    sorted_vector = vector;
end

function f_zerowe = f0(a, b, c)
    delta = b.^2 - 4*a*c;    
    
    if delta > 0
        x1 = (-b + sqrt(delta)) / (2*a);
        x2 = (-b - sqrt(delta)) / (2*a);
        f_zerowe = [x1 x2];
    elseif delta == 0
        x1 = -b / (2*a);
        f_zerowe = x1;
    else
        fprintf('Brak miejsc zerowych (delta < 0)\n');
    end


    % Rysuj wykres funkcji
    x = linspace(min(x1, x2) - 1, max(x1, x2) + 1, 100);
    y = a*x.^2 + b*x + c;
    plot(x, y);
    xlabel('x');
    ylabel('f(x)');
    title('Wykres funkcji f(x)');
    
    % Oznacz miejsca zerowe na wykresie
    hold on;
    plot(x1, a*x1^2 + b*x1 + c, 'ro', 'MarkerSize', 10);
    plot(x2, a*x2^2 + b*x2 + c, 'ro', 'MarkerSize', 10);
    legend('f(x)', 'Miejsca zerowe');
    hold off;
end

function check_winner(plansza)
    figure
    plot([.5 3.5],[-1.5 -1.5], 'k','linewidth',2);
    hold on
    plot([.5 3.5],[-2.5 -2.5], 'k','linewidth',2)
    plot([1.5 1.5],[-.5 -3.5], 'k','linewidth',2)
    plot([2.5 2.5],[-.5 -3.5], 'k','linewidth',2)
    hold off
    axis off
end
