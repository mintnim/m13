#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename,vector<string> &names,vector<int> &scores,vector<char> &grades){
	ifstream source(filename.c_str());

	string textline;
	vector<string> files;
	
	while(getline(source,textline)){		
		files.push_back(textline);
	}
	source.close();
	for(unsigned i=0; i<files.size();i++){
		char name[100];
		char format[] = "%[^:]: %d %d %d";
		int a,b,c;
		sscanf(files[i].c_str(),format,name,&a,&b,&c);
		
		names.push_back(name);
		scores.push_back(a+b+c);
		grades.push_back(score2grade(a+b+c));
	}
	

}

void getCommand(string &command,string &key){
	cout << "Please input your command: ";
	string input;
	getline(cin,input);
	char format[] = "%s %[^\n]";
	char k[100];
	char s[100];
	sscanf(input.c_str(),format,s,k);
	key = k;
	command = s;
	
}

void searchName(vector<string> names,vector<int> scores,vector<char> grades,string key){
	cout << "---------------------------------\n";
	for(unsigned int i = 0; i<names.size() ;i++){
		if(toUpperStr(names[i]) == key){
            cout << names[i] << "'s score = " << scores[i] << "\n";
            cout << names[i] << "'s grade = " << grades[i] << "\n";
            cout << "---------------------------------\n";
            return;
		}
	}
	cout << "Cannot found.\n";
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> names,vector<int> scores,vector<char> grades,string key){
	cout << "---------------------------------\n";
	for(unsigned int i = 0; i<names.size() ;i++){
		if(grades[i] == key[0])
            cout << names[i] << " (" << scores[i] << ")\n";
	}
	cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}