#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;
//used to concatenate strings inside vector to one string
string combineStrings(vector<string> v){
	string userText;
	for (unsigned i = 0; i < v.size(); ++i){
		userText += v.at(i);
		userText += " ";
	}
	return userText;
}
int longestWord(vector<string> v){
	int min = -1; //small value to be overwritten later
	string userText = combineStrings(v);
	string temp;

	//clears content of vector to be filled later with single words
	v.clear();

	// fills vector with only words
	unsigned length = userText.length();
	for (unsigned i = 0; i < length; ++i){
		if (isalpha(userText.at(i)) && !isdigit(userText.at(i))){
			temp += userText.at(i);
		} else {
			v.push_back(temp);
			temp = "";
		}
	}

	//finds largest length of word
	for (unsigned i = 0; i < v.size(); ++i){
		int currLen = v.at(i).length();
		if (currLen > min)
			min = currLen;
	}
	return min;
}
//finds the empty space in the text to begin separation of string to each line
//variables rtn, index, finished are of reference type in order to have modified values that can be used in align()
void findEmptySpace(string userText, int width, string& rtn, int& index, bool& finished){
	if (userText.length() > width){
		for (int j = width; j > 0; --j){
			if (isspace(userText.at(j))){
				rtn += userText.substr(0, j+1);
				index = j+1;
				break;
			}
		}
	} else if (userText.length() < width && userText.length() > 0){
		for (int j = userText.length()-1; j > 0; --j){
			if (isspace(userText.at(j))){
				rtn += userText.substr(0, j+1);
				index = j+1;
				finished = true;
				break;
			}
		}
	} else { finished = true; }

}
void align(string alignment, int width, vector<string> v){

	string rtn;
	string userText = combineStrings(v);
	int index = 0;
	bool finished = false;

	if (alignment == "left"){
		while(!finished){
			rtn = "";
			userText = userText.substr(index); //sets userText to the string after alignment by row

			if (userText.length() == 0) break;

			findEmptySpace(userText, width, rtn, index, finished);

			rtn = rtn.substr(0, rtn.length()-1);
			//loop to add spaces for left alignment
			if (rtn.length() < width){
				for (int k = rtn.length(); k < width; ++k){
					rtn += " ";
				}
			} else {
				rtn = rtn.substr(0, width);
			}

			cout << "|" << rtn << "|" << endl;
		}
	} else if (alignment == "right") {
		while(!finished){

			if (width == userText.length()){
				cout << "| " << userText.substr(0, userText.length() - 1) << "|" << endl;
				break;
			}
			rtn = "";
			userText = userText.substr(index);

			if (userText.length() == 0) break;

			findEmptySpace(userText, width, rtn, index, finished);


			rtn = rtn.substr(0, rtn.length()-1);

			//loop to add spaces for right alignment
			string temp;
			for (int i = 0; i < (width - rtn.length()); ++i){
				temp += " ";
			}
			temp += rtn;

			cout << "|" << temp << "|" << endl;
		}
	} else if (alignment == "center"){
		while(!finished){
			if (width == userText.length()){
				cout << "| " << userText.substr(0, userText.length() - 1) << "|" << endl;
				break;
			}
			rtn = "";

			userText = userText.substr(index);

			if (userText.length() == 0) break;

			findEmptySpace(userText, width, rtn, index, finished);

			rtn = rtn.substr(0, rtn.length()-1);

			int spaceLeft = (width - rtn.length()) / 2;
			double spaceRight = (round((width - rtn.length()) / (2+0.0)));

			//loop to add spaces for right alignment
			string temp;
			for (int i = 0; i < spaceLeft; ++i){
				temp += " ";
			}
			temp += rtn;

			for (int i = 0; i < spaceRight; ++i){
				temp += " ";
			}

			cout << "|" << temp << "|" << endl;
		}
	}
}
int main() {
	vector<string> userInputs;

	//loop to get inputs from user
	while (true){
		string x; // placeholder for input
		cout << "> ";
		getline(cin, x);

		if (x.length() < 1) break; //checks if blank line or not
		userInputs.push_back(x); //adds each line of text to vector of strings
	}

	//loop for editor
	bool looped = false;
	while (true) {
		string alignment, border; int chars;
		cout << "Enter left|right|center and paragraph width:" << endl;
		//in case input was invalid, clear inputs
		if (looped){ //ignore first loop because it takes double input
			cin.clear();
			cin.ignore(100000, '\n'); //ignore up to 100000 characters of input up to next line
		}
		cin >> alignment >> chars;

		//error checking
		if ((alignment != "left" && alignment != "right" && alignment != "center") || cin.fail()){
			cout << "Invalid justification command..." << endl; looped = true;
			continue;
		}
		if (chars == 0 && !isalpha(chars)) {cout << "Bye..." << endl; break;} //end loop

		//check if width is larger than length of the longest word
		if (chars < longestWord(userInputs)) {
			cout << "Paragraph width too small to fit the longest word of size " << longestWord(userInputs) << "..." << endl;
		}
		else{ // border generation
			border += "+";
			for (int i = 1; i <= chars; ++i){
				if (i % 10 == 0)
					border += "+";
				else border += "-";
			}
			border += "+";
			cout << border << endl;

			//actual text is output
			if (chars == combineStrings(userInputs).length() && alignment == "left"){
				cout << "|" << combineStrings(userInputs) << "|" << endl;
			} else {
				align(alignment, chars, userInputs);
			}

			cout << border << endl;
		}
		looped = true;
	}
	return 0;

}
