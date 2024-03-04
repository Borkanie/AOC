#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

template <typename Range, typename T>
size_t index_of(Range const& range, T const& c) {
    using std::begin;
    using std::end;

    auto b = begin(range), e = end(range);
    auto match = std::find(b, e, c);

    return (e==match)? -1 : std::distance(b, match);
}

using namespace std;
const char cards[] = {'A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4','3','2'};
const int number_of_possible_cards = sizeof(cards)/sizeof(char);
int index_of(char c){
	for(int i=0;i<number_of_possible_cards;i++){
		if(cards[i]==c){
			return i;
		}
	}
	return 25;
}
template <typename arr>
void printArr(arr const range,int size) {
    for(int i=0;i<size;i++){
		cout<<range[i]<<",";
	}
	cout<<endl;
}

struct Hand{
	string cards;
	int bet;
	int hand_value;
	public:
	string print(){
		return cards + " " + to_string(bet) + " has value:" + to_string(hand_value);
	}
	
	// Overload < operator
    bool operator>(const Hand& other) const {
		if(this->hand_value > other.hand_value)
			return true;
		if(other.hand_value == this->hand_value)
		{
			for(int i=0;i<this->cards.size();i++){
				if(index_of(this->cards[i])<index_of(other.cards[i])){
					return true;					
				}
				if(index_of(this->cards[i])>index_of(other.cards[i])){
					return false;					
				}
			}
		}
		return false;
    }

	// Overload < operator
    bool operator<(const Hand& other) const {
		if(this->hand_value < other.hand_value)
			return true;
		if(other.hand_value == this->hand_value)
		{
			for(int i=0;i<this->cards.size();i++){
				if(index_of(this->cards[i])>index_of(other.cards[i])){
					return true;
				}if(index_of(this->cards[i])<index_of(other.cards[i])){
					return false;
				}
			}
		}
		return false;
    }

	 // Overload the << operator
    friend ostream& operator<<(std::ostream& os, const Hand& p) {
        os << p.cards + " " + to_string(p.bet) + " has value:" + to_string(p.hand_value)<< endl;
        return os; // Return the ostream object to enable chaining
    }
};


vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    
    return tokens;
}

void get_hand_rank(Hand* hand){
	hand->hand_value = 0;
	int card_numbers[number_of_possible_cards] = {} ; // we get list of zeros
	for(int i=0;i<hand->cards.size();i++){
		int index_of_current_character = index_of(hand->cards[i]);
		card_numbers[index_of_current_character]++;
	}
	//cout<<max<<" ";
	for(int i=0;i<number_of_possible_cards;i++){
		hand->hand_value += card_numbers[i]*card_numbers[i];
	}
}

Hand interpret_line(const string& input) {
    
	auto strings = split(input,' ');
	Hand hand;
	hand.cards = strings[0];
	hand.bet = stoi(strings[1]);
	get_hand_rank(&hand);
    return hand;
}

void quickSort(vector<Hand>& arr, int left, int right) {
    int i = left, j = right;
    Hand tmp;
    Hand pivot = arr[(left + right) / 2];

    /* Partition */
    while (i <= j) {
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i <= j) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    };

    /* Recursion */
    if (left < j)
        quickSort(arr, left, j);
    if (i < right)
        quickSort(arr, i, right);
}

int main(){	
int result =0;
	ifstream file("input.in");
	string line;
 	int index = 0;
	vector<Hand> hands;
	if (file.is_open()) 
		{
			int factor = 1;
        	while (getline(file, line)) {
				hands.push_back(interpret_line(line));
				//cout<<hands[index].print()<<endl;
				index++;
			}
			file.close();
		} else {
        	cerr << "Unable to open file" << endl;
        	return 1;
    	}

	//printArr(hands,hands.size());
	
	quickSort(hands,0,hands.size()-1);
	
	
	//printArr(hands,hands.size());
	
	for(int i=0;i<hands.size();i++){
		result+=hands[i].bet*(i+1);
		//cout<<hands[i] << " * "<<i+1 << endl;
	}
	//printArr(hands,hands.size());
	cout<<result;
	return 0;
}
