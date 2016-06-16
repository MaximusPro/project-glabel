//version 0.9

#include <stdio.h>
#include <cstring>
#include <cstdlib>
//#include <cunistd>
#include <string.h>
#include <iostream>
using namespace std;

char* NAME;

#define VERSION "0.9"

int quots(char* str)
{
    int s = strlen(str);
    if(str[0] == '\"' && str[s] == '\"')
    {
        return 1;
    }
    return 0;
}

int manual()
{
    FILE* file = fopen("/usr/share/glabel/manual.txt", "r");
    char c;
    if(file == NULL)
    {
        printf("Could not open manual!\n");
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

char* DefaultOption(char* prefix)
{
    if(!strcmp(prefix, "-gn"))
    {
        return NAME;
    }
    else if(!strcmp(prefix, "-te"))
    {
        return "false";
    }
    else if(!strcmp(prefix, "-ty"))
    {
        return "Application";
    }
    else if(!strcmp(prefix, "-i"))
    {
        
    }
    else if(!strcmp(prefix, "-d"))
    {
        return "false";
    }
    return " ";
}

int main(int argc, char* argv[])
{
    if(argc == 1)
    {
        printf("ERROR: Unknown parameters for generating file!\nFor details used command --man\n");
        return 1;
    }
    //char* file;
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
    //char Iman = 0;
    Name = Comment = GenericName = Keywords = Exec = Terminal = Type = Icon = Path = Categories = NoDisplay = PathToFile = NULL;
    for(int i = 1; i < argc; i++)
    {
        if(!strcmp("-n", argv[i]))
        {
                Name = argv[i+1];
        }
        else if(!strcmp("-c", argv[i]))
        {
                Comment = argv[i+1];
        }
        else if(!strcmp("-gn", argv[i]))
        {
                GenericName = argv[i+1];
        }
        else if(!strcmp("-k", argv[i]))
        {
                Keywords = argv[i+1];
        }
        else if(!strcmp("-e", argv[i]))
        {
                Exec = argv[i+1];
        }
        else if(!strcmp("-te", argv[i]))
        {
           
                Terminal = argv[i+1];
            
        }
        else if(!strcmp("-ty", argv[i]))
        {
            
                Type = argv[i+1];
            
        }
        else if(!strcmp("-i", argv[i]))
        {
            
                Icon = argv[i+1];
           
        }
        else if(!strcmp("-p", argv[i]))
        {
            
                Path = argv[i+1];
            
        }
        else if(!strcmp("-ca", argv[i]))
        {
            
                Categories = argv[i+1];
            
        }
        else if(!strcmp("-d", argv[i]))
        {
            
                NoDisplay = argv[i+1];
            
        }
        else if(!strcmp("--man", argv[i]))
        {
           return manual();
        }
	else if(!strcmp("--version", argv[i]))
        {
           return printf("version %s\n", VERSION);
            
        }
	else if(!strcmp("-pf", argv[i]))
        {
           PathToFile = argv[i+1];
            
        }
    }
    if(Name == NULL)
    {
        printf("ERROR: Unknown name!\n");
        return -1;
    }
    else if(Exec == NULL)
    {
        printf("ERROR: Unknown path to run a file!\n");
        return -1;
    }
    else if(Path == NULL)
    {
        printf("ERROR: Unknown path to run a file!\n");
        return -1;
    }
    NAME = Name;
    char *NameFile = new char[100];
    char *FullPath = new char[200];
    if(PathToFile != NULL) strcat(FullPath, PathToFile);
    strcat(FullPath, Name);
    strcat(FullPath, ".desktop");
    strcat(NameFile, Name);
    strcat(NameFile, ".desktop");
    char* Str = NULL;
    int index = 0;
    for(int i = 0; i < strlen(NameFile); i++)
    {
	if(NameFile[i] == '\0')
	index = i;
    }
    Str = new char[index+1];
    
	
    //printf("NameFile = %s\n", NameFile);
    //string Path(PathToFile);
    if(Comment == NULL) Comment =  DefaultOption("-c");
    if(Keywords == NULL) Keywords = DefaultOption("-k");
    if(GenericName == NULL) GenericName = DefaultOption("-gn");
    if(Terminal == NULL) Terminal =  DefaultOption("-te");
    if(Type == NULL) Type = DefaultOption("-ty");
    if(Icon == NULL) Type = DefaultOption("-i");
    if(Categories == NULL) Categories =  DefaultOption("-ca");
    if(NoDisplay == NULL) NoDisplay = DefaultOption("-d");
	if(PathToFile==NULL)
	{	
		printf("NameFile = %s\n", NameFile);
		system("echo \"Default path: /home/$(whoami)/\"");
		
	}
	else 
	{
		printf("NameFile = %s\n", NameFile);
		printf("Saved in %s\n", PathToFile);
		/*for(int i = 0; i < index+1; i++)
	    {
		Path.push_back(&NameFile[i]);
    	    }*/
		//Path = Path + NameFile;
		NameFile = FullPath;
	}
	FILE* File = fopen(NameFile, "w");
    fprintf(File, "[Desktop Entry]\n");
    fprintf(File, "Name=%s\n", Name);
    fprintf(File, "Comment=%s\n", Comment);
    fprintf(File, "GenericName=%s\n", GenericName);
    fprintf(File, "Keywords=%s\n", Keywords);
    fprintf(File, "Exec=%s\n", Exec);
    fprintf(File, "Terminal=%s\n", Terminal);
    fprintf(File, "Type=%s\n", Type);
    fprintf(File, "Icon=%s\n", Icon);
    fprintf(File, "Path=%s\n", Path);
    fprintf(File, "Categories=%s\n", Categories);
    fprintf(File, "NoDisplay=%s\n", NoDisplay);
    fclose(File);
	string Command("chmod a+x ");
	Command = Command + "\"" + NameFile + "\"";
	system(Command.c_str());
	//execl("chmod", "a+x", command, NULL);
    free(NameFile);
	
}
