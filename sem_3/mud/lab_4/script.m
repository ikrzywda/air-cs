% syms a0 a1 x(t) b u0
% Igor Krzywda, 275480
% grupa 5, pt. 11:15
% cw. 4

close all;
clear;

du = 5;
t0 = 0; 

a1 = 2;
a0 = 8;
b = 4;
u0 = 0;

initialConditions = [1/4];
analyticalParams = [-9/4];

% initialConditions = [10, -42, 0, 13];
% analyticalParams = [0, -9/4, -5/2, 21/2];
analyticalExp = -4;
analyticalFreeSolution = 5/2;
t = 0:0.01:2;

for i = 1:length(initialConditions)
    figure();
    x10 = initialConditions(i);
    [output] = sim('lab_4_sim.slx', 'StartTime','0','StopTime','1','FixedStep','0.01');
    hold on;
    ylim([0, 3.5]);
    % ylim([min(output.x) - 0.2, max(output.x) + 0.2]);
    plot(t, analyticalFreeSolution + 0 * t, ':');    
    plot(output.tout, output.x);
    % title(sprintf("Wykres symulacyjny %d", i));
    legend('x(t)');
    hold off;
    saveas(gcf, "sim4", "png");

    figure();
    hold on;
    a = analyticalParams(i);
    ylim([0, 3.5]);
    plot(t, analyticalFreeSolution + 0 * t, ':');    
    plot(t, a * exp(analyticalExp * t) + analyticalFreeSolution, 'k-');
    plot(t, a * exp(analyticalExp * t), 'r:');
    legend('x(t)');
    % title(sprintf("Wykres analityczny %d", i));
    hold off;
    saveas(gcf, "an4", "png");
end

