x=1:13;
y1=[];
y2=[];
y3=[];
y4=[];
for v=x
	v
	R=randswitchchain(v, 0.5, 0.5);
	[L M]=lump(R);
	y1=[y1 2^v];
	y2=[y2 length(M)];
	y3=[y3 length(find(R))];
	y4=[y4 length(find(L))];
end
plot(x,y1,x,y2)
pause
plot(x,y2./y1)
pause
plot(x, y3, x, y4)
pause
plot(x, y4./y3)
