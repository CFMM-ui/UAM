
clear, clc, close all

folder = 'Data Inspection\m=0.25';

load(strcat(folder, '\Results.mat'))

TimeTable = extractTimetable(logsout);

TimeTable = renamevars(TimeTable, 'K(t)', 'Kt');

t  = seconds(TimeTable.Time);
xlab = 'Time(s)';

xti = 0:50:tf;
% xti = 0:20:60;
qlims = [-50 90];
xlines = PickObj.Time;

ftsize = 22;

%% Plot Ref vs ASMC

try
    open(strcat(folder,'\fig files\Tracking.fig'))
catch
x     = TimeTable.Positions(:,1);
y     = TimeTable.Positions(:,2);
z     = TimeTable.Positions(:,3);
phi   = TimeTable.Positions(:,4);
theta = TimeTable.Positions(:,5);
psi   = TimeTable.Positions(:,6);
q1    = TimeTable.Positions(:,7);
q2    = TimeTable.Positions(:,8);
xobj     = TimeTable.qd(:,1);
yobj     = TimeTable.qd(:,2);
zobj     = TimeTable.qd(:,3);
phiobj   = TimeTable.qd(:,4);
thetaobj = TimeTable.qd(:,5);
psiobj   = TimeTable.qd(:,6);
q1obj    = TimeTable.qd(:,7);
q2obj    = TimeTable.qd(:,8);

rffobj = EndEffector([xobj,yobj,zobj,phiobj,thetaobj,psiobj,q1obj,q2obj],...
                      ArmConstants);
rff = EndEffector([x,y,z,phi,theta,psi,q1,q2], ArmConstants);

f = figure(); grid on
hold on
plot3(xobj, yobj, zobj, '--r', LineWidth=2)
plot3(x, y, z, '-b', LineWidth=2)
plot3(rffobj(:,1), rffobj(:,2), rffobj(:,3), '--m', LineWidth=1.5)
plot3(rff(:,1), rff(:,2), rff(:,3), '-k', LineWidth=1.5)
f.CurrentAxes.FontSize = 18;
xlim([-2 3]), xticks(-2:2:2)
ylim([-3 2]), yticks(-2:2:2)
zlim([0 1.1]), zticks(0:0.5:1)
xlabel('$x$(m)')
ylabel('$y$(m)')
zlabel('$z$(m)')

dx = diff(x);
dy = diff(y);
dz = diff(z);
paso = 250;

quiver3(x(1:paso:end-1),y(1:paso:end-1),z(1:paso:end-1), dx(1:paso:end),...
        dy(1:paso:end), dz(1:paso:end), LineWidth=2, Color='b',...
        AutoScaleFactor=1.5)

legend({'UAV Ref', 'UAV ASMC', 'End Effector Ref', 'End Effector ASMC',...
        ''},...
        Box='off')

end

%% Plot Errors

try
    open(strcat(folder,'\fig files\Error.fig'))
    open(strcat(folder,'\fig files\ErrorPos.fig'))
    open(strcat(folder,'\fig files\ErrorAngle.fig'))
    open(strcat(folder,'\fig files\ErrorJoints.fig'))
catch
Error = TimeTable.error_q;

ex = Error(:,1);
ey = Error(:,2);
ez = Error(:,3);
ephi = rad2deg(Error(:,4));
ethe = rad2deg(Error(:,5));
epsi = rad2deg(Error(:,6));
eq1 = rad2deg(Error(:,7));
eq2 = rad2deg(Error(:,8));

f = figure();
hold on
f.CurrentAxes.FontSize = 18;
plot(t, ex, '-r', LineWidth=1.5)
plot(t, ey, '--b', LineWidth=1.5)
plot(t, ez, '-.k', LineWidth=1.5)
xlabel(xlab)
ylabel('Position Error(m)')
xlim([xti(1), xti(end)])
xticks(xti)
legend({'$e_x$', '$e_y$', '$e_z$'},...
        Box='off', Location='southeast', FontSize=19)
ylim([-0.05 0.025])
yticks(-0.05:0.025:0.05)

f = figure();
hold on
f.CurrentAxes.FontSize = 18;
plot(t, ephi, '-r', LineWidth=1.5)
plot(t, ethe, '--b', LineWidth=1.5)
plot(t, epsi, '-.k', LineWidth=1.5)
xlabel(xlab)
ylabel('Angular Error(deg)')
xlim([xti(1), xti(end)])
xticks(xti)
legend({'$e_\phi$', '$e_\theta$', '$e_\psi$'},...
       Box='off', FontSize=19)
ylim([-2 5])
yticks(-2:2:6)

f = figure();
hold on
f.CurrentAxes.FontSize = 18;
plot(t, eq1, '-r', LineWidth=1.5)
plot(t, eq2, '-.k', LineWidth=1.5)
xlabel(xlab)
ylabel('Joints Error(deg)')
xlim([xti(1), xti(end)])
xticks(xti)
legend({'$e_{q1}$', '$e_{q2}$'},...
        Box='off', Location='southeast', FontSize=19)
ylim([-50 50])
yticks(-50:25:50)

end

%% Plot Gains

try
    open(strcat(folder,'\fig files\KUAV.fig'))
    open(strcat(folder,'\fig files\KJoints.fig'))
catch
Kt = TimeTable.Kt;

