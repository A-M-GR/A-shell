
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include <regex.h>

#define length 512


int quit_function(char * ptr);



int main (int argc,char * argv[])


{

pid_t child_id;
int len = 0;
int error_check = -1;
char * ptr1 = NULL;
char * ptr = NULL;
char user_input [length];


int flag_for_quit=0;

while (1)
{


printf("[Andreas@localhost]$ ");
fgets(user_input,sizeof(user_input),stdin);




ptr = strtok(user_input,";");
ptr1=ptr;


if(strcmp(ptr,"\n") == 0 )
{
printf("this is an empty command\n");
continue;
}



error_check = quit_function(ptr);
if( error_check == 1)
{
flag_for_quit = 1;
}





while(1)
{
ptr1 = strtok(NULL,";");




if(ptr1 == NULL)
break;

len = strlen(ptr1);

if(len == 0)
{
break;
}




if(quit_function(ptr1) == 1)
{
flag_for_quit=1;

continue;
}



if(strcmp (ptr1,"\n") == 0)
{
continue;
}





child_id = fork();// create child


if(child_id == -1)
{
printf("child could not created");
exit(1);
}




if(child_id == 0)
{

char new_argument[len+1];

strcpy(new_argument,ptr1);

printf("%s",new_argument);
exit(0); // simple exit from child 0 == all ok

}

if (child_id > 0)
{
wait(NULL); // is waiting for child  process to finish

}





}



if(flag_for_quit == 1)
exit(EXIT_SUCCESS);




}

return 0;
}











int quit_function(char * ptr)
{

// need a string as value
// return the value 1 if regex is be found otherwise the value 0

int len = strlen(ptr);
regex_t regext;
int reti;

char * regex = "[ \t\n]*quit[ \t\n]*";





for(int i =0; i<len; i++)
{

if( (ptr[i]== 'q') || (ptr[i]== 'u') || (ptr[i]== 'i') || (ptr[i]== 't') || (ptr[i]==' ') || (ptr[i] =='\n') || (ptr[i]== '\t'))

continue;

else
return 0;


}



reti = regcomp(&regext,regex,0);

reti = regexec(&regext,ptr,0,NULL,0);

if(reti == 0)
{

 return 1;
}
else
return 0;



}








