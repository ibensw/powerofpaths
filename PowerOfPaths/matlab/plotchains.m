l=0.05:0.05:1;
s=10;
r=zeros(1, length(l));
rs=r;
ru=r;

j=1;
for i=l
	r(j)=avghops(rightchain(s, i), 0);
	rs(j)=avghops(randswitchchain(s, i), 0);
	%ru(j)=avghops(randunvisitedchain(s, i), 0);
	j=j+1;
end

plot(l, r./r, l, rs./r);
