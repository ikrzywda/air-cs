SIMPLIFIED_MODEL_PATH = "lab_7_sim.slx";

Aw1 = 0.1 * 2;
Aw2 = Aw1;
H1 = 5;
H2 = 4;
g = 9.81;

a1 = (Aw1 * sqrt(2 * g * (H1 - H2))) / (H1 - H2);
a2 = (Aw2 * sqrt(2 * g * H2)) / (H1 - H2);

fwe1max = a1 * (H1 - H2);
fwe2max = a2 - fwe1max;

Vfwe10=[0,0.5*fwe1max,0.9*fwe1max];
Vfwe20=[0,0.5*fwe2max,0.9*fwe2max];

fwe20=0.2*fwe2max;
dfwe2=0;
dfwe1=0.1*fwe1max;

for i = 1:3
    fwe10=Vfwe10(i);
    h20=(fwe10+fwe20)/a2;
    h10=fwe10/a1 + h20;
    [output] = sim(SIMPLIFIED_MODEL_PATH);
    subplot(211);
    hold on;
    grid on;
    plot(output.tout, output.h1);
    xlabel('t [s]');
    ylabel('h1(t)');
    title('Reakcja zbiornika 1. na pobudzenie w pierwszym zbiorniku (model uproszczony)');
    subplot(212)
    hold on;
    grid on;
    plot(output.tout, output.h2);
    xlabel('t [s]');
    ylabel('h2(t)');
    title('Reakcja zbiornika 2. na pobudzenie w pierwszym zbiorniku (model uproszczony)');
end
