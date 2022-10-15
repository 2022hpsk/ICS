#include<bits/stdc++.h>
#define M 5005
using namespace std;

int m;//读入总数
char asm_code[M*4][55];//存汇编码的每一部分
int n;//汇编码总行数 
int st[M];//存每行汇编开始位置
int line_all;//机器码总行数
int line[M];//存每行汇编码转机器码的PC-base
map<string,int>label;//存储label对应的机器码PC-base

void Print_reg(char reg[]){//输出寄存器 
	char num[5]="";
	int x=reg[1]-'0';
	for(int j=2;j>=0;j--){
		num[j]=x%2+'0';
		x=x/2;
	}
	num[3]='\0';
	printf("%s",num);
}

void Print_imm(char dec[],int dig){//输出十进制转dig位二进制
	char num[55]="";
	int i=1,x=0,flag=0;
	if(dec[i]=='-'){
		flag=1;
		i++;
	}
	while(dec[i]!='\0'){
		x=x*10+dec[i]-'0';
		i++;
	}
	for(int j=dig-1;j>=0;j--){
		num[j]=x%2+'0';
		x=x/2;
	}
	num[dig]='\0';
	if(flag){
		for(int i=0;i<dig;i++)
			num[i]=1-(num[i]-'0');
		num[dig-1]++;
		for(int i=dig-1;i>0;i--)
			if(num[i]==2){
				num[i]=0;
				num[i-1]++;
			}
		if(num[0]==2)num[0]=0;
		for(int i=0;i<dig;i++)
			num[i]=num[i]+'0';
	}
	printf("%s",num);
}
void Print_off(int x,int dig){//输出十进制转dig位二进制 
	char num[55]="";
	int flag=0;
	if(x<0)flag=1;
	x=abs(x);
	for(int i=dig-1;i>=0;i--){
		num[i]=x%2+'0';
		x=x/2;
	}
	num[dig]='\0';
	if(flag){
		for(int i=0;i<dig;i++)
			num[i]=1-(num[i]-'0');
		num[dig-1]++;
		for(int i=dig-1;i>0;i--)
			if(num[i]==2){
				num[i]=0;
				num[i-1]++;
			}
		if(num[0]==2)num[0]=0;
		for(int i=0;i<dig;i++)
			num[i]=num[i]+'0';
	}
	printf("%s",num);
}

void Print_hex(char hex[],int dig){//输出十六进制转十进制再转dig位二进制 
	int i=1,x=0,flag=0;
	if(hex[i]=='-'){
		flag=1;
		i++;
	}
	while(hex[i]!=0){
		int a=0;
		if(hex[i]>='0'&&hex[i]<='9')a=hex[i]-'0';
		if(hex[i]>='A'&&hex[i]<='F')a=hex[i]-'A'+10;
		if(hex[i]>='a'&&hex[i]<='f')a=hex[i]-'a'+10;
		x=x*16+a;
		i++;
	}
//	printf("%d\n",x);
	if(flag)x=-x;
	Print_off(x,dig);
}

