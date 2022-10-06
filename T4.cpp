#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#include <bits/stdc++.h>
#define re register
#define inl inline
#define ll long long
#define ull unsigned long long
#define ui unsigned int
#define us unsigned short
#define KEYBYTES (16)
#define SPNBYTES (8)
#define INPUTBYTES (1<<24)
#define getc() (pa==pd&&(pd=(pa=buf)+fread(buf,1,100000,stdin),pa==pd)?EOF:*pa++)
using namespace std;
static char buf[100000],*pa=buf,*pd=buf;
ull p_box_position[2][64]={{0,16,32,48,1,17,33,49,2,18,34,50,3,19,35,51,4,20,36,52,5,21,37,53,6,22,38,54,7,23,39,55,8,24,40,56,9,25,41,57,10,26,42,58,11,27,43,59,12,28,44,60,13,29,45,61,14,30,46,62,15,31,47,63},{0,4,8,12,16,20,24,28,32,36,40,44,48,52,56,60,1,5,9,13,17,21,25,29,33,37,41,45,49,53,57,61,2,6,10,14,18,22,26,30,34,38,42,46,50,54,58,62,3,7,11,15,19,23,27,31,35,39,43,47,51,55,59,63}};
ull p_box_array[64];
ull s_box[2][16]={{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},{14,3,4,8,1,12,10,15,7,13,9,6,11,2,0,5}};
inl ull P_Box(ull ptext)
{
	ull m=1;
	for(re int i=0;i<64;i++)
	{
		p_box_array[i]=((ptext&m)==0?0:1);
		m<<=1;
	}
	ptext=0;
	for(re int i=0;i<64;i++)
	{
		ptext^=(p_box_array[p_box_position[0][i]]<<i);
	}
	return ptext;
}

inl ull SPN_enhance(ull k[5],ull ptext)
{
	for(int i=0;i<3;i++)
	{
		ptext^=k[i];
		ptext=s_box[0][ptext&0xf]|((s_box[0][(ptext&0xf0)>>4])<<4)|((s_box[0][(ptext&0xf00)>>8])<<8)|((s_box[0][(ptext&0xf000)>>12])<<12)|((s_box[0][(ptext&0xf0000)>>16])<<16)|((s_box[0][(ptext&0xf00000)>>20])<<20)|((s_box[0][(ptext&0xf000000)>>24])<<24)|((s_box[0][(ptext&0xf0000000)>>28])<<28)|((s_box[0][(ptext&0xf00000000)>>32])<<32)|((s_box[0][(ptext&0xf000000000)>>36])<<36)|((s_box[0][(ptext&0xf0000000000)>>40])<<40)|((s_box[0][(ptext&0xf00000000000)>>44])<<44)|((s_box[0][(ptext&0xf000000000000)>>48])<<48)|((s_box[0][(ptext&0xf0000000000000)>>52])<<52)|((s_box[0][(ptext&0xf00000000000000)>>56])<<56)|((s_box[0][(ptext&0xf000000000000000)>>60])<<60);
		ptext=P_Box(ptext);
	}
	ptext^=k[3];
	ptext=s_box[0][ptext&0xf]|((s_box[0][(ptext&0xf0)>>4])<<4)|((s_box[0][(ptext&0xf00)>>8])<<8)|((s_box[0][(ptext&0xf000)>>12])<<12)|((s_box[0][(ptext&0xf0000)>>16])<<16)|((s_box[0][(ptext&0xf00000)>>20])<<20)|((s_box[0][(ptext&0xf000000)>>24])<<24)|((s_box[0][(ptext&0xf0000000)>>28])<<28)|((s_box[0][(ptext&0xf00000000)>>32])<<32)|((s_box[0][(ptext&0xf000000000)>>36])<<36)|((s_box[0][(ptext&0xf0000000000)>>40])<<40)|((s_box[0][(ptext&0xf00000000000)>>44])<<44)|((s_box[0][(ptext&0xf000000000000)>>48])<<48)|((s_box[0][(ptext&0xf0000000000000)>>52])<<52)|((s_box[0][(ptext&0xf00000000000000)>>56])<<56)|((s_box[0][(ptext&0xf000000000000000)>>60])<<60);
	ptext^=k[4];
	return ptext;
}
inl ll read()
{
	re ll x=0;
	re char ch=getc();
	while(ch<'0'||ch>'9'){ch=getc();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getc();}
	return x;
}
int main()
{
	ull k[5]={0},ptext[1]={0},ctext[1]={0};//只有声明为数组才能使用fread函数
  	ull val=20021113;
	fread(k,SPNBYTES,1,stdin);
	fread(k+4,SPNBYTES,1,stdin);
	fread(ptext,SPNBYTES,1,stdin);
	k[1]=((k[0]<<16)&0xffffffffffff0000)^((k[4]>>48)&0xffff);
	k[2]=((k[0]<<32)&0xffffffff00000000)^((k[4]>>32)&0xffffffff);
	k[3]=((k[0]<<48)&0xffff000000000000)^((k[4]>>16)&0xffffffffffffff);
	ptext[0]^=val;
	ctext[0]=SPN_enhance(k,ptext[0]);
	fwrite(ctext,SPNBYTES,1,stdout);
	for(int i=1;i<(INPUTBYTES/SPNBYTES);i++)
	{
      	//cbc
		fread(ptext,SPNBYTES,1,stdin);
		ptext[0]^=ctext[0];
		ctext[0]=SPN_enhance(k,ptext[0]);
		fwrite(ctext,SPNBYTES,1,stdout);
	}
	return 0;
}