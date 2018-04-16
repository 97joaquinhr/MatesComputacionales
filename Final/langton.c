#include<stdio.h>
#include <stdlib.h>
#ifndef SI
#define SI 20
#endif

void fill(int m[SI][SI]){
	int i,j;
	for(i=0;i<SI;i++){
		for(j=0;j<SI;j++){
			m[i][j]=1;
		}
	}
}
void print(int m[SI][SI]){
	int i,j;
	for(i=0;i<SI;i++){
		for(j=0;j<SI;j++){
			printf("%i ",m[i][j]);
		}
		printf("\n");
	}
}
void langton(int m[SI][SI],int j,int i){
	int dir=rand()%4;
	int k;
	//printf("dir: %i\n",dir);
	//siempre empieza en negro
	for(k=0;k<1000;k++){
		if(m[i][j]==0){
			m[i][j]=1;
			if(dir>0)
				dir--;
			else
				dir=3;
		}else{
			m[i][j]=0;
			if(dir<3)
				dir++;
			else
				dir=0;
		}
		switch(dir){
			case 0:
				if(i>0)
					i--;
				else
					i=SI-1;
				//printf("Dir:north\n");
				break;
			case 1:
				if(j<SI-1)
					j++;
				else
					j=0;
				//printf("Dir:east2\n");
				break;
			case 2:
				if(i<SI-1)
					i++;
				else
					i=0;
				//printf("Dir:south3\n");
				break;
			case 3:
				if(j>0)
					j--;
				else
					j=SI-1;
				//printf("Dir:west4\n");
				break;
			default:
				//printf("error\n");
				break;
		}
	}
}

int main(){
	int m[SI][SI],i,j,k;
	srand(time(NULL));
	i=rand()%SI;
	j=rand()%SI;
	fill(m);
	langton(m,i,j);
	print(m);
	return 0;
}