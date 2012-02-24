function [r, refindex, coverage] = makestates(rsize)
	powers = 2.^[0:rsize-1];
	
	function [v] = rotate(a, size)
		p=2^(size-1);
		v = a*2 + floor(a/p) - 2*p*floor(a/p);
	end

	function [r] = makesmallest(a)
		r=a;
		for i=1:(rsize-1)
			a=rotate(a,rsize);
			if a<r
				r=a;
			end
		end
	end
	
	refindex = [];
	for i=0:(2^rsize)-1
		refindex = [refindex makesmallest(i)];
	end
	%refindex = arrayfun(arrayfun(@(x) makesmallest(x), 0:(2^rsize)-1));
	%refindex = arrayfun(makesmallest, 0:(2^rsize)-1);
	
	
	function [c] = cover(a, size)
		c=1;
		a=makesmallest(a);
		b=rotate(a, size);
		while a ~= b
			b=rotate(b, size);
			c=c+1;
		end
	end

	function [r] = smallest(a, size)
		r=a;
		%disp('smallest')
		%size
		for i=1:(size-1)
			a=rotate(a,size);
			%dec2bin(a);
			if a<r
				r=a;
			end
		end
	end
	
	function [v] = f(word, bits, place, size)
		if place > size
			v = word;
		elseif bits == 0
			v = f(word, bits, place+1, size);
		elseif place + bits > size
			v = f(word + powers(place), bits-1, place+1, size);
		else
			v = [f(word + powers(place), bits-1, place+1, size) f(word, bits, place+1, size)];
		end
	end
	

	function [r] = makecombs(k, n)
		leadzeros = ceil(n/k)-1;
		%disp('Leadingzeros: '); disp(leadzeros);
		fullsize = n - leadzeros - 1;
		r = f(0,k-1,1,fullsize)*2 + 1;
	end

	%r = f(0,2,1)
	r=[0 2^(rsize)-1];
	for i=1:rsize-1
		r = [r makecombs(i, rsize)];
	end
	
	s=[];
	for i=r
		s=[s refindex(i+1)];
	end
	
	r=unique(s);
	refindex = arrayfun(@(x) find(r == x), refindex);

	coverage=[];
	for w=r
		coverage=[coverage cover(w, rsize)];
	end

end

