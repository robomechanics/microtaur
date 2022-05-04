function sdot = flows(t, x, u, domain)
adotdot = u(1);
bdotdot = u(2);

leg1 = 3;
leg2 = 6;

a = x(1);
adot = x(2);
b = x(3);
bdot = x(4);
y = x(5);
ydot = x(6);

sdot = zeros(6,1);
sdot(1) = adot;
sdot(2) = adotdot;
sdot(3) = bdot;
sdot(4) = bdotdot;

sdot(5) = leg1*sin(a)*adot + (leg1^2*sin(a + b)*(adot + bdot))/(4*leg2*((leg1^2*(cos(a + b) - 1))/(2*leg2^2) + 1)^(1/2));

sdot(6) = 0;%leg1*(adotdot*sind(a) + (adot^2)*cosd(a)) + (1/16)* (leg1^4)*(sind(a + b)^2)*((a + b)^2) * ((leg2^2) - (leg1^2)/2 + ((leg1^2)/2)*cosd(a + b))^(-3/2) + (1/4)*(leg1^4)*sind(a + b)*cos(a + b)*(adotdot + bdotdot)*(adot + bdot)^2 * (leg2^2 - (leg1^2)/2 + ((leg1^2)/2)*cosd(a + b))^(-1/2);
end
