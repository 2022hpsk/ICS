#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void ScanfInstruction();
void ScanfReg();
void PrintReg(int n);
void DoAdd();
void DoAnd();
void DoNot();
void DoLd();
void DoLdr();
void DoLdi();
void DoLea();
void DoSt();
void DoStr();
void DoSti();
void DoTrap();
void DoHalt();
void DoOrig();
void DoBr(int i);
void DoJmp();
void DoRet();
void DoJsr();
void DoJsrr();
void DoRti();
void DoFill();
void DoBlkw();
void DoStringz();
void Scanfimm5();
void Scanfimm6();
void Printoff9(int off);
void Printoff11(int off);
void DoLabel();
void DoLabelpre(char* nowLabel);
void DoLabelafter(int n);
char Label[50][30];//存储label 
int  LabelRow[50];//存储label对应的行数 
int  NowRow =0;
FILE *fp;
int UNUSE;
int main(){
	if(!(fp=fopen("print.txt","w+"))){
		printf("open failed");
		return -1;
	}
	
	ScanfInstruction();
	
	fseek(fp,0,SEEK_SET);
	char c;
	int nowrow=0;
	char nowlabel[30];
	while(!feof(fp)){
		c=fgetc(fp);
		if(c=='\n'){
			nowrow++;
		}
		
		if(c==' '){
			UNUSE=fscanf(fp,"%s",nowlabel);
			for(int i=0;i<NowRow;i++){
				if(strcmp(Label[i],nowlabel)==0){
					Printoff11(LabelRow[i]-nowrow-1);
					break;
				}
			}	
		}else if(c=='9'){
			UNUSE=fscanf(fp,"%s",nowlabel);
			for(int i=0;i<NowRow;i++){
				if(strcmp(Label[i],nowlabel)==0){
					Printoff9(LabelRow[i]-nowrow-1);
					break;
				}
			}
		}else {
		  printf("%c",c);			
		}
	} 

	fclose(fp);
	fp=NULL;
	return 0;

}

void Printoff9(int off){
	char num[10];
	num[9]='\0';
	if(off>=0){
		for(int i=8;i>=0;i--){
		  num[i]=off%2+48;
		  off /= 2;
		}
	}else {
		off=-off;
		for(int i=8;i>=0;i--){
		  num[i]=off%2+48;
		  num[i]=1-num[i];
		  off /= 2;
		}
		for(int i=8;i>=0;i--){
			num[i]++;
			if(num[i]==2){
				num[i]=0;
			}else break;
		}
	}

	printf("%s",num);
}

void Printoff11(int off){
	char num[12];
	num[11]='\0';
	if(off>=0){
		for(int i=10;i>=0;i--){
		  num[i]=off%2+48;
		  off /= 2;
		}
	}else {
		off=-off;
		for(int i=10;i>=0;i--){
		  num[i]=off%2+48;
		  num[i]=1-num[i];
		  off /= 2;
		}
		for(int i=10;i>=0;i--){
			num[i]++;
			if(num[i]==2){
				num[i]=0;
			}else break;
		}
	}

	printf("%s",num);
}

void DoLabelpre(char* nowLabel){
	static int labelnum=0;
	strcpy(Label[labelnum],nowLabel);
	LabelRow[labelnum]=NowRow; 
	labelnum ++;
}

void DoLabelafter(int n){
	char labeltodo[30];
	UNUSE=scanf("%s",labeltodo);
	if(n==9)
	fprintf(fp,"9%s\n",labeltodo);
  else 
  fprintf(fp," %s\n",labeltodo);
}

void DoAnd(){
	char flag;
	int n;
	fprintf(fp,"0101");
  UNUSE=scanf(" ");
  ScanfReg();
	UNUSE=scanf(", ");
	ScanfReg();
	UNUSE=scanf(", ");
	UNUSE=scanf("%c",&flag);
	if(flag=='R'){
	  fprintf(fp,"000");
		UNUSE=scanf("%d",&n);
		PrintReg(n);
		fprintf(fp,"\n");
	}else {//flag == # 
		fprintf(fp,"1");
		Scanfimm5();
	}
	NowRow ++;
}

