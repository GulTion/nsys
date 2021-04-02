#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct login_signup
{
    char username[200];
    char password[200];
}userdata;

FILE *data = NULL;
int setup(int situation);
void login();
int find_occ(char* string, char to_find);
void create_account();
int find_occ_t(char* string, char to_find, int times, int indexes[]);


int main(){
    int choice;
    printf("What you wanna do?\n");
    printf("1. Login\n");
    printf("2. Register\n");
    printf("> ");
    scanf("%d", &choice);
    if (choice==1){
        login();
    }
    else if (choice==2)
    {
        create_account();
        system("cls");
        printf("Your account has been created.\nLogin to continue.\n");
        login();
    }
    else{
        printf("Wrong choice dude.");
    }
    
    return 0;
}

void create_account(void){
    printf("Choose a username for your account: ");
    scanf("%s", userdata.username);
    printf("Choose a password for your account: ");
    scanf("%s", userdata.password);
    setup(1);
}

void login(void){
    char temp[200];
    printf("Username: ");
    scanf("%s", temp);
    if (strcmp(temp,userdata.username) !=0){
            printf("Wrong dude");
            exit(0);
        }
        printf("Password: ");
        scanf("%s", temp);
        if (strcmp(temp,userdata.password) !=0){
            printf("Wrong dude");
            exit(0);
        }
        setup(2);
}

int setup(int situation){
    if (situation==1){
        char info;
        data = fopen("data.txt", "a");
        if (data==NULL){
            printf("The file you specified doesn't exits!");
            exit(0);
        }
        strcpy(&info, userdata.username);
        strcat(&info, ": ");
        strcat(&info, userdata.password);
        fputs(&info, data);
        fputs("\n", data);
        fclose(data);
    }
    else if (situation==2)
    {
        // login
        char usernames[200];
        char passwords[200];
        char c;
        char info[200];
        int occurrences, indexes[20000];
        data = fopen("data.txt", "r");
        if (data==NULL){
            data = fopen("data.txt", "a");
        }
        c = fgetc(data);
        int length=0;
        while (c!=EOF)
        {
            strncat(info, &c, 1);
            c = fgetc(data);
            length++;
        }
        info[length]=0;
        // find the occurrences of : then run loop that times and then seperate usernames and passwords
        occurrences = find_occ(info, ':');
        find_occ_t(info, ':', occurrences, indexes);
        printf("%d", indexes[0]);   
    }
    
    return 0;
}


int find_occ(char* string, char to_find){
    int occurrences=0;
    for (int i=0; i<strlen(string); i++){
        if (string[i]==to_find){
            occurrences++;
        }
    }
    return occurrences;
}

int find_occ_t(char* string, char to_find, int times, int indexes[]){
    int count = 0;
    for (int i=0; count<times; i++){
        if (string[i]==to_find){
            indexes[count]=i;
            count++;
        }
    }
    return 0;
}