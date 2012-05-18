x=3:1:14;
s=10;
y=zeros(1, length(x));
y2=y;

j=1;
for i=x
	i
	y(j)=lumpavghops(rprimechain(i, 1.0))/i;
	y2(j)=ruavghops(runvisitedchain(i, 1.0), 0)/i;
	j=j+1;
end

plot(x,y,x,y2);

