//优化成功版
#pragma GCC target("avx")
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#include <bits/stdc++.h>
#define re register
typedef unsigned short us;
using namespace std;
const int __buffsize = 100000;
char __buff[__buffsize];
char *__buffs, *__buffe;
#define getc() (__buffs == __buffe ? fread(__buff, 1, __buffsize, stdin), __buffe = __buff + __buffsize, *((__buffs = __buff)++): *(__buffs++))
int S_Box_E[] = {0xE,0x4,0xD,0x1,0x2,0xF,0xB,0x8,0x3,0xA,0x6,0xC,0x5,0x9,0x0,0x7};
int S_Box_D[] = {0xE,0x3,0x4,0x8,0x1,0xC,0xA,0xF,0x7,0xD,0x9,0x6,0xB,0x2,0x0,0x5};
int P_Box[] = {0,4,8,12,1,5,9,13,2,6,10,14,3,7,11,15};
us v_c[16]={0}; 
char number[]={'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
int num,key=0,tmp=0,x=0,y=0,k=0,t=0;
int read(){
    //十六进制快读
    re int a=0;re char c;
    c=getc();
    while(c<'0'){c=getc();}
    while(c>='0'){
        if(c<='9') a=(a<<4)+(c-48);
        else a=(a<<4)+c-87;
        c=getc();
    }
    return a;
}
void print(us a){
    //十六进制快写
    int tmp;
    for(re int i=1;i<=4;i++){
        tmp=(a>>((4-i)<<2))&0xf;
        putchar(number[tmp]);
    }
}
int main(){
    scanf("%d",&num); 
    while(num--){
        key=tmp=read();x=read();

        //加密
        for(re int r=1;r<=3;r++){
            //获得本轮密钥
            k=(tmp&0xffff0000)>>16;
            x^=k;
            tmp<<=4;
            //S盒操作
            for(re int i=0;i<4;i++){
                t=x&0xf000;
                t>>=12;
                x=(x<<4)|S_Box_E[t];
            }
            //P盒操作
            for(re int i=0;i<16;i++){
                v_c[i]=((x<<(P_Box[i]))&0x8000)>>(i);
            }
            x=0;
            for(re int i=0;i<16;i++){
                x|=v_c[i];
            }
        }
        //最后一轮
        k=(tmp&0xffff0000)>>16;
        x^=k;
        tmp<<=4;
        //S盒操作
        for(re int i=1;i<=4;i++){
            t=x&0xf000;
            t>>=12;
            x=(x<<4)|S_Box_E[t];
        }
        k=(tmp&0xffff0000)>>16;
        y=x^k;
        print(y);
        putchar(' ');

        //解密
        x=y^0x1;
        k=key;
        //解密最后一轮
        tmp=k&0xffff;
        x^=tmp;
        k>>=4;
        for(re int i=0;i<4;i++){
            t=x&0xf000;
            t>>=12;
            x=(x<<4)|S_Box_D[t];
        }
        //解密前面所有轮
        for(re int r=1;r<=3;r++){
            tmp=k&0xffff;
            x^=tmp;
            k>>=4;
            //P盒^(-1)
            for(re int i=0;i<16;i++){
                v_c[i]=((x<<(P_Box[i]))&0x8000)>>(i);
            }
            x=0;
            for(re int i=0;i<16;i++){
                x|=v_c[i];
            }
            //S盒^(-1)
            for(re int i=0;i<4;i++){
                t=x&0xf000;
                t>>=12;
                x=(x<<4)|S_Box_D[t];
            }
        }
        tmp=k&0xffff;
        x^=tmp;
        k>>=4;
        print(x);
        putchar('\n');
    }
    return 0;
}