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
//#include <src/main.h>
using namespace std;
//.h doesn't work, so delaration here for the moment
string CleanString(string);
vector<string> Split(string);
vector <vector <string> > SplitCmd(vector<string>);
int main(int argc, char ** argv){
//cout<<"EXXXXTERMINATEEE! --- love, a lonely DALEK"<<endl;
string in;
vector<string> arg;
vector <vector <string> > args; //vector of commands
//bool hashtag = false;
while (in !="quit"){
    cout<<"$ ";
    std::getline(cin,in);
    arg=Split(in);
    args = SplitCmd(arg); // we have here a list of command with their args
    for(int j=0; j< args.size();j++)
    {
        //conversion zone
        char * argFinal[args[j].size()];
        for(int i=0; i<args[j].size();i++){
            argFinal[i] = (char*)args[j][i].c_str();
        }
        argFinal[args[j].size()]=NULL; //last arg must be null
        int pid = fork(); // for the process to be able to do the execvp 
        if(pid ==1){
            perror("fork failed");//if the fork failed
        }
        else if(pid==0){
    	    //child process
            if(execvp(argFinal[0],argFinal) !=0 && in != "quit"){
        	    perror("error in execvp");
            }
            else if(in =="quit")
            {
                exit(0);//quit the process if quit is typed
            }
        exit(0);
        }
        else{
        //parent process
            wait(NULL);//wait till the child is finished
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
  
   if (it[0][0]==';'){
    	args.push_back(splitedArg);
    	splitedArg.clear();
    	//it.erase(it.begin());
    	//vector<string> tmp;
    	/*for(int m=1; m<*it.size();m++)
    	{
            tmp[m-1] = it[m];
    	}*/
    	/*for(string::iterator it2 = *it.begin(); it2 != *it.end();++it2){
            
    	}*/
    //	vector <string> tmp = *it ;
    //	splitedArg.push_back(tmp.erase(tmp.begin()));
        it[0] = CleanString(it[0]);
        splitedArg.push_back(*it);
    	
    }
    else if(it[0]==" "&&splitedArg.size()>0)
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
string splitedPiece;
bool testHashtag = false;
for(string::iterator it = input.begin(); it != input.end();++it)
{
    currentChar =*it;
    if((currentChar==' '||currentChar==';')&&splitedPiece.size()>1 && !testHashtag )//if the it arrives to a space and the size of the piece of string if greater than 2 char
    {
        arg.push_back(splitedPiece);//add this piece of text to the vector
        splitedPiece.clear();//clean the piece to do another one to fill it again
    }
   /* if(currentChar==';'&&splitedPiece.size()>1&&!testHashtag)
    
        arg.push_back(splitedPiece);
        splitedPiece.clear();
    }*/
    if(testHashtag && it == input.end()-1)
    {
    	arg.push_back(" ;echo ");//add the ; to say it's a new function
        arg.push_back(splitedPiece);//we add the big comment to the list of arg
    }
    if((currentChar==' '||currentChar=='\t') && splitedPiece.size() <= 1&& it != input.end()-1)
    {
        //if there is a lonely space
        // we go into that if so we dont go into the else, so the space is not taken in the arg, so this is what I want. I'm sad to let an if empty.
    }
    else{
        splitedPiece.push_back(*it);//add the current char to the plited piece of tex to make an arg, between two spaces => it s an arg we are filling
        if(currentChar =='#')
        {
            testHashtag =true;
        }
   }
}
return arg;
}

string CleanString(string input){
string finalInput = new char[input.size()];
finalInput = input;
finalInput.erase(remove(finalInput.begin(),finalInput.end(),';'),finalInput.end());
return finalInput;
//remove the " of the input, avoiding injections
}
