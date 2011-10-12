function [ ] = avghops(Q)
	steady=ctmcsteadystate(Q);

	len=length(Q);
	states=log2(len);
	avg=0;
	total=0;

	for i=0:(states-1)
		c=0;
		prefix=((2^i)-1) * 2^(states-i);
		for j=0:(2^(states-i-1))-1
			c=c+steady(prefix + j + 1);
		end
		total=total+c;
		fprintf('%d hops: %f\n', i, c);
		avg=avg+(c*i);
	end

	fprintf('Total: %f\nAverage #hops: %f\n', total, avg);

end

