#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctype.h>
#include <utility>

std::vector<std::vector<char>> matrix;

int getNumber(std::pair<int,int> position){
    int line = position.first;
    int column = position.second;
    int result = 0;

    std::vector<char> digits;
    // Accumulate digits before the asterisk
    int place = 1;
    for(int j = column; j >= 0 && isdigit(matrix[line][j]); j--){
        digits.insert(digits.begin(),matrix[line][j]);
    }

    // Accumulate digits after the asterisk
    for(int j = column + 1; j < matrix[line].size() && isdigit(matrix[line][j]); j++){
        digits.push_back(matrix[line][j]);
    }

    for(char c : digits){
        result = result*10 + (c-'0');
    }

    return result;
}


std::vector<std::pair<int,int>> checkForNumbers(int line, int column){
    std::vector<std::pair<int,int>> numbers;
    for(int i = -1; i <= 1; i++){
        if(line + i < 0 || line + i >= matrix.size())
            continue;
        for(int j = -1; j <= 1; j++){
            if(column + j < 0 || column + j >= matrix[line + i].size())
                continue;
            if(i == 0 && j == 0)  // Skip the gear position itself
                continue;
            if(isdigit(matrix[line + i][column + j])){
                numbers.push_back({line + i, column + j});
                // Skip other digits of the same number
                while(column + j + 1 < matrix[line + i].size() && isdigit(matrix[line + i][column + j + 1])){
                    j++;
                }
            }
        }
    }
    return numbers;
}


int main() {
    std::ifstream file("input.txt");
    std::string line;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            // Create a vector of chars from the line
            // concatenate a dot to get rifd of last nuber
            line+=".";
            std::vector<char> row(line.begin(), line.end());
            // Add the row to the matrix
            matrix.push_back(row);
        }
        file.close();
    } else {
        std::cerr << "Unable to open file" << std::endl;
        return 1;
    }

    long result =0;
    for (int i=0;i<matrix.size();i++) {
        for (int j=0;j<matrix[i].size();j++) {
            // search fo star
            if(matrix[i][j] == '*'){
                auto numbers = checkForNumbers(i,j);
                // a gear needs exactly two numbers nearby
                std::vector<std::pair<int,int>> lineNumberPairs;
                for(auto n : numbers){
                    auto n1 = getNumber(n);
                    bool copycat = false;
                    //std::cout<<numbers.size()<<std::endl;
                    for(auto pair : lineNumberPairs){
                        if(pair.first == n.first && n1 == pair.second){
                            copycat = true;
                            break;
                        }
                    }
                    if(!copycat)
                        lineNumberPairs.push_back({n.first,n1});
                    // do not get the same number twice;
                    
                }
                if(lineNumberPairs.size()==2){
                    result+=lineNumberPairs[0].second*lineNumberPairs[1].second;
                }
            }
            
        }
        
    }
    std::cout<<result << std::endl;
    return 0;
}
