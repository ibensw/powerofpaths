l=0.10:0.10:1;
s=11;
r=zeros(1, length(l));
rs=r;
ru=r;
rp=r;

j=1;
for i=l
	fprintf('%f\t', i);
	r(j)=avghops(rightchain(s, i), 0);
	rs(j)=avghops(randswitchchain(s, i), 0);
	rp(j)=avghops(rprimechain(s, i), 0);
	ru(j)=ruavghops(runvisitedchain(s, i), 0);
	j=j+1;
end
fprintf('\n');

%plot(l, r./r, l, rs./r);
plot(l, r./r, l, rs./r, l, rp./r, l, ru./r);
