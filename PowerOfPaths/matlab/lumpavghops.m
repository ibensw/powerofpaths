function [ avg ] = lumpavghops(Q)

	fullsize=length(Q);
	[Q S]=lump(Q);
	lumpsize=length(S);
	nodes=log2(fullsize);
	hops=zeros(1,nodes+1);

	steady=ctmcsteadystate(Q);

	hops(1)=steady(1); %zero hops
	hops(nodes+1)=steady(lumpsize); %loss
	for i=2:lumpsize-1;
		bits=ceil(log2(S(i)+1));
		hops(1)=hops(1)+(nodes-bits)/nodes*steady(i);
		
		for j=bits:-1:1
			c=0;
			while c<j && bitand(S(i), 2^(j-c-1))
				c=c+1;
			end
			hops(c+1)=hops(c+1) + steady(i)/nodes;
		end
	end

	fprintf('Sum:\t%f\n',sum(hops));

	avg=(hops(1:nodes)*[0:nodes-1]')/(1-steady(lumpsize));

end

