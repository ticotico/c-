#include <stdio.h>
typedef struct{
	int value;
	int boolin;
}Point;

int value_to_boolin(int input){
	return (1<<input) >>1;	
}

int boolin_to_value (int input){
	int count = 0 , result;
	for(int j = 1 ; j <= 9 ; j++){
		if(input%2){
			count++;
		}
		else{
			result = j ;
		}
		input /= 2;
	}
	
	if(count == 8){
		return result;
	}
	else{
		return 0;
	}
}

int main(){
	Point p[10][10]; //數獨9*9的陣列 使用[1][1]到[9][9] 
	int check_start = 0; //loop開始求解時已確定的數字個數 
	int check_end  = 0;	//loop結束時已確定的數字個數 
	//---start read input---
	FILE *input;
	input=fopen("input.txt","r"); 
	for(int i = 1 ; i <= 9 ; i++){
		for(int j = 1 ; j <= 9 ; j++){
			fscanf(input,"%d",&p[i][j].value);
			check_end = (p[i][j].value != 0) ? check_end + 1: check_end ; //決定一開始已經確定的數字個數 
			p[i][j].boolin = value_to_boolin(p[i][j].value); //將不為0的輸入轉換為判斷用數值 
			
		}
	}
	fclose(input);
	//---end of reading input---
	
	
	//---test tern : check input---
	for(int i = 1 ; i <= 9 ; i++){
		for( int j = 1 ; j <= 9 ; j++){
			printf("%d ",p[i][j].value);
		}
		printf("\n");
	}
	//---test tern : check input---
	
	
	//---get result---
	int loopcount = 0;
	while(check_end < 81 && check_end > check_start){
		//做迴圈:在確定81個已確定數字之前或這個循環沒有找出新的已確定數字 
		//loopcount++;
		check_start = check_end ; //將上個迴圈結束時的已確定數字帶入這個迴圈一開始 
		for(int i = 1 ; i <= 9 ; i++){
			for(int j = 1 ; j <= 9 ; j++){
				if(p[i][j].value ==0){ //對數獨陣列中，尚未找出確定數字(值為0)的數字嘗試求解 
					for(int k = 1 ; k <= 9 ; k++){
						p[i][j].boolin = p[i][j].boolin | p[i][k].boolin; //橫向作判斷用數值 
					}
					for(int k = 1 ; k <= 9 ; k++){
						p[i][j].boolin = p[i][j].boolin | p[k][j].boolin; //縱向作判斷用數值  
					}
					for(int m = i-(i-1)%3; m <= i-(i-1)%3+2 ; m++){ //3*3方格作判斷用數值  
						for(int n = j-(j-1)%3; n <= j-(j-1)%3+2 ; n++){
							p[i][j].boolin = p[i][j].boolin | p[m][n].boolin;
						}
					}
					p[i][j].value = boolin_to_value(p[i][j].boolin); //將判斷用數值換成數獨陣列內確定數字(1~9)或未確定數字(0)s 
					p[i][j].boolin = value_to_boolin(p[i][j].value); //依照數獨陣列內的確定與否換成供其他未確定數字判斷用的判斷值 
					if(p[i][j].value != 0){
						check_end+=1;
					}
				}
			}
		}
	}
	//printf("loopcount = %d\n",loopcount);
	//---get result---
	
	//---test tern : print output---
	printf("The result is :\n");
	for(int i = 1 ; i <= 9 ; i++){
		if(i%3==1){
			printf("\n");
		}
		for( int j = 1 ; j <= 9 ; j++){
			printf("%d ",p[i][j].value);
			if(j%3==0){
				printf("\t");
			}
		}
		printf("\n");
	}
	//---test tern : print output---
	 
	return 0;
}
