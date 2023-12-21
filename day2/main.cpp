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

vector<int> numberOfBallsInPick(const string pick){

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

vector<int> getNumberOfBalls(string pick){
	vector<int> balls = {0,0,0};
	
	vector<string> entrys = splitString(pick, ',');
	for(int i=0;i<entrys.size();i++){
		vector<string> entryElements =splitString(entrys[i],' ');
		//cout<<entryElements[0] << "  "<< entryElements[1]<<"  "<< entryElements[2]<< "\n";	
		balls[findStringIndex(entryElements[2])] = stoi(entryElements[1]);
	}
	//cout<< "done";
	return balls;
}

vector<int> minimumNumberOfBalls(const vector<string> input){
	vector<int> minBalls = {1,1,1};
	for(int index=0;index<input.size();index++){
	     string pick = input[index];
	     vector<int> currentBalls = getNumberOfBalls(pick);
	     for(int i=0;i<minBalls.size();i++){
		     if(minBalls[i] < currentBalls[i])
			     minBalls[i] = currentBalls[i];
	     
	     }
    	}
	cout<< minBalls[0] <<"|"<<minBalls[1]<<"|"<<minBalls[2]<<"\n";
	return minBalls;
}

int powerOfMinimum(const vector<string> input){
	vector<int> minimums = minimumNumberOfBalls(input);
	
	return minimums[0]*minimums[1]*minimums[2];
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
	        sum += powerOfMinimum(input);
	
		cout<<line<<" SUM: "<< sum <<"\n";
	}
    }
    cout<<result;
    return 0;
}
       

