% Igor Krzywda, 275480
% grupa 5, pt. 11:15
% cw. 5

close all;

SIMULATION_PATH = "simulation.slx";
OUTPUT_PATH_DIR = "output_figures";
OMEGA = 7;

xiVals = [3, -14/5, 0,  0.25, -0.2];

roots = [
    7 * (sqrt(8) - 3), 7 * (sqrt(8) + 3);
    7 * (14/15 + sqrt(196/25 - 1)), 7 * (14/15 - sqrt(196/25 - 1));
    1i * 7, -1i * 7;
    -7/4 + 1i * (7  * sqrt(3/2)), -7/4 - 1i * (7  * sqrt(3/2));
    7/5 + 1i * (7 * sqrt(24/25)), 7/5 - 1i * (7 * sqrt(24/25))
];

roots(4, :)

SIMULATION_OUTPUT_FILE_PREFIXES = arrayfun(@(xi) sprintf("%s/xi-%2.2f", OUTPUT_PATH_DIR, xi), xiVals);
CMP_OUTPUT_FILES_PREFIXES = arrayfun(@(xi) sprintf("%s/cmp-%d", OUTPUT_PATH_DIR, xi), 1:3);


% for it = 1:length(roots)
%     hold on;
%     roots(it, :)
%     plotRoots(roots(it, :));
%     hold off;
% end


omega = OMEGA;
b = 1;
% for it = 1:length(xiVals) 
%     figure();
%     xi = xiVals(it);
%     [output] = sim(SIMULATION_PATH, "StartTime","0","StopTime","3","FixedStep","0.01");
% 
%     plot(output.tout, output.x,'LineWidth', 2);
%     xlabel("t");
%     ylabel("x(t)");
%     saveas(gcf, sprintf("%s-sim.png", SIMULATION_OUTPUT_FILE_PREFIXES(it)), "png");
% 
%     figure();
%     plotRoots(roots(it, :));
%     xlabel("Re");
%     ylabel("Im");
%     saveas(gcf, sprintf("%s-roots.png", SIMULATION_OUTPUT_FILE_PREFIXES(it)), "png");
% end



DAMPED_OSCILLATION = 0.25;
ROOTS = computeRootsForPairs(DAMPED_OSCILLATION, OMEGA);
dampingVals1 = arrayfun(@(x) DAMPED_OSCILLATION, 1:4);
% omegaVals1 = [OMEGA, arrayfun(@(x) rand(1) * 10, 1:3)];
omegaVals1 = [OMEGA,8,9,10];
roots1 = computeRootsForPairs(dampingVals1, omegaVals1);

dampingVals2 = [DAMPED_OSCILLATION, arrayfun(@(x) (0.5 + rand(1)) / 2, 1:3)];
omegaVals2 = arrayfun(@(x) OMEGA, 1:4);
roots2 = computeRootsForPairs(dampingVals2, omegaVals2);

imagValues = arrayfun(@(x) i * rand(1) * 20, 1:3);
ROOT_REAL = real(ROOTS(1));
roots3 = [
    ROOTS;
    ROOT_REAL + 10i, ROOT_REAL - 10i;
    ROOT_REAL + 12i, ROOT_REAL - 12i;
    ROOT_REAL + 8i, ROOT_REAL - 8i
];
dampingVals3 = zeros(1,4);
omegaVals3 = zeros(1,4);
for i = 1:size(roots3, 1)
    % Call calculateDampingRatio for each row
    dampingVals3(i) = calculateDampingRatio(roots3(i, 1), roots3(i, 2), OMEGA);
    omegaVals3(i) = abs(roots3(i, 1));
end
dampingVals = [dampingVals1;dampingVals2;dampingVals3];
omegaVals = [omegaVals1;omegaVals2;omegaVals3];
rootValues = cat(3, roots1, roots2, roots3)

[m,n] = size(dampingVals)


COLORS = ["r", "b", "m", "k"];

for it = 1:m
    figure();
    hold on;
    for jt = 1:n
        xi = dampingVals(it, jt)
        omega = omegaVals(it, jt)
        xi = dampingVals(it, jt);
        omega = omegaVals(it, jt);
        [output] = sim(SIMULATION_PATH, "StartTime","0","StopTime","5","FixedStep","0.01");
        plot(output.tout, output.x, "color", COLORS(jt), 'LineWidth', 1.5);
        legendEntry = sprintf('xi=%.2f, omega=%.2f', xi, omega);
        legendEntries{jt} = legendEntry;
    end 
    legend(legendEntries, 'Location', 'best');
    legendEntries = {};  % Clear legend entries for the next iteration
    xlabel("t");
    ylabel("x(t)");
    hold off
    saveas(gcf, sprintf("%s-sim.png", CMP_OUTPUT_FILES_PREFIXES(it)), "png");
end

[rm, rn, rk] = size(rootValues)
for it = 1:rk
    figure();
    hold on;
    for jt = 1:rm
        for kt = 1:rn
            root = rootValues(jt,kt,it);
            plot(real(root), imag(root), 'o', 'MarkerFaceColor', COLORS(kt));
            xlabel("Re");
            ylabel("Im");
        end
    end
    hold off;
    saveas(gcf, sprintf("%s-roots.png", CMP_OUTPUT_FILES_PREFIXES(it)), "png");
end

function plotRoots(rootVals) 
    hold on;
    for it = 1:length(rootVals)
        root = rootVals(it);
        % plot(real(root), imag(root), 'o', 'MarkerSize', 10, 'MarkerFaceColor', 'k');
        plot(real(root), imag(root), 'o');
    end
    hold off;
end

function roots = computeRootsForPairs(dampingVals, frequencyVals)
    % Initialize an array to store the roots
    roots = zeros(length(dampingVals), 2);

    % Loop through the rows of dampingVals
    for i = 1:length(dampingVals)
        % Replace the following line with your actual function call
        computedRoots = computeRoots(dampingVals(i), frequencyVals(i));

        % Store the computed roots in the roots array
        roots(i, :) = computedRoots;
    end
end


function roots= computeRoots(damping, frequency)
    discriminatorRoot = sqrt((damping ^ 2) - 1);

    lambda1 = frequency * (-damping + discriminatorRoot);
    lambda2 = frequency * (-damping - discriminatorRoot);
    roots = [lambda1, lambda2];
end



function damping = calculateDampingRatio(s1, s2, omega_n)
    % Check if the roots are complex conjugate pairs
    if ~isequal(s1, conj(s2))
        error('Input roots must be complex conjugate pairs for an underdamped system.');
    end

    % Calculate damping ratio
    damping = abs(real(s1)) / abs(imag(s1));
end


