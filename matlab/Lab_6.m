clc
close all
clear all

%A = [2 2 1; 1 4 1; 0 1 2];
%A = [4 1 4; 2 -1 2; 1 1 2];
A = [2 2 1 -1; 0 3 1 2; 1 2 2 1; 1 1 1 0];

%b = [3 -1 1]';
%b = [2 -4 -1]';
b = [6 -1 4 4]';

[l,u] = lu(A);
[L,U] = LU(A);
norm(l-L)
norm(u-U)

x = LUb(L, U, b);
norm(A*x-b)

function [L,U] = LU(A)
    [m,n] = size(A);
    assert(m==n)
    L = eye(n);
    U = zeros(n);
    for i=1:m
        for j=1:n
            suma = [];
            for k=1:j-1
                suma(end + 1) = L(i, k).*U(k, j);
            end
            suma = sum(suma);
            if i>j
                L(i,j) = (A(i,j) - suma) / U(j,j);
            else
                U(i,j) = A(i,j) - suma;
            end
        end
    end
end

function x = LUb(L, U, b)
    n = length(b);

    y = zeros(n,1);
    y(1) = b(1);
    for i=1:n
        suma = [];
        for j=1:i-1
            suma(end + 1) = L(i,j)*y(j);
        end
        suma = sum(suma);
        y(i,1) = b(i, 1) - suma;
    end

    x = zeros(n,1);
    x(n) = b(n);
    for i=n:-1:1
        suma = [];
        for j=i+1:n
            suma(end + 1) = U(i,j)*x(j);
        end
        suma = sum(suma);
        x(i,1) = 1./U(i, i) * (y(i,1) - suma);
    end
end