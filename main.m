
delete(instrfindall) ;
s = serial('/dev/tty.usbmodem1421');
fclose(s);
fopen(s);

th = linspace(0,2*pi,100);
x = 50*sin(th);
y = 50*cos(th);
z = -120*ones(1,length(x));
xyz = [x' y' z'];
while(1)
for i = 1:1:length(x)
servo(s, xyz(i,:));
pause(1/100);
end
end
fclose(s);