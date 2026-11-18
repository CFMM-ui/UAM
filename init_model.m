
clear, clc

% Open 'HexaProject.prj' to add all needed files to MATLAB path
try
    proj = currentProject;
catch
    proj = openProject("UAM_Hexa_PID.prj");
end
%%
% Init Arm Model
ArmConstants = InitArmConstants();          % load arm's inertia info

% Init Hexa Model
run("Hexa_with_Arm_DataFile.m")             % load CAD rigid transform info
HexaConstants = InitHexaConstants();        % load Hexa's inertia info
%%
% Get Trajectory: Go to InitTrajectoryPoints to set a custom trajectory
m = 0.05;                                   % mass of the object
[Trajectory, PickObj] = InitTrajectoryPoints(m);
tf = 30;                                % final time of simulation
st = 0.01;
SampleTime = 0.01;
MAVLink_Input_Read_Size = 1024;

%% Init Controller and Model

% mdl = "UAM_Hexa_PD_Diff_0";
%mdl = "UAM_Hexa_PD_Diff_SIL";
%mdl = "UAM_Hexa_PD_Diff";
% mdl = "UAM_Hexa_PD_Obs";
mdl = "UAM_Hexa_PD_Obs_Disc";
% mdl = "UAM_Hexa_PD_Obs_SinSimscape_triste";
% mdl = "UAM_Hexa_PD_Diff_HITL";
%mdl = "UAM_Hexa_PD_Diff_HTL_Disc_Pixhawk";
%mdl = "UAM_Hexa_PD_Diff_Pos_Man";
%mdl = "UAM_Hexa_PD";  
PID = InitController();                     % load controller gains
Differentiator = InitDifferentiator();
Observer = InitObserver();
% open_system(mdl)                            % open Simulink model
% sim(mdl)                                    % simulate model

%%

function [Trajectory, PickObj] = InitTrajectoryPoints(m)

xobj = -3;
yobj = -0.5;
zobj = 1;

xobj2 = 3;
yobj2 = 0.5;
zobj2 = 1.5;

PickPose = [xobj; yobj; zobj; 0; 0; 90];
Pickq = [60; 30];

% QUIETO
Tray = [0   , 0         , 0         , 0.24  , 0, 0, 0 , 0 , 0 ;...
        10  , 0         , 0         , 0.24  , 0, 0, 0 , 0 , 0 ;...
        20  , 0         , 0         , 0.24  , 0, 0, 0 , 45 , 45 ;...
        30  , 0         , 0         , 0.24  , 0, 0, 0 , 0 , 0 ;...
        ];

%Pick and Place

% Tray = [0   , 0         , 0         , 0.24  , 0, 0, 0 , 0 , 0 ;...
%         15  , 0         , 0         , 0.8   , 0, 0, 0 , 0 , 0 ;...
%         22  , xobj+0.5  , 0         , zobj  , 0, 0, 90, 0 , 0 ;...
%         30  , xobj+0.5  , yobj      , zobj  , 0, 0, 90, 0 , 0 ;...
%         40  , xobj+0.5  , yobj      , zobj  , 0, 0, 90, Pickq';...
%         45  , PickPose'                               , Pickq';...
%         60  , PickPose'                               , Pickq';...
%         65  , xobj+0.5  , yobj      , zobj  , 0, 0, 90, Pickq';...
%         85  , xobj+0.5  , yobj      , zobj  , 0, 0, 90, 0 , 0 ;...
%         95  , xobj+0.5  , yobj2     , zobj2 , 0, 0, 90, 0 , 0 ;...
%         110 , xobj2     , yobj2     , zobj2 , 0, 0, 0 , 0 , 0 ;...
%         135 , xobj2-0.5 , yobj2     , zobj2 , 0, 0, -90 , Pickq';...
%         140 , xobj2     , yobj2     , zobj2 , 0, 0, -90, Pickq';...
%         155 , xobj2     , yobj2     , zobj2 , 0, 0, -90, Pickq';...
%         160 , xobj2-0.5 , yobj2     , zobj2 , 0, 0, 0 , Pickq';...
%         175 , xobj2     , yobj2     , zobj2 , 0, 0, 0 , 0 , 0 ;...
%         195 , 0         , -0.3      , zobj2 , 0, 0, 0 , 0 , 0 ;...
%         210 , 0         , 0         , 0.24  , 0, 0, 0 , 0 , 0
%         ];

