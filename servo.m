function servo(s,xyz)
th = inversekinematics(xyz)

%{
if (th<90) ~= 0
    error('shit happened')
end
%}
OCR = round(th/90*200)
fwrite(s,OCR(1))
fwrite(s,OCR(2))
fwrite(s,OCR(3))
end