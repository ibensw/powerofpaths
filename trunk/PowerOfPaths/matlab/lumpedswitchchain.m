function [Q S] = lumpedswitchchain( nodes, rate, p )
%LUMPEDSWITCHCHAIN Summary of this function goes here
%   Detailed explanation goes here

	function [c] = bitcount(v)
		c=0;
		while v
			c=c+1;
			v=bitand(v, v-1);
		end
	end

	function [s] = leftlap(v, b, mbits)
		if bitand(v, b)
			s=0;
		else
			s=1;
			b=2*b;
			if b == 2^mbits
				b=1;
			end
			while bitand(v, b)
				s=s+1;
				b=2*b;
				if b == 2^mbits
					b=1;
				end
			end
		end
	end

	function [s] = rightlap(v, b, mbits)
		if bitand(v, b)
			s=0;
		else
			s=1;
			b=b/2;
			if b < 1
				b=2^(mbits-1);
			end
			while bitand(v, b)
				s=s+1;
				b=b/2;
				if b < 1
					b=2^(mbits-1);
				end
			end
		end
	end

	[S R C] = makestates(nodes);
	s=length(S);

	Q=sparse(s, s);
	bits=2.^[0:nodes-1];
	bmax=2^nodes;

	for i=1:s
		for j=0:2^nodes-1
			if i > R(j+1)
				if bitcount(bitxor(S(i),j))==1
					Q(i,R(j+1))=Q(i,R(j+1))+1;
				end
			end
		end
	end

	for i=1:s
		for j=bits
			ns=bitor(S(i),j);
			if ns > S(i)
				Q(i,R(ns+1))=Q(i,R(ns+1))+rate*(p*leftlap(S(i),j,nodes) + (1-p)*rightlap(S(i),j,nodes));
			end
		end

		Q(i,i)=-sum(Q(i,:));
	end

end

