#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct STADIUM {
	string name;
	int capacity;
	string city;
	string clubs;
	string renovations;
	string record_attendance;
	string address;
};

struct Node
{
	STADIUM key;
	Node* left;
	Node* right;
};

int myStoi(string str) {
	string tmp = "";
	for(int i = 0; i < str.size(); i++) {
		if(str[i] != ' ') tmp += str[i];
	}
	return atoi(tmp.c_str());
}

void parseCSV(string line, string elements[]) {
	int index = 0;
	bool flag = false;
	string str;

	for(int i = 0; i < line.length(); i++) {
		char ch = line[i];
		if(ch == '\"') 
		{
			if(i == line.length() - 1) elements[index++] = str;
			flag = !flag;	
		}
		else if(ch == ',' && !flag) {
			elements[index++] = str;
			str.clear();
		} else str += ch;
	}
}

STADIUM readLine(string line) {
	STADIUM stadium;
	string elements[7];
	parseCSV(line, elements);

	stadium.name = elements[0];
	string capacity = elements[1];
	stadium.capacity = myStoi(capacity);
	stadium.city = elements[2];
	stadium.clubs = elements[3];
	stadium.renovations = elements[4];
	stadium.record_attendance = elements[5];
	stadium.address = elements[6];

	return stadium;
}

vector<STADIUM> readFile(string filename) {
	vector<STADIUM> res;
	ifstream ifs(filename);
	if(!ifs.is_open()) {
		cout << "File error";
		return res;
	}

	string tmp;
	getline(ifs, tmp);
	while(!ifs.eof()) {
		getline(ifs, tmp);
		STADIUM stadium = readLine(tmp);
		if (stadium.name.empty()) continue;
		res.push_back(stadium);
	}

	ifs.close();
	return res;
}

void printStadium(vector<STADIUM> stadiums) {
	for (int i = 0; i < stadiums.size(); ++i) {
		cout << i + 1 << " Name: " << stadiums[i].name << "\n"
		     << "Capacity: " << stadiums[i].capacity << "\n"
		     << "City: " << stadiums[i].city << "\n"
		     << "Clubs: " << stadiums[i].clubs << "\n"
		     << "Renovations: " << stadiums[i].renovations << "\n"
		     << "Record Attendance: " << stadiums[i].record_attendance << "\n"
		     << "Address: " << stadiums[i].address << "\n"
		     << "------------------------" << "\n";
	}
}

void printBT(const string& prefix, const Node* node, bool isLeft)
{
    if( node != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "L--" );

        // print the value of the node
        cout << node->key.capacity << endl;

        // enter the next tree level - left and right branch
        printBT( prefix + (isLeft ? "|   " : "    "), node->left, true);
        printBT( prefix + (isLeft ? "|   " : "    "), node->right, false);
    }
}

void insert(Node* &root, STADIUM x)
{
    if(!root)
    {
        root = new Node{x, NULL, NULL};
        return;
    }
    if(x.capacity > root->key.capacity) insert(root->right, x);
    else if(x.capacity < root->key.capacity) insert(root->left, x);
    else return;
}

Node* createTree(vector<STADIUM> stadiums)
{
	Node* res = NULL;
	for(int i = 0; i < stadiums.size(); i++)
	{
		insert(res, stadiums[i]);
	}
	return res;
}

int main() {
	vector<STADIUM> stadiums = readFile("stadium.csv");
	Node* tree = createTree(stadiums);
	string prefix;
	bool isLeft;
	printBT(prefix, tree, isLeft);
	//printStadium(stadiums);
	return 0;
}
  
