//label大小个数，file总大小 stringz大小 命令大小写不区分   label大小写不区分  label一个字符   
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAXLABEL 200
#define MAXLABELNUMBER 1000
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
void Scanfimm(int w);
void imm0(int w);
void Scanfimmx(int w); 
void Printoff9(int off);
void Printoff11(int off);
void DoLabel();
void DoLabelpre(char* nowLabel);
void DoLabelafter(int n,char c);
char Label[MAXLABELNUMBER][MAXLABEL];//存储label 
int  LabelRow[MAXLABELNUMBER];//存储label对应的行数 
int  NowRow =0;
char file[100000];
int UNUSE;
int mycmp(char* a,char* b);
int main(){	
	ScanfInstruction();
	int i=0;
	char c;
	int nowrow=0;
	char nowlabel[MAXLABEL];
	while(file[i]!='\0'){
		c=file[i];
		i++;
		if(c=='\n'){
			nowrow++;
		}
		
		if(c==' '){
			
//			UNUSE=fscanf(fp,"%s",nowlabel);
      for(int j=0;j<MAXLABEL;j++){
      	nowlabel[j]=file[i+j];
      	if(file[i+j]=='\n'){
      	  nowlabel[j]='\0';
      	  i+=j;
					break;	
				}
			} 
			for(int i=0;i<NowRow;i++){
				if(mycmp(Label[i],nowlabel)==0){
					Printoff11(LabelRow[i]-nowrow-1);
					break;
				}
			}	
		}else if(c=='9'){
//			UNUSE=fscanf(fp,"%s",nowlabel);
      for(int j=0;j<MAXLABEL;j++){
      	nowlabel[j]=file[i+j];
      	if(file[i+j]=='\n'){
      	  nowlabel[j]='\0';
      	  i+=j;
					break;	
				}
			}
//			printf("%send",nowlabel); 
			for(int i=0;i<NowRow;i++){
				if(mycmp(Label[i],nowlabel)==0){
					Printoff9(LabelRow[i]-nowrow-1);
					break;
				}
			}
		}else {
		  printf("%c",c);			
		}
		
	} 

//	for(int i=0;i<NowRow;i++){
//		printf("%send\n",Label[i]);
//	}
	return 0;

}


