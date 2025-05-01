#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "string_action.h"
//arg format
struct targ_definition{ char *name; char *shortname; char *value; char *targ_used; int used; };
//arg_options
struct targ_options {
    struct  targ_definition *targs;
    int     targs_size;
};
// args list
struct  targ_definition targs[100];
int     targi = 0;
void add_cmd_arg(char* name,char* shortname)
{
    struct targ_definition arg =  {name,shortname};
    targs[targi] = arg;
    targi++;
}
struct targ_options get_args(struct  targ_definition *opt_args)
{
    struct targ_options defi;
    defi.targs = opt_args != 0 ? opt_args : targs ;
    defi.targs_size = targi;
    return defi;
}
struct targ_options parse_args(int argc, char** argv )
{
    int i           = 0;
    int args_met    = 0; 
    struct targ_options options = get_args(0);
    argv++;argc--;
    while (argc > 0) {
        while(i < targi)
        {
            struct targ_definition targ = options.targs[i];
            char* argname = targ.name;
            char* shortguess = malloc(sizeof(argname)+sizeof("--"));
            char* longguess = malloc(sizeof(argname)+sizeof("-"));
            sprintf(longguess,"--%s",argname);
            sprintf(shortguess,"-%s",argname);
            if  (    (strcmp(*argv, shortguess) == 0 ) ||  (strcmp(*argv, longguess) == 0 )  )   {
                options.targs[i].name       = targ.name;
                options.targs[i].shortname  = targ.shortname;
                options.targs[i].used       = 1;
                options.targs[i].targ_used  = *argv;
                options.targs[i].value = sizeof(argv) > args_met ? argv[++args_met] : "NULL" ; // Make sure to check bounds
                argc--; argv++; // Move to next argument
            }
            i++;
        }
        args_met++;
        argc--; argv++; // Move to the next argument if no match found
    }
    // return options;
    return get_args(options.targs);
}
int main(int argc, char** argv)
{
    int i = 0;
    add_cmd_arg("help","h");
    add_cmd_arg("source","s");
    struct targ_options options = parse_args(argc,argv);
    while(i < targi)
    {
        struct targ_definition targ = options.targs[i];
        if(targ.used)
        {
            printf("argument used = %s \n",targ.targ_used);
            printf("%s = %s \n",targ.name,targ.value);
        }
        i++;
    }
}