%Simulacion 2 Oscilacion del manipulador

% Tray = [0   , 0         , 0         , 0.24  , 0, 0, 0 , 0  , 0 ;...
%     10  , 0         , 0         , 1     , 0, 0, 0 , 0 , 0;...
%     15  , 0         , 0         , 1     , 0, 0, 0 , 45 , 45;...
%     20  , 0         , 0         , 1     , 0, 0, 0 , 0 , 0;...
%     25  , 0         , 0         , 1     , 0, 0, 0 , -45 , -45;...
%     30  , 0         , 0         , 1     , 0, 0, 0 , 0 , 0;...
%     35  , 0         , 0         , 1     , 0, 0, 0 , 45 , 45;...
%     40  , 0         , 0         , 1     , 0, 0, 0 , 0 , 0;...
%     45  , 0         , 0         , 1     , 0, 0, 0 , -45 , -45;...
%     50  , 0         , 0         , 1     , 0, 0, 0 , 0 , 0;...
%     ];

%Simulacion 3 Oscilacion del manipulador

% Tray = [0   , 0         , 0         , 0.24  , 0, 0, 0 , 0  , 0 ;...
%     10  , 0         , 0         , 1     , 0, 0, 0 , 0 , 0;...
%     20  , 0         , 0         , 1     , 0, 0, 90 , 0 , 0;...
%     ];

% To radians
tstamps = Tray(:,1)';
TrayPoints = Tray(:,2:end);
TrayPoints(:,4:end) = deg2rad(TrayPoints(:,4:end));

Trajectory = struct('Tstamps', tstamps,...
                    'Waypoints', TrayPoints');

PickObj = struct('Radius', 0.023,...
                 'Mass', m,...
                 'Time', [48, 143]);
                 %'Time', [348, 443]);

end

function ArmConstants = InitArmConstants()

L = 0.08312; % Distance from hexa to first joint
l1_dim = 0.17; % Links dimension in meters
l2_dim = 0.17959;

ml1 = 0.142;
ml2 = 0.143;

Hl1 = diag([0.00005484, 0.00050874,  0.00046501]);
Hl2 = diag([0.00008085, 0.00034964,  0.00030340]);

c1 = 0.11464;
c2 = 0.09794;

% Servos
T1max = 2.5;
T2max = 2.5;

Servos = struct('T1max', T1max,...
                'T2max', T2max);

ArmConstants = struct('l1_dim', l1_dim,...
                       'l2_dim', l2_dim,...
                       'Hexa_to_joint_L', L,...
                       'Mass1', ml1,...
                       'Mass2', ml2,...
                       'Inertia1', Hl1,...
                       'Inertia2', Hl2,...
                       'MC1', c1,...
                       'MC2', c2,...
                       'Servos', Servos);

end

function HexaConstants = InitHexaConstants()

    mb = 1.8188;
    Jxx = 0.03937480;       % Inertia x.
    Jyy = 0.04043155;       % Inertia y.
    Jzz = 0.06214814;       % Inertia z.
    J = diag([Jxx, Jyy, Jzz]);

    allo = 1.0e-05*[-0.2372    0.2372    0.0000   -0.2372    0.2372    0.0000;...
                     0.1369    0.1369   -0.2739    0.1369    0.1369   -0.2739;...
                     0.7525    0.7525    0.7525    0.7525    0.7525    0.7525;...
                     0.1694    0.1694    0.0000   -0.1694   -0.1694    0.0000;...
                    -0.0978    0.0978    0.1956    0.0978   -0.0978   -0.1956;...
                     0.0830   -0.0830    0.0830   -0.0830    0.0830   -0.0830];

    invallo = inv(allo);

    kT = 8.0082e-06;

    HexaConstants = struct('Mass', mb,...
                        'Inertia', J ,...
                        'allo', allo, ...
                        'invallo', invallo,...
                        'kT', kT);

end

function Controller = InitController()

