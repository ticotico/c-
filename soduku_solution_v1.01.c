#include <iostream>
#include <fstream>
using namespace std;

class Soduku_Array{
	public:
		int value;
		int boolin;
		int neighbor;
		
		Soduku_Array(){
			value = 0;
			boolin = 0;
			neighbor = 0;
		}
		
		void value_to_boolin(){
			boolin = (1 << value) >> 1;
		}
		
		void boolin_to_value(){
			int count = 0 , result;
			for(int i = 1 ; i <= 9 ; i++){
				if(boolin%2 == 1){
					count++;
				}
				else{
					result = i;
				}
				boolin /= 2;
			}
			
			if(count ==8){
				value = result;
			}
			else{
				value = 0;
			}
			
			value_to_boolin();
		}		
};

void get_soduku_fromfile(Soduku_Array p[][10]){
	fstream in("input.txt",ios::in);
	for(int i = 1 ; i <= 9 ; i++){
		for(int j = 1 ; j <= 9 ; j++){
			in>>p[i][j].value;
		}
	}
	in.close();
}

void print_soduku_array(Soduku_Array p[][10]){
	for(int i = 1 ; i <= 9 ; i++){
		for(int j = 1 ; j <= 9 ; j++){
			cout<<p[i][j].value<<" ";
			if(j % 3 == 0){
				cout<<" ";
			}
		}
		cout<<endl;
		if(i % 3 == 0){
			cout<<endl;
		}
	}
}

void get_boolin(Soduku_Array p[][10] , int x , int y){
	for(int i = 1 ; i <= 9 ; i++){
		p[x][y].boolin |= p[i][y].boolin;
	}
	
	for(int i = 1 ; i <= 9 ; i++){
		p[x][y].boolin |= p[x][i].boolin;
	}
	
	for(int i = x - (x-1)%3 ; i <= x - (x-1)%3 + 2 ; i++){
		for(int j = y - (y-1)%3 ; j <= y - (y-1)%3 +2 ; j++){
			p[x][y].boolin |= p[i][j].boolin;;
		}
	}
}

void add_neighbor(Soduku_Array p[][10] , int x , int y){
	for(int i = 1 ; i <= 9 ; i++){
		p[i][y].neighbor += 1;
	}
	
	for(int i = 1 ; i <=9 ; i++){
		p[x][i].neighbor += 1;
	}
	
	for(int i = x - (x-1)%3 ; i <= x - (x-1)%3 + 2 ; i++){
		for(int j = y - (y-1)%3 ; j <= y - (y-1)%3 +2 ; j++){
			p[i][j].neighbor += 1;
		}
	}
	
	for(int i = x - (x-1)%3 ; i <= x - (x-1)%3 + 2 ; i++){
		p[i][y].neighbor -= 1;
	}
	
	for(int i = y - (y-1)%3 ; i <= y - (y-1)%3 +2 ; i++){
		p[x][i].neighbor -= 1;
	}
}

int find_nonzero_value(Soduku_Array p[][10]){
	int result = 0;
	for(int i = 1 ; i <= 9 ; i++){
		for(int j = 1 ; j <= 9 ; j++){
			if(p[i][j].value != 0){
				result++;
			}
		}
	}
	//cout << "There are " << result << "nonzero value." << endl;
	return result;
}

void slove_soduku_array(Soduku_Array p[][10]){
	int nonzero_start = 0 , nonzero_end;
	int nonzero_now = find_nonzero_value(p);
	nonzero_end = nonzero_now;
	
	for(int i = 1 ; i <= 9 ; i++){
		for(int j = 1 ; j <= 9 ; j++){
			if(p[i][j].value != 0){
				add_neighbor(p , i , j);
				p[i][j].value_to_boolin();
				//p[i][j].boolin = value_to_boolin (p[i][j].value);
			}
		}
	}
	
	while(nonzero_now < 81 && nonzero_start < nonzero_end){
		nonzero_start = nonzero_now;
		
		for(int i = 1 ; i <= 9 ; i++){
			for(int j = 1 ; j <= 9 ; j++){
				if(p[i][j].neighbor >= 8 && p[i][j].value == 0){
					get_boolin(p , i , j);
					p[i][j].boolin_to_value();
					if(p[i][j].value != 0){
						add_neighbor(p , i , j);
						nonzero_now += 1;
					}
				}
			}
		}
		
		nonzero_end = nonzero_now;
		
	}
}

int main(){
	Soduku_Array p[10][10];
	get_soduku_fromfile(p);
	cout<<"The problem is :"<<endl;
	print_soduku_array(p);
	slove_soduku_array(p);
	cout<<"The solution is :"<<endl;
	print_soduku_array(p);
	return 0;
}
