function D=richard(f,a,h,M)
    D=zeros(M+1,M+1);
    for n=0:M
        dh=h/(2^n);
        D(n+1,1)=(feval(f,a+dh)-feval(f,a-dh))/(2*dh);
    end
    for k=1:M
        for n=k:M
            D(n+1,k+1)=D(n+1,k)+(D(n+1,k)-D(n,k))/(4^k-1);
        end
    end
end
