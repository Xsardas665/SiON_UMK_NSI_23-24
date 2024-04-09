function [c,err,yc,k]=bisect(f,a,b,delta,epsilon,max)
    ya=feval(f,a);
    yb=feval(f,b);
    if sign(ya)==sign(yb)
        c='error';err='error';yc='error';k='error';
        disp('error: sign(f(a))==sign(f(b))')
        return;
    end
    for k=1:max
        c=a+(b-a)/2;%c=(a+b)/2
        yc=feval(f,c);
        err=abs((b-a)/2);
        if (err<delta) || (abs(yc)<epsilon)
            return;
        end
        if sign(yb)==sign(yc)
            b=c;
            yb=yc;
        else
            a=c;
        end
    end
end