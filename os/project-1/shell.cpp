#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <queue>
#include <regex>
#include <fstream>
using namespace std;

int main(){

    //initializing the variables that will be used during the program.
    string userName = getlogin(); // saves the user name in the variable;
    string command; // holds the string that the user enters to the shell
    string tmp; // some arbitrary variable that holds temporary strings 
    bool didIDO = false; // after a dididothat command shell uses this variable to check what it should return
    queue<string> history; // command history is saved in a queue
    int historyLength = 0; // saves the lenght in order to clean old commands after the count pasts 15
    char hostname[32]; 
    gethostname(hostname, size(hostname)); // saves the name of the computer
    string textEditor = getenv("EDITOR"); // saves the EDITOR environment variable as a string


    while(true){

        cout << userName << " >>> "; // prints shell line
        getline(cin, command); // takes user input

        if(command == ""){ // if there is no input skip to the next input
            continue;
        }

        if(historyLength < 15){ // as long as there are less than 15 commands in history,
            history.push(command); // adds the input to queue without deleting old command
            historyLength++;       // and increments the length
        } else { 
            history.pop(); //otherwise deletes the oldest command before adding the new one
            history.push(command);
        }

        if(command == "exit"){ // exits with return code 0 in case the user inputs exit
            exit(0);
        }

        if(command == "listdir"){ // listdir command calls for the ls program
            system("ls");
        } else if(command == "mycomputername"){

            cout << hostname << endl; //prints the name of the computer that is saved in hostname variable

        } else if(command == "hellotext"){
            
            if(textEditor == ""){
                system("gedit"); // if there is no editor set in environment variable calls gedit
            } else {
                system("$EDITOR"); // calls program in the EDITOR environment variable
            }

        } else if(command == "whatsmyip"){

            system("hostname -I | awk '{print $1}'"); // prints the first of the two ips that returned by hostname -I command
            
        } else if(regex_match(command, regex("^printfile [^ \t\n]*$"))){

            ifstream input(command.substr(command.find(" ")+1, command.length())); // gets the filename using string methods and then opens it

            while(getline(input, tmp)){ // prints a line everytime user presses enter
                cout << tmp;
                cin.get(); // waits until enter
            }

            input.close();

        } else if(regex_match(command, regex("^printfile [^ \t\n]* > [^ \t\n]*$"))){
            // gets the filename between "printfile" and > symbol and opens it as input file
            ifstream input(command.substr(command.find(" ")+1, command.find(">")-command.find(" ")-2)); 
            // gets the filename after the > symbol and opens it as output file
            ofstream output(command.substr(command.rfind(" ")+1,command.length()));

            if(getline(input, tmp)){ // copies the first line to the output (first line is out of the loop to prevent one extra empty line)
                output << tmp;
            }

            while(getline(input, tmp)){ // copies the rest of the lines to the output
                output << endl;
                output << tmp;
            }

            input.close();
            output.close();

        } else if(regex_match(command,  regex("^dididothat .*$"))){

            string query; // holds the argument of the command

            if(regex_match(command,  regex("^dididothat \".*\"$"))){ 
                // if the dididothat command uses quotation marks in the arguments, ignores them (apart from the ones that is included inside the command)
                query = command.substr(command.find("\"")+1, command.rfind("\"")-command.find("\"")-1);
            } else {
                query = command.substr(command.find(" ")+1, command.length());
            }

            for(int i = 0; i < 15; i++){ // checks through the queue to check if the argument is used as a command before

                tmp = history.front(); // gets the last command

                if(tmp == query){ //checks if it is used before
                    didIDO = true; //if it is sets the flag true
                }

                history.pop(); // pops the last command to check previous elements
                history.push(tmp); //pushes back to the back of the queue (after 15 iteration the queue returns to its initial state)

            }

            if(didIDO){ // writes the output according to the flag
                cout << "yes\n";
                didIDO = false; // returns the flag to false for future dididothat commands
            } else {
                cout << "no\n";
            }

        }

    }

}
