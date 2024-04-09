function R=romberg(f,a,b,M)
    h=b-a;
    R=zeros(M+1,M+1);
    R(1,1)=h*(feval(f,a)+feval(f,b))/2;
    for n=1:M
        h=h/2;
        R(n+1,1)=1/2*R(n,1)+h*sum(feval(f,a+(2*[1:2^(n-1)]-1)*h));
        for m=1:n
            R(n+1,m+1)=R(n+1,m)+(R(n+1,m)-R(n,m))/(4^m-1);
        end
    end
end