function [time_vec, state_vec] = simulate_system(x_0, dt, end_time, u)
time_vec = [];
state_vec = [];
u_param = u;
curr_state = x_0;
domain = 1;
curr_time = 0;

while curr_time < end_time
    options = odeset('Events', @(t,x)guards(t,x,domain, u_param)); % checking for guard event
    [time, states] = ode45(@(t,x)flows(t,x,u_param, domain), [curr_time, curr_time + dt], curr_state, options);
    new_time = time(end);
    new_state = states(end,:);
    disp(states(:,5));
    
    % check if hybrid event occured
    if new_time < curr_time + dt
        [new_state, u_param] = resets(new_time, new_state, domain, u_param); % apply reset map
        
        % change domains
        if domain < 2
            domain = domain + 1;
        else
            domain = 1;
        end

        % simulate for rest of time step
        [time, states] = ode45(@(t,x)flows(t,x,u_param),[new_time,curr_time + dt],new_state);

        new_time = time(end); % update time
        new_state = states(end,:)'; % update state
    end
    time_vec = [time_vec; time];
    state_vec = [state_vec; states];
    
    curr_state = new_state;
    curr_time = new_time;
end
final_time = curr_time;
final_state = new_state;
end
