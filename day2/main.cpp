// Your First C++ Program

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <array>
#include <vector>

using namespace std;
// Array of digit strings in lowercase

const array<string, 3> colors = {"red", "green", "blue"};

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

int findStringIndex(const string& target) {
    for (size_t i = 0; i < colors.size(); ++i) {
        if (colors[i] == target) {
            return i;  // Return the index of the found string
        }
    }
    return -1;  // Return -1 if the string is not found
}

bool fitsInArray(const vector<string> input,const vector<int> margin){
	vector<int> balls = {0, 0 ,0};
	
	for(int index=0;index<input.size();index++){
	     const vector<string> balls = splitString(input[index],',');
	     for(int ballIndex = 0; ballIndex < balls.size(); ballIndex++){
		int number = stoi(splitString(balls[ballIndex],' ')[1]);
		int colorIndex = findStringIndex(splitString(balls[ballIndex],' ')[2]);
		if(margin[colorIndex] < number)
			return false;
	     }
     
    	}
	return true;
}

int main() {
    string line;
    int result = 0;
    ifstream file("input.txt");
    vector<int> margin = { 12, 13 ,14};
    int sum = 0;
    if(file.is_open()){
    	while(getline(file,line)){
		vector<string> input = splitString( splitString(line,':')[1], ';');
	        if(fitsInArray(input, margin)){
 			sum += stoi(splitString(splitString(line,':')[0],' ')[1]);
		}
		cout<<line<<" SUM: "<< sum <<"\n";
	}
    }
    cout<<result;
    return 0;
}
       