int mycmp(char* a,char* b){
	int i=0;
	while(a[i]!='\0' && b[i]!='\0'){
		if(a[i]==b[i]) i++;
		else if(a[i]>b[i]){
			if(a[i]>='a' && a[i]<='z' && b[i]>='A' && b[i]<='Z' && a[i]-32==b[i]) i++;
			else return 1;
		}
		else if(a[i]<b[i]){
			if(a[i]<b[i]){
				if(a[i]>='A' && a[i]<='Z' && b[i]>='a' && b[i]<='z' && a[i]==b[i]-32) i++;
				else return -1;
			}
		}
	}
	if(a[i]=='\0' && b[i]=='\0') return 0;
	else if(a[i]=='\0' && b[i]!='\0') return -1;
	else if(a[i]!='\0' && b[i]=='\0') return 1;
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
		  num[i]=off%2;
		  num[i]=1-num[i];
		  num[i]+=48;
		  off /= 2;
		}
		for(int i=8;i>=0;i--){
			num[i]++;
			if(num[i]=='2'){
				num[i]='0';
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
		  num[i]=off%2;
		  num[i]=1-num[i];
		  num[i]+=48;
		  off /= 2;
		}
		for(int i=10;i>=0;i--){
			num[i]++;
			if(num[i]=='2'){
				num[i]='0';
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

void DoLabelafter(int n,char c){
	char flag;
	int i=1;
	char labeltodo[MAXLABEL];
//	char labeltoread[MAXLABEL];
	labeltodo[0]=c;
	labeltodo[1]='\0';
	UNUSE=scanf("%c",&flag);
  while(flag!='\n'&&flag!=' '){
  	labeltodo[i]=flag;
  	labeltodo[i+1]='\0'; 
  	i++;
  	UNUSE=scanf("%c",&flag);
	}
//	printf("\nthe label : %s\n",labeltodo);
//	UNUSE=scanf("%s",labeltoread);
//
//	if(strcmp(labeltodo,labeltoread)==0){
//	  //do nothing;	
//	}else strcat(labeltodo,labeltoread);
	if(n==9){
		strcat(file,"9");
	  strcat(file,labeltodo);	
	  strcat(file,"\n");
	}else{
		strcat(file," ");
	  strcat(file,labeltodo);
		strcat(file,"\n");	
	}
}

void DoAnd(){
	char flag;
	int n;
	strcat(file,"0101");
  UNUSE=scanf(" ");
  ScanfReg();
	UNUSE=scanf(", ");
	ScanfReg();
	UNUSE=scanf(", ");
	UNUSE=scanf("%c",&flag);
	if(flag=='R'||flag=='r'){
	  strcat(file,"000");
		UNUSE=scanf("%d",&n);
		PrintReg(n);
		strcat(file,"\n");
	}else if(flag=='#'){//flag == # 
		strcat(file,"1");
		Scanfimm5();
	}else if(flag=='x'){
		strcat(file,"1");
		Scanfimmx(5);
	}else if(flag=='0'){
		strcat(file,"1");
		imm0(5);
	}
	NowRow ++;
}

void DoAdd(){
	char flag;
	int n;
	strcat(file,"0001");
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
	if(flag=='R'||flag=='r'){
	  strcat(file,"000");
		UNUSE=scanf("%d",&n);
		PrintReg(n);
		strcat(file,"\n");
	}else if(flag=='#'){//flag == # 
		strcat(file,"1");
		Scanfimm5();
	}else if(flag=='x'){
		strcat(file,"1");
		Scanfimmx(5);
	}else if(flag=='0'){
		strcat(file,"1");
		imm0(5);
	}
	NowRow ++;
}

void DoNot(){
	strcat(file,"1001");
	UNUSE=scanf(" ");
	ScanfReg();
	UNUSE=scanf(", ");
	ScanfReg();
	strcat(file,"111111\n");
	NowRow ++; 
}

void DoLd(){
	char c;
	strcat(file,"0010");
	UNUSE=scanf(" ");
	ScanfReg();
	UNUSE=scanf(", ");
	UNUSE=scanf("%c",&c);
	if(c=='#'){
		Scanfimm(9);
	}else if(c=='0'){
		imm0(9);
	}else DoLabelafter(9,c);
	NowRow ++; 
}

void DoLdr(){
	char c;
	strcat(file,"0110");
	UNUSE=scanf(" ");
	ScanfReg();
	UNUSE=scanf(", ");
	ScanfReg();
	UNUSE=scanf(", ");
	UNUSE=scanf("%c",&c);
	if(c=='#'){
    Scanfimm6();	
	}else if(c=='x'){
		Scanfimmx(6);
	}else if(c=='0'){
		imm0(6);
	}
	NowRow ++; 
}

void DoLdi(){
	char c;
	strcat(file,"1010");
	UNUSE=scanf(" ");
	ScanfReg();
	UNUSE=scanf(", ");
	UNUSE=scanf("%c",&c);
	if(c=='#'){
		Scanfimm(9);
	}else if(c=='0'){
		imm0(9);
	}else DoLabelafter(9,c);
	NowRow ++; 
}

void DoLea(){
	char c;
	strcat(file,"1110");
	UNUSE=scanf(" ");
	ScanfReg();
	UNUSE=scanf(", ");
	UNUSE=scanf("%c",&c);
	if(c=='#'){
		Scanfimm(9);
	}else if(c=='0'){
		imm0(9);
	}else DoLabelafter(9,c);
	NowRow ++; 
}

void DoSt(){
	char c;
	strcat(file,"0011");
	UNUSE=scanf(" ");
	ScanfReg();
	UNUSE=scanf(", ");
	UNUSE=scanf("%c",&c);
	if(c=='#'){
		Scanfimm(9);
	}else if(c=='0'){
		imm0(9);
	}else DoLabelafter(9,c);
	NowRow ++; 
}

void DoStr(){
	char c;
	strcat(file,"0111");
	UNUSE=scanf(" ");
	ScanfReg();
	UNUSE=scanf(", ");
	ScanfReg();
	UNUSE=scanf(", ");
	UNUSE=scanf("%c",&c);
	if(c=='#'){
    Scanfimm6();	
	}else if(c=='x'){
		Scanfimmx(6);
	}else if(c=='0'){
		imm0(6);
	}
	NowRow ++; 
}

void DoSti(){
	char c;
	strcat(file,"1011");
	UNUSE=scanf(" ");
	ScanfReg();
	UNUSE=scanf(", ");
	UNUSE=scanf("%c",&c);
	if(c=='#'){
		Scanfimm(9);
	}else if(c=='0'){
		imm0(9);
	}else DoLabelafter(9,c);
	NowRow ++; 
}

void DoTrap(){
	strcat(file,"11110000");
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
  for(int i=7;i>=0;i--){
		num[i]=n%2+48;
		n /= 2;
	}
	strcat(file,num);
	strcat(file,"\n");
	NowRow ++;
}

void DoOrig(){
	int n=0;
	char c='0';
	int flag=0; 
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
  for(int i=15;i>=0;i--){
		num[i]=n%2+48;
		n /= 2;
	}
	strcat(file,num);
	strcat(file,"\n");
	NowRow ++;
}

void DoHalt(){	
	strcat(file,"1111000000100101");
	strcat(file,"\n");
	NowRow ++;
}

void DoBr(int i){
	char c;
	strcat(file,"0000");
	if(i==0||i==7){
		strcat(file,"111");
	}else if(i==1){
		strcat(file,"100");
	}else if(i==2){
		strcat(file,"010");
	}else if(i==3){
		strcat(file,"001");
	}else if(i==4){
		strcat(file,"110");
	}else if(i==5){
		strcat(file,"011");
	}else if(i==6){
		strcat(file,"101");
	}
	UNUSE=scanf(" ");
	UNUSE=scanf("%c",&c);
	if(c=='#'){
		Scanfimm(9);
	}else if(c=='0'){
		imm0(9);
	}else DoLabelafter(9,c);
	NowRow ++; 
}

void DoJmp(){
	strcat(file,"1100000");
	UNUSE=scanf(" ");
	ScanfReg();
	strcat(file,"000000\n");
  NowRow ++;
}

void DoRet(){
	strcat(file,"1100000111000000");
	strcat(file,"\n");
	NowRow ++;
}

void DoJsr(){
	char c;
	strcat(file,"01001");
	UNUSE=scanf(" ");
	UNUSE=scanf("%c",&c);
	if(c=='#'){
		Scanfimm(11);
	}else if(c=='0'){
		imm0(11);
	}else DoLabelafter(11,c);
	NowRow ++;
}

void DoJsrr(){
	strcat(file,"0100000");
	UNUSE=scanf(" ");
	ScanfReg();
	strcat(file,"000000");
	strcat(file,"\n");
	NowRow ++;
}

void DoRti(){
	strcat(file,"1000000000000000");
	strcat(file,"\n");
	NowRow ++;
}

void DoFill(){
	char c;
	int n=0;
	int flag=0;
	char num[17];
  num[16]='\0';
	UNUSE=scanf(" ");
	UNUSE=scanf("%c",&c);
	if(c== '#'){
	  UNUSE=scanf("%d",&n);		
	}else if(c=='x'){//十六进制读入 
	  c='0';
	  do{
	  	 if(c=='-'){
	  	 	flag=1;
	  	 	UNUSE=scanf("%c",&c);
	  	 	continue;
			 } 
		   if(c>='a'&&c<='f'){
		 	  n=n*16+c-87;	
		   }else if(c>='A'&&c<='F'){
 	       n=n*16+c-55;
		   }else if(c>='0'&&c<='9'){
		 	   n=n*16+c-48;	
		   }
		   UNUSE=scanf("%c",&c);

	  }while(c != '\n' && c!= ' '); 			
	}else if(c=='0'){
		n=0;
	} 

	if(flag==1)n=-n;
  if(n>=0){//转换为二进制输出
    for(int i=15;i>=0;i--){
		  num[i]=n%2+48;
		  
		  n /= 2;
	  }
	}else {
		n=-n;
		for(int i=15;i>=0;i--){
		  num[i]=n%2;
		  num[i]=1-num[i];
		  num[i]+=48;
			n /= 2;
		}
	  for(int i=15;i>=0;i--){
			num[i]++;
			if(num[i]=='2'){
				num[i]='0';
			}else break;
		}
	}
	strcat(file,num);
	strcat(file,"\n");
	NowRow ++;
}

void DoBlkw(){
	char c;
	int n;
	UNUSE=scanf(" ");
	UNUSE=scanf("%c",&c);
	if(c=='#'){
	  UNUSE=scanf("%d",&n);
	}else if(c=='x'){
	  c='0';
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
	}else if(c=='0')n=0;
	for(int i=0;i<n;i++){
		strcat(file,"0111011101110111");
		strcat(file,"\n");
	}
	NowRow +=n;
}

void DoStringz(){
	char string[3000];
//	UNUSE=scanf(" \"%s\"",string);
  UNUSE=scanf(" \"");
  
	
//	UNUSE=scanf("%s",string);
  
  
  //**为拟合check，使stringz可以读空格 {
  char a,b;
  scanf("%c",&b);
  for(int i=0;i<1000;i++){
  	a=b;
  	scanf("%c",&b);
  	if(b!='\n'){
  		string[i]=a;
		}else {
			string[i]=a;
			string[i+1]='\0';
			break;
		}
		
	} 
  
  
  
  //**   }为拟合check，使stringz可以读空格 
	for(int i=0;i<1000;i++){
		
		if(string[i+1]=='\0')break;
		char num[17];
		num[16]='\0';
	  for(int j=15;j>=0;j--){
		  num[j]=string[i]%2+48;

      string[i] /= 2;
    } 

	  strcat(file,num);
	  strcat(file,"\n");
	  NowRow++;
	}
	strcat(file,"0000000000000000");
	strcat(file,"\n");
	NowRow ++;
}

void Scanfimmx(int w){//读入并输出5位(或6位）立即数 (十六进制） 
	int n=0;
	char c='0';
	int flag=0; 
	UNUSE=scanf(" x");//读入十六进制数 
	do{
		 if(c=='-'){
		 	 flag=1;
		 	 UNUSE=scanf("%c",&c);
		 	 continue;
		 }
		 if(c>='a'&&c<='f'){
		 	n=n*16+c-87;	
		 }else if(c>='A'&&c<='F'){
		 	n=n*16+c-55;
		 }else if(c>='0'&&c<='9'){
		 	n=n*16+c-48;	
		 }
		 UNUSE=scanf("%c",&c);
	}while(c != '\n' && c!= ' ');
	
	char num[w+1];
	num[w]='\0';
	if(flag==1)n=-n; 
	if(n>=0){
	  for(int i=w-1;i>=0;i--){
		  num[i]=n%2+48;
		  n /= 2;
	  }
	}else {
		n=-n;
	  for(int i=w-1;i>=0;i--){
		  num[i]=n%2;
		  num[i]=1-num[i];
		  num[i]+=48;
		  n /= 2;
	  }
	  for(int i=w-1;i>=0;i--){
			num[i]++;
			if(num[i]=='2'){
				num[i]='0';
			}else break;
		}  
	}
	strcat(file,num);
	strcat(file,"\n");
}

void imm0(int w){
  int n=0;
	char num[w+1];
	num[w]='\0';
  for(int i=w-1;i>=0;i--){
    num[i]=n%2+48;
    n /= 2;
  }
	strcat(file,num);
	strcat(file,"\n");
}

void Scanfimm(int w){
	int n;
	UNUSE=scanf("%d",&n);
	char num[w+1];
	num[w]='\0';
	if(n>=0){
	  for(int i=w-1;i>=0;i--){
		  num[i]=n%2+48;
		  n /= 2;
	  }
	}else {
		n=-n;
	  for(int i=w-1;i>=0;i--){
		  num[i]=n%2;
		  num[i]=1-num[i];
		  num[i]+=48;
		  n /= 2;
	  }
	  for(int i=w-1;i>=0;i--){
			num[i]++;
			if(num[i]=='2'){
				num[i]='0';
			}else break;
		}  
	}
	strcat(file,num);
	strcat(file,"\n");
	
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
		  num[i]=n%2;
		  num[i]=1-num[i];
		  num[i]+=48;
		  n /= 2;
	  }
	  for(int i=4;i>=0;i--){
			num[i]++;
			if(num[i]=='2'){
				num[i]='0';
			}else break;
		}  
	}
	strcat(file,num);
	strcat(file,"\n");
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
		  num[i]=n%2;
		  num[i]=1-num[i];
		  num[i]+=48;
		  n /= 2;
	  }
	  for(int i=5;i>=0;i--){
			num[i]++;
			if(num[i]=='2'){
				num[i]='0';
			}else break;
		}  
	}
	strcat(file,num);
	strcat(file,"\n");
}

