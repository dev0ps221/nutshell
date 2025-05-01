#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

// Get current directory | Recuperer le repertoire actuel
char* t_current_dir()
{
    int namesize = 1000;
    char* currentdir = malloc(namesize);
    getcwd(currentdir,namesize);
    return currentdir;
}
// Go to specific directory | Aller dans un repertoire specifique
char* t_goto_dir(char* target_dir)
{
    if(strlen (target_dir) )
    {
        if(chdir(target_dir))
        {
            return t_current_dir();
        }
    }
    else
    {
        printf("'t_goto_dir': Aucun dossier spécifié");
    }
    return "ERR";
}
// List the content of a specific directory | Lister le contenu d'un repertoire specifique
struct dirent** t_listdir(char* current_dir)
{
    int free_current_dir        = 0;
    if(strlen(current_dir) == 0)
    {
        int free_current_dir    = 1;
        current_dir             = malloc(1000);
        getcwd(current_dir,1000);
    }
    struct dirent *itm;
    DIR *dirlist                    = opendir(current_dir); 
    struct dirent** dircontent      = malloc(1000);
    int i                           = 0;
    while((itm = readdir(dirlist)) != NULL)
    {
        dircontent[i] = itm;
        if(itm->d_type == 4)
        {
            printf("\n");
            printf(":::::::::");
        }
        printf(">> %s",itm->d_name);
        printf("\n");
    }
    if(free_current_dir)
    {
        free(current_dir);
    }
    free(dircontent);
    return dircontent;
}
int main()
{
    t_listdir("");
}