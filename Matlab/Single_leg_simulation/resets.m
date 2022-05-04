function [x_plus, u_plus] = resets(t, x, domain, u)

% if domain == 2
if domain == 2 % approaching ground
    x_plus = x; % all other params stay the same
    x_plus(2) = 0; % set adot to zero
    x_plus(4) = 0; % set bdot to zero
    u_plus = u;
    u_plus(1) = -u(1); % pos acc up
    u_plus(2) = -u(2); % pos acc up
    
elseif domain == 1 % approaching peak
    x_plus = x; % all other params stay the same
    x_plus(2) = 0; % set adot to zero
    x_plus(4) = 0; % set bdot to zero
    u_plus = u;
    u_plus(1) = -u(1); % reverse acc down
    u_plus(2) = -u(2); % reverse acc down
end
end
