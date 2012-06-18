l=0.05:0.05:1;
s=10;
r=zeros(1, length(l));
rs=r;
ru=r;
rp=r;
lrs=r;

lr=r;

j=1;
for i=l
	fprintf('%f ', i);
	ru(j)=ruavghops(runvisitedchain(s, i), 0);

	lr(j)=lumpavghops(rightchain(s, i));
	lrs(j)=lumpavghops(randswitchchain(s, i));
	lrp(j)=lumpavghops(rprimechain(s, i));
	j=j+1;
end
fprintf('\n');

plot(l, lr./lr, l, lrp./lr, l, ru./lr);
