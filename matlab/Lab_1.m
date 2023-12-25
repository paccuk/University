clc
close all
clear all

a = 6;
b = 5.5;
s = 'informatyka';

C = [1,2,3,4];
A = [
    1;
    2;
    3;
    4
    ];
B = [
    -12,-11,-10,-9;
    8, 7, 6, 5;
    1, 2, 3, 4
    ];

%length(A) % 4
%length(B) % 4
%size(B)   % 3 4
%size(B, 1)% 3
%size(B, 2)% 4
%numel(A)  % 4
%numel(B)  % 12
%sum(A)    % 10
%sum(B)    % -3 -2 -1 0
%sum(sum(B))% -6

% Zad 1
sum(B, 2)

% Zad 2
min(B, [], 2)

% Zad 3
% A*B
B*A
% A*B'
% B*A'

% Indexing
% Zad 4
B([1, 3], :)

% Zad 5
A(end + 1) = 5;
A(end)
A(end + 1) = 6;
A(end)
A(end + 1) = 7;
A(end)
%A = [A 6];
%A(end)

% Zad 6
B(:, end + 1) = sum(B, 2);

% Przypisanie a porównanie
z = 7
x = z
x == z

% Petle, instrukcje warunkowe
for i = B(:)
    i
end

while x < 10
    x = x + 1
end

if x < 10
    x < 10
elseif x > 10
    x > 10
else
    x
end





C = randi(10, 5, 4)
%for i = 1:numel(C)
%    if mod(C(i), 2) == 0
%        C(i) = 0
%    else
%        C(i) = 100
%    end
%end

L = mod(C, 2) == 0

if C(L) == 0
        C(L) = 0
    else
        C(L) = 100
end