void DoAdd(){
	char flag;
	int n;
	fprintf(fp,"0001");
//	do{
//		scanf("%c",&flag);
//	}while(flag!='R');
//	scanf("%d",&n);
//	PrintReg(n);
//  这些都可用 scanf(" ");ScanfReg();代替 
  UNUSE=scanf(" ");
  ScanfReg();
	UNUSE=scanf(", ");
	ScanfReg();
	UNUSE=scanf(", ");
	UNUSE=scanf("%c",&flag);
	if(flag=='R'){
	  fprintf(fp,"000");
		UNUSE=scanf("%d",&n);
		PrintReg(n);
		fprintf(fp,"\n");
	}else {//flag == # 
		fprintf(fp,"1");
		Scanfimm5();
	}
	NowRow ++;
}

void DoNot(){
	fprintf(fp,"1001");
	UNUSE=scanf(" ");
	ScanfReg();
	UNUSE=scanf(", ");
	ScanfReg();
	fprintf(fp,"\n");
	NowRow ++; 
}

void DoLd(){
	fprintf(fp,"0010");
	UNUSE=scanf(" ");
	ScanfReg();
	UNUSE=scanf(", ");
	DoLabelafter(9);
	NowRow ++; 
}

void DoLdr(){
	fprintf(fp,"0110");
	UNUSE=scanf(" ");
	ScanfReg();
	UNUSE=scanf(", ");
	ScanfReg();
	UNUSE=scanf(", ");
	UNUSE=scanf("#");
  Scanfimm6();
	NowRow ++; 
}

void DoLdi(){
	fprintf(fp,"1010");
	UNUSE=scanf(" ");
	ScanfReg();
	UNUSE=scanf(", ");
	DoLabelafter(9);
	NowRow ++; 
}

void DoLea(){
	fprintf(fp,"1110");
	UNUSE=scanf(" ");
	ScanfReg();
	UNUSE=scanf(", ");
	DoLabelafter(9);
	NowRow ++; 
}

void DoSt(){
	fprintf(fp,"0011");
	UNUSE=scanf(" ");
	ScanfReg();
	UNUSE=scanf(", ");
	DoLabelafter(9);
	NowRow ++; 
}

void DoStr(){
	fprintf(fp,"0111");
	UNUSE=scanf(" ");
	ScanfReg();
	UNUSE=scanf(", ");
	ScanfReg();
	UNUSE=scanf(", ");
	UNUSE=scanf("#");
  Scanfimm6();
	NowRow ++; 
}

void DoSti(){
	fprintf(fp,"1011");
	UNUSE=scanf(" ");
	ScanfReg();
	UNUSE=scanf(", ");
	DoLabelafter(9);
	NowRow ++; 
}

void DoTrap(){
	fprintf(fp,"1111");
	int n=0;
	char c='0'; 
	UNUSE=scanf(" x");
	do{
		 if(c>='a'&&c<='f'){
		 	n=n*16+c-87;	
		 }else if(c>='A'&&c<='F'){
		 	n=n*16+c-55;
		 }else if(c>='0'&&c<='9'){
		 	n=n*16+c-48;	
		 }
		 UNUSE=scanf("%c",&c);

	}while(c != '\n' && c!= ' ');
	char num[9];//转换为二进制输出 
	num[8]='\0';
	if(n>=0){
		for(int i=7;i>=0;i--){
		  num[i]=n%2+48;
		  n /= 2;
	  }
	}else {
		n=-n;
		for(int i=7;i>=0;i--){
		  num[i]=n%2+48;
		  num[i]=1-num[i];
		  n /= 2;
		}
	  for(int i=7;i>=0;i--){
			num[i]++;
			if(num[i]==2){
				num[i]=0;
			}else break;
		}
	}
	fprintf(fp,"%s\n",num);
	NowRow ++;
}

