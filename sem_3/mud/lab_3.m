% Igor Krzywda, 275480
% pt 11:15, lab 5

close all

t = 0:0.1:10;
L1 = -0.5;
L2 = -3;
XK = 2/3;


W10 = 2;
W11 = 0;
A1 = (L2 * (XK - W10) + W11) / (L1 - L2);
A2 = (-L1 * (XK - W10) + W11) / (L1 - L2);

przyklad_wolny = (A1 * exp(L1 * t)) + A2 * exp(L2 * t);
przyklad1 = (A1 * exp(L1 * t)) + A2 * exp(L2 * t) + XK;

figure();
title("Wymuszenie stałe, przykład 1", "Interpreter", "latex");
hold on
plot(t, przyklad_wolny, ':');
plot(t, (2 / 3) + t * 0, ':');
plot(t, przyklad1, '-');
 
legend("xs", "xt", "x(t)");
hold off


figure();
hold on
title("Wymuszenie stale, przykład 2", "Interpreter", "latex");
plot(t, (-30/7 * exp(-0.5 * t)) + 1/21 * exp(-3 * t), ':');
plot(t, (2 / 3) + t * 0, ':');
plot(t, (-30/7 * exp(-0.5 * t)) + 1/21 * exp(-3 * t) + (2 / 3) + t * 0, '-');
legend("xs", "xt", "x(t)");
hold off
% 
% 

XP = A1 + A2 + XK;
skokowe = ((L2 * (XK - XP)) / (L1 - L2)) * exp(L1 * t) + ((-L1 * (XK - XP)) / (L1 - L2)) * exp(L2 * t) + XK;
figure();
hold on
title("Wymuszenie skokowe", "Interpreter", "latex");
plot( ...
    t, ...
    skokowe, ...
    '-' ...
);
plot(t, (2 / 3) + t * 0, ':');
legend("x(t)", "xt");
hold off
 

figure();
title("Porownanie", "Interpreter", "latex");
hold on
plot(t, przyklad1, '-');
plot(t, (-30/7 * exp(-0.5 * t)) + 1/21 * exp(-3 * t) + (2 / 3) + t * 0, '-');
plot(t, skokowe, '-');
plot(t, (2 / 3) + t * 0, ':');
legend("x1(t)", "x2(t)", "xs(t)", "xt")
hold off


figure();
title("impuls")
hold on
plot(t, 2/3 * ((L1 * L2)/(L1 - L2)) * (exp(L1 * t) - exp(L2 * t)));
hold off
    
