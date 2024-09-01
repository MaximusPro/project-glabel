//version 0.9-3
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <filesystem>
//#include <iostream>
using namespace std;
char* NAME;

#define VERSION "0.9-3"

struct Parameters
{
    char* Name;
    char* Comment;
    char* GenericName;
    char* Keywords;
    char* Exec;
    char* Terminal;
    char* Type;
    char* Icon;
    char* Path;
    char* Categories;
    char* NoDisplay;
    char* PathToFile;
};

int manual()
{
    FILE* file = fopen("/usr/share/glabel/manual.txt", "r");
    char c;
    if(file == NULL)
    {
        printf("\33[31mCould not open manual!\33[0m\n");
        return 1;
    }
    
    while(fscanf(file, "%c", &c) == 1)
    {
        printf("%c", c);
    }
    printf("\n");
    fclose(file);
    return 0;
}

char* DefaultOption(char* prefix, Parameters &Colors)
{
    if(!strcmp(prefix, "-gn"))
    {
        Colors.GenericName == nullptr ? Colors.GenericName = "\33[34m": NULL;
        return NAME;
    }
    else if(!strcmp(prefix, "-te"))
    {
        Colors.Terminal == nullptr ? Colors.Terminal = "\33[34m": NULL;
        return "false";
    }
    else if(!strcmp(prefix, "-ty"))
    {
        Colors.Type == nullptr ? Colors.Type = "\33[34m": NULL;
        return "Application";
    }
    else if(!strcmp(prefix, "-i"))
    {
        Colors.Icon == nullptr ? Colors.Icon = "\33[34m": NULL;
        string CurrentPath = filesystem::current_path();
        CurrentPath += "/favicon.ico";
        char* Str = new char[CurrentPath.size()+1];
        strcpy(Str, CurrentPath.c_str());
        return (char* )Str;
    }
    else if(!strcmp(prefix, "-d"))
    {
        Colors.NoDisplay == nullptr ? Colors.NoDisplay = "\33[34m": NULL;
        return "false";
    }
    return " ";
}

bool find(string Array, char symbol)
{
    bool Index = false;
    for(char Symb:Array)
    {
        if(Symb == symbol){ Index = true; break;}
    }
    return (Index);
}

Parameters WarningsFilter(const Parameters Param, Parameters &Colors)
{
   char* InvalidChars = "&;|*?'\"`[]()$<>{}^#\/%!\0";     
    string Name, GenericName, KeyWords, Exec, Terminal, Type, Icon, Path, Categories, NoDisplay, PathToFile;
    filesystem::path SystemPath(Param.Path);
    filesystem::path SystemExec(Param.Exec);
    char* n = Param.PathToFile;
   if(Colors.PathToFile != "\33[34m" && Param.PathToFile != nullptr)
    {
    filesystem::path SystemPathToFile(Param.PathToFile); 
    (filesystem::exists(SystemPathToFile))? Colors.PathToFile = "\33[32m": Colors.PathToFile = "\33[31m";
    }
    if(Colors.Icon != "\33[34m" && Param.Icon != nullptr){filesystem::path SystemIconPath(Param.Icon); (filesystem::exists(SystemIconPath))? Colors.Icon = "\33[32m": Colors.Icon = "\33[31m";}
    (filesystem::exists(SystemPath))? Colors.Path = "\33[32m": Colors.Path = "\33[31m";
    (filesystem::exists(SystemExec))? Colors.Exec = "\33[32m": Colors.Exec = "\33[31m";
    Name = Param.Name;
    (Param.Keywords != nullptr && Colors.Keywords == nullptr)?KeyWords = Param.Keywords: Colors.Keywords = "\33[31m";
    (Param.Categories != nullptr && Colors.Categories == nullptr)?Categories = Param.Categories: Colors.Categories = "\33[31m";
    if(Param.Type != nullptr && Colors.Type == nullptr){Type = Param.Type;} 
    else{if(Colors.Type != nullptr){} else{Colors.Type = "\33[0m";}}
    if(Param.GenericName != nullptr && Colors.GenericName == nullptr){GenericName = Param.GenericName;}
    Colors.Comment = "\33[0m";
    if(!find(GenericName, '\\') && !find(GenericName, '//') && !GenericName.empty() && Colors.GenericName != "\33[34m") {Colors.GenericName = "\33[32m";}
    else {if(!GenericName.empty() && Colors.GenericName != "\33[34m"){Colors.GenericName = "\33[31m";} else{if(Colors.GenericName != "\33[34m")Colors.GenericName = "\33[0m";}}
    if(Colors.NoDisplay != "\33[34m")
    {
    (Param.NoDisplay != nullptr && Colors.NoDisplay == nullptr)?NoDisplay = Param.NoDisplay: Colors.NoDisplay = "\33[31m";
    if(NoDisplay == "false" || NoDisplay == "true" && Colors.NoDisplay == nullptr) {Colors.NoDisplay = "\33[32m";} 
    else {Colors.NoDisplay = "\33[31m";}
    }
    if(Colors.Terminal != "\33[34m")
    {
    (Param.Terminal != nullptr && Colors.Terminal == nullptr)?Terminal = Param.Terminal: Colors.Terminal = "\33[31m";
    if(Terminal == "false" || Terminal == "true" && Colors.Terminal == nullptr) {Colors.Terminal= "\33[32m";} 
    else {Colors.Terminal = "\33[31m";}
    }
    if(!find(Name, '\\') && !find(Name, '//') && !Name.empty()) {Colors.Name = "\33[32m";}
    if(!find(Name, '\\') && !find(Name, '//') && !Name.empty()) {Colors.Name = "\33[32m";}
    else {Colors.Name = "\33[31m";}
    
    for(int i = 0; i < InvalidChars[i] != '\0'; i++)
    {

        if(find(KeyWords, InvalidChars[i]) && InvalidChars[i] != ';' && !KeyWords.empty() && Colors.Keywords != "\33[34m]"){Colors.Keywords = "\33[31m"; break;}
        else {Colors.Keywords = "\33[32m";}
    }
    for(int i = 0; i < InvalidChars[i] != '\0'; i++)
    {

        if(find(Type, InvalidChars[i]) && !Type.empty() && Colors.Type != "\33[34m"){Colors.Type = "\33[31m"; break;}
        else {if(Colors.Type == nullptr)Colors.Type = "\33[32m";}
    }
    for(int i = 0; i < InvalidChars[i] != '\0'; i++)
    {

        if(find(Categories, InvalidChars[i]) && InvalidChars[i] != ';' && !Categories.empty() && Colors.Categories != "\33[34m]"){Colors.Categories = "\33[31m"; break;}
        else {Colors.Categories = "\33[32m";}
    }
    return Colors;
}