void DoOrig(){
	int n=0;
	char c='0'; 
	UNUSE=scanf(" x");//读入十六进制数 
	do{
		 if(c>='a'&&c<='f'){
		 	n=n*16+c-87;	
		 }else if(c>='A'&&c<='F'){
		 	n=n*16+c-55;
		 }else if(c>='0'&&c<='9'){
		 	n=n*16+c-48;	
		 }
		 UNUSE=scanf("%c",&c);

	}while(c != '\n' && c!= ' ');
	char num[17];//转换为二进制输出 
	num[16]='\0';
	if(n>=0){
		for(int i=15;i>=0;i--){
		  num[i]=n%2+48;
		  n /= 2;
	  }
	}else {
		n=-n;
		for(int i=15;i>=0;i--){
		  num[i]=n%2+48;
		  num[i]=1-num[i];
		  n /= 2;
		}
	  for(int i=15;i>=0;i--){
			num[i]++;
			if(num[i]==2){
				num[i]=0;
			}else break;
		}
	}
	fprintf(fp,"%s\n",num);
	NowRow ++;
}

void DoHalt(){	
	fprintf(fp,"1111000000100101\n");
	NowRow ++;
}

void DoBr(int i){
	fprintf(fp,"0000");
	if(i==0||i==7){
		fprintf(fp,"111");
	}else if(i==1){
		fprintf(fp,"100");
	}else if(i==2){
		fprintf(fp,"010");
	}else if(i==3){
		fprintf(fp,"001");
	}else if(i==4){
		fprintf(fp,"110");
	}else if(i==5){
		fprintf(fp,"011");
	}else if(i==6){
		fprintf(fp,"101");
	}
	UNUSE=scanf(" ");
  DoLabelafter(9);
	NowRow ++; 
}

void DoJmp(){
	fprintf(fp,"1100");
	UNUSE=scanf(" ");
	ScanfReg();
	fprintf(fp,"\n");
  NowRow ++;
}

void DoRet(){
	fprintf(fp,"1100000111000000\n");
	NowRow ++;
}

void DoJsr(){
	fprintf(fp,"01001");
	UNUSE=scanf(" ");
	DoLabelafter(11);
	NowRow ++;
}

void DoJsrr(){
	fprintf(fp,"0100000");
	UNUSE=scanf(" ");
	ScanfReg();
	fprintf(fp,"000000\n");
	NowRow ++;
}

void DoRti(){
	fprintf(fp,"1000000000000000\n");
	NowRow ++;
}

void DoFill(){
	UNUSE=scanf(" #");
	int n;
	UNUSE=scanf("%d",&n);
	char num[17];
	num[16]='\0';
	if(n>=0){
	  for(int i=15;i>=0;i--){
		  num[i]=n%2+48;
		  n /= 2;
	  }
	}else {
		n=-n;
	  for(int i=15;i>=0;i--){
		  num[i]=n%2+48;
		  num[i]=1-num[i];
		  n /= 2;
	  }
	  for(int i=15;i>=0;i--){
			num[i]++;
			if(num[i]==2){
				num[i]=0;
			}else break;
		}  
	}
	fprintf(fp,"%s\n",num);
	NowRow ++;
}

void DoBlkw(){
	UNUSE=scanf(" #");
	int n;
	UNUSE=scanf("%d",&n);
	for(int i=0;i<n;i++){
		fprintf(fp,"0111011101110111\n");
	}
	NowRow +=n;
}

void DoStringz(){
	char string[30];
	UNUSE=scanf(" \"%s\"",string);
	for(int i=0;i<30;i++){
		if(string[i]=='\0')break;
		char num[17];
		num[16]='\0';
	  for(int i=15;i>=0;i--){
		  num[i]=string[i]%2+48;
      string[i] /= 2;
    } 
	  fprintf(fp,"%s\n",num);
	  NowRow++;
	}
	fprintf(fp,"0000000000000000\n");
	NowRow ++;
}


