#include <stdio.h>
#include <string.h>

char *USERNAME = "phoebe";
char *PASSWORD = "1234";

char user[100];
char pass[100];

int main(){
printf("input Username: \n");
scanf("%s", user);
printf("input Password: \n");
scanf("%s", pass);

if(strcmp(user, USERNAME) == 0 && strcmp(pass,PASSWORD)==0){
printf("pass\n");
return 1;
}
else{
printf("incorrect. input again\n");
return 0;
}


}
