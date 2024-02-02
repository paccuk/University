clc
close all
clearvars

A = [2, 1;
     3, 3;
     2, 0];
b = [10; 24; 8];
c = [300, 200];
[m, n] = size(A);
A = [A, eye(m)];
c = [c, zeros(1, m)];

wb = n+1:m+n;
while 1
    cb = c(wb);
    f = cb * b;

    ww = [];
    for j=1:length(c)
        ww(end + 1) = c(j) - cb * A(:, j);
    end

    if all(ww <= 0)
        break;
    end

    [~, kk] = max(ww);
    ilorazy = b ./ A(:, kk);
    
    ilorazy(ilorazy<0) = inf;
    [~, wk] = min(ilorazy);
    er = A(wk, kk);
    wb(wk) = kk;
    b(wk) = b(wk) / er;
    A(wk, :) = A(wk, :) / er;

    for i=1:m
        if i ~= wk
            b(i) = b(i) - b(wk) * A(i, kk);
            A(i, :) = A(i, :) - A(wk, :) * A(i, kk);
        end
    end
end

xi = [];
for i=1:m
    if i ~= wk
        xi(end + 1) = b(i);
    end
end
xi
Z = f

