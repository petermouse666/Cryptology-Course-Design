#pragma GCC optimize("-fdelete-null-pointer-checks,inline-functions-called-once,-funsafe-loop-optimizations,-fexpensive-optimizations,-foptimize-sibling-calls,-ftree-switch-conversion,-finline-small-functions,inline-small-functions,-frerun-cse-after-loop,-fhoist-adjacent-loads,-findirect-inlining,-freorder-functions,no-stack-protector,-fpartial-inlining,-fsched-interblock,-fcse-follow-jumps,-fcse-skip-blocks,-falign-functions,-fstrict-overflow,-fstrict-aliasing,-fschedule-insns2,-ftree-tail-merge,inline-functions,-fschedule-insns,-freorder-blocks,-fwhole-program,-funroll-loops,-fthread-jumps,-fcrossjumping,-fcaller-saves,-fdevirtualize,-falign-labels,-falign-loops,-falign-jumps,unroll-loops,-fsched-spec,-ffast-math,Ofast,inline,-fgcse,-fgcse-lm,-fipa-sra,-ftree-pre,-ftree-vrp,-fpeephole2", 3)
#pragma GCC target("avx","sse2")
#include <bits/stdc++.h>
#include <map>
#include <string>
#include <string.h>
#define inl inline
#define re register
#define ui unsigned int
#define ll long long
#define uc unsigned char
#define SHA1_ROTL(a,b) (SHA1_tmp=(a),((SHA1_tmp>>(32-b))&(0x7fffffff>>(31-b)))|(SHA1_tmp<<b))
#define SHA1_F(B,C,D,t) ((t<40)?((t<20)?((B&C)|((~B)&D)):(B^C^D)):((t<60)?((B&C)|(B&D)|(C&D)):(B^C^D)))
using namespace std;
ui SHA1_tmp;
int m; 
string s1,s2;
map<string,string> rbt;
unsigned tmpsha[5],sha[5],shatmp[5];
char t1[6666]={0},t2[6666]={0},str[6666]={0};
inl int UnitSHA1(const char* str, int length, unsigned sha1[5]){
	uc *pp, *ppend;
	ui l, i, K[80], W[80], TEMP, A, B, C, D, E, H0, H1, H2, H3, H4;
	H0 = 0x67452301, H1 = 0xEFCDAB89, H2 = 0x98BADCFE, H3 = 0x10325476, H4 = 0xC3D2E1F0;
	for (i = 0; i < 20; K[i++] = 0x5A827999);
	for (i = 20; i < 40; K[i++] = 0x6ED9EBA1);
	for (i = 40; i < 60; K[i++] = 0x8F1BBCDC);
	for (i = 60; i < 80; K[i++] = 0xCA62C1D6);
	l = length + ((length % 64 > 56) ? (128 - length % 64) : (64 - length % 64));
	if (!(pp = (unsigned char*)malloc((unsigned int)l))) return -1;
	for (i = 0; i < length; pp[i + 3 - 2 * (i % 4)] = str[i], i++);
	for (pp[i + 3 - 2 * (i % 4)] = 128,i++; i < l; pp[i + 3 - 2 * (i % 4)] = 0,i++);
	*((unsigned int*)(pp + l - 4)) = length << 3;
	*((unsigned int*)(pp + l - 8)) = length >> 29;
	for (ppend = pp + l; pp < ppend; pp += 64){
		for (i = 0; i < 16; W[i] = ((unsigned int*)pp)[i], i++);
		for (i = 16; i < 80; W[i] = SHA1_ROTL((W[i - 3] ^ W[i - 8] ^ W[i - 14] ^ W[i - 16]), 1), i++);
		A = H0, B = H1, C = H2, D = H3, E = H4;
		for (i = 0; i < 80; i++){
			TEMP = SHA1_ROTL(A, 5) + SHA1_F(B, C, D, i) + E + W[i] + K[i];
			E = D, D = C, C = SHA1_ROTL(B, 30), B = A, A = TEMP;
		}
		H0 += A, H1 += B, H2 += C, H3 += D, H4 += E;
	}
	free(pp - l);
	sha1[0]=H0, sha1[1]=H1, sha1[2]=H2, sha1[3]=H3, sha1[4]=H4;
	return 0;
}
inl void getstr(unsigned n,char str[8])  
{
	str[0]='a';str[1]='0';str[2]='0';str[3]='0';str[4]='0';str[5]='0';str[6]='0';str[7]='0';
	int i=2;
	unsigned tmp; 
	while(n)
	{
		tmp=n%36;
		if(tmp<10) str[i++]=tmp+'0';
		else str[i++]=tmp-10+'a';
		n=n/36;
	}
}
inl void R(unsigned sha1[5],char str[8],int i)   
{
	getstr((sha1[0]+sha1[1]*i)%2176782336,str);
}

inl bool checkfromstart(string end,string head){
	char ch[6666]={0};
	for(re int i=0;i<head.length();i++) ch[i]=head[i];
	ch[head.length()]=0;
	for(re int r=1;r<=100;++r){
		for(re int i=1;i<=100;++i){
			UnitSHA1(ch,strlen(ch),tmpsha);
			for(re int j=0;j<=5;++j){
				if(sha[j]!=tmpsha[j]) break;              
				if(j==5){
					printf("%s",ch);
					return true;
				}
			}
			R(tmpsha,ch,i);
		}
	}
	return false;
}

int main(){
	scanf("%d",&m);
	for(re int i=0;i<m;++i){
		scanf("%s%s",t1,t2);
		s1=t1;s2=t2;
		rbt[s2]=s1;
	}
    scanf("%8x%8x%8x%8x%8x",&(sha[0]),&(sha[1]),&(sha[2]),&(sha[3]),&(sha[4]));
	for(re int startp=1;startp<=100;++startp){ //从Ri开始处理
		for(re int i=0;i<5;++i) shatmp[i]=sha[i];
		for(re int i=startp;i<100;++i){
			R(shatmp,str,i);
			UnitSHA1(str,strlen(str),shatmp);
		}
		R(shatmp,str,100); //处理到最后结果，存储在str中
        //100轮到终点
        bool flag=false;
		for(re int r=1;r<=100;++r){
			s1=str;
			if(rbt.find(s1)!=rbt.end()){
                flag=checkfromstart(s1,rbt[s1]);
			}
            if(flag) goto END;
            else{
                for(re int i=1;i<=100;++i){ //不行就在链上继续
				    UnitSHA1(str,strlen(str),shatmp);
				    R(shatmp,str,i);
			    }
            }
			
		}
	}
	printf("None");
    END:;
	return 0;
}