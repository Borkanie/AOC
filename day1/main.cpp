// Your First C++ Program

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

int main() {
    string line;
    int result = 0;
    ifstream file("input.txt");
    if(file.is_open()){
    	while(getline(file,line)){
		int current = 0;
		bool first = true;
		int last = -1;
		for(char c : line){
		   if(isdigit(c)){
		   	if(first){
			   current = (c - '0' ) * 10;
			   first = false;
			}
			else{
			   last = c - '0';
			}
		   }
		}
		if(last == -1)
			current += current/10;
		else
			current += last;
		result +=current;
		cout<<line<< " " <<current<<"\n";
	}
    }
    cout<<result;
    return 0;
}
       

