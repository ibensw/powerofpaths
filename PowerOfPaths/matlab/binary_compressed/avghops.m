function [ avg ] = avghops(Q, T, d)
	if nargin < 2
		d=1;
	end

	%a full vector so make it full
	steady=full(ctmcsteadystate(Q));

	len=length(T);
	states=log2(len);
	avg=0;
	total=0;

	for i=0:(states-1)
		c=0;
%		prefix=((2^i)-1) * 2^(states-i);
		for j=0:len(Q)
			c=c+steady(j + 1);
		end
		total=total+c;
		if d
			fprintf('%d hops:\t%f\n', i, c);
		end
		avg=avg+(c*i);
	end

	loss=steady(T(len));
	avg=avg/(1-loss);
	if d
		fprintf('Loss:\t%f\nTotal:\t%f\nAverage #hops:\t%f\n', loss, total + loss, avg);
	end
end