%Control SIN diferenciador
% Kp_xy = ones(1,2)*10;
% Kp_z = 25;
% Kp_angle = [15 15 30];
% Kp_man = [800 800];
% 
% Kd_xy = ones(1,2)*10;
% Kd_z = 25;
% Kd_angle = [15 15 15];
% Kd_man = [300 300];

% Control CON diferenciador
% Intento para diferenciador con periodo  100Hz
% Kp_xy = ones(1,2)*0.5;
% Kp_z = 1;
% Kp_angle = [2 2 2];
% Kp_man = [50 100];
% 
% Kd_xy = ones(1,2)*0.5;
% Kd_z = 1;
% Kd_angle = [2 2 2];
% Kd_man = [50 100];
%ES ESTE PELUTOUDO DE MIERDA ESTE ES EL BUENO
% % % Kp_xy = ones(1,2)*0.5;
% % % Kp_z = 250;
% % % Kp_angle = [2 2 2];
% % % Kp_man = [20 20];
% % % 
% % % Kd_xy = ones(1,2)*0.5;
% % % Kd_z = 250;
% % % Kd_angle = [2 2 2];
% % % Kd_man = [20 20];
%%%el de arriba GIL

%Da bien, para discreto con OBS
Kp_xy = ones(1,2)*2;
Kp_z = 3;
Kp_angle = [2 2 2];
Kp_man = [10 10];

Kd_xy = Kp_xy;
Kd_z = Kp_z;
Kd_angle = Kp_angle;
Kd_man = Kp_man;
 
Kp = [Kp_xy Kp_z Kp_angle Kp_man];
Kd = [Kd_xy Kd_z Kd_angle Kd_man];

Controller = struct('Kp', Kp ,...
    'Kd'     , Kd      );
end


function Differentiator = InitDifferentiator()

%Observador para 200Hzc

% G1 = [05; 05; 10; 10; 10; 10; 20; 20];
% G2 = [10; 10; 20; 40; 40; 40; 300; 300];
% Q1 = [16; 16; 16; 16; 16; 16; 16; 16];
% Q2 = [16; 16; 16; 40; 40; 40; 300; 300];
% w1 = [0.6; 0.6; 0.6; 0.6; 0.6; 0.6; 0.6; 0.6];
% w2 = w1*2-1;
% p1 = [1.2; 1.2; 1.2; 1.2; 1.2; 1.2; 1.2; 1.2];
% p2 = p1*2-1;

%Sistema Funcional Quieto 100Hz

% G1 = [05; 05; 10; 15; 15; 15; 20; 20];
% G2 = [10; 10; 20; 40; 40; 40; 150; 200];
% Q1 = [16; 16; 16; 16; 16; 16; 16; 16];
% Q2 = [16; 16; 16; 40; 40; 40; 150; 200];
% w1 = [0.6; 0.6; 0.6; 0.6; 0.6; 0.6; 0.55; 0.55];
% w2 = w1*2-1;
% %p1 = [1.2; 1.2; 1.2; 1.2; 1.2; 1.2; 1.1; 1.1];
% p1 = [1.2; 1.2; 1.2; 1.2; 1.2; 1.2; 1.05; 1.05];
% p2 = p1*2-1;

%NUEVO INTENTO
%POR FIN DIO CON 100 Hz, ESTA LOCURA NO LA PODES ENTENDER
% G1 = [05; 05; 10; 5; 5; 5; 20; 20];
% G2 = [10; 10; 20; 10; 10; 10; 150; 200];
% Q1 = [16; 16; 16; 16; 16; 16; 16; 16];
% Q2 = [16; 16; 16; 40; 40; 40; 150; 200];
%100Hz DISCRETOS MIERDA
% % % G1 = [05; 05; 10; 5; 5; 5; 15; 15];
% % % G2 = [10; 10; 20; 10; 10; 10; 15; 15];
% % % % G2 = [10; 10; 20; 10; 10; 10; 15; 90]; %Este estamejor, da con ganancia 2
% % % % G2 = [10; 10; 20; 10; 10; 10; 30; 50];
% % % Q1 = [16; 16; 16; 16; 16; 16; 16; 16];
% % %  Q2 = [16; 16; 16; 40; 40; 40; 16; 16];
% % % % Q2 = [16; 16; 16; 40; 40; 40; 60; 90]; %Este estamejor, da con ganancia 2
% % % % Q2 = [16; 16; 16; 40; 40; 40; 30; 50];
% % % w1 = [0.6; 0.6; 0.6; 0.6; 0.6; 0.6; 0.55; 0.55];
% % % w2 = w1*2-1;
% % % %p1 = [1.2; 1.2; 1.2; 1.2; 1.2; 1.2; 1.1; 1.1];
% % % p1 = [1.2; 1.2; 1.2; 1.2; 1.2; 1.2; 1.05; 1.05];
% % % p2 = p1*2-1;

