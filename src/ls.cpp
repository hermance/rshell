#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
using namespace std;

int main(){
DIR *dir;
struct dirent *dirp;
dir = opendir("bin");
if(dir == NULL)
{
    perror("opendir failed");
}
else{
    /*for(int i=0; i< dir.size(); i++){
        cout<<dir[i]<<endl;
    }*/
    while((dirp = readdir(dir)) != NULL){
        cout<<(string)dirp->d_name<<endl;
    }
}
return 0;
}
