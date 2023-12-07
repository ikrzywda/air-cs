% Igor Krzywda, 275480
% grupa 5, pt. 11:15
% cw. 6

close all;
SIMULATION_PATH = "simulation.slx";

% Step time
T0 = 2;

% Area of the bottom
A1 = 2;
A2 = 8;

% Areas of holes
AW1 = 0.2;
AW2 = 0.8;

% Heights of containers
H1 = 4;
H2 = 5;

g = 9.81;

% Linearization constants
a1 = (AW1 * sqrt(2 * g * H1)) / H1;
a2 = (AW2 * sqrt(2 * g * H2)) / H2;

% Maximum input values
flow_input_max_1 = a1 * H1;
flow_input_max_2 = a2 * H2 - a1 * H1;

% Flow values
flow_inputs_vec_1 = [0, 0.5 * flow_input_max_1, 0.9 * flow_input_max_1];
flow_inputs_vec_2 = [0, 0.5 * flow_input_max_2, 0.9 * flow_input_max_2];
flow_input_step_1 = 0.1 * flow_input_max_1;
flow_input_step_2 = 0;

% Initial conditions -- used in sumulation
initial_height_1 = 0;
initial_height_2 = 0;
initial_flow_input_1 = 0;
initial_flow_input_2 = flow_input_max_2;

% Case no. 1: step in container one and constant level in container 2
fig_1 = figure();
for i = 1:3
    initial_height_1 = flow_inputs_vec_1(i) / a1;
    initial_height_2 = (flow_input_max_2 + flow_inputs_vec_1(i))/ a2;
    initial_flow_input_1 = flow_inputs_vec_1(i);
    
    [output] = sim(SIMULATION_PATH);

    hold on;
    subplot(211);
    plot(output.tout, output.h1);
    xlabel("t [s]");
    ylabel("h_1(t) [m]");
    title("Odpowiedź w zbiorniku 1");

    
    hold on;
    subplot(212);
    plot(output.tout, output.h2);
    xlabel("Czas [s]");
    ylabel("h_2(t) [m]");
    title("Odpowiedź w zbiorniku 2");    
end
figure(fig_1);
subplot(211);
legend(generate_descriptors("f_we1", flow_inputs_vec_1 ./ a1), "Location", "best");
figure(fig_1);
subplot(212);
legend(generate_descriptors("f_we2", flow_inputs_vec_1 ./ a1), "Location", "best");

% Case no. 2: step in container two and constant flow in container 2

flow_input_step_1 = 0;
flow_input_step_2 = 0.1 * flow_input_max_2;
fig_1 = figure();
for i = 1:3
    initial_height_1 = flow_input_max_1 / a1;
    initial_height_2 = (flow_inputs_vec_2(i) + flow_input_max_1) / a2;
    initial_flow_input_1 = flow_inputs_vec_1(i);

    [output] = sim(SIMULATION_PATH);

    hold on;
    subplot(211);
    plot(output.tout, output.h1);
    xlabel("t [s]");
    ylabel("h_1(t) [m]");
    title("Odpowiedź w zbiorniku 1");


    hold on;
    subplot(212);
    plot(output.tout, output.h2);
    xlabel("Czas [s]");
    ylabel("h_2(t) [m]");
    title("Odpowiedź w zbiorniku 2");    
end
figure(fig_1);
subplot(211);
legend(generate_descriptors("f_we1", flow_inputs_vec_1 ./ a1), "Location", "best");
figure(fig_1);
subplot(212);
legend(generate_descriptors("f_we2", flow_inputs_vec_1 ./ a1), "Location", "best");


function descriptors = generate_descriptors(param_name, value_vec)
    descriptors = string([]);
    for i = 1:length(value_vec)
        descriptors(i) = sprintf("%s = %.2f", param_name, value_vec(i));
    end
end