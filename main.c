#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#define bzero(p, l) memset(p, 0, l)	// Since not on windows
#define bcopy(a, b, c) memcpy(b, a, c)		// Since not on windows


/* Usage: dh base exponent modulus */ 


typedef unsigned char u;
u m[1024],g[1024],e[1024],b[1024];
int n,v,d,z,S=129;

a( u *x,u *y,int o)
{
     d=0;
     for(v=S;v--;)
     {
                  d+=x[v]+y[v]*o;
                  x[v]=d;d=d>>8;
     }
}

s(u *x)
{
    for( v=0;(v<S-1)&&(x[v]==m[v]); ) 
    v++;
    if(x[v]>=m[v])a(x,m,-1);
}

r(u *x)
{
    d=0;
    for(v=0;v< S;)
    {
               d|=x[v];
               x[v++]=d/2;
               d=(d&1)<<8;
    }
}

M(u *x,u *y)
{
    u X[1024],Y[1024];
    bcopy(x,X,S);
    bcopy(y,Y,S);
    bzero(x,S);
    for(z=S*8;z--;)
    {
                   if(X[S-1]&1)
                   {
                               a(x,Y,1);
                               s(x);
                   }
                   
                   r(X);
                   a(Y ,Y,1);
                   s(Y);
    }
}

h(char *x,u *y)
{
       bzero(y,S);
       for(n=0;x[n]>0;n++)
       {
                          for(z=4;z--;)
                          a(y,y ,1);
                          x[n]|=32;y[S-1]|=x[n]-48-(x[n]>96)*39;
       }
}

p(u *x)
{
    for(n=0;!x[n];)n++;
    for(;n< S;n++)
    printf("%c%c",48+x[n]/16+(x[n]>159)*7,48+(x[n]&15)+7*((x[n]&15)>9));
    printf("\n");
}


main(int c,char **v)
{
		char ans[254];
		char ans2[254];
		char ans3[254];

		printf("Enter Public Generator:\n");
		scanf("%s", &ans);
		printf("Enter Secret Random Number:\n");
		scanf("%s", &ans2);
		printf("Enter Public Modulus:\n");
		scanf("%s", &ans3);

		h(ans,g);
		h(ans2,e);
		h(ans3,m);

		//printf("Public Generator = %s\n", ans);
		//printf("Secret Random Number = %s\n", ans2);
		//printf("Public Modulus = %s\n", ans3);
		printf("Calculated Output: ");

         bzero(b,S);
         b[ S-1]=1;
         for(n=S*8;n--;)
         {
                        if(e[S-1]&1)M(b,g);
                        M(g,g);
                        r(e);
         }

p(b);
system("PAUSE");

}
