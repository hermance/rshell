#include <iostream>
#include <pwd.h>
#include <grp.h>
#include <cstring>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <vector>
#include <sstream>
using namespace std;
void printA(vector<string> vect, int cas2)
{
for(int i = 0; i< vect.size(); i++){
	if(cas2 != 2 &&(vect[i][0] =='.'|| vect[i] =="..")){
	 	 //do nothing
	}
	else
	{
	   	 cout<<" "<<vect[i];
	}
	if(i==vect.size()-1)cout<<endl;
}
}
void printL(vector<string> vect, int cas2){
struct stat s;
for(int k= 0; k< vect.size();k++)
{
if(cas2 != 2 && (vect[k][0] =='.'|| vect[k] =="..")){}
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
	//user
	struct passwd *pw = getpwuid(s.st_uid);
	struct group *gr = getgrgid(s.st_gid);
	if(pw != 0 && gr != 0)
	{
		cout<<" "<<pw->pw_name<<" "<<gr->gr_name;
	}
	else{
		perror("getpwuid/getgrgid failed");
		}
		//evil number
		if(s.st_size<10)cout<<"    ";
		else if(s.st_size<100)cout<<"   ";
		else if(s.st_size <1000)cout<<"  ";
		else if(s.st_size <10000)cout<<" ";
		cout<<" "<<s.st_size;
        int year;
        int hour;
        int min;
        int month;
        int day;
        string realDay;
        string realMonth;
        string realMin;
        struct tm date;
        localtime_r(&s.st_mtime, &date);
        char timbuf[80];
        string months[] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep",    "Oct","Nov","Dec"};

        strftime(timbuf, sizeof(timbuf), "%c", &date);
        month = date.tm_mon;
        realMonth = months[month];
        day = date.tm_mday;
        stringstream ss;
        ss<<day;
        if(day<10)realDay = ss.str() + " ";
        else realDay = ss.str();
        hour = date.tm_hour;
        min = date.tm_min;
        stringstream ss2;
        ss2<<min;
        if(min<10)realMin = ss2.str()+" ";
        else realMin = ss2.str();
        cout<<" "<<realMonth<<" "<<realDay<<" "<<hour<<":"<<realMin;
        //name
        cout<<" "<<vect[k];
        cout<<endl;
        }

}
}
void openPrintR(vector<string> vect,int cas, int cas2, int cas3){
//cas 2 : -a, cas3 : -l
DIR * dir;
struct dirent * dirp;
for(int i=0; i<vect.size(); i++){
//parcours de la liste des attributs
struct stat s;
stat((const char*)vect[i].c_str(),&s); //get file
if(vect[i][0]!='.')cout<<" "<<vect[i]<<endl;

char directory[1024];
char * getc = getcwd(directory, sizeof(directory));
//if(stat((directory+vect[i]).c_str(), &s) == -1)perror("stat failed");

if(S_ISDIR(s.st_mode)&& vect[i][0] !='.'){
//if it is a rep
//get the path
cout<<"\tTHE SUBFOLDER --------------------"<<endl;
//char directory[1024];
vector<string> vect2;
char * getc = getcwd(directory, sizeof(directory));
//if(stat((directory+vect[i]).c_str(), &s) == -1)perror("stat failed");
//etc =  getcwd(directory, sizeof(directory));

if(getc == NULL){
	perror("getcwd failed");
}
else{
	//directory += vect[i];
	vect[i].insert(0,"/");
    dir = opendir((directory + vect[i]).c_str());
    //cout<<"path : "<<directory + vect[i]<<endl;
    if(dir==NULL){
    	perror("opendir failed");
        cout<<"path : "<<directory + vect[i]<<endl;
    }
    else{
        while((dirp = readdir(dir))!=NULL){
            vect2.push_back((string)dirp->d_name);//on rempli le nouveau truc
        }
        closedir(dir);
    openPrintR(vect2,cas, cas2, cas3); // appel recursif
    }
}
}
}
/*
switch (cas){
	case 1 :
	printA(vect, cas2);
	break;
	case 3 :
	printL(vect,cas2);
	break;
	case 4 : 
	printA(vect,cas2);
	} */
	     //closedir(dir);


}
int main(int argc, char* argv[]){
DIR *dir;
struct dirent *dirp;
char directory[1024];
int cas2;
int cas3;
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
                //cas = 2;
                cas2=2;
                //cout<<"cas 2 "<<endl;
            }
            if(strcmp(argv[i],"-l")==0){
                cas = 3;
                cas3 = 1;//plus long format
            }
            if(strcmp(argv[i],"-R")==0){
                cas =4;//recursif
            }
            if(strcmp(argv[i],"-lR")==0 || strcmp(argv[i],"-Rl")==0){
                cas = 4;
                cas3 = 1; //long plus recursif
            }
        }
        switch (cas){
            case 1 :
            printA(vect, cas2);
            break;
            case 3 :
            printL(vect,cas2);
            break;
            case 4 :
            openPrintR(vect,cas,cas2,cas3);
            break;
        }
    closedir(dir);   
    }
}
return 0;
}