G1 = [05; 05; 10; 5; 5; 5; 15; 15];
G2 = [10; 10; 20; 10; 10; 10; 15; 15];
% G2 = [10; 10; 20; 10; 10; 10; 15; 90]; %Este estamejor, da con ganancia 2
% G2 = [10; 10; 20; 10; 10; 10; 30; 50];
Q1 = [16; 16; 16; 16; 16; 16; 16; 16];
Q2 = [16; 16; 16; 40; 40; 40; 16; 16];
% Q2 = [16; 16; 16; 40; 40; 40; 60; 90]; %Este estamejor, da con ganancia 2
% Q2 = [16; 16; 16; 40; 40; 40; 30; 50];
w1 = [0.6; 0.6; 0.6; 0.6; 0.6; 0.6; 0.55; 0.55];
w2 = w1*2-1;
p1 = [1.2; 1.2; 1.2; 1.2; 1.2; 1.2; 1.05; 1.05];
p2 = p1*2-1;

Differentiator = struct('G1', G1 ,...
    'G2', G2 ,...
    'Q1', Q1 ,...
    'Q2', Q2 ,...
    'w1', w1 ,...
    'w2', w2 ,...
    'p1', p1 ,...
    'p2', p2);
end

function Observer = InitObserver()

% E1 = [16; 16; 16; 16; 16; 16; 50; 50];
% E2 = [60; 60; 60; 150; 150; 150; 1000; 1000];
% E3 = [100; 100; 100; 450; 450; 450; 5000; 5000];
% E4 = [0.01; 0.01; 0.01; 0.01; 0.01; 0.01; 0.01; 0.01];
% MU1 = [16; 16; 16; 16; 16; 16; 50; 50];
% MU2 = [60; 60; 60; 150; 150; 150; 1000; 1000];
% MU3 = [100; 100; 100; 450; 450; 450; 5000; 5000];
% alpha = [0.6; 0.6; 0.6; 0.6; 0.6; 0.6; 0.6; 0.6];
% beta = [1.2; 1.2; 1.2; 1.2; 1.2; 1.2; 1.2; 1.2];

E1 = [16; 16; 16; 16; 16; 16; 50; 50];
E2 = [60; 60; 60; 150; 150; 150; 500; 500];
E3 = [100; 100; 100; 450; 450; 450; 2000; 2000];
E4 = [0.01; 0.01; 0.01; 0.01; 0.01; 0.01; 0.01; 0.01];
MU1 = E1;
MU2 = E2;
MU3 = E3;
alpha = [0.6; 0.6; 0.6; 0.6; 0.6; 0.6; 0.6; 0.6];
beta = [1.2; 1.2; 1.2; 1.2; 1.2; 1.2; 1.2; 1.2];

% E1 = [16; 16; 16; 16; 16; 16; 50; 50];
% E2 = [30; 30; 30; 100; 100; 100; 500; 500];
% E3 = [50; 50; 50; 300; 300; 300; 2000; 2000];
% E4 = [0.01; 0.01; 0.01; 0.01; 0.01; 0.01; 0.01; 0.01];
% MU1 = E1;
% MU2 = E2;
% MU3 = E3;
% alpha = [0.6; 0.6; 0.6; 0.6; 0.6; 0.6; 0.6; 0.6];
% beta = [1.2; 1.2; 1.2; 1.2; 1.2; 1.2; 1.2; 1.2];


Observer = struct('E1', E1 ,...
    'E2', E2 ,...
    'E3', E3 ,...
    'E4', E4 ,...
    'MU1', MU1 ,...
    'MU2', MU2 ,...
    'MU3', MU3 ,...
    'alpha', alpha ,...
    'beta', beta);
end