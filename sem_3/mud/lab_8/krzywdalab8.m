%MUX -ca> SS -> DEMUX

SS_SIM_PATH = "krzywdalab8_ss_si.slx";
TF_SIM_PATH = "krzywdalab8_tf_si.slx";

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
tab_fwe1 = [0, 0.5 * fwe1max, 0.9 * fwe1max];

A = [(-a1/A1) a1/A1; a1/A2 (-a1 - a2)/A2];
B = [1/A1 0; 0 1/A2];
C = [1 0; 0 1];
D = [0 0; 0 0];

fwe20=0.1 * fwe2max;
dfwe2= 0;
dfwe1= 0.1 * fwe1max;
figure();

hold on;
for it = 1:3
    fwe10 = tab_fwe1(it);
    h20 = (fwe10 + fwe20) / a2;
    h10 = (fwe10 + a1 * h20) / a1;
    H0 = [h10 h20];
    [output] = sim(SS_SIM_PATH, "StartTime","0","StopTime","30","FixedStep","0.1");
    plot(output.tout, output.h1); 
    title("Odpowiedź h1 dla modelu równania stanu");
end
hold off;

figure();
hold on;
for it = 1:3
    fwe10 = tab_fwe1(it);
    h20 = (fwe10 + fwe20) / a2;
    h10 = (fwe10 + a1 * h20) / a1;
    H0 = [h10 h20];
    [output] = sim(SS_SIM_PATH, "StartTime","0","StopTime","30","FixedStep","0.1");
    plot(output.tout, output.h2); 
    title("Odpowiedź h2 dla modelu równania stanu");
end
hold off;



% 

M = [(A1*A2) (a1*A1+a2*A1+a1*A2) a1*a2];
N_11 = [A2 (a1+a2)];
N_12 = [a1];
N_21 = [a1];
N_22 = [A1 a1];


figure();

hold on;
for it = 1:3
    fwe10 = tab_fwe1(it);
    h20 = (fwe10 + fwe20) / a2;
    h10 = (fwe10 + a1 * h20) / a1;
    H0 = [h10 h20];
    [output] = sim(TF_SIM_PATH, "StartTime","0","StopTime","30","FixedStep","0.1");
    plot(output.tout, output.h1); 
    title("Odpowiedź h1 dla transmisyjnego modelu");
end
hold off;



figure();

hold on;
for it = 1:3
    fwe10 = tab_fwe1(it);
    h20 = (fwe10 + fwe20) / a2;
    h10 = (fwe10 + a1 * h20) / a1;
    H0 = [h10 h20];
    [output] = sim(TF_SIM_PATH, "StartTime","0","StopTime","30","FixedStep","0.1");
    plot(output.tout, output.h2); 
    title("Odpowiedź h2 dla transmisyjnego modelu");
end
hold off;
