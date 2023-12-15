% Igor Krzywda, 275480
% grupa 5, pt. 11:15
% cw. 9

% Notes: using SI Units unless stated otherwise in variable name


% constants
Vw1 = 40;
Vw2 = 0.8 * Vw1;    
cpp = 1000;
rop = 1.2;

% nominal values
TzewN = -20;
Twew1N = 20;
Twew2N = 15;
TkzN = 30;
PkN = 20000;
fkN = (...
    (PkN) / (cpp * rop * (Twew1N - TzewN)) ...
);

ks1N = ( ...
    (0.7 * PkN) / (Twew1N - TzewN) ...
);
k0N = (cpp * rop * fkN * (TkzN - Twew1N) - ks1N * (TkzN - Twew1N)) / (Twew1N - Twew2N);
ks2N = (k0N * (Twew1N - Twew2N) + cpp * rop * fkN * (Twew1N - Twew2N)) / (Twew2N - TzewN);
