#define _GNU_SOURCE
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

int calc(){
    char o;
    float a,b;
    printf("Enter a simple expression\n");
    scanf("%f%c%c%f", &a, &o, &o, &b);
    if(o=='/' && b==0.0){
        printf("You can't divide by zero!\n");
    }
    else {
        switch(o){
        case '+':
            printf("Result: %g\n", a+b);
            break;
        case '-':
            printf("Result: %g\n", a-b);
            break;
        case '*':
            printf("Result: %g\n", a*b);
            break;
        case '/':
            printf("Result: %g\n", a/b);
            break;
        case '^':
            printf("Result: %g\n", pow(a, b));
            break;
        }
    }
}

int date(){
   time_t t = time(NULL);
   struct tm tm = *localtime(&t);
   printf("It is %d:%d, %d.%d.%d.\n", tm.tm_hour, tm.tm_min, tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}


int wiki(const char *term){
   char *search = NULL;
   asprintf(&search, "wikit %s", term);
   system(search);
   free(search);
}

int google(char *srchterm){
   char *search = NULL;
   for(char *p = srchterm; p = strchr(p, ' '); p++) {*p = '+';}
   asprintf(&search, "https://www.google.com/search?q=%s", srchterm);
   printf("Link to google search: %s\n", search);
   free(search);
}

int wttr(){
   system("curl -Ss wttr.in?format='%C,%t' | tr '+' ' '");
}

int main(){
    char *name = NULL, *action = NULL;
    size_t n;
    printf("What is your name?\n");
    getline(&name, &n, stdin);
    name[strlen(name) - 1] = '\0';
    printf("Hi %s!\n", name);
    free(name);
    while(1) {
    printf("What would you like me to do?\n");
    getline(&action, &n, stdin);
    action[strlen(action) - 1] = '\0';
    if(strcmp(action, "open calculator") == 0){
        calc();
    }
    else if(strcmp(action, "tell me the time") == 0) {
        date();
    }
    else if(strncmp(action, "search wikipedia for", 20) == 0) {
        wiki(action + strlen("search wikipedia for "));
    }
    else if(strcmp(action, "quit") == 0) {
        break;
    }
    else if(strncmp(action, "search google for", 17) == 0) {
        google(action + strlen("search google for "));
    }
    else if(strcmp(action, "tell me the weather info") == 0) {
        wttr();
    }
    else {
        printf("No such thing.\n");
    }
    free(action);
    }
}
