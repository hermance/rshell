#include <iostream>
#include <string>
#include <alloca.h>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <vector>
using namespace std;
//.h doesn't work, so delaration here for the moment
string CleanString(string, char);
vector<string> Split(string);
vector <vector <string> > SplitCmd(vector<string>);
int main(int argc, char ** argv){
string in;
string out;
vector<string> arg;
vector <vector <string> > args; //vector of commands
while (out !="exit"){
    cout<<"$ ";
    std::getline(cin,in);
    arg=Split(in);
    args = SplitCmd(arg); // we have here a list of command with their args
    for(int j=0; j< args.size();j++)
    {
        //conversion zone
        char * argFinal[args[j].size()];
        for(int k =0; k<args[j].size();k++){
            argFinal[k]=(char*)args[j][k].c_str();
        }
        if(strcmp(argFinal[0],"exit") == 0)
        {
            out = "exit";
            break;
        }
        else{
            argFinal[args[j].size()]=NULL; //last arg must be null
            int pid = fork(); // for the process to be able to do the execvp 
            if(pid ==1){
                perror("fork failed");//if the fork failed
            }
            else if(pid==0){
    	    //child process
                if(execvp(argFinal[0],argFinal) !=0){
        	        perror("error in execvp");
                }
           /* else if(in =="quit")
            {
                exit(0);//quit the process if quit is typed
            }*/
            exit(0);
            }
            else{
                 //parent process
                wait(NULL);//wait till the child is finished
            }
        }
    }
}
return 0;
}
vector <vector <string> > SplitCmd(vector<string> arg){
vector <vector <string> > args;
vector<string> splitedArg;
arg.push_back(" ");
for(vector<string>::iterator it = arg.begin(); it !=arg.end();++it){
  bool hashtag = false;
   if (it[0][0]==';'&&!hashtag){
    	args.push_back(splitedArg);
    	splitedArg.clear();
        it[0] = CleanString(it[0],';');
        splitedArg.push_back(*it);
    }
    else if(it[0][0]=='#'&&!hashtag){
    	if(splitedArg.size()>1 && !hashtag)
    	{
    		//del last space
    	//	splitedArg[splitedArg.size()-1] = CleanString(splitedArg[splitedArg.size()-1],' ');
        //args.push_back(splitedArg);
        splitedArg.erase(splitedArg.end());
       /** for(int i=0; i< splitedArg.size();i++){
            //splitedArg[i] = CleanString(splitedArg[i],' ');
            
            cout<<"splited arg : '"<<splitedArg[i]<<"'"<<endl;
        }*/
        
        args.push_back(splitedArg);
    	}
    	
        splitedArg.clear();
        splitedArg.push_back("echo");
        it[0] = CleanString(it[0],'#');
        splitedArg.push_back(*it);
        args.push_back(splitedArg);
        hashtag =true;
        splitedArg.clear();
    }
    else if(it[0]==" "&&splitedArg.size()>0 && !hashtag)
    {
        args.push_back(splitedArg);
    }
    else{
        splitedArg.push_back(*it);
    }
}
return args;
}
vector<string> Split(string input){
input.push_back(' ');//to be able to go in the if for the end of the text
vector <string> arg;
char currentChar;
string comm;
string splitedPiece;
bool testHashtag = false;
for(string::iterator it = input.begin(); it != input.end();++it)
{
    currentChar =*it;
    if((currentChar==' '||currentChar==';')&&splitedPiece.size()>1 && !testHashtag )//if the it arrives to a space and the size of the piece of string if greater than 2 char
    {
        arg.push_back(splitedPiece);//add this piece of text to the vector
        splitedPiece.clear();//clean the piece to do another one to fill it again
        /*if(currentChar='#'){
            testHashtag=true;
            comm.push_back(*it);
        }*/
    }
    if(testHashtag && it == input.end()-1)
    {
        arg.push_back(comm);//we add the big comment to the list of arg
    }
    if((currentChar==' '||currentChar=='\t') && splitedPiece.size() <= 1&& it != input.end()-1 && !testHashtag)
    {
        //if there is a lonely space
        // we go into that if so we dont go into the else, so the space is not taken in the arg, so this is what I want. I'm sad to let an if empty.
    }
    else{
    	
        if(currentChar =='#')
        {   
            testHashtag =true;
            arg.push_back(splitedPiece);
            splitedPiece.clear();
            comm.push_back(*it);
        }
        if(testHashtag)
        {
            comm.push_back(*it);
        }
        else
        {
            splitedPiece.push_back(*it);//add the current char to the plited piece of tex to make an arg, between two spaces => it s an arg we are filling
        }
  }
}
return arg;
}

string CleanString(string input, char param){
string finalInput = new char[input.size()];
finalInput = input;
finalInput.erase(remove(finalInput.begin(),finalInput.end(),param),finalInput.end());
return finalInput;
//remove the " of the input, avoiding injections
}
