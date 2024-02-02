function Lab_17
    clc
    close all

    wybor = 1;

    switch wybor
        case 1
            f = @(x) 10 * x(1, :) .^ 2 + 15 * x(2, :) .^ 2 + 20 * x(1, :) .* x(2, :) + 5 * x(1, :) - 20 * x(2, :);
            xp = -8; xk = 8; yp = -8; yk = 8; x0 = [7; -8];
        case 2
            f = @(x) 100 * (x(2, :) - x(1, :) .^ 2) .^ 2 + (1 - x(1, :)) .^ 2;
            xp = -2; xk = 2; yp = -1; yk = 4; x0 = [-2; 3];
        case 3
            f = @(x)log(exp(x(1, :) + 3 * x(2, :) - 0.1) + exp(x(1, :) - 3 * x(2, :) - 0.1) + exp(-x(1, :) - 0.1));
            xp = -4; xk = 4; yp = -2; yk = 2; x0 = [2; 2];
        otherwise
    end

    tol = 1e-4; ftol = 1e-4;

    [x_opt_1, dx_1, it_1] = m_newtona(f, x0, tol, ftol);
    [x_opt_2, dx_2, it_2] = m_min_kierunkow(f, x0, tol, ftol);

    fprintf("f(%f,%f) = %f, #it = %d\n", x_opt_1(1), x_opt_1(2), f(x_opt_1), it_1)
    fprintf("f(%f, %f) = %f, #it = %d\n", x_opt_2(1), x_opt_2(2), f(x_opt_2), it_2)

    [X, Y] = meshgrid(linspace(xp, xk, 100), linspace(yp, yk, 100));
    Z = reshape(f([X(:), Y(:)]'), size(X));
    figure;
    contour(X, Y, Z, 100)
    hold on
    plot(x0(1), x0(2), "r*"); text(x0(1), x0(2), "START")
    plot(x_opt_1(1), x_opt_1(2), "r*"); text(x_opt_1(1), x_opt_1(2), "STOP1")
    plot(x_opt_2(1), x_opt_2(2), "r*"); text(x_opt_2(1), x_opt_2(2), "STOP")

    for k = 1:length(dx_1) - 1
        line([dx_1(1, k) dx_1(1, k + 1)], [dx_1(2, k) dx_1(2, k + 1)], "Color", "g")
    end

    for k = 1:length(dx_2) - 1
        line([dx_2(1, k) dx_2(1, k + 1)], [dx_2(2, k) dx_2(2, k + 1)], "Color", "r")
    end

end

function [x_opt, dx, it] = m_newtona(f, x0, gtol, ftol)
    max_iter = 1000;
    x_opt = x0;
    dx = [x0];

    for it = 1:max_iter
        % Calculate the gradient and Hessian
        grad = gradient(f, x_opt);
        hessian = hessian_matrix(f, x_opt);

        % Check the gradient norm for convergence
        if norm(grad) < gtol
            break;
        end

        % Calculate the search direction using the Newton method
        direction = -inv(hessian) * grad;

        % Perform line search to find the step size
        t = line_search(f, x_opt, direction);

        % Update the current solution
        x_opt = x_opt + t * direction;

        % Store the current solution for visualization
        dx = [dx x_opt];

        % Check the function value change for convergence
        if abs((f(x_opt) - f(dx(:, end - 1))) / f(dx(:, end - 1))) < ftol
            break;
        end
    end

end

function [x_opt, dx, it] = m_min_kierunkow(f, x0, gtol, ftol)
    max_iter = 1000;
    x_opt = x0;
    dx = [x0];

    for it = 1:max_iter
        % Calculate the gradient
        grad = gradient(f, x_opt);

        % Check the gradient norm for convergence
        if norm(grad) < gtol
            break;
        end

        % Calculate the search direction (steepest descent)
        direction = -grad;

        % Perform line search to find the step size
        t = line_search(f, x_opt, direction);

        % Update the current solution
        x_opt = x_opt + t * direction;

        % Store the current solution for visualization
        dx = [dx x_opt];

        % Check the function value change for convergence
        if abs((f(x_opt) - f(dx(:, end - 1))) / f(dx(:, end - 1))) < ftol
            break;
        end
    end
end

function grad = gradient(f, x)
    h = 1e-6;
    grad = zeros(size(x));

    for i = 1:length(x)
        x1 = x;
        x2 = x;
        x1(i) = x1(i) - h;
        x2(i) = x2(i) + h;
        grad(i) = (f(x2) - f(x1)) / (2 * h);
    end
end

function hessian = hessian_matrix(f, x)
    h = 1e-6;
    n = length(x);
    hessian = zeros(n, n);

    for i = 1:n

        for j = 1:n
            x1 = x;
            x2 = x;
            x1(i) = x1(i) - h;
            x2(i) = x2(i) + h;

            gx1 = gradient(f, x1);
            gx2 = gradient(f, x2);

            hessian(i, j) = (gx2(j) - gx1(j)) / (2 * h);
        end
    end
end

function t = line_search(f, x, direction)
    alpha = 0.01;
    beta = 0.5;
    t = 1;

    while f(x + t * direction) > f(x) + alpha * t * gradient(f, x)' * direction
        t = beta * t;
    end
end