void ViewParameters(const Parameters Param, Parameters Colors)
{
    char* WhiteColor = "\33[0m";
    cout << "Name= " << Colors.Name << Param.Name << WhiteColor << endl;
    cout << "Comment= " << Colors.Comment << Param.Comment << WhiteColor << endl;
    cout << "GenericName= " << Colors.GenericName << Param.GenericName << WhiteColor << endl;
    cout << "Keywords= " << Colors.Keywords << Param.Keywords << WhiteColor << endl;
    cout << "Exec= " << Colors.Exec << Param.Exec << WhiteColor << endl;
    cout << "Terminal= " << Colors.Terminal << Param.Terminal << WhiteColor << endl;
    cout << "Type= " << Colors.Type << Param.Type << WhiteColor << endl;
    cout << "Icon= " << Colors.Icon << Param.Icon << WhiteColor << endl;
    cout << "Path= " << Colors.Path << Param.Path << WhiteColor << endl;
    cout << "Categories= " << Colors.Categories << Param.Categories << WhiteColor << endl;
    cout << "NoDisplay= " << Colors.NoDisplay << Param.NoDisplay << WhiteColor << endl;
    cout << "PathToFile= " << Colors.PathToFile << Param.PathToFile << WhiteColor << endl;

}

int main(int argc, char* argv[])
{
    if(argc == 1)
    {
        printf("\033[31mERROR: Unknown parameters for generating file!\nFor details used command --man\033[0m\n");
        return 1;
    }
    else if(argc%2 == 0)
    {
        printf("\033[31mError in current parameters!\n");
        printf("You should write like this: \33[32mglabel [prefix1] Argument1 [prefix2] Argement2 ...\33[0m\n");
        printf("\33[31mUse \33[32m\"\" \033[31mfor path or names!\033[0m\n");
        return 2;
    }
    Parameters Colors;
    Colors.Name = nullptr;
    Colors.Comment = nullptr;
    Colors.GenericName = nullptr;
    Colors.Keywords = nullptr;
    Colors.Exec = nullptr;
    Colors.Terminal = nullptr;
    Colors.Type = nullptr;
    Colors.Icon = nullptr;
    Colors.Path = nullptr;
    Colors.Categories = nullptr;
    Colors.NoDisplay = nullptr;
    Colors.PathToFile = nullptr;
    Parameters PM;
    PM.Name = PM.Comment = PM.GenericName = PM.GenericName = PM.Exec = PM.Terminal = PM.Type = PM.Icon = PM.Path = PM.Categories = PM.NoDisplay = PM.PathToFile = PM.Keywords = NULL;
    
    for(int i = 1; i < argc; i++)
    {
        if(!strcmp("-n", argv[i])){PM.Name = argv[i+1];}
        else if(!strcmp("-c", argv[i])){PM.Comment = argv[i+1];}
        else if(!strcmp("-gn", argv[i])){PM.GenericName = argv[i+1];}
        else if(!strcmp("-k", argv[i])){PM.Keywords = argv[i+1];}
        else if(!strcmp("-e", argv[i])){PM.Exec = argv[i+1];}
        else if(!strcmp("-te", argv[i])){PM.Terminal = argv[i+1];}
        else if(!strcmp("-ty", argv[i])){PM.Type = argv[i+1];}
        else if(!strcmp("-i", argv[i])){PM.Icon = argv[i+1];}
        else if(!strcmp("-p", argv[i])){PM.Path = argv[i+1];}
        else if(!strcmp("-ca", argv[i])){PM.Categories = argv[i+1];}
        else if(!strcmp("-d", argv[i])){PM.NoDisplay = argv[i+1];}
        else if(!strcmp("--man", argv[i])){return manual();}
	else if(!strcmp("--version", argv[i])){return printf("version %s\n", VERSION);}
	else if(!strcmp("-pf", argv[i])){PM.PathToFile = argv[i+1];}
    }
    if(PM.Name == NULL){printf("\033[31mERROR: Unknown name!\033[0m\n");return -1;}
    else if(PM.Exec == NULL)
    {printf("\033[31mERROR: Unknown path to run a file!033[0m\n");return -1;}
    else if(PM.Path == NULL){printf("\033[31mERROR: Unknown path to run a file!033[0m\n");return -1;}
    NAME = PM.Name;
    char *NameFile = new char[1000];
    char *FullPath = new char[2000];
    if(PM.PathToFile != NULL) strcat(FullPath, PM.PathToFile);
    strcat(FullPath, "/");
    strcat(FullPath, PM.Name);
    strcat(FullPath, ".desktop");
    strcat(NameFile, PM.Name);
    strcat(NameFile, ".desktop");
    char* Str = NULL;
    int index = 0;
    for(int i = 0; i < strlen(NameFile); i++)
    {
	if(NameFile[i] == '\0')
	index = i;
    }
    Str = new char[index+1];
    
    if(PM.Comment == NULL) PM.Comment =  DefaultOption("-c", Colors);
    if(PM.Keywords == NULL) PM.Keywords = DefaultOption("-k", Colors);
    if(PM.GenericName == NULL) PM.GenericName = DefaultOption("-gn", Colors);
    if(PM.Terminal == NULL) PM.Terminal =  DefaultOption("-te", Colors);
    if(PM.Type == NULL) PM.Type = DefaultOption("-ty", Colors);
    if(PM.Icon == NULL) PM.Icon = DefaultOption("-i", Colors);
    if(PM.Categories == NULL) PM.Categories =  DefaultOption("-ca", Colors);
    if(PM.NoDisplay == NULL) PM.NoDisplay = DefaultOption("-d", Colors);
	if(PM.PathToFile==NULL)
	{	
		printf("\33[32mNameFile = %s\33[0m\n", NameFile);
		system("echo \"Default path: /home/$(whoami)/\"");
        string FileToPath = filesystem::current_path();
        FileToPath = FileToPath + "/" + NameFile;
        PM.PathToFile = new char[FileToPath.size()+1];
        strcpy(PM.PathToFile,(char*)FileToPath.c_str());
		Colors.PathToFile = "\33[34m";
	}
	else 
	{
		printf("\33[32mNameFile = %s\33[0m\n", NameFile);
		NameFile = FullPath;
	}
    Colors = WarningsFilter((const Parameters)PM, Colors);
    ViewParameters(PM, Colors);

	FILE* File = fopen(NameFile, "w");
    if(File != nullptr)
    {
    fprintf(File, "[Desktop Entry]\n");
    fprintf(File, "Name=%s\n", PM.Name);
    fprintf(File, "Comment=%s\n", PM.Comment);
    fprintf(File, "GenericName=%s\n", PM.GenericName);
    fprintf(File, "Keywords=%s\n", PM.Keywords);
    fprintf(File, "Exec=%s\n", PM.Exec);
    fprintf(File, "Terminal=%s\n", PM.Terminal);
    fprintf(File, "Type=%s\n", PM.Type);
    fprintf(File, "Icon=%s\n", PM.Icon);
    fprintf(File, "Path=%s\n", PM.Path);
    fprintf(File, "Categories=%s\n", PM.Categories);
    fprintf(File, "NoDisplay=%s\n", PM.NoDisplay);
    fclose(File);
    printf("\33[32mSaved in %s\n\33[0m", PM.PathToFile);
    char* C_Command = new char[1000];
    for(int i = 0; i < 1000; i++)
    {
        C_Command[i] = '\0';
    }
    strcat(C_Command,"chmod a+x ");
    strcat(C_Command, "\"");
    strcat(C_Command, NameFile);
    strcat(C_Command, "\"");
	system(C_Command);
    }
    else {printf("\033[31mERROR: FullPath: %s Does not exist!\033[0m\n",FullPath);}
    free(NameFile);
	
}
