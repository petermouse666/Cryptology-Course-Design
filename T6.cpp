#include <bits/stdc++.h>
#include <gmp.h>
using namespace std;
int n;
char tmp[6666]={0};
mpz_t e,m,p,q,N,ans;
void myexpmod(mpz_t e,mpz_t m,mpz_t N,mpz_t ans){
    mpz_t i,j,ret;
    mpz_init(i);mpz_init(j);mpz_init(ret);
    mpz_set(i,e);mpz_set_ui(ret,1);
    while(mpz_cmp_ui(i,1)){
        mpz_cdiv_r_ui(j,i,2);
        if(!mpz_cmp_ui(j,0)){
            mpz_mul(m,m,m);
            mpz_cdiv_q_ui(i,i,2);
        }
        else{
            mpz_mul(ret,ret,m);
            mpz_sub_ui(i,i,1);
        }
        mpz_mod(m,m,N);
        mpz_mod(ret,ret,N);
    }
    mpz_mul(ans,m,ret);
    mpz_mod(ans,ans,N);
    mpz_clear(i);mpz_clear(j);mpz_clear(ret);
}
int main(){
    scanf("%d",&n);
    mpz_init(e);mpz_init(m);
    mpz_init(p);mpz_init(q);
    mpz_init(N);mpz_init(ans);
    while(n--){
        scanf("%s",tmp);mpz_set_str(e,tmp,10);
        scanf("%s",tmp);mpz_set_str(m,tmp,10);
        scanf("%s",tmp);mpz_set_str(p,tmp,10);
        scanf("%s",tmp);mpz_set_str(q,tmp,10);
        mpz_mul(N,p,q);
        myexpmod(e,m,N,ans);
        gmp_printf("%Zd\n",ans);
    }
    mpz_clear(e);mpz_clear(m);
    mpz_clear(p);mpz_clear(q);
    mpz_clear(N);mpz_clear(ans);
    return 0;
}