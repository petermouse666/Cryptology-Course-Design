#pragma GCC optimize("-fdelete-null-pointer-checks,inline-functions-called-once,-funsafe-loop-optimizations,-fexpensive-optimizations,-foptimize-sibling-calls,-ftree-switch-conversion,-finline-small-functions,inline-small-functions,-frerun-cse-after-loop,-fhoist-adjacent-loads,-findirect-inlining,-freorder-functions,no-stack-protector,-fpartial-inlining,-fsched-interblock,-fcse-follow-jumps,-fcse-skip-blocks,-falign-functions,-fstrict-overflow,-fstrict-aliasing,-fschedule-insns2,-ftree-tail-merge,inline-functions,-fschedule-insns,-freorder-blocks,-fwhole-program,-funroll-loops,-fthread-jumps,-fcrossjumping,-fcaller-saves,-fdevirtualize,-falign-labels,-falign-loops,-falign-jumps,unroll-loops,-fsched-spec,-ffast-math,Ofast,inline,-fgcse,-fgcse-lm,-fipa-sra,-ftree-pre,-ftree-vrp,-fpeephole2", 3)
#pragma GCC target("avx","sse2")
#include <bits/stdc++.h>
#include <gmp.h>
#define re register
#define getc() (__buffs == __buffe ? fread(__buff, 1, __buffsize, stdin), __buffe = __buff + __buffsize, *((__buffs = __buff)++): *(__buffs++))
int n;
const int __buffsize = 100000;
char __buff[__buffsize];
char tmp[1024],etmpc[1024];
char *__buffs, *__buffe;
mpz_t e,p,q,p_1,q_1,N,phiN,d,p1,q1,c,ans1,ans2,ans,dtmp1,dtmp2,ctmp1,ctmp2;
using namespace std;
inline int myinvert(mpz_t d,const mpz_t e,const mpz_t phiN,int mode){
    mpz_t a1,a2,a3,b1,b2,b3,c1,c2,c3,k,p,tmp;
    mpz_t etmp,phiNtmp;
    mpz_init(a1);mpz_init(a2);mpz_init(a3);
    mpz_init(b1);mpz_init(b2);mpz_init(b3);
    mpz_init(c1);mpz_init(c2);mpz_init(c3);
    mpz_init(k);mpz_init(p); 
    mpz_init_set(tmp,phiN);mpz_init_set(etmp,e);mpz_init_set(phiNtmp,phiN);
    if(mode && mpz_cmp(etmp,phiNtmp)>0)	mpz_swap(etmp,phiNtmp);
    mpz_set_ui(a1,1); mpz_set_ui(a2,0); mpz_set(a3,phiNtmp);
    mpz_set_ui(b1,0); mpz_set_ui(b2,1); mpz_set(b3,etmp);
    while (1){
        if(mpz_cmp_ui(b3,0)==0){
            mpz_set_ui(d,0);break;
        }
        if(mpz_cmp_ui(b3,1)==0){
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
    if(mpz_cmp_ui(d,0)<0)	mpz_add(d,d,tmp);
    return 0;
}
inline void myexpmod(mpz_t e,mpz_t m,mpz_t N,mpz_t ans){
    mpz_t tmp,ret;
    mpz_init_set(tmp,m);mpz_init(ret);
    mpz_set_ui(ret,1);
    mpz_get_str(etmpc,2,e);
    for(re int i=0;etmpc[i];++i){
        mpz_mul(ret,ret,ret);
        mpz_mod(ret,ret,N);
        if(etmpc[i]=='1'){
            mpz_mul(ret,ret,tmp);
            mpz_mod(ret,ret,N);
        }
    }
    mpz_set(ans,ret);
}
inline void read(mpz_t c){
    mpz_init(c);
    re char ch=getc(); 
    while(ch<'0')    ch=getc();
    while(ch>='0'){
        mpz_mul_ui(c,c,10);
        mpz_add_ui(c,c,(ch-'0'));
        ch=getc();
    }
}
inline void init(){
    mpz_init(e);mpz_init(p);mpz_init(q);
    mpz_init(N);mpz_init(phiN);mpz_init(d);
    mpz_init(p1);mpz_init(q1);mpz_init(ans1);mpz_init(ans2);
    mpz_init(p_1);mpz_init(q_1);mpz_init(dtmp1);mpz_init(dtmp2);
    mpz_init(ctmp1);mpz_init(ctmp2);
}
inline void clear(){
    mpz_clear(e);mpz_clear(p);mpz_clear(q);
    mpz_clear(N);mpz_clear(phiN);mpz_clear(d);
    mpz_clear(p1);mpz_clear(q1);mpz_clear(ans1);mpz_clear(ans2);
    mpz_clear(p_1);mpz_clear(q_1);mpz_clear(dtmp1);mpz_clear(dtmp2);
    mpz_clear(ctmp1);mpz_clear(ctmp2);
}
int main(){
    init();
    /*scanf("%d",&n);
    scanf("%s",tmp);mpz_set_str(p,tmp,10);
    scanf("%s",tmp);mpz_set_str(q,tmp,10);
    scanf("%s",tmp);mpz_set_str(e,tmp,10);*/
    //gmp_scanf("%d%Zd%Zd%Zd",&n,p,q,e);
    scanf("%d",&n);
  	read(p);read(q);read(e);
  	mpz_mul(N,p,q);
    mpz_sub_ui(p1,p,1);
    mpz_sub_ui(q1,q,1);
    mpz_mul(phiN,p1,q1);
    // mpz_invert(d,e,phiN);  	
    myinvert(d,e,phiN,1);
    // gmp_printf("%Zd\n",d);        //d has been got
    // mpz_invert(p_1,p,q);
    // mpz_invert(q_1,q,p);  
    myinvert(q_1,q,p,0);
    myinvert(p_1,p,q,0);
    while(n--){
        //mpz_powm(c,m,e,n);//c=m^e(mod n)
        //scanf("%s",tmp);mpz_set_str(c,tmp,10);
        read(c);
        //gmp_scanf("%Zd",c);
        mpz_mod(dtmp1,d,p1);
        mpz_mod(dtmp2,d,q1);
        mpz_mod(ctmp1,c,p);
        mpz_mod(ctmp2,c,q);
        // mpz_powm(ans1,ctmp1,dtmp1,p);
        // mpz_powm(ans2,ctmp2,dtmp2,q);
        myexpmod(dtmp1,ctmp1,p,ans1);
        myexpmod(dtmp2,ctmp2,q,ans2);
        mpz_mul(ans1,ans1,q);   mpz_mul(ans1,ans1,q_1);
        mpz_mul(ans2,ans2,p);   mpz_mul(ans2,ans2,p_1);
        mpz_add(ans1,ans1,ans2);
        mpz_mod(ans1,ans1,N);
        gmp_printf("%Zd\n",ans1);
    }
    clear();
    return 0;
}