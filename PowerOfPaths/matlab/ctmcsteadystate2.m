function [ pi ] = ctmcsteadystate2( Q )
%better version, works w/o inverse so faster for sparse matrices
	len=length(Q);
	T=[Q ones(len, 1); zeros(1, len+1)];
	z=zeros(1, len+1);
	z(len+1)=1;
	pi=mrdivide(z,T);
	pi=cs_cholsol(T',z')';
end