void ScanfInstruction(){
	char Ins[MAXLABEL];
	UNUSE=scanf("%s",Ins);
	while(mycmp(Ins,".END")!=0){
		if(mycmp(Ins,"ADD")==0){
			DoAdd();
		}else if(mycmp(Ins,"AND")==0){
			DoAnd();
		}else if(mycmp(Ins,"NOT")==0){
			DoNot();
		}else if(mycmp(Ins,"LD")==0){
			DoLd();
		}else if(mycmp(Ins,"LDR")==0){
			DoLdr();
		}else if(mycmp(Ins,"LDI")==0){
			DoLdi();
		}else if(mycmp(Ins,"LEA")==0){
			DoLea();
		}else if(mycmp(Ins,"ST")==0){
			DoSt();
		}else if(mycmp(Ins,"STR")==0){
			DoStr();
		}else if(mycmp(Ins,"STI")==0){
			DoSti();
		}else if(mycmp(Ins,"TRAP")==0){
			DoTrap();
		}else if(mycmp(Ins,"HALT")==0){
			DoHalt();
		}else if(mycmp(Ins,"BR")==0){
			DoBr(0);
		}else if(mycmp(Ins,"BRn")==0){
			DoBr(1);
		}else if(mycmp(Ins,"BRz")==0){
			DoBr(2);
		}else if(mycmp(Ins,"BRp")==0){
			DoBr(3);
		}else if(mycmp(Ins,"BRnz")==0){
			DoBr(4);
		}else if(mycmp(Ins,"BRzp")==0){
			DoBr(5);
		}else if(mycmp(Ins,"BRnp")==0){
			DoBr(6);
		}else if(mycmp(Ins,"BRnzp")==0){
			DoBr(7);
		}else if(mycmp(Ins,"JMP")==0){
			DoJmp();
		}else if(mycmp(Ins,"RET")==0){
			DoRet();
		}else if(mycmp(Ins,"JSR")==0){
			DoJsr();
		}else if(mycmp(Ins,"JSRR")==0){
			DoJsrr();
		}else if(mycmp(Ins,"RTI")==0){
			DoRti();
		}else if(mycmp(Ins,".ORIG")==0){
			DoOrig();
		}else if(mycmp(Ins,".FILL")==0){
			DoFill();
		}else if(mycmp(Ins,".BLKW")==0){
			DoBlkw();
		}else if(mycmp(Ins,".STRINGZ")==0){
			DoStringz();
		}else if(mycmp(Ins,"GETC")==0){
			strcat(file,"1111000000100000");
	    strcat(file,"\n");
	    NowRow ++;
		}else if(mycmp(Ins,"OUT")==0){
			strcat(file,"1111000000100001");
	    strcat(file,"\n");
	    NowRow ++;
		}else if(mycmp(Ins,"PUTS")==0){
			strcat(file,"1111000000100010");
	    strcat(file,"\n");
	    NowRow ++;
		}else if(mycmp(Ins,"IN")==0){
			strcat(file,"1111000000100011");
	    strcat(file,"\n");
	    NowRow ++;
		}else if(mycmp(Ins,"PUTSP")==0){
			strcat(file,"1111000000100100");
	    strcat(file,"\n");
	    NowRow ++;
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
	strcat(file,num);
}

