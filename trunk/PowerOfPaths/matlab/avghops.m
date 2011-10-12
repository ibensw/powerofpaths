function [ ] = avghops(Q)
	steady=ctmcsteadystate(Q);

	len=length(Q);
	states=log2(len);
	avg=0;
	total=0;
	t=[];

	for i=0:(states-1)
		c=0;
		prefix=((2^i)-1) * 2^(states-i);
		for j=0:(2^(states-i-1))-1
			c=c+steady(prefix + j + 1);
			t=[t (prefix + j + 1)];
		end
		total=total+c;
		fprintf('%d hops: %f\n', i, c);
		avg=avg+(c*i);
	end

	fprintf('Loss: %f\nTotal: %f\nAverage #hops: %f\n', steady(len), total + steady(len), avg/(1-steady(len)));
end

