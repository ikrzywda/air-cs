% Igor Krzywda, 275480
% grupa 5, pt. 11:15
% cw. 9

close all;
clear all;


SIMULATION_TIME = "1000";
SIMULATION_STEP_SIZE = "100";

% constants
Vw1 = 40;
Vw2 = 0.8 * Vw1;    
cpp = 1000;
rop = 1.2;

T0 = 100;
dTzew = 0;
dTkz = 0;


% nominal values
TzewN = -20;
Twew1N = 20;
Twew2N = 15;
TkzN = 30;
PkN = 20000;
fkN = PkN / (cpp * rop * (TkzN - Twew1N));
ks1N = (0.7 * PkN) / (Twew1N - TzewN);
k0N = (cpp * rop * fkN * (TkzN - Twew1N) - ks1N * (Twew1N - TzewN)) / (Twew1N - Twew2N);
ks2N = (k0N * (Twew1N - Twew2N) + cpp * rop * fkN * (Twew1N - Twew2N)) / (Twew2N - TzewN);

dfk = 0.2 * fkN;

Cv1 = cpp * rop * Vw1;
Cv2 = cpp * rop * Vw2;

% time domain
Tzew0 = TzewN;
Tkz0 = TkzN;
fk0 = fkN * 0.8;
ks1 = ks1N;
ks2 = ks2N;
k0 = k0N;
cppRop = cpp * rop;
[Twew10, Twew20] = solve_initial_conditions(cppRop, fk0, Tzew0, Tkz0, k0, ks1, ks2);


[output] = sim("simulink_models/time_domain.slx", "StartTime", "0", "StopTime", SIMULATION_TIME, "FixedStep", SIMULATION_STEP_SIZE);


figure();
hold on;
plot(output.tout, output.Twew1);
plot(output.tout, output.Twew2);
hold off;

[output] = sim("simulink_models/time_domain.slx", "StartTime", "0", "StopTime", SIMULATION_TIME, "FixedStep", SIMULATION_STEP_SIZE);

figure();
hold on;
plot(output.tout, output.Twew1);
plot(output.tout, output.Twew2);
title("Time domain");
hold off;


% transfer function


x = cpp * rop * fk0;



M1 = [Cv1 (x + ks1 + k0)];
M2 = [Cv2 (x + ks2 + k0)];


M = [ ...
    (Cv1 * Cv2) ...
    (Cv1 * (k0 + x + ks2) + Cv2 * (x + ks1 + k0)) ...
    (x * (k0 + x + ks2) + ks1 * (k0 + x + ks2) + k0 * (k0 + x + ks2)) ...
];


N_11 = [(Cv2 * x) (x * (k0 + x + ks2))];
N_12 = [(Cv2 * ks1) (ks1 * (k0 + x + ks2) + k0 * ks1)];


N_21 = k0 * x + x^2; % input Tkz
N_22 = [(Cv2 * ks2) (ks2 * (k0 + ks2 + x) + k0 * ks1 + x * ks1)];


[output] = sim("simulation_transfer_function.slx", "StartTime", "0", "StopTime", SIMULATION_TIME, "FixedStep", SIMULATION_STEP_SIZE);

figure();
hold on;
plot(output.tout, output.Twew1);
plot(output.tout, output.Twew2);
title("Transfer function");
hold off;


% state space
% [Twew10, Twew20] = solve_initial_conditions(cpp, fkN, TzewN, TkzN, k0N, ks1N, ks2N);
A = [(-(x + ks1 + k0) / Cv1) (k0 / Cv1); ((k0 + x) / Cv2) (-(k0 + x + ks2) / Cv2)];
B = [(x/Cv1) (ks1/Cv1); 0 (ks2/Cv2)];
C = [1 0; 0 1];
D = [0 0; 0 0];
TInitial = [Twew10 Twew20];

[output] = sim("simulation_ss.slx", "StartTime", "0", "StopTime", SIMULATION_TIME, "FixedStep", SIMULATION_STEP_SIZE);

figure();
hold on;
plot(output.tout, output.Twew1);
plot(output.tout, output.Twew2);
title("State space");
hold off;


function [T_w1_solution, T_w2_solution] = solve_initial_conditions(c_pp, f_k, T_zew, T_kz, k0, ks1, ks2)
    initial_values_initial_guess = [0, 0];
    options = optimset('Display', 'off'); % Suppress display
    initial_values_result = fsolve(@(variables) initial_conditions_equations(variables, c_pp, f_k, T_zew, T_kz, k0, ks1, ks2), initial_values_initial_guess, options);

    T_w1_solution = initial_values_result(1);
    T_w2_solution = initial_values_result(2);
end

function equations = initial_conditions_equations(variables, c_pp, f_k, T_zew, T_kz, k0, ks1, ks2)
    T_w1 = variables(1);
    T_w2 = variables(2);
    eq1 = c_pp * f_k * (T_kz - T_w1) - ks1 * (T_w1 - T_zew) - k0 * (T_w1 - T_w2);
    eq2 = k0 * (T_w1 - T_w2) + c_pp * f_k * (T_w1 - T_w2) - ks2 * (T_w2 - T_zew);
    equations = [eq1; eq2];
end



