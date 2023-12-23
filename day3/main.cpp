#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctype.h>

std::vector<std::vector<char>> matrix;

bool checkForSign(int line, int column){
    for(int i=-1;i<=1;i++){
        if(line+i <0 || line+i >= matrix.size())
            continue;
        for(int j=-1;j<=1;j++){
            if(column+j <0 || column+j >= matrix[i].size())
                continue;
            if(!isdigit(matrix[line+i][column+j]) && matrix[line+i][column+j]!='.'){
                return true;
            }
        }
    }
    return false;
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

    // Display the matrix
    for (const auto& row : matrix) {
        for (char c : row) {
            std::cout << c;
        }
        std::cout << std::endl;
    }

    int result =0;
    for (int i=0;i<matrix.size();i++) {
        int number = 0;
        bool hasSign = 0;
        for (int j=0;j<matrix[i].size();j++) {
            if(isdigit(matrix[i][j])){
                number = number * 10 + (matrix[i][j] - '0');
                if(!hasSign){
                    hasSign = checkForSign(i,j);
                }
            }
            else{
                if(number>0){
                    if(hasSign){
                        result += number;
                        std::cout<<number <<std::endl;
                    }
                    number = 0;
                    hasSign = false;
                }
            }
        }
        
    }
    std::cout<<result << std::endl;
    return 0;
}
