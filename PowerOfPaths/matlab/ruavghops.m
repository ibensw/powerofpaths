function [ avg ] = ruavghops( Q, d )
	if nargin < 2
		d=1;
	end

	steady=ctmcsteadystate(Q);
	
	len=length(Q);
	
	avg = 0;
	avgp = zeros(1, len);
	
	for i=0:len-2
		%fprintf('Calculate when %i of %i are busy (chance = %f)\n', i, len-1, steady(i+1));
		tmpavg = 0;
		for h=0:i
			c = prod(i-h+1:i) * (len-1-i) / prod(len-1-h:len-1);
			tmpavg = tmpavg + (c * h);
			avgp(h+1) = avgp(h+1) + (c*steady(i+1));
			%fprintf(' %i \t %f \t %f\n', h, c, c*steady(i+1));
		end
		%fprintf('Average of %f\n\n', tmpavg);
		avg=avg + steady(i+1) * tmpavg;
	end
	
	avgp(len) = steady(len);
	
	loss=steady(len);
	avg=avg/(1-loss);
	if d
		avgp
		fprintf('Loss:\t%f\nAverage #hops:\t%f\n', loss, avg);
	end
	
end

