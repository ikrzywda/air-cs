

SIMPLIFIED_MODEL_PATH = "lab_7_sim.slx";
PRECISE_MODEL_PATH = "lab_7_sim_nl.slx";

T0 = 2;
Aw1 = 0.1 * 2;
Aw2 = Aw1;
H1 = 5;
H2 = 4;
g = 9.81;
A1 = 1;
A2 = 1;

a1 = (Aw1 * sqrt(2 * g * (H1 - H2))) / (H1 - H2);
a2 = (Aw2 * sqrt(2 * g * H2)) / (H1 - H2);

fwe1max = a1 * (H1 - H2);
fwe2max = a2 - fwe1max;

fwe1max_nl = Aw1 * sqrt(2 * g * (H1 - H2));
fwe2max_nl = Aw2 * sqrt(2 * g * H2) - Aw1 * sqrt(2 * g * (H1 - H2));

tab_fwe1 = [0, 0.5 * fwe1max, 0.9 * fwe1max];
tab_fwe2 = [0, 0.5 * fwe2max, 0.9 * fwe2max];
fwe2 = 0.2 * fwe2max;


tab_fwe1_nl = [0, 0.5 * fwe1max_nl, 0.9 * fwe1max_nl];
tab_fwe2_nl = [0, 0.5 * fwe2max_nl, 0.9 * fwe2max_nl];
% fwe2_nl = 0.2 * fwe2max;
fwe20=0.2 * fwe2max;
dfwe2= 0;
dfwe1= 0.1 * fwe1max;

figure();
hold on;
for it = 1:3
    fwe10 = tab_fwe1(it);
    % fwe20 = tab_fwe2(it);
    h20 = (fwe10 + fwe20) / a2;
    h10 = (fwe10 + a1 * h20) / a1;
    [output] = sim(SIMPLIFIED_MODEL_PATH, "StartTime","0","StopTime","30","FixedStep","0.1");
    plot(output.tout, output.h1); 
    title("Odpowiedź h1 dla uproszczonego modelu");
end
hold off;

figure();
hold on;
for it = 1:3
    fwe10 = tab_fwe1(it);
    % fwe20 = tab_fwe2(it);
    h20 = (fwe10 + fwe20) / a2;
    h10 = (fwe10 + a1 * h20) / a1;
    [output] = sim(SIMPLIFIED_MODEL_PATH, "StartTime","0","StopTime","30","FixedStep","0.01");
    plot(output.tout, output.h2); 
    title("Odpowiedź h2 dla uproszczonego modelu");
end
hold off;

fwe20 = 1 * fwe2max_nl;

% figure();
% hold on;
% for it = 1:3
%     fwe10 = tab_fwe1_nl(it);
%     fwe20 = tab_fwe2(it);
%     % h20 = (fwe20 ^ 2 + 2 * fwe20 * sqrt(fwe10) + fwe10) / (Aw2 * 2 * g);
%     % h20 = (fwe10 + fwe20) ^ 2;
%     h20 = ((fwe10 + fwe20) ^ 2) / (Aw2^2 * 2 * g);
%     h10 = (fwe10 ^ 2 + Aw1 ^ 2 * 2 * g * h20) / (2 * Aw1 ^ 2 * g);
%     [output] = sim(PRECISE_MODEL_PATH, "StartTime","0","StopTime","30","FixedStep","0.01");
%     plot(output.tout, output.h1); 
%     title("Odpowiedź h1 dla dokładnego modelu");
% end
% hold off;
% 
% figure();
% hold on;
% for it = 1:3
%     fwe10 = tab_fwe1(it);
%     fwe20 = tab_fwe2(it);
%     h20 = ((fwe10 + fwe20) ^ 2) / (Aw2^2 * 2 * g);
%     h10 = (fwe10 ^ 2 + Aw1 ^ 2 * 2 * g * h20) / (2 * Aw1 ^ 2 * g);
%     [output] = sim(PRECISE_MODEL_PATH, "StartTime","0","StopTime","30","FixedStep","0.01");
%     plot(output.tout, output.h2); 
%     title("Odpowiedź h2 dla dokładnego modelu");
% end
% hold off;
