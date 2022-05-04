clear all
close all

L1 = 3;
L2 = 6;

y_vec = zeros(1, 181);
theta_vec = 0:2:360;

theta = 0:2:360;

for i = 1:length(theta)
    
    % angles alpha = beta = theta
    % simulates both motors moving synchronously
    theta2(i) = theta(i);

    % when reaching peak, reverse back to bottom
    % this is meant to imitate guards: apex, floor
    if theta(i) > 180
        theta2(i) = 360-theta(i);
    end
    
    beta(i) = theta2(i);
    alpha(i) = theta2(i);
    h(i) = L1*sqrt(2*(1 - cosd(alpha(i) + beta(i))));
    phi(i) = acosd(h(i)/(2*L2));
    
    % Leg 1
    Ax(i) = 0;
    Ay(i) = 9;
    
    Bx(i) = Ax(i) - L1*sind(alpha(i));
    By(i) = Ay(i) - L1*cosd(alpha(i));
    
    D1x(i) = Bx(i) + L2*cosd(phi(i));
    D1y(i) = By(i) - L2*sind(phi(i));
    
    Cx(i) = Ax(i) + L1*sind(beta(i));
    Cy(i) = Ay(i) - L1*cosd(beta(i));
    
    D2x(i) = Cx(i) - L2*cosd(phi(i));
    D2y(i) = Cy(i) - L2*sind(phi(i));
    
    % Left Link
    plot( [Ax(i) Bx(i)], [Ay(i) By(i)],[Bx(i) D1x(i)], [By(i) D1y(i)],... %ABD
          'LineWidth', 3);
    hold on;
    % Right Link
    plot( [Ax(i) Cx(i)], [Ay(i) Cy(i)],[Cx(i) D2x(i)], [Cy(i) D2y(i)], 'LineWidth', 3);
    hold on;
    
    % Leg 2
    A1x(i) = 9;
    A1y(i) = 9;
    
    B1x(i) = A1x(i) - L1*sind(alpha(i));
    B1y(i) = A1y(i) - L1*cosd(alpha(i));
    
    D12x(i) = B1x(i) + L2*cosd(phi(i));
    D12y(i) = B1y(i) - L2*sind(phi(i));
    
    C1x(i) = A1x(i) + L1*sind(beta(i));
    C1y(i) = A1y(i) - L1*cosd(beta(i));
    
    D22x(i) = C1x(i) - L2*cosd(phi(i));
    D22y(i) = C1y(i) - L2*sind(phi(i));
    


    % Left Link
    plot([A1x(i) B1x(i)], [A1y(i) B1y(i)],[B1x(i) D12x(i)], [B1y(i) D12y(i)],... %ABD
          'LineWidth', 3);
    hold on;
    % Right Link
    plot( [A1x(i) C1x(i)], [A1y(i) C1y(i)],[C1x(i) D22x(i)], [Cy(i) D22y(i)], 'LineWidth', 3);
    hold on;
    
    plot ( [Ax(i) A1x(i)], [Ay(i) A1y(i)] , 'LineWidth', 3 );
    
    hold on;
    
    grid on;
    axis equal;
    axis ( [-5 15 -5 15] );
    drawnow;
    hold off;
    

%     v = [D22x(i) D22y(i)];
%     Uncomment to model angles:
%     theta_vec = [theta_vec; theta(i)];
%     y_vec(i) = D1y(i);
%     x = [D1y];

end

% figure(1);
% plot(theta_vec, y_vec)
% xlabel('theta');
% ylabel('Y');
% title('Angle Displacement vs. Y Position');
