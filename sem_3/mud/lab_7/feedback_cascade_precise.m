% Igor Krzywda, 275480
% grupa 5, pt. 11:15
% cw. 6

close all;
SIMULATION_PATH = "lab_7_sim_nl.slx";

% Step time
T0 = 2;

% Area of the bottom
bottom_area = 2;


% Areas of holes
hole_1_cross_area = 0.1 * bottom_area;
hole_2_cross_area = 0.8;

% Heights of containers
max_water_level_1 = 5;
max_water_level_2 = 4;
water_level_delta = max_water_level_1 - max_water_level_2;

g = 9.81;


% Maximum input values
flow_input_max_1 = hole_1_cross_area *  sqrt(2 * g * water_level_delta);
flow_input_max_2 = hole_2_cross_area *  sqrt(2 * g * max_water_level_2) - flow_input_max_1;

% Flow values
flow_inputs_vec_1 = [0, 0.5 * flow_input_max_1, 0.9 * flow_input_max_1];
flow_inputs_vec_2 = [0, 0.5 * flow_input_max_2, 0.9 * flow_input_max_2];
flow_input_step_1 = 0.1 * flow_input_max_1;
flow_input_step_2 = 0;

% Simulation parameters
A1 = bottom_area;
A2 = bottom_area;
Aw1 = hole_1_cross_area;
Aw2 = hole_2_cross_area;
initial_height_1 = 0;
initial_height_2 = 0;
initial_flow_input_1 = 0;
initial_flow_input_2 = flow_input_max_2;


% Case no. 1: step in container one and constant level in container 2
fig_1 = figure();
for i = 1:3
    initial_flow_input_1 = flow_inputs_vec_1(i);
    initial_height_2 = (...
        ((flow_input_max_2 + initial_flow_input_1) ^ 2) / (2 * g * hole_2_cross_area ^ 2) ...
    );

    initial_height_1 = (initial_flow_input_1 ^ 2) / (2 * g * hole_1_cross_area ^ 2) + initial_height_2;
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
legend(generate_descriptors("f_we1", flow_inputs_vec_1), "Location", "best");
figure(fig_1);
subplot(212);
legend(generate_descriptors("f_we1", flow_inputs_vec_1), "Location", "best");

saveas(fig_1, "feedback_precise.png");

function descriptors = generate_descriptors(param_name, value_vec)
    descriptors = string([]);
    for i = 1:length(value_vec)
        descriptors(i) = sprintf("%s = %.2f", param_name, value_vec(i));
    end
end