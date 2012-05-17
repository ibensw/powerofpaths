x=0.1:0.1:1.0;
s=10;
y=zeros(1, length(x));
m=[0; 0; 1; 1; 2; 2; 3; 3; 4; 4];

j=1;
for i=x
	i
	[a,b]=avghops(rightchain(10,i),0);
	y(j)= (b*m);
	j=j+1;
end

[x' y']

