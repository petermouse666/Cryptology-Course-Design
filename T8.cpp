#pragma GCC optimize("-fdelete-null-pointer-checks,inline-functions-called-once,-funsafe-loop-optimizations,-fexpensive-optimizations,-foptimize-sibling-calls,-ftree-switch-conversion,-finline-small-functions,inline-small-functions,-frerun-cse-after-loop,-fhoist-adjacent-loads,-findirect-inlining,-freorder-functions,no-stack-protector,-fpartial-inlining,-fsched-interblock,-fcse-follow-jumps,-fcse-skip-blocks,-falign-functions,-fstrict-overflow,-fstrict-aliasing,-fschedule-insns2,-ftree-tail-merge,inline-functions,-fschedule-insns,-freorder-blocks,-fwhole-program,-funroll-loops,-fthread-jumps,-fcrossjumping,-fcaller-saves,-fdevirtualize,-falign-labels,-falign-loops,-falign-jumps,unroll-loops,-fsched-spec,-ffast-math,Ofast,inline,-fgcse,-fgcse-lm,-fipa-sra,-ftree-pre,-ftree-vrp,-fpeephole2", 3)
#pragma GCC target("avx","sse2")
#include <bits/stdc++.h>
#include <algorithm>
#include <math.h>
#include <openssl/pkcs7.h>
#include <openssl/pem.h>
#include <openssl/x509.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#define re register
#define uc unsigned char
#define error() {printf("ERROR\n"); return 0;}
using namespace std;
char tmp[66666]={0},ans[66666]={0};
const char CA_root[]={R"(-----BEGIN CERTIFICATE-----
MIIB/zCCAaagAwIBAgIJAKKa0PAt9M1FMAoGCCqBHM9VAYN1MFsxCzAJBgNVBAYT
AkNOMQ4wDAYDVQQIDAVIdUJlaTEOMAwGA1UEBwwFV3VIYW4xDTALBgNVBAoMBEhV
U1QxDDAKBgNVBAsMA0NTRTEPMA0GA1UEAwwGY2Fyb290MB4XDTIwMDkyMDIwNTkx
OVoXDTMwMDkxODIwNTkxOVowWzELMAkGA1UEBhMCQ04xDjAMBgNVBAgMBUh1QmVp
MQ4wDAYDVQQHDAVXdUhhbjENMAsGA1UECgwESFVTVDEMMAoGA1UECwwDQ1NFMQ8w
DQYDVQQDDAZjYXJvb3QwWTATBgcqhkjOPQIBBggqgRzPVQGCLQNCAASJ8mm28JJR
bZKLr6DCo1+KWimpKEsiTfZM19Zi5ao7Au6YLosyN71256MWmjwkwXxJeLa0lCfm
kF/YWCX6qGQ0o1MwUTAdBgNVHQ4EFgQUAL5hW3RUzqvsiTzIc1gUHeK5uzQwHwYD
VR0jBBgwFoAUAL5hW3RUzqvsiTzIc1gUHeK5uzQwDwYDVR0TAQH/BAUwAwEB/zAK
BggqgRzPVQGDdQNHADBEAiAaZMmvE5zzXHx/TBgdUhjtpRH3Jpd6OZ+SOAfMtKxD
LAIgdKq/v2Jkmn37Y9U8FHYDfFqk5I0qlQOAmuvbVUi3yvM=
-----END CERTIFICATE-----)"};
const char PK_B[]={R"(-----BEGIN EC PARAMETERS-----
BggqgRzPVQGCLQ==
-----END EC PARAMETERS-----
-----BEGIN EC PRIVATE KEY-----
MHcCAQEEINQhCKslrI3tKt6cK4Kxkor/LBvM8PSv699Xea7kTXTToAoGCCqBHM9V
AYItoUQDQgAEH7rLLiFASe3SWSsGbxFUtfPY//pXqLvgM6ROyiYhLkPxEulwrTe8
kv5R8/NA7kSSvcsGIQ9EPWhr6HnCULpklw==
-----END EC PRIVATE KEY-----)"};
X509* CA_ChToX509(const char* CA_root){
    BIO *b=BIO_new(BIO_s_mem());
    X509 *ret;
    BIO_puts(b,CA_root);
    ret=PEM_read_bio_X509(b,0,0,0);
    return ret;
}
EVP_PKEY* PK_ChToEvp(const char* PK_B){
    BIO *b=BIO_new_mem_buf(PK_B,strlen(PK_B));
    if(b==0) return 0;
    else return PEM_read_bio_PrivateKey(b,0,0,0);
}
int main(){
    ERR_load_crypto_strings();
	OpenSSL_add_all_algorithms();
    EVP_PKEY *pk_b=PK_ChToEvp(PK_B);
    if(pk_b==0) error();
    X509_STORE *ca_st=X509_STORE_new();
    X509_STORE_add_cert(ca_st,CA_ChToX509(CA_root));
    string s="";
    const char* ctmp;
    while(fgets(tmp,sizeof(tmp),stdin)!=0)  s+=tmp; s+='\n';
    ctmp=s.c_str();
    BIO *bin=0,*bout=0;
    bin=BIO_new_mem_buf(ctmp,strlen(ctmp));
    PKCS7 *p=PKCS7_new();
    p=PEM_read_bio_PKCS7(bin,0,0,0);
    if(p==0)  error();
    bout=PKCS7_dataDecode(p,pk_b,0,0);
    int len=BIO_read(bout,ans,sizeof(ans));
    if(len<0)  error();
    STACK_OF(PKCS7_SIGNER_INFO) *stof=PKCS7_get_signer_info(p);
    if(stof==0)  error();
    PKCS7_SIGNER_INFO *sinfo;
    int num=sk_PKCS7_SIGNER_INFO_num(stof);
    for(re int i=0;i<num;i++){
        sinfo=sk_PKCS7_SIGNER_INFO_value(stof,i);
        X509_STORE_CTX *stctx=X509_STORE_CTX_new();        
        if(PKCS7_dataVerify(ca_st,stctx,bout,p,sinfo)!=1) error();
    }
    for(re int i=0;i<len;++i){
        printf("%c",ans[i]);
    }
    return 0;
}