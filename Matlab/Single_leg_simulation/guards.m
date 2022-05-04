function [value, isterminal, directions] = guards(t, x, domain, u)

floor = x(5);
y_max = 6 - x(5);


g(1) = y_max; % apex
g(2) = floor; % ground strike

if floor < 0.001
    g(2) = 0;
end

% Check all contact conditions with this value
value = g(domain); % The value that we want to be zero
isterminal = 1;  % Halt integration and change contact modes
directions = 0;   % The zero can only be approached from

end

