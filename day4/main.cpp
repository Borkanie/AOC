#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <vector>
#include <sstream>
#include <map>

std::vector<int> extractIntegers(const std::string& str) {
    std::vector<int> integers;
    std::istringstream iss(str);
    int number;

    while (iss >> number) {
        integers.push_back(number);
    }

    return integers;
}

std::vector<std::string> splitString(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::string temp;
    
    for (char ch : str) {
        if (ch == delimiter) {
            if (!temp.empty()) {
                result.push_back(temp);
                temp.clear();
            }
        } else {
            temp += ch;
        }
    }

    if (!temp.empty()) {
        result.push_back(temp);  // Add the last substring
    }

    return result;
}

void printVector(const std::vector<int> vector){
	std::cout<<std::endl;
	for(auto el : vector){
		std::cout<<el<<" ";
	}
	std::cout<<std::endl;
}

void printVector(const std::vector<std::pair<int,int>> vector){
	std::cout<<std::endl;
	for(auto el : vector){
		std::cout<<el.first<<","<<el.second<<" | ";
	}
	std::cout<<std::endl;
}

int main(){
	int result =0;
	std::ifstream file("input.txt");
	std::string line;
 	std::vector<int> lucky;
	std::vector<int> numbers;
	int index = 0;
	std::vector<std::pair<int,int>> factors;
	if (file.is_open()) {
			int factor = 1;
        	while (std::getline(file, line)) {
          		int stage = 0;
				int nr = 0;

            	std::vector<std::string> inputs = splitString(line, '|');
            	std::vector<int> extractedLucky = extractIntegers(splitString(inputs[0], ':')[1]);
            	std::vector<int> extractedNumbers = extractIntegers(inputs[1]);

            	lucky.insert(lucky.end(), extractedLucky.begin(), extractedLucky.end());
            	numbers.insert(numbers.end(), extractedNumbers.begin(), extractedNumbers.end());
			
				// will be used to count number of correct numbers
				nr = 0;
				//std::cout << "  Output:\n";
				for(auto number : numbers){
					for(auto luck : lucky){
						if(luck == number){
							nr++;
							break;
					
						}
					}
				}

				factors.push_back({nr,1});
				//std::cout<<nr<<std::endl;
				numbers.clear();
				lucky.clear();
        	}
			//factors.clear();
        	file.close();
			//result += factors[index];
    	} else {
        	std::cerr << "Unable to open file" << std::endl;
        	return 1;
    	}
		//std::cout<<factors.size();
		//printVector(factors);
		for(int i=0;i<factors.size();i++){
			
			result += factors[i].second;
			//std::cout<<factors[i].first<<std::endl;
			//printVector(factors);
			if(factors[i].first!=0){
				//std::cout<<factors[i].second<<std::endl;
				for(int j=1;j<=factors[i].first;j++){
					if(i+j>factors.size()){
						break;
					}
					factors[i+j].second += factors[i].second;
				}	
			}
		}
		std::cout << result ;
 		return 0;
	}

