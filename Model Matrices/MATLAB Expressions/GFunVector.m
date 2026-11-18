function Gv = GFunVector(xi)

g = 9.80665;

mb = 1.8188;
ml1 = 0.142;
ml2 = 0.143;

L   = 0.08312;

l1  = 0.17;

c1  = 0.11464;
c2  = 0.09794;

phi = xi(4);
th  = xi(5);

q1   = xi(7);
q2   = xi(8);

Gv=[0,...
    0,...
    g*(mb+ml1+ml2),...
    -g*cos(th)*(-L*(ml1+ml2)*sin(phi)-(c1*ml1+l1*ml2)*sin(phi+q1)-c2*ml2*sin(phi+q1+q2)),...
    g*(L*(ml1+ml2)*cos(phi)+(c1*ml1+l1*ml2)*cos(phi+q1)+c2*ml2*cos(phi+q1+q2))*sin(th),...
    0,...
    -g*cos(th)*(-(c1*ml1+l1*ml2)*sin(phi+q1)-c2*ml2*sin(phi+q1+q2)),...
    c2*g*ml2*cos(th)*sin(phi+q1+q2)]';

end
