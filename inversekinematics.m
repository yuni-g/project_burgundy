function th =  inversekinematics(x, y, z)
  wb = 50; % distance between the center to the servo on the base
  wp = 20; % distance between the center to the servo on the EE
  L =  100; % Length of the bicep
  l = 185; % Length of the forearm
  
  a = wb-wp; % Variable for easier calculation
  E = [2.*(a+y).*L,(a-sqrt(3).*x-y).*L,(-a+sqrt(3).*x-y).*L];
  F = [2.*z.*L, 2.*z.*L,2.*z.*L];
  G = [ x.*x+y.*y+z.*z+a.*a+L.*L+2.*y.*a-l.*l ...
        x.*x+y.*y+z.*z+a.*a+L.*L-sqrt(3)-l.*l ...
        x.*x+y.*y+z.*z+a.*a+L.*L-sqrt(3).*a.*x-a.*y-l.*l];
  
  real = sqrt(E.*E+F.*F-G.*G);
  if ~isreal(real)
      fprintf('IK failed. (%d, %d, %d) is outside work space.\n',x,y,z);
      return
  end
  
  num1 = -F-real;
  num2 = -F+real;
  den= G-E;
  th1= atan2(num1,den).*2.*360/(2.*pi);
  th2= atan2(num2,den).*2.*360/(2.*pi);

  if (th1 > th2); th = th1;
  else; th = th2; end

end