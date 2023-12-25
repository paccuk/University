clc
close all
clear all

p = 3;

switch p
    case 1
        A = [2 2 1;   1 4 1;   0 1 2];
        B = [3; -1; 1];
    case 2
        A = [1 1 2; 2 -1 2; 4 1 4];
        B = [-1; -4; 2];
    case 3
        A = [1 1 1 0; 2 2 1 -1; 0 3 1 2; 1 2 2 1];
        B = [4; 6; -1 ;4];
    otherwise 
        A = [0 3 1; 2 1 -1; -2 1 4];
        B = [-2; 4; -4];
end
x = eleminacjaGaussa(A, B)
norm(B-A*x)

function x = eleminacjaGaussa(A, b)
    n = length(b);
    A = [A b];

    for i = 1:n
        [~, k] = max(abs(A(i:n, i)));
        k = k+i-1;
        A([i k], :) = A([k i], :);
        for j = i+1:n
            z = -A(j,i)/A(i,i);
            A(j,:) = A(j, :) + A(i,:) * z;
        end
        A
    end
    x = zeros(n, 1);
    x(n) = A(n, end) / A(n,n);
    A(1:n-1, end) = A(1:n-1, end) - x(n) * A(1:n-1, n);

    for i = n-1:-1:1
        x(i) = A(i, end) / A(i, i);
        A(1:i-1, end) = A(1:i-1, end) - x(i) * A(1:i-1, i);
    end   
end

