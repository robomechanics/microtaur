clear; close all;
tic
%% 
% alpha = a
% beta = b
% Initial conditions/state:
% L1 = 3, L2 = 6
x_0 = [0;0;0;0;0;0]; % initial state

% simulate
u = [1;1];
dt = 0.01;
end_time = 10;

% simulate
[time_vec, state_vec] = simulate_system(x_0, dt, end_time, u);

%% Plot trajectory
xlabel('t');
ylabel('y');
hold on;

figure(1);
plot(time_vec,state_vec(:,5)); % plot y position
title('Y Position');

figure(2);
plot(time_vec,state_vec(:,2)); % plot adot || bdot
xlabel('time');
ylabel('rad');
title('Angular Acceleration');

figure(3);
plot(time_vec,state_vec(:,1)); % plot adot || bdot
title('Alpha Velocity');
xlabel('time');
ylabel('rad');

figure(4);
plot(time_vec,state_vec(:,3)); % plot adot || bdot
title('Beta Velocity');
xlabel('time');
ylabel('rad');