void Scanfimm5(){//读入并输出5位立即数 
	int n;
	UNUSE=scanf("%d",&n);
	char num[6];
	num[5]='\0';
	if(n>=0){
	  for(int i=4;i>=0;i--){
		  num[i]=n%2+48;
		  n /= 2;
	  }
	}else {
		n=-n;
	  for(int i=4;i>=0;i--){
		  num[i]=n%2+48;
		  num[i]=1-num[i];
		  n /= 2;
	  }
	  for(int i=4;i>=0;i--){
			num[i]++;
			if(num[i]==2){
				num[i]=0;
			}else break;
		}  
	}
	fprintf(fp,"%s\n",num);
}

void Scanfimm6(){//读入并输出6位立即数 
	int n;
	UNUSE=scanf("%d",&n);
	char num[7];
	num[6]='\0';
	if(n>=0){
	  for(int i=5;i>=0;i--){
		  num[i]=n%2+48;
		  n /= 2;
	  }
	}else {
		n=-n;
	  for(int i=5;i>=0;i--){
		  num[i]=n%2+48;
		  num[i]=1-num[i];
		  n /= 2;
	  }
	  for(int i=5;i>=0;i--){
			num[i]++;
			if(num[i]==2){
				num[i]=0;
			}else break;
		}  
	}
	fprintf(fp,"%s\n",num);
}

void ScanfInstruction(){
	char Ins[16];
	UNUSE=scanf("%s",Ins);
	while(strcmp(Ins,".END")!=0){
		if(strcmp(Ins,"ADD")==0){
			DoAdd();
		}else if(strcmp(Ins,"AND")==0){
			DoAnd();
		}else if(strcmp(Ins,"NOT")==0){
			DoNot();
		}else if(strcmp(Ins,"LD")==0){
			DoLd();
		}else if(strcmp(Ins,"LDR")==0){
			DoLdr();
		}else if(strcmp(Ins,"LDI")==0){
			DoLdi();
		}else if(strcmp(Ins,"LEA")==0){
			DoLea();
		}else if(strcmp(Ins,"ST")==0){
			DoSt();
		}else if(strcmp(Ins,"STR")==0){
			DoStr();
		}else if(strcmp(Ins,"STI")==0){
			DoSti();
		}else if(strcmp(Ins,"TRAP")==0){
			DoTrap();
		}else if(strcmp(Ins,"HALT")==0){
			DoHalt();
		}else if(strcmp(Ins,"BR")==0){
			DoBr(0);
		}else if(strcmp(Ins,"BRn")==0){
			DoBr(1);
		}else if(strcmp(Ins,"BRz")==0){
			DoBr(2);
		}else if(strcmp(Ins,"BRp")==0){
			DoBr(3);
		}else if(strcmp(Ins,"BRnz")==0){
			DoBr(4);
		}else if(strcmp(Ins,"BRzp")==0){
			DoBr(5);
		}else if(strcmp(Ins,"BRnp")==0){
			DoBr(6);
		}else if(strcmp(Ins,"BRnzp")==0){
			DoBr(7);
		}else if(strcmp(Ins,"JMP")==0){
			DoJmp();
		}else if(strcmp(Ins,"RET")==0){
			DoRet();
		}else if(strcmp(Ins,"JSR")==0){
			DoJsr();
		}else if(strcmp(Ins,"JSRR")==0){
			DoJsrr();
		}else if(strcmp(Ins,"RTI")==0){
			DoRti();
		}else if(strcmp(Ins,".ORIG")==0){
			DoOrig();
		}else if(strcmp(Ins,".FILL")==0){
			DoFill();
		}else if(strcmp(Ins,".BLKW")==0){
			DoBlkw();
		}else if(strcmp(Ins,".STRINGZ")==0){
			DoStringz();
		}else {
			DoLabelpre(Ins); 
		}	
		UNUSE=scanf("%s",Ins);
	}
	
	return;
}

void ScanfReg(){//读入寄存器名称 
	char c;
	int n;
	UNUSE=scanf("%c%d",&c,&n);	
	PrintReg(n);
	return;
}

void PrintReg(int n){//输出寄存器 
	char num[4];
	num[3]='\0';
	for(int i=2;i>=0;i--){
		num[i]=n%2+48;
		n /= 2;
	}
	fprintf(fp,"%s",num);
}

