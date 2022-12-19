// RUN COMMAND: cls && echo COMPILING... && g++ -o aoc aoc.cpp && aoc.exe

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Folder {
    public:
        string name;
        string path;
        int size;
};

class Terminal {
    vector<string> instructions;
    vector<string> path;
    vector<Folder> folders;
    

    public: 
        void parseInstructions(string filename){
            string line;

            ifstream inputFile("input.txt");
            while (getline (inputFile, line)) {
                instructions.push_back(line);
            }

            inputFile.close();
        }

        void readInstructions(){

            Folder newFolder;
            newFolder.name = "root";
            newFolder.path = "root";
            newFolder.size = 0;

            folders.push_back(newFolder);
            
            for(int i = 0; i < instructions.size(); i++){
                string instruction = instructions[i];

                if(instruction.at(0) == '$'){
                    runCommand(instruction);
                }
                
                else if(instruction.substr(0,3) == "dir"){
                    handleFolder(instruction);
                }

                else if(isdigit(instruction.at(0))){
                    handleFile(instruction);
                }
            }

            char* part = getenv("part");
            if (part == NULL || string(part) == "PART1") {
                int sum = 0;

                for(int i = 0; i < folders.size(); i++){
                    if(folders[i].size <= 100000){
                        sum += folders[i].size;
                    }
                }
                cout << sum << endl;
            }
            else if (string(part) == "PART2") {
                int rootSize = folders[0].size;
                int missingFreeSpace =  rootSize - 40000000;

                int lowestValue = rootSize;

                for(int i = 0; i < folders.size(); i++){
                    if(folders[i].size >= missingFreeSpace){
                        if(folders[i].size < lowestValue){
                            lowestValue = folders[i].size;
                        }
                    }
                }

                cout << lowestValue << endl;
            } 
            else {
                cout << "Unknown part" << endl;
            }

            

            //  44.376.732
            //  70.000.000
            //   4.376.732
            
        }

    void runCommand(string instruction){
        string commandType;
        string commandVariable;

        commandType = instruction.substr(2, 2);
        int instructionLenght = instruction.size();

        if(instructionLenght > 4){
            commandVariable = instruction.substr(5, instructionLenght - 4);
        }
        else if(commandType == "cd"){
            handleCommand_cd(commandVariable);
        }
    }

    void handleFile(string instruction){

        int instructionSize = instruction.size();
        int splitIndex = instruction.find_first_of(" ");
        
        string fileSize_str = instruction.substr(0, splitIndex);
        string fileName = instruction.substr(splitIndex + 1, instructionSize - splitIndex - 1);
        int fileSize_int = stoi(fileSize_str);

        for (int i = 0; i < folders.size(); i++){
            string joinedPath = joinPath();
            
            if(folders[i].path == joinedPath){
                vector<string> pathParts = splitPath();

                while(pathParts.size() > 0){
                    string newPath = joinString(pathParts, "/");

                    for(int k = 0; k < folders.size(); k++){
                        if(folders[k].path == newPath){
                            folders[k].size += fileSize_int;
                        }
                    }

                    pathParts.pop_back();
                }

                //break;
            }    
        }
    }

    void handleFolder(string instruction){
        int instructionSize = instruction.size();
        string folderName = instruction.substr(4, instructionSize - 4);

        bool folderExists = false;

        for (int i = 0; i < folders.size(); i++){
            if(folders[i].path == joinPath() + "/" + folderName){
                folderExists = true;
            }    
        }

        if(!folderExists){
            Folder newFolder;
            newFolder.name = folderName;
            newFolder.path = joinPath() + "/" + folderName;
            newFolder.size = 0;

            folders.push_back(newFolder);
        }
    }

    void handleCommand_cd(string commandVariable){
        if(commandVariable == ".."){
            path.pop_back();
            //cout << "OUT" << endl;
        }
        else if(commandVariable != ".."){
            if(commandVariable == "/") {
                path.push_back("root");    
            }
            else{
                path.push_back(commandVariable);
            }
            //cout << "IN: " + commandVariable << endl;
        }
    }

    string joinString(vector<string> strings, string join){
        string joinedString;
        for(int i = 0; i < strings.size(); i++){
            joinedString.append(strings[i] + join);
        }

        return joinedString.substr(0, joinedString.size() -1);
    }

    string joinPath(){
        string joinedPath;
        for(int i = 0; i < path.size(); i++){
            joinedPath.append(path[i] + "/");
        }

        return joinedPath.substr(0, joinedPath.size() -1);
    }

    vector<string> splitPath(){
        vector<string> splittedPath;
        string _path = joinPath();

        int count = 0;

        while(_path.size() > 0){
            int splitIndex = _path.find_first_of("/");
            if(splitIndex == -1){
                splittedPath.push_back(_path);
                break;
            }
            string pathPart = _path.substr(0, splitIndex);

            splittedPath.push_back(pathPart);
            _path.erase(0, splitIndex + 1);
        }

        return splittedPath;
    }
};

int main(){
    Terminal terminal;
    terminal.parseInstructions("input.txt");
    terminal.readInstructions();

    return 0;
}