f = figure(); hold on
xticks(xti)
xlim([xti(1),xti(end)])
plot(t, Kt(:,1), ':r', LineWidth=2)
plot(t, Kt(:,2), '--b', LineWidth=2)
plot(t, Kt(:,3), '-', Color="#00640E", LineWidth=2)
idx = 1:200:length(t);
plot(t(idx), Kt(idx,3), '*', Color="#00640E", MarkerSize=3)
plot(t, Kt(:,4),'-.m', LineWidth=1.5)
plot(t, Kt(:,5), '-k', LineWidth=1.5)
plot(t, Kt(:,6), '-', Color="#8F00E1", LineWidth=2)
idx = 1:200:length(t);
plot(t(1:200:end), Kt(1:200:end,6), 'o', Color="#8F00E1", MarkerSize=3)
legend({'$K_x$', '$K_y$', '', '$K_z$',...
        '$K_\phi$', '$K_\theta$', '', '$K_\psi$'},...
         Box='off', FontSize=19)
f.CurrentAxes.FontSize=ftsize;
xlabel(xlab)
ylabel('UAV Adaptive Gains')
ylim([0 4])

f = figure(); hold on
xticks(xti)
xlim([xti(1),xti(end)])
plot(t, Kt(:,7), '-r', LineWidth=1.5)
plot(t, Kt(:,8), '-.k', LineWidth=1.5)
legend({'$K_{q1}$', '$K_{q2}$'}, Box='off', FontSize=19)
f.CurrentAxes.FontSize=ftsize;
xlabel(xlab)
ylabel('Joints Adaptive Gains')
ylim([0 200])
end

%% Plot mu

try
    open(strcat(folder,'\fig files\mUAV.fig'))
    open(strcat(folder,'\fig files\muJoints.fig'))
catch
mu = TimeTable.mu;

f = figure(); hold on
xticks(xti)
xlim([xti(1),xti(end)])
plot(t, mu(:,1), ':r', LineWidth=2)
plot(t, mu(:,2), '--b', LineWidth=2)
plot(t, mu(:,3), '-', Color="#00640E", LineWidth=2)
idx = 1:200:length(t);
plot(t(idx), mu(idx,3), '*', Color="#00640E", MarkerSize=3)
plot(t, mu(:,4),'-.m', LineWidth=1.5)
plot(t, mu(:,5), '-k', LineWidth=1.5)
plot(t, mu(:,6), '-', Color="#8F00E1", LineWidth=2)
idx = 1:200:length(t);
plot(t(1:200:end), mu(1:200:end,6), 'o', Color="#8F00E1", MarkerSize=3)
legend({'$\mu_x$', '$\mu_y$', '','$\mu_z$',...
        '$\mu_\phi$', '$\mu_\theta$', '','$\mu_\psi$'}, Box='off', FontSize=19)
f.CurrentAxes.FontSize=ftsize;
xlabel(xlab)
ylabel('UAV $\mu$')
ylim([0 0.15])

f = figure(); hold on
xticks(xti)
xlim([xti(1),xti(end)])
plot(t, mu(:,7), '-r', LineWidth=1.5)
plot(t, mu(:,8), '-.k', LineWidth=1.5)
legend({'$\mu_{q1}$', '$\mu_{q2}$'},Box='off', FontSize=19)
f.CurrentAxes.FontSize=ftsize;
xlabel(xlab)
ylabel('Joints $\mu$')
ylim([0 6])
yticks(0:2:6)
end
%% Plot FM and Tq

u = TimeTable.u;

try
    open(strcat(folder,'\fig files\Forces.fig'))
    open(strcat(folder,'\fig files\Torques.fig'))
    open(strcat(folder,'\fig files\JointTorques.fig'))
catch 
f = figure(); 
subplot(2,1,1), hold on
xticks(xti)
xlim([xti(1),xti(end)])
plot(t, u(:,1), '-r', LineWidth=1.5)
plot(t, u(:,2), '-.b', LineWidth=1.5)
legend({'$u_x(t)$', '$u_y(t)$'},Box='off', FontSize=19)
f.CurrentAxes.FontSize=ftsize;
ylim([-4 2])
yticks(-4:2:2)

subplot(2,1,2), hold on
xticks(xti)
xlim([xti(1),xti(end)])
plot(t, u(:,3), '-k', LineWidth=1.5)
legend({'$u_z(t)$'},Box='off', FontSize=19)
xlabel(xlab)
f.CurrentAxes.FontSize=ftsize;
ylim([20 28])
yticks(20:4:28)
ylabel('Generalized Forces(N)')

f = figure(); 
subplot(2,1,1), hold on
xticks(xti)
xlim([xti(1),xti(end)])
plot(t, u(:,4), '-r', LineWidth=1.5)
legend({'$u_\phi(t)$'},Box='off', FontSize=19)
f.CurrentAxes.FontSize=ftsize;
ylim([0 2.5])
yticks(0:1.25:2.5)

subplot(2,1,2), hold on
xticks(xti)
xlim([xti(1),xti(end)])
plot(t, u(:,5), '-b', LineWidth=1.5)
plot(t, u(:,6), '-.k', LineWidth=1.5)
legend({'$u_\theta(t)$', '$u_\psi(t)$'},Box='off', FontSize=19)
xlabel(xlab)
f.CurrentAxes.FontSize=ftsize;
ylim([-0.04 0.04])
yticks(-0.04:0.04:0.04)
ylabel('Generalized Torques(Nm)')

f = figure(); hold on
xticks(xti)
xlim([xti(1),xti(end)])
plot(t, u(:,7), '-r', LineWidth=1.5)
plot(t, u(:,8), '-.k', LineWidth=1.5)
xlabel(xlab)
legend({'$\tau_{q1}(t)$', '$\tau_{q2}(t)$'},Box='off', FontSize=19)
f.CurrentAxes.FontSize=ftsize;
ylabel('Joint Torques (Nm)') 
ylim([0 3])
yticks(0:1:3)
end
%% Thrust

w2 = TimeTable.w2;
w = sqrt(w2);
T = TimeTable.Fthrust;

figure()
subplot(1,2,1)
plot(t, T)
subplot(1,2,2)
plot(t,w)
