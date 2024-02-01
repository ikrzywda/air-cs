% Igor Krzywda 275480
% gr. 5, pt. 11:15

close all;
clear all;

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

x = cpp * rop * fk0;


M1 = [Cv1 (x + ks1 + k0)];
M2 = [Cv2 (x + ks2 + k0)];


M = [ ...
    (Cv1 * Cv2) ...
    (Cv1 * (k0 + x + ks2) + Cv2 * (x + ks1 + k0)) ...
    (x * (k0 + x + ks2) + ks1 * (k0 + x + ks2) + k0 * (k0 + x + ks2)) ...
];
N1 = [(Cv2 * x) (x * (k0 + x + ks2))];
N2 = k0 * x + x^2; % input Tkz

N_11 = [(Cv2 * x) (x * (k0 + x + ks2))];
N_12 = [(Cv2 * ks1) (ks1 * (k0 + x + ks2) + k0 * ks1)];
N_21 = k0 * x + x^2; % input Tkz
N_22 = [(Cv2 * ks2) (ks2 * (k0 + ks2 + x) + k0 * ks1 + x * ks1)];

transferFunction1 = tf(N1, M);
transferFunction2 = tf(N2, M);

transferFunction3 = tf(N_12, M1);
transferFunction4 = tf(N_22, M2);

K1 = x + ks1 + k0;
K2 = x + k0 + ks2;

s1 = K1/Cv1;
s2 = K2/Cv2;

sprintf("s1 = %f\n", s1)
sprintf("s2 = %f\n", s2)
sprintf("1/s1 = %f\n", 1/s1)
sprintf("1/s2 = %f\n", 1/s2)

figure(1);
bode(transferFunction1);
grid on;
title("Bode diagram of transfer function 1");
% WNIOSKI:
% - współczynniki czasowe na podstawie wykresu Bodego wynoszą:
%   - 1/T1 = 0.0639
% - wyliczone współczynniki czasowe:
%   - 1/T1 = 0.065
% Współczynniki są do siebie zbliżone

figure(2);
nyquist(transferFunction1);
grid on;
title("Nyquist diagram of transfer function 1");

figure(3);
bode(transferFunction2);
grid on;
title("Bode diagram of transfer function 2");

% WNIOSKI:
% - współczynniki czasowe na podstawie wykresu Bodego wynoszą:
%   - 1/T1 = 0.0639
%   - 1/T2 = 0.162
% - wyliczone współczynniki czasowe:
%   - 1/T1 = 0.065
%   - 1/T2 = 0.084
% Współczynniki T1 są do siebie zbliżone, T2 nie są
% bliskie, może to być spowodowane błędem przy sczytywaniu 
% parametrów z wykresu Bodego (niska rozdzielczość Data Tip'ów w Matlabie)
% Członu forsującego nie widać.

figure(4);
nyquist(transferFunction2);
grid on;
title("Nyquist diagram of transfer function 2");
% WNIOSKI:
% Układ jest drugiego stopnia.


% Wniosek:
% zrekreowany model przypomina oryginalny

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
