clc
close all
clearvars


A = [
    3, 2, 1;
    5, 4, 3;
    1, 1, 0;
    -1, 0, 0;
    0, -1, 0;
    0, 0, -1
    ];

b = [120; 300; 50; 0; 0; 0];
c = [12; 8; 10];
[m, n] = size(A);
x_feas = [];
C = nchoosek(1:length(b), n);
eps = 10^-12;

for i = C'
    Ai = A(i,:);
    bi = b(i);
    
    if det(Ai) == 0
       continue
    end
    
    xi = [];
    W = det(Ai);
    for j = 1:n
        Aj = Ai;
        Aj(:, j) = bi;
        Wj = det(Aj);
        xi(j, :) = Wj/W;
    end
   
    res = A * xi;
    if all(res - b <= eps)
        x_feas(:,end + 1) = transpose(xi);
    end
    
    
    
end

T = convhull(x_feas(1,:), x_feas(2, :), x_feas(3, :));
trisurf(T, x_feas(1,:), x_feas(2, :), x_feas(3, :));
