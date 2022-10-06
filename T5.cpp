#include <bits/stdc++.h>
#include <gmp.h>

#define MAX 1<<31
int n;
char tmp[6666]={0};
mpz_t e,p,q,gcd,dis,N,phiN,d,p1,q1;
using namespace std;
void mygcd(mpz_t gcd,mpz_t a,mpz_t b){
    mpz_t rtmp,atmp,btmp;
    mpz_init(rtmp);mpz_init_set(atmp,a);mpz_init_set(btmp,b);
    if(mpz_cmp(atmp,btmp)<0) mpz_swap(atmp,btmp);
    mpz_mod(rtmp,atmp,btmp);
    while(mpz_cmp_ui(rtmp,0)){
        mpz_set(atmp,btmp);mpz_set(btmp,rtmp);mpz_mod(rtmp,atmp,btmp);
    }
    mpz_set(gcd,btmp);
}
int myinvert(mpz_t d,mpz_t e,mpz_t phiN)
{
    mpz_t a1,a2,a3,b1,b2,b3,c1,c2,c3,k,p,tmp;
    mpz_init(a1);mpz_init(a2);mpz_init(a3);
    mpz_init(b1);mpz_init(b2);mpz_init(b3);
    mpz_init(c1);mpz_init(c2);mpz_init(c3);
    mpz_init(k);mpz_init(p); 
    mpz_init_set(tmp,phiN);
    if (mpz_cmp(e,phiN)>0)	mpz_swap(e,phiN);
    mpz_set_ui(a1,1); mpz_set_ui(a2,0); mpz_set(a3,phiN);
    mpz_set_ui(b1,0); mpz_set_ui(b2,1); mpz_set(b3,e);
    while (1){
        if(mpz_cmp_ui(b3,0)==0){
            mpz_set_ui(d,0);	break;
        }
        if(mpz_cmp_ui(b3, 1) == 0){
            mpz_set(d,b2);	break;
        }
        mpz_mod(p,a3,b3);
		mpz_sub(k,a3,p);
        mpz_cdiv_q(k,k,b3);
        mpz_mul(c1,k,b1); mpz_sub(c1,a1,c1);
        mpz_mul(c2,k,b2); mpz_sub(c2,a2,c2);
        mpz_mul(c3,k,b3); mpz_sub(c3,a3,c3);
        mpz_set(a1,b1);mpz_set(a2,b2);mpz_set(a3,b3);
        mpz_set(b1,c1);mpz_set(b2,c2);mpz_set(b3,c3);
    }
    if(mpz_cmp_ui(d,0)<=0)	mpz_add(d,d,tmp);
    return 1;
}

int main()
{
    scanf("%d",&n);
    mpz_init(e);mpz_init(p);mpz_init(q);mpz_init(gcd);
    mpz_init(N);mpz_init(dis);mpz_init(phiN);mpz_init(d);
    mpz_init(p1);mpz_init(q1);
    while(n--)
    {
        scanf("%s",tmp);mpz_set_str(e,tmp,10);
        scanf("%s",tmp);mpz_set_str(p,tmp,10);
        scanf("%s",tmp);mpz_set_str(q,tmp,10);
        if(mpz_cmp_ui(e, 65536)<=0){
            printf("ERROR\n");	continue;
        }
        if(mpz_probab_prime_p(p,20)==0||mpz_probab_prime_p(q,20)==0){
            printf("ERROR\n");	continue;
        }
        if(mpz_cmp(p, q)==0){
            printf("ERROR\n");	continue;
        }
        mpz_mul(N,p,q);
        mpz_sqrt(N,N);
        mpz_sub(dis,p,N);
        mpz_abs(dis,dis);
        if(mpz_cmp_ui(dis,MAX)<=0){
            printf("ERROR\n");	continue;
        }
        mpz_sub(dis,q,N);
        mpz_abs(dis,dis);
        if(mpz_cmp_ui(dis,MAX)<=0){
            printf("ERROR\n");	continue;
        }
        mpz_sub_ui(p1,p,1);
        mpz_sub_ui(q1,q,1);
        mpz_mul(phiN,p1,q1);
        //mpz_gcd(gcd,q1,p1);
        mygcd(gcd,q1,p1);
        if(mpz_cmp_ui(gcd,16)>0){
            printf("ERROR\n");	continue;
        }
        //mpz_invert(d,e,phiN);
		//mpz_gcd(gcd,e,phiN);
      	myinvert(d,e,phiN);
        mygcd(gcd,e,phiN);
        if(mpz_cmp_ui(gcd,1)){
            printf("ERROR\n");	continue;
        }
        gmp_printf("%Zd\n",d);
    }
    mpz_clear(e);mpz_clear(p);mpz_clear(q);mpz_clear(gcd);
    mpz_clear(N);mpz_clear(dis);mpz_clear(phiN);mpz_clear(d);
    mpz_clear(p1);mpz_clear(q1);
}