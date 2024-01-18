% Igor Krzywda, 275480
% grupa 5, pt. 11:15
% cw. 9

close all;
clear all;


SIMULATION_TIME = "30";
SIMULATION_STEP_SIZE = "10";

% constants
Vw1 = 40;
Vw2 = 0.8 * Vw1;    
cpp = 1000;
rop = 1.2;

T0 = 2;
dTzew = -2;
dTkz = 10;
dfk = 0;

% nominal values
TzewN = -20;
Twew1N = 20;
Twew2N = 15;
TkzN = 30;
PkN = 20000;
% fkN = PkN / (cpp * rop * (Twew1N - TzewN));
% ks1N = (0.7 * PkN) / (Twew1N - TzewN);
% k0N = (cpp * rop * fkN * (TkzN - Twew1N) - ks1N * (Twew1N - TzewN)) / (Twew1N - Twew2N);
% ks2N = (k0N * (Twew1N - Twew2N) + cpp * rop * fkN * (Twew1N - Twew2N)) / (Twew2N - TzewN);

fkN = 1.6666666666666667;
k0N = 1200.0;
ks1N = 350.0;
ks2N = 457.1428571428572;

Cv1 = cpp * rop * Vw1;
Cv2 = cpp * rop * Vw2;

% time domain
Tzew0 = TzewN;
Tkz0 = TkzN;
fk0 = fkN;
ks1 = ks1N;
ks2 = ks2N;
k0 = k0N;
Twew10 = Twew1N;
Twew20 = Twew2N;
[output] = sim("simulink_models/time_domain.slx", "StartTime", "0", "StopTime", SIMULATION_TIME, "FixedStep", SIMULATION_STEP_SIZE);

figure();
hold on;
plot(output.tout, output.Twew1);
plot(output.tout, output.Twew2);
hold off;

T_wew10 = 20.0;
T_wew20 = 15.0;
% Twew20 = ((((k0 + x) * (x * Tkz0 + ks1 * Tzew0)) / helper_denominator_1) + ks2 * Tzew0) / helper_denominator_2;


[output] = sim("simulink_models/time_domain.slx", "StartTime", "0", "StopTime", SIMULATION_TIME, "FixedStep", SIMULATION_STEP_SIZE);

figure();
hold on;
plot(output.tout, output.Twew1);
plot(output.tout, output.Twew2);
title("Time domain");
hold off;


% transfer function

x = cpp * rop * fk0;

M1 = [(x + k0) Cv1];
M2 = [(k0 + ks2) Cv2];

M = [ ...
    (Cv1 * Cv2) ...
    (Cv1 * k0 + Cv1 * ks2 + x * Cv2) ...
    (k0 * x + x * ks2 + k0^2 + k0 * ks2 - (k0^2 + x)) ...
];

N_11 = [(Cv2 * x) (x * k0 + x * ks2)]; % input Tkz
N_12 = [(Cv2 * ks1) (k0 * ks1 + ks2 * ks1)];  % input Tzew

N_21 = x * (k0 + x); % input Tkz
N_22 = [(Cv1 * ks2) (x * ks2 + k0 * ks2 + k0 * ks1 + x * ks1)]; % input Tzew

[output] = sim("simulation_transfer_function.slx", "StartTime", "0", "StopTime", SIMULATION_TIME, "FixedStep", SIMULATION_STEP_SIZE);

figure();
hold on;
plot(output.tout, output.Twew1);
plot(output.tout, output.Twew2);
title("Transfer function");
hold off;


% state space

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
