clc 
clear all
%% Define Global Simulation Parameters
global waypointx 
global waypointy 
global a
global b
global c
global e
global v_d
global sx_0
global sy_0
global psi_0
global delta
global init_v
global tlookahead
global tsched
global v_env1
global v_env2
global time
global lane_offset


%% Initialize scenario
init_psi=0;
% Desired velocity (m/s)
v_d =11.1;
% Time horizon (s)
tfinal= 0.1;
% Time series
t=[0:0.1:tfinal];
% Initial position x (m)
sx_0 = 0;
% Initial position y (m)
sy_0 = 0;
% Initial velocity (m/s)
init_v = 11.1;
% Velocity for env1
v_env1=6;
% Velocity for env2
v_env2=7;
% Initialize the computation mode, cannot be picked...
init_computation = [0,0,0,0,0,0,0,0,0,0]';

% Set the initial time (s) along traj that env1 should be moved ahead by...
% This should be a variable that S-Taliro gets to vary...
t_init_env1=0.5;

% Set the initial offset (lane offset for env2) in meters
% This should be a variable that S-Taliro gets to vary...

lane_offset=3.7;

% Set the initial time (s) along traj that env2 should be moved ahead by...
% This should be a variable that S-Taliro gets to vary...
t_init_env2= 0.67;

% Set the lookahead time for the ego-vehicle.
% This is a parameter that can be chosen by S-Taliro
tlookahead= 0.1;
tsched=0.1;
time=0;

% Initialize the ego-vehicle state vector
% Can be picked by S-Taliro
s1.y=[0,0,0,init_v,0,0,0,0,0,0,0,0,0,0]';

% Initialize env1 state vector
% Can be picked by S-Taliro
init_env1 = [0,0,0,0]';

% Initialize env2 state vector
% Can be picked by S-Taliro
init_env2 = [0,0,0,0]';

%% Define Parameters for Road Centerline
s = (33.831636);
kappa_0 =(0.000000);
kappa_1 = (0.006046);
kappa_2 = (-0.000322);
kappa_3 = (0.000000);

a = kappa_0;
b = ((-0.50)*(-2*kappa_3 + 11*kappa_0 - 18*kappa_1 + 9*kappa_2)/s);
c = ((4.50)*(-kappa_3 + 2*kappa_0 - 5*kappa_1 +4*kappa_2)/(s*s));
e = ((-4.50)*(-kappa_3 + kappa_0 - 3*kappa_1 + 3*kappa_2)/(s*s*s));

%% Compute The Initial Waypoint
g1=ode45(@computation,[0,tlookahead],init_computation);
deltax=g1.y(3,end);
deltay=g1.y(4,end);
waypointx = sx_0+deltax;
waypointy = sy_0+deltay;
psi_0=0;

%% Compute the initial Position for env1
env1=ode45(@initEnv1, [0, t_init_env1], init_env1);

%% Compute the initial position for env2
env2= ode45(@initEnv2, [0,t_init_env2], init_env2); 

