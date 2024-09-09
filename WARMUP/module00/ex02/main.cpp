#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string ConvertUpper(const string &str){
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

string ConvertLower(const string &str){
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

int main(int argc, char *argv[])
{
    if(argc != 3){
        cerr << "invalid syntax -> ./convert {command} {string}\n";
        return 1;
    }
    string command = argv[1];
    string input = argv[2];
    string answer;
    if (command.compare("up")){
        answer = ConvertUpper(input);
    }else if (command.compare("down")){
        answer = ConvertLower(input);
    }else {
        cerr << "invalid command -> command should be up or down\n";
        return 1;
    }
    cout << answer << endl;
    return 0;
}
