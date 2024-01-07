% Igor Krzywda, 275480
% grupa 5, pt. 11:15
% cw. 9

close all;
clear all;


% constants
Vw1 = 40;
Vw2 = 0.8 * Vw1;    
cpp = 1000;
rop = 1.2;

T0 = 1;
dTzew = 0;
dTkz = 0;
dfk = 0;

% nominal values
TzewN = -20;
Twew1N = 20;
Twew2N = 15;
TkzN = 30;
PkN = 20000;

fkN = PkN / (cpp * rop * (Twew1N - TzewN));
ks1N = (0.7 * PkN) / (Twew1N - TzewN);


k0N = (cpp * rop * fkN * (TkzN - Twew1N) - ks1N * (Twew1N - TzewN)) / (Twew1N - Twew2N);
ks2N = (k0N * (Twew1N - Twew2N) + cpp * rop * fkN * (Twew1N - Twew2N)) / (Twew2N - TzewN);


Cv1 = cpp * rop * Vw1;
Cv2 = cpp * rop * Vw2;

% running simulation with nominal values and no step
Tzew0 = TzewN;
Tkz0 = TkzN;
fk0 = fkN;
ks1 = ks1N;
ks2 = ks2N;
k0 = k0N;
Twew10 = Twew1N;
Twew20 = Twew2N;
[output] = sim("simulation.slx", "StartTime", "0", "StopTime", "10");

figure();
hold on;
plot(output.tout, output.Twew1);
plot(output.tout, output.Twew2);
ylim([0, 25]);
hold off;

x = cpp * rop * fk0;
helper_denominator_1 = x + ks1 + k0;
helper_denominator_2 = k0 + x + ks2 - (k0 * (k0 + x) / helper_denominator_1);
Twew20 = ((((k0 + x) * (x * Tkz0 + ks1 * Tzew0)) / helper_denominator_1) + ks2 * Tzew0) / helper_denominator_2;
Twew10 = (x * Tkz0 + ks1 * Tzew0 + k0 * Twew20) / helper_denominator_1;


dTzew = 0;
dfk = 0;
[output] = sim("simulation.slx", "StartTime", "0", "StopTime", "10");

figure();
hold on;
plot(output.tout, output.Twew1);
plot(output.tout, output.Twew2);

hold off;


% transfer function

M1 = [(x + k0) Cv1];
M2 = [(k0 + ks2) Cv2];

M = [ ...
    (Cv1 * Cv2) ...
    (Cv1 * (k0 + ks2) + Cv2 * (x + k0)) ...
    (k0 * (x + k0 + ks2) + x * ks2) ...
];

N_11 = M2 .* x; % input Tkz
N_12 = M2 .* ks1 + [(k0 * ks2) 0];  % input Tzew

N_21 = [x * (k0 + x)]; % input Tkz
N_22 = (M1 * ks2 * k0) + [k0 * (k0 + x) * ks1 0 ]; % input Tzew

[output] = sim("simulation_transfer_function.slx", "StartTime", "0", "StopTime", "10");

figure();
hold on;
plot(output.tout, output.Twew1);
plot(output.tout, output.Twew2);

hold off;
