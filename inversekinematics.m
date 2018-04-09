function th =  inversekinematics(xyz)
    x = xyz(:,1);
    y = xyz(:,2);
    z = xyz(:,3);
  wb = 55; % distance between the center to the servo on the base
  wp = 15; % distance between the center to the servo on the EE
  L =  100; % Length of the bicep
  l = 150; % Length of the forearm
  
  a = wb-wp; % Variable for easier calculation

  E = [2.*(a+y).*L, (2*a-sqrt(3).*x-y).*L,    (2*a+sqrt(3).*x-y).*L];
  F = [2.*z.*L,      2.*z.*L,               2.*z.*L];
  G = [ x.*x+y.*y+z.*z+a.*a+L.*L+2.*y.*a-l.*l ...
        x.*x+y.*y+z.*z+a.*a+L.*L-sqrt(3).*a.*x-a.*y-l.*l ...
        x.*x+y.*y+z.*z+a.*a+L.*L+sqrt(3).*a.*x-a.*y-l.*l];
  
  real = sqrt(E.*E+F.*F-G.*G);
  if ~isreal(real)
      fprintf('IK failed. (%d, %d, %d) is outside work space.\n',x',y',z');
      return
  end
  
  num1 = -F-real;
  num2 = -F+real;
  den= G-E;
  th1= atan2(num1,den)*2*180/(pi);
  th2= atan2(num2,den)*2*180/(pi);
  
  th1(th1<0) = th1(th1<0) +360;
  th = th1;