function servo(a,b,c)
s = serial('/dev/tty.usbmodem1421');
fwrite(s,a)
fwrite(s,b)
fwrite(s,c)
end