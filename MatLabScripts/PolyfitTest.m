% make some data

p=randn(1,6);

[x,y]=ndgrid([0:.1:1],[0:.1:1]);

z = [1 1 1 1 1 1 1 1 1 1 1; 1 .5 .5 .5 .5 .5 .5 .5 .5 .5 1; 1 .5 .25 .25 .25 .25 .25 .25 .25 .5 1; 1 .5 .25 .1 .1 .1 .1 .1 .25 .5 1; 1 .5 .25 .1 0 0 0 .1 .25 .5 1;  1 .5 .25 .1 0 -1 0 .1 .25 .5 1; 1 .5 .25 .1 0 0 0 .1 .25 .5 1; 1 .5 .25 .1 .1 .1 .1 .1 .25 .5 1; 1 .5 25 .25 .25 .25 .25 .25 .25 .5 1; 1 .5 .5 .5 .5 .5 .5 .5 .5 .5 1;  1 1 1 1 1 1 1 1 1 1 1]
    

%z=polyval(p(1:3),x)+polyval(p(4:6),y)+.1*randn(size(x));

plot3(x(:),y(:),z(:),'+')


hold on

disp(p)

clear('p')



%fit 

fun='polyval(p(1:3),x)+polyval(p(4:6),y)';

chi=inline(['sum((' fun '-z).^2)'],'p','x','y','z');

h=@(p)chi(p,x(:),y(:),z(:));


options = optimset('display','on','MaxIter',1d4,'TolFun',1d-49,'TolX',1d-49,'maxfuneval',1d4);

p=fminsearch(h,randn(1,6),options);


zf=feval(inline(fun,'p','x','y'),p,x,y);

surf(x,y,zf)

disp(p)

%axis labels
xlabel('X');
ylabel('Y');
zlabel('Z');


%Find Minimum
[Myv, My] = min(zf)
[Mxv, Mx] = min(zf(My(1, :)))
plot3((Mx- 1)/10,(My(1) - 1)/10, zf(Mx, My(1)), 'marker', 'O')