int main(){
//	freopen("1.txt","w",stdout);
	while(scanf("%s",asm_code[++m])){//读入
		if(!strcmp(asm_code[m],".END"))break;
		if(!strcmp(asm_code[m],".STRINGZ")){
			int flag=0;
			char c;
			while(scanf("%c",&c))
				if(c=='"')break;
			int len=0;
			++m;
			asm_code[m][len]='"';
			while(scanf("%c",&c)){
				asm_code[m][++len]=c;
				if(c=='"')break;
			}
			asm_code[m][len+1]='\0';
		}
	}
//	printf("!!!%d\n",m);
	for(int i=1;i<=m;i++)//处理汇编码与机器码的位置
		if((!strcmp(asm_code[i],"ADD"))||
		   (!strcmp(asm_code[i],"AND"))||
		   (!strcmp(asm_code[i],"LDR"))||
		   (!strcmp(asm_code[i],"STR"))){
			++n;
			st[n]=i;
			i+=3;
			++line_all;
			line[n]=line_all;
		}else
		if((!strcmp(asm_code[i],"NOT"))||
		   (!strcmp(asm_code[i],"LD"))||
		   (!strcmp(asm_code[i],"LDI"))||
		   (!strcmp(asm_code[i],"LEA"))||
		   (!strcmp(asm_code[i],"ST"))||
		   (!strcmp(asm_code[i],"STI"))){
			++n;
			st[n]=i;
			i+=2;
			++line_all;
			line[n]=line_all;
		}else
		if((!strcmp(asm_code[i],"TRAP"))||
		   (!strcmp(asm_code[i],"BR"))||
		   (!strcmp(asm_code[i],"BRn"))||
		   (!strcmp(asm_code[i],"BRz"))||
		   (!strcmp(asm_code[i],"BRp"))||
		   (!strcmp(asm_code[i],"BRnz"))||
		   (!strcmp(asm_code[i],"BRzp"))||
		   (!strcmp(asm_code[i],"BRnp"))||
		   (!strcmp(asm_code[i],"BRnzp"))||
		   (!strcmp(asm_code[i],"JMP"))||
		   (!strcmp(asm_code[i],"JSR"))||
		   (!strcmp(asm_code[i],"JSRR"))||
		   (!strcmp(asm_code[i],".ORIG"))||
		   (!strcmp(asm_code[i],".FILL"))){
			++n;	
			st[n]=i;
			i+=1;
			++line_all;
			line[n]=line_all;
		}else
		if(!strcmp(asm_code[i],".BLKW")){
			++n;
			st[n]=i;
			i+=1;
			int sum=0;
			for(int j=1;j<strlen(asm_code[i]);j++)
				sum=sum*10+asm_code[i][j]-'0';
			line_all+=sum;
			line[n]=line_all;
		}else
	   	if(!strcmp(asm_code[i],".STRINGZ")){
			++n;
			st[n]=i;
			i+=1;
			int sum=strlen(asm_code[i])-1;
			line_all+=sum;
			line[n]=line_all;
	   	}else
		if((!strcmp(asm_code[i],"GETC"))||
		   (!strcmp(asm_code[i],"OUT"))||
		   (!strcmp(asm_code[i],"PUTS"))||
		   (!strcmp(asm_code[i],"IN"))||
		   (!strcmp(asm_code[i],"PUTSP"))||
		   (!strcmp(asm_code[i],"HALT"))||
		   (!strcmp(asm_code[i],"RET"))||
		   (!strcmp(asm_code[i],"RTI"))||
		   (!strcmp(asm_code[i],".END"))){
			++n;
			st[n]=i;
			++line_all;
			line[n]=line_all;
		}else{
			string a=asm_code[i];
			label[a]=line_all;
		}
//	printf("!!!!!!%d\n",n);
//	for(int i=1;i<=n;i++)printf("%d\n",st[i]);
	for(int i=1;i<=n;i++){//根据汇编码输出 
		if(!strcmp(asm_code[st[i]],"ADD")){//reg reg reg/imm5
			printf("0001");
			Print_reg(asm_code[st[i]+1]);
			Print_reg(asm_code[st[i]+2]);
			if(asm_code[st[i]+3][0]=='R'){
				printf("000");
				Print_reg(asm_code[st[i]+3]);
			}else{
				printf("1");
				if(asm_code[st[i]+3][0]=='#')Print_imm(asm_code[st[i]+3],5);
				else Print_hex(asm_code[st[i]+3],5);
			}
			printf("\n");
		}else
		if(!strcmp(asm_code[st[i]],"AND")){//reg reg reg/imm5
			printf("0101");
			Print_reg(asm_code[st[i]+1]);
			Print_reg(asm_code[st[i]+2]);
			if(asm_code[st[i]+3][0]=='R'){
				printf("000");
				Print_reg(asm_code[st[i]+3]);
			}else{
				printf("1");
				if(asm_code[st[i]+3][0]=='#')Print_imm(asm_code[st[i]+3],5);
				else Print_hex(asm_code[st[i]+3],5);
			}
			printf("\n");
		}else
		if(!strcmp(asm_code[st[i]],"NOT")){//reg reg
			printf("1001");
			Print_reg(asm_code[st[i]+1]);
			Print_reg(asm_code[st[i]+2]);
			printf("111111\n");
		}else
		if(!strcmp(asm_code[st[i]],"LD")){//reg off9
			printf("0010");
			Print_reg(asm_code[st[i]+1]);
			if(asm_code[st[i]+2][0]=='#'){
				Print_imm(asm_code[st[i]+2],9);
			}else{
				string a=asm_code[st[i]+2];
				int tmp=label[a]-line[i];
				Print_off(tmp,9);
			}
			printf("\n");
		}else
		if(!strcmp(asm_code[st[i]],"LDR")){//reg reg imm6
			printf("0110");
			Print_reg(asm_code[st[i]+1]);
			Print_reg(asm_code[st[i]+2]);
			if(asm_code[st[i]+3][0]=='#')Print_imm(asm_code[st[i]+3],6);
			else Print_hex(asm_code[st[i]+3],6);
			printf("\n");
		}else
		if(!strcmp(asm_code[st[i]],"LDI")){//reg off9
			printf("1010");
			Print_reg(asm_code[st[i]+1]);
			if(asm_code[st[i]+2][0]=='#'){
				Print_imm(asm_code[st[i]+2],9);
			}else{
				string a=asm_code[st[i]+2];
				int tmp=label[a]-line[i];
				Print_off(tmp,9);
			}
			printf("\n");
		}else
		if(!strcmp(asm_code[st[i]],"LEA")){//reg off9
			printf("1110");
			Print_reg(asm_code[st[i]+1]);
			if(asm_code[st[i]+2][0]=='#'){
				Print_imm(asm_code[st[i]+2],9);
			}else{
				string a=asm_code[st[i]+2];
				int tmp=label[a]-line[i];
				Print_off(tmp,9);
			}
			printf("\n");
		}else
		if(!strcmp(asm_code[st[i]],"ST")){//reg off9
			printf("0011");
			Print_reg(asm_code[st[i]+1]);
			if(asm_code[st[i]+2][0]=='#'){
				Print_imm(asm_code[st[i]+2],9);
			}else{
				string a=asm_code[st[i]+2];
				int tmp=label[a]-line[i];
				Print_off(tmp,9);
			}
			printf("\n");
		}else
		if(!strcmp(asm_code[st[i]],"STR")){//reg reg imm6
			printf("0111");
			Print_reg(asm_code[st[i]+1]);
			Print_reg(asm_code[st[i]+2]);
			if(asm_code[st[i]+3][0]=='#')Print_imm(asm_code[st[i]+3],6);
			else Print_hex(asm_code[st[i]+3],6);
			printf("\n");
		}else
		if(!strcmp(asm_code[st[i]],"STI")){//reg off9
			printf("1011");
			Print_reg(asm_code[st[i]+1]);
			if(asm_code[st[i]+2][0]=='#'){
				Print_imm(asm_code[st[i]+2],9);
			}else{
				string a=asm_code[st[i]+2];
				int tmp=label[a]-line[i];
				Print_off(tmp,9);
			}
			printf("\n");
		}else
		if(!strcmp(asm_code[st[i]],"TRAP")){//vect8
			printf("11110000");
			Print_hex(asm_code[st[i]+1],8);
			printf("\n");
		}else
		if((!strcmp(asm_code[st[i]],"BR"))||
		   (!strcmp(asm_code[st[i]],"BRnzp"))){//off9
			printf("0000111");
			if(asm_code[st[i]+1][0]=='#'){
				Print_imm(asm_code[st[i]+1],9);
			}else{
				string a=asm_code[st[i]+1];
				int tmp=label[a]-line[i];
				Print_off(tmp,9);
			}
			printf("\n");
		}else
		if(!strcmp(asm_code[st[i]],"BRn")){//off9
			printf("0000100");
			if(asm_code[st[i]+1][0]=='#'){
				Print_imm(asm_code[st[i]+1],9);
			}else{
				string a=asm_code[st[i]+1];
				int tmp=label[a]-line[i];
				Print_off(tmp,9);
			}
			printf("\n");
		}else
		if(!strcmp(asm_code[st[i]],"BRz")){//off9
			printf("0000010");
			if(asm_code[st[i]+1][0]=='#'){
				Print_imm(asm_code[st[i]+1],9);
			}else{
				string a=asm_code[st[i]+1];
				int tmp=label[a]-line[i];
				Print_off(tmp,9);
			}
			printf("\n");
		}else
		if(!strcmp(asm_code[st[i]],"BRp")){//off9
			printf("0000001");
			if(asm_code[st[i]+1][0]=='#'){
				Print_imm(asm_code[st[i]+1],9);
			}else{
				string a=asm_code[st[i]+1];
				int tmp=label[a]-line[i];
				Print_off(tmp,9);
			}
			printf("\n");
		}else
		if(!strcmp(asm_code[st[i]],"BRnz")){//off9
			printf("0000110");
			if(asm_code[st[i]+1][0]=='#'){
				Print_imm(asm_code[st[i]+1],9);
			}else{
				string a=asm_code[st[i]+1];
				int tmp=label[a]-line[i];
				Print_off(tmp,9);
			}
			printf("\n");
		}else
		if(!strcmp(asm_code[st[i]],"BRnp")){//off9
			printf("0000101");
			if(asm_code[st[i]+1][0]=='#'){
				Print_imm(asm_code[st[i]+1],9);
			}else{
				string a=asm_code[st[i]+1];
				int tmp=label[a]-line[i];
				Print_off(tmp,9);
			}
			printf("\n");
		}else
		if(!strcmp(asm_code[st[i]],"BRzp")){//off9
			printf("0000011");
			if(asm_code[st[i]+1][0]=='#'){
				Print_imm(asm_code[st[i]+1],9);
			}else{
				string a=asm_code[st[i]+1];
				int tmp=label[a]-line[i];
				Print_off(tmp,9);
			}
			printf("\n");
		}else
		if(!strcmp(asm_code[st[i]],"JMP")){//reg
			printf("1100000");
			Print_reg(asm_code[st[i]+1]);
			printf("000000\n");
		}else
		if(!strcmp(asm_code[st[i]],"RET")){
			printf("1100000111000000\n");
		}else
		if(!strcmp(asm_code[st[i]],"JSR")){//off11
			printf("01001");
			if(asm_code[st[i]+1][0]=='#'){
				Print_imm(asm_code[st[i]+1],11);
			}else{
				string a=asm_code[st[i]+1];
				int tmp=label[a]-line[i];
				Print_off(tmp,11);
			}
			printf("\n");
		}else
		if(!strcmp(asm_code[st[i]],"JSRR")){//reg
			printf("0100000");
			Print_reg(asm_code[st[i]+1]);
			printf("000000\n");
		}else
		if(!strcmp(asm_code[st[i]],"RTI")){
			printf("1000000000000000\n");
		}else
		if(!strcmp(asm_code[st[i]],".ORIG")){//vect16
			Print_hex(asm_code[st[i]+1],16);
			printf("\n");
		}else
		if(!strcmp(asm_code[st[i]],".FILL")){//imm16
			if(asm_code[st[i]+1][0]=='#'){
				Print_imm(asm_code[st[i]+1],16);
				printf("\n");
			}else{
				Print_hex(asm_code[st[i]+1],16);
				printf("\n");
			}
		}else
		if(!strcmp(asm_code[st[i]],".BLKW")){
			int j=1,x=0;
			while(asm_code[st[i]+1][j]!='\0'){
				x=x*10+asm_code[st[i]+1][j]-'0';
				j++;
			}
			while(x--)printf("0111011101110111\n");
		}else
		if(!strcmp(asm_code[st[i]],".STRINGZ")){
			for(int j=1;j<strlen(asm_code[st[i]+1])-1;j++){
				Print_off(asm_code[st[i]+1][j],16);
				printf("\n");
			}
			printf("0000000000000000\n");
		}else
		if(!strcmp(asm_code[st[i]],"GETC")){
			printf("1111000000100000\n");
		}else
		if(!strcmp(asm_code[st[i]],"OUT")){
			printf("1111000000100001\n");
		}else
		if(!strcmp(asm_code[st[i]],"PUTS")){
			printf("1111000000100010\n");
		}else
		if(!strcmp(asm_code[st[i]],"IN")){
			printf("1111000000100011\n");
		}else
		if(!strcmp(asm_code[st[i]],"PUTSP")){
			printf("1111000000100100\n");
		}else
		if(!strcmp(asm_code[st[i]],"HALT")){
			printf("1111000000100101\n");
		}
//		printf("%s\n",asm_code[st[i]]);
	}
//	printf("%d %d\n",n,m);
	return 0;
}
