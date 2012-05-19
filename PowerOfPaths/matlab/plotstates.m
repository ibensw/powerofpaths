x=0.1:0.1:1.0;
s=10;
y=x;
M=floor([0:s-1]./2)';

j=1;
for i=x
	i
	[a b]=avghops(randswitchchain(s, i),0);
	success=sum(b);
	y(j)=(b*M)/success;
	j=j+1;
end

plot(x,y);
[x' y']
