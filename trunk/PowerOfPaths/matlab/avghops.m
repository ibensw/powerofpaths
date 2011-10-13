function [ avg ] = avghops(Q, d)
	if nargin < 2
		d=1;
	end

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
		if d
			fprintf('%d hops:\t%f\n', i, c);
		end
		avg=avg+(c*i);
	end

	loss=steady(len);
	avg=avg/(1-loss);
	if d
		fprintf('Loss:\t%f\nTotal:\t%f\nAverage #hops:\t%f\n', loss, total + loss, avg);
	end
end

