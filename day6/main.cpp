#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    
    return tokens;
}

vector<int> extractIntegers(const string& input) {
    vector<int> integers;
	vector<string> inp = split(input,':');
    vector<string> numbers = split(inp[1],' ');
	for(int i=0;i<numbers.size();i++)
	{
		if(numbers[i].size()>0)
		{	
			integers.push_back(stoi(numbers[i]));
			
		}
	}

    return integers;
}

struct Race{
	int total;
	int best;
};

int travel(int total_time, int hold){
	if(hold >= total_time)
		return 0;
	int travel_time = total_time - hold;
	int speed = hold;
	return speed*travel_time;

}
// dist = vit * t_ramas
// vit = total - t_ramas
// dist = t_ramas* ( total - t_ramas)
// dist = -t_ramas^2 + total*t_ramas
// - t_ramas^2 +total*t_ramas - dist = 0
// we look for max for a second order function with negaative coefficient tot he second order component soo max = Df/Dt = 0
// -2*t_ramas + total = 0 => t_ramas = total/2 
// Sooo for every run maximum distance is achieved when hold time is total/2
int how_many_times_better (Race race){
	int result = 0;
	for(int i=0;i<=race.total;i++){
		if(travel(race.total,i) > race.best)
			result ++;
	}
	return result;
}

int main(){	
	ifstream file("input.in");
    string str[2]; 
	vector<int> firstRow;
	vector<int> secondRow;
    for(int i=0;i<2;i++){
		getline(file, str[i]);
	}
	firstRow = extractIntegers(str[0]);
	secondRow = extractIntegers(str[1]);
	vector<Race> races;
	for(int i = 0;i< firstRow.size(); i++){
		Race race;
		race.total = firstRow[i];
		race.best = secondRow[i];
		races.push_back(race);
	}
	long result = 1;
	for(int i=0; i<races.size(); i++){
		result *= how_many_times_better(races[i]);
	}
	cout<<result<<endl;
	return result;
}
