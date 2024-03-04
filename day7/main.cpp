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
		if(this->cards.size() != other.cards.size())
			return false;
		if(this->hand_value > other.hand_value)
			return true;
		if(other.hand_value > this->hand_value)
			return false;
		for(int i=0;i<this->cards.size();i++){
			if(index_of(cards,this->cards[i])>index_of(cards,other.cards[i])){
				return true;
			}
		}
		return false;
    }

	// Overload < operator
    bool operator<(const Hand& other) const {
		if(this->cards.size() != other.cards.size())
			return true;
		if(this->hand_value < other.hand_value)
			return true;
		if(other.hand_value < this->hand_value)
			return false;
		for(int i=0;i<this->cards.size();i++){
			if(index_of(cards,this->cards[i])<index_of(cards,other.cards[i])){
				return true;
		}
	}
		return false;
    }

	 // Overload the << operator
    friend ostream& operator<<(std::ostream& os, const Hand& p) {
        os << p.cards + " " + to_string(p.bet) + " has value:" + to_string(p.hand_value);
        return os; // Return the ostream object to enable chaining
    }
};

char cards[] = {'A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4','3','2'};

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
	int card_numbers[sizeof(cards)/sizeof(char)] = {} ; // we get list of zeros
	int max=0;
	for(int i=0;i<hand->cards.size();i++){
		int index_of_current_character = index_of(cards,hand->cards[i]);
		card_numbers[index_of_current_character]++;
		//cout<<"found "<<hand->cards[i]<<" at "<< index_of_current_character<<endl;
		if(card_numbers[index_of_current_character]>max){
			max = card_numbers[index_of_current_character];
			//printArr(card_numbers,sizeof(card_numbers)/sizeof(int));
	
		}
	}
	//cout<<max<<" ";
	hand->hand_value = max;
}

Hand interpret_line(const string& input) {
    
	auto strings = split(input,' ');
	Hand hand;
	hand.cards = strings[0];
	hand.bet = stoi(strings[1]);
	get_hand_rank(&hand);
    return hand;
}

bool greater(Hand hand_1,Hand hand_2){
	if(hand_1.hand_value > hand_2.hand_value)
		return true;
	if(hand_2.hand_value > hand_1.hand_value)
		return false;
	for(int i=0;i<hand_1.cards.size();i++){
		if(index_of(cards,hand_1.cards[i])>index_of(cards,hand_2.cards[i])){
			return true;
		}
	}
	return false;
}

void quickSort(vector<Hand>& arr, int left, int right) {
    int i = left, j = right;
    Hand tmp;
    int pivot = arr[(left + right) / 2].hand_value;

    /* Partition */
    while (i <= j) {
        while (arr[i].hand_value < pivot)
            i++;
        while (arr[j].hand_value > pivot)
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
				cout<<hands[index].print()<<endl;
				index++;
			}
			file.close();
		} else {
        	cerr << "Unable to open file" << endl;
        	return 1;
    	}

	printArr(hands,hands.size()-1);
	quickSort(hands,0,hands.size()-1);

	printArr(hands,hands.size()-1);
	return 0;
}
