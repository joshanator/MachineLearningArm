function [fitresult, gof] = createFit(x1, y1, z1)
%CREATEFIT(X1,Y1,Z1)
%  Create a fit.
%
%  Data for 'untitled fit 1' fit:
%      X Input : x1
%      Y Input : y1
%      Z Output: z1
%  Output:
%      fitresult : a fit object representing the fit.
%      gof : structure with goodness-of fit info.
%
%  See also FIT, CFIT, SFIT.

%  Auto-generated by MATLAB on 08-Apr-2017 22:00:36


%% Fit: 'untitled fit 1'.
[xData, yData, zData] = prepareSurfaceData( x1, y1, z1 );

% Set up fittype and options.
ft = 'biharmonicinterp';

% Fit model to data.
[fitresult, gof] = fit( [xData, yData], zData, ft, 'Normalize', 'on' );

% Plot fit with data.
figure( 'Name', 'untitled fit 1' );
h = plot( fitresult, [xData, yData], zData );
legend( h, 'untitled fit 1', 'z1 vs. x1, y1', 'Location', 'NorthEast' );
% Label axes
xlabel x1
ylabel y1
zlabel z1
grid on
view( -15.5, -1.2 );



