function [Q] = rightchain(size, rate)
%RIGHTCHAIN Summary of this function goes here
%   Detailed explanation goes here

	[S T] = makestates(size);

    totalsize = 2^size;
    csize = length(S);
    Q = sparse(csize, csize);

    BITS = 2.^[0:size-1];
    
    for i=0:(totalsize-1)
		t=0;
        for b=1:size
		    j=bitxor(i, BITS(b));
		    if bitand(i, BITS(b))
				Q(T(i+1), T(j+1)) = Q(T(i+1), T(j+1))+1;
		    else
%				r=rate;
%				bt=b+1;
%				while bitand(i, BITS(mod(bt-1, size)+1)) & (bt ~= (b))
%				    bt=bt+1;
%				    r = r + rate;
%				end
%				Q(T(i+1), T(j+1))=Q(T(i+1), T(j+1))+r;
	    	end
%			t=t + Q(T(i+1), T(j+1));
        end
%		Q(T(i+1), T(i+1)) = -t;
    end

end

