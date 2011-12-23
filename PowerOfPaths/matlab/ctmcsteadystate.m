function [ pi ] = ctmcsteadystate( Q )
%CTMCSTEADYSTATE Steady state distribution of a continious time markov chain
%Source: http://speed.cis.nctu.edu.tw/~ydlin/course/cn/nsd2009/Markov-chain.pdf (slide 10)
%	T=Q;
%	len=length(Q);
%	T(:,len)=ones(len, 1);
%	e=zeros(1, len);
%	e(len)=1;
%	pi=e*inv(T);

%better version, works w/o inverse so faster for sparse matrices
	len=length(Q);
	T=[Q ones(len, 1); zeros(1, len+1)];
	z=zeros(1, len+1);
	z(len+1)=1;
	pi=mrdivide(z,T);
	%pi=cs_cholsol(T',z')';
end

