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
using namespace std;

int main(){
//cout<<"EXXXXTERMINATEEE! --- love, a lonely DALEK"<<endl;
string cmd;
while (cmd !="quit"){
cout<<"$ ";
getline(cin,cmd);
cout<<"Nice "<<cmd<<endl;
}
return 0;
}
