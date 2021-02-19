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

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream fin(filename);
    string text;
    int i = 0;
    int a,b,c;
    char name[100];
    char format[] ="%[^:]: %d %d %d";
    while(getline(fin,text))
    {
        const char * textConverted = text.c_str();
        sscanf(textConverted,format,name,&a,&b,&c);
        string nameConverted = name;
        names.push_back(nameConverted);
        scores.push_back(a+b+c);
        grades.push_back(score2grade(a+b+c));
        i++;
    }
    
}

void getCommand(string &command,string &key){
    string text;
    char format[] = "%s %[^\n]";
    char command2[50];
    char key2[50];
    cout << "Please input your command: ";
    getline(cin,text);
    const char * textConverted = text.c_str();
    sscanf(textConverted,format,command2,key2); 
    command = command2;
    key = key2;
}

void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key){
    unsigned int i = 0;
    bool trigger = 0;
    cout << "---------------------------------\n";
    while(i < names.size())
    {
        if(key == toUpperStr(names[i]))
        {
            cout << names[i] << "'s score = " << scores[i] << "\n";
            cout << names[i] << "'s grade = " << grades[i] << "\n";
            trigger = 1;
        }
        i++;
    }
    if(!trigger)
    {
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key){
    unsigned int i = 0;
    bool trigger = 0;
    cout << "---------------------------------\n";
    while(i < grades.size())
    {
        if(key[0] == grades[i])
        {
            cout << names[i] << " (" << scores[i] << ")\n";
            trigger = 1;
        }
        i++;
    }
    if(!trigger)
    {
        cout << "Cannot found.\n";
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
