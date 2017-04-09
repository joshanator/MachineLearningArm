x = [0 .5 1 2 2];
y = [2 1 1 0 2];
z = [4 2 0 4 5];

%% Fit: 'untitled fit 1'.
[xData, yData, zData] = prepareSurfaceData( x, y, z );

% Set up fittype and options.
ft = 'biharmonicinterp';

% Fit model to data.
[fitresult, gof] = fit( [xData, yData], zData, ft, 'Normalize', 'on' );

% Plot fit with data.
figure( 'Name', 'untitled fit 1' );
h = plot( fitresult, [xData, yData], zData );
legend( h, 'untitled fit 1', 'z1 vs. x1, y1', 'Location', 'NorthEast' );
% Label axes
xlabel x
ylabel y
zlabel z
grid on
view( -15.5, -1.2 );