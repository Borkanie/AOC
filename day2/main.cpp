// Your First C++ Program

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <array>

using namespace std;
// Array of digit strings in lowercase

const array<string> colors = {"red", "green", "blue"};

vector<string> splitString(const string& str, char delimiter) {
    vector<string> result;
    size_t start = 0;
    size_t end = str.find(delimiter);

    while (end != string::npos) {
        result.push_back(str.substr(start, end - start));
        start = end + 1;
        end = str.find(delimiter, start);
    }

    result.push_back(str.substr(start));
    return result;
}

int findStringIndex(const vector<string>& vec, const string& target) {
    for (size_t i = 0; i < vec.size(); ++i) {
        if (vec[i] == target) {
            return static_cast<int>(i);  // Return the index of the found string
        }
    }
    return -1;  // Return -1 if the string is not found
}

bool fitsInArray( vector<stirng> input, vector<int> margin){
	vector<int> balls = {0, 0 ,0};
	for(string ball : input){
	     balls
	}
}

int main() {
    string line;
    int result = 0;
    ifstream file("input.txt");
    vector<int> margin = { 12, 13 ,14};

    if(file.is_open()){
    	while(getline(file,line)){
		vector<string> input = splitString( splitString(line,':')[1], ';');
		
		cout<<line<<"\n";
	}
    }
    cout<<result;
    return 0;
}
       

