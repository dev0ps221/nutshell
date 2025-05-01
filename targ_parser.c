#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "string_action.h"
//arg format
struct targ_definition{ char *name; char *shortname; char *value; };
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
            printf("%d is i and %d is targi",i,targi);
            struct targ_definition targ = options.targs[i];
            if  
            (    
                    strcmp(replace_part("--", "", argv[0]), targ.name) == 0 
                ||  
                    strcmp(replace_part("-", "", argv[0]), targ.shortname) == 0
            )       
            {
                options.targs[i].name = targ.name;
                options.targs[i].shortname = targ.shortname;
                options.targs[i].value = (argc > args_met+1) ? argv[args_met+1] : NULL; // Make sure to check bounds
            }
            argc--; argv++; // Move to next argument
            i++;
        }
        args_met++;
        argc--; argv++; // Move to the next argument if no match found
    }
    return options;
    // return get_args(options.targs);
}
int main(int argc, char** argv)
{
    int i = 0;
    add_cmd_arg("help","h");
    add_cmd_arg("source","s");
    printf("here");
    struct targ_options options = parse_args(argc,argv);
    printf("nere");
    while(i < targi)
    {
        struct targ_definition targ = options.targs[i];
        printf("%s == %s \n",targ.name,targ.value);
        i++;
    }
}
