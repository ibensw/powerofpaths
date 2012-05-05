function [ pi ] = ctmcsteadystate( Q )
%CTMCSTEADYSTATE Steady state distribution of a continious time markov chain
%Source: http://speed.cis.nctu.edu.tw/~ydlin/course/cn/nsd2009/Markov-chain.pdf (slide 10)
	T=Q;
	len=length(Q);
	T(:,len)=ones(len, 1);
	e=zeros(1, len);
	e(len)=1;
	pi=e*inv(T);
end

