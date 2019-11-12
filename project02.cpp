#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include<iostream>
#include<map>
using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::cin;
using std::ifstream;
using std::map;


vector<string> create_vector() {
	string line;
	//cout << "vector" << endl;
	vector<string> passwords;
	std::ifstream myfile("common_passwords.txt");
	while (std::getline(myfile, line)) {
		//cout << line << endl;
	// Line contains string of length > 0 then save it in vector
		if (line.size() > 0) {
			//cout << "Adding to vector..." << endl;
			passwords.push_back(line);
		}
	}
	//cout << "done creating vector" << endl;
	return passwords;
}

auto create_map(string input, vector<string> passwords) {
	map<string, int> values;
	int input_length = (int)input.length();

	//getting difference
	for (int i = 0; i < (int)passwords.size(); i++) {
		//cout << passwords[i] << endl;
		int difference = 0;
		//finding difference in length:
		int size_diff = 0;
		size_diff = input_length - (int)(passwords[i].length());
		if (size_diff < 0) { //flips size_diff if it's negative
			size_diff = size_diff * (-1);
		}
		//cout << "size diff: " << size_diff << endl;
		difference += size_diff;
		//cout << "difference 1: " << difference << endl;
		//password from file is smaller than the input password
		if ((int)passwords[i].length() < input_length) {
			//checks each character
			//cout << "password from file is smaller than t he input password (1)" << endl;
			for (int x = 0; x < (int)passwords[i].length(); x++) {
				if (passwords[i][x] != input[x]) {
					difference += 1;
				}
			}
			//cout << "difference after (1): " << difference << endl;
		}
		//password from file is larger or equal to length of the input:
		else if (input_length <= (int)passwords[i].length()) {
			//cout << "password from file is larger than length of input (2)" << endl;
			for (int y = 0; y < input_length; y++) {
				if (input[y] != passwords[i][y]) {
					difference += 1;
				}
			}
			//cout << "difference after (2): " << difference << endl;
		}
		//length of password from file and input are equal:

		
		string& wordpass = passwords[i];
		values.insert(make_pair(wordpass, difference));
	}
	return values;
}

void print_similar_passwords(map<string, int> passwords) {
	vector<string>most_similar;
	int count = 0;
	int difference = 0;
	bool found = false;
	vector<string> print;
	//while loop continues until count is found
	while (!found) {
		//for loop to iterate through all map elements
		for (auto const& i : passwords) {
			difference = (int)(i.second);
			//cout << "difference: " << difference << endl;
			if (difference == count) {
				string str = i.first;
				//cout << "str1:" << str << endl;
				print.push_back(i.first);
				found = true;
				
			}
		}
		count++;
		//cout << "count: " << count << endl;
	}
	for (int itr = 0; itr < (int)print.size(); itr++) {
		cout << print[itr] << ", ";
	}
	cout << '\n';
	auto diff = passwords[ print[0] ];
	cout << "All of which are " << diff << " character(s) different." << endl;
}

int main() {
	auto vec = create_vector();
	string InputPass;
	cout << "Give me a password: ";
	cin >> InputPass;
	cout << "You provided a password of " << InputPass << endl;
	cout << "The most similar passwords to " << InputPass << " are:" << endl;
	auto pass_map = create_map(InputPass, vec);
	print_similar_passwords(pass_map);

}
