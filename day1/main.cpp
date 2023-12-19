// Your First C++ Program

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <array>

using namespace std;
// Array of digit strings in lowercase

const array<string, 10> digitStrings = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};


// Function to convert string to digit
int stringToDigit(const string& str) {
     for (size_t i = 0; i < digitStrings.size(); ++i) {
 	 
	 if (str.length()>=digitStrings[i].length()  && digitStrings[i] == str.substr(0,digitStrings[i].length())) {
             return static_cast<int>(i);
         }
     }
     return -1; // Return -1 to indicate no match was found
}

int isDigitExtended(string line,int startingIndex){
	if(isdigit(line[startingIndex])){
		return line[startingIndex] - '0';
	}
	 
        return stringToDigit(line.substr(startingIndex, line.length()-startingIndex));

}


int main() {
    string line;
    int result = 0;
    ifstream file("input.txt");
    if(file.is_open()){
    	while(getline(file,line)){
		int current = 0;
		bool first = true;
		int last = -1;
		for(int i=0;i<line.length();i++){
		    int digit = isDigitExtended(line,i);   
		    if(digit > -1){
		   	if(first){
			   current = digit * 10;
			   first = false;
			}
			else{
			   last = digit;
			}
		   }
		}
		if(last == -1)
			current += current/10;
		else
			current += last;
		result +=current;
		cout<<line<< " " <<current<<  " "<< last << "\n";
	}
    }
    cout<<result;
    return 0;
}
       

