#include <iostream>
#include <cstring>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <vector>
using namespace std;
/*DIR  getDirectory(){
char cwd[1024];
char * getc = getcwd(cwd, sizeof(cwd));
if(getc == NULL)
{
    perror ("getcwd failed");
    return NULL;
}
else{
    return cwd;
}
}*/
int main(int argc, char* argv[]){
DIR *dir;
struct dirent *dirp;
char directory[1024];
struct stat s;
vector<string> vect;
char * getc = getcwd(directory, sizeof(directory));
if(getc == NULL)
{
    perror("getcwd failed");
}
else{
    //tout s'est bien passé
    dir = opendir(directory);
    if(dir == NULL)
    {
        perror("opendir failed");
    }
    else{
        while((dirp = readdir(dir)) != NULL){
           vect.push_back((string)dirp->d_name);
        }
        int cas;
        for(int i =0;i<argc;i++){
        	if(strcmp(argv[i],"bin/ls")==0){
                cas=1;
                //cout<<"cas 1"<<endl;
            }
            if(strcmp(argv[i],"-a")==0){
                cas = 2;
                //cout<<"cas 2 "<<endl;
            }
            if(strcmp(argv[i],"-l")==0){
                cas = 3;
            }
        }
        switch (cas){
            case 1 :
            for(int i = 0; i< vect.size(); i++){
                if(vect[i][0] =='.'|| vect[i] ==".."){
                    //do nothing
                }
                else
                {
                	cout<<" "<<vect[i];
                }
                if(i==vect.size()-1)cout<<endl;
            }
            break;
            case 2:
            for(int i= 0; i< vect.size();i++){
                cout<<vect[i]<<" ";
                if(i==vect.size()-1)cout<<endl;
            }
            break;
            case 3 :
            //thats the long case
            //struct stat s;
            for(int k= 0; k< vect.size();k++)
            {
                if(vect[k][0] =='.'|| vect[k] ==".."){}
                else{
                    stat((const char*)vect[k].c_str(),&s);
                    cout<<((S_ISREG(s.st_mode))?"d":"-");
                    //USER
                    cout<<((s.st_mode&S_IRUSR)?"r":"-");
                    cout<<((s.st_mode&S_IWUSR)?"w":"-");
                    cout<<((s.st_mode&S_IXUSR)?"x":"-");
                
                    cout<<" ";

                    //GROUP
                    cout<<((s.st_mode&S_IRGRP)?"r":"-");
                    cout<<((s.st_mode&S_IWGRP)?"w":"-");
                    cout<<((s.st_mode&S_IXGRP)?"x":"-");

                    cout<<" ";

                    //TOUS
                    cout<<((s.st_mode&S_IROTH)?"r":"-");
                    cout<<((s.st_mode&S_IWOTH)?"w":"-");
                    cout<<((s.st_mode&S_IXOTH)?"x":"-");

                    //nb de liesn materiens
                    cout<<" "<<s.st_nlink;

                    //username
                    char * login = getlogin();
                    if(login ==NULL) perror("getlogin failed");
                    cout<<" "<<login<<endl;
                }
                

            }
            break;
        }
        
    }
}
return 0;
}
