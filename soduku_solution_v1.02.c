#include <iostream>
#include <fstream>
using namespace std;

class Soduku_Point{
	public:
		int value;
		int boolin;
		int neighbor;
		
		Soduku_Point(){
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

class Soduku_Array{
	public:
		Soduku_Point p[10][10];
		
		void get_point_fromfile(){
			fstream in ("input.txt" , ios::in);
			for(int i = 1 ; i <= 9 ; i++){
				for(int j = 1 ; j <= 9 ; j++){
					in>>p[i][j].value;
				}
			}
		}
		
		void print_array(){
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
		
		void get_boolin(int x , int y){
			for(int i = 1 ; i <= 9 ; i++){
				p[x][y].boolin |= p[i][y].boolin;
			}
			
			for(int i = 1 ; i <= 9 ; i++){
				p[x][y].boolin |= p[x][i].boolin;
			}
			
			for(int i = x - (x-1)%3 ; i <= x - (x-1)%3 + 2 ; i++){
				for(int j = y - (y-1)%3 ; j <= y - (y-1)%3 +2 ; j++){
					p[x][y].boolin |= p[i][j].boolin;
				}
			}
		}
		
		void add_neighbor(int x , int y){
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
		
		int find_nonzero_value(){
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
		
		void slove_soduku_array(){
			int nonzero_start = 0 , nonzero_end;
			int nonzero_now = find_nonzero_value();
			nonzero_end = nonzero_now;
	
			for(int i = 1 ; i <= 9 ; i++){
				for(int j = 1 ; j <= 9 ; j++){
					if(p[i][j].value != 0){
						add_neighbor(i , j);
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
							get_boolin(i , j);
							p[i][j].boolin_to_value();
							if(p[i][j].value != 0){
								add_neighbor(i , j);
								nonzero_now += 1;
							}
						}
					}
				}
		
				nonzero_end = nonzero_now;
		
			}
		}
};

int main(){
	Soduku_Array array1;
	array1.get_point_fromfile();
	cout<<"The problem is :"<<endl;
	array1.print_array();
	array1.slove_soduku_array();
	cout<<"The solution is :"<<endl;
	array1.print_array();
	return 0;
}
