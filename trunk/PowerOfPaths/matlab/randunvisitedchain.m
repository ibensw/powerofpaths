function [Q] = randunvisitedchain(size, rate)
%RIGHTCHAIN Summary of this function goes here
%   Detailed explanation goes here

    totalsize = 2^size;
    Q = zeros(totalsize);
    
    BITS = zeros(1, size);
    
    for i=1:size
        BITS(i) = 2^(i-1);
    end
    
    for i=0:(totalsize-1)
	t=0;
	bitson=sum(dec2bin(i)-'0');
	bitsoff=size-bitson;
	r=rate + rate*bitson/bitsoff;
        for b=1:size
	    j=bitxor(i, BITS(b));
	    if bitand(i, BITS(b))
		Q(i+1, j+1)=1;
	    else
		Q(i+1, j+1)=r;
	    end
	    t=t + Q(i+1, j+1);
        end
	Q(i+1, i+1) = -t;
    end

end

