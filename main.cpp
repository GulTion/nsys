#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int const MAX_CHAR  =30;
int const II = sizeof(int);
int const CC = sizeof(char);

struct user{
  char name[MAX_CHAR];
  char pass[MAX_CHAR];
}you;


struct info{
  int how_many=0;
  int user_index=0;
}db_info;


void countUser(FILE *db){
  int c=0;
  fread(&db_info.how_many, II, 1,db);
}

bool checkPass(){

  FILE * f = fopen("db.db", "r");
  countUser(f);
  struct user u;
  int how = db_info.user_index;
  fseek(f, II, SEEK_SET);
  while(how--){
  fread(&u.name, CC, MAX_CHAR, f);
  fread(&u.pass, CC, MAX_CHAR, f);
    if(strcmp(u.pass, you.pass)==0){

      return true;

    
  }

  }

  fclose(f);
  return false;

}

bool checkUser(){
  // if is_pass is true then it will match for password
  // if is_pass is false then it will match for user

  bool isExist = false;
  FILE * f = fopen("db.db", "r");
  countUser(f);
  struct user u;
  int how = db_info.how_many;
  fseek(f, II, SEEK_SET);
  while(how--){
  fread(&u.name, CC, MAX_CHAR, f);
  fread(&u.pass, CC, MAX_CHAR, f);
  
    if(strcmp(u.name, you.name)==0){
      db_info.user_index = db_info.how_many-how;
      return true;

    
  }

  }

  fclose(f);
   return false;
   
};





void addUser(){
  if(checkUser()){
    printf("User `%s` is Already Exist!\n", you.name);
    exit(0);
  }

  FILE * f = fopen("db.db", "a+");
  fwrite(you.name, CC, MAX_CHAR, f);
  fwrite(you.pass, CC, MAX_CHAR, f);
  fclose(f);

  printf("Hurry ! `%s` You Account is Created !\n",you.name);
  
  f = fopen("db.db", "r+");
  int j= ++db_info.how_many;
  fwrite(&j, II, 1, f);
  fclose(f);


}

void viewAllUser(){
  struct user u;
  
  
  FILE * f = fopen("db.db", "r");
  countUser(f);
  int how = db_info.how_many;
  fseek(f, II, SEEK_SET);

  while(how--){
  fread(&u.name, CC, MAX_CHAR, f);
  fread(&u.pass, CC, MAX_CHAR, f);
  printf("%s:%s\n",u.name,u.pass);
  }
  fclose(f);
  
}

void UserWelcome(){
  
  printf("`%s` is SuccessFully Login !\n",you.name);
}

void loginUser(){
  if(!checkUser()){
    printf("`%s` not find in Our Database! 404!\n",you.name);
  exit(0);
   
  }if(!checkPass()){
     printf("Password is inCorrent for `%s`!\n",you.name);
    exit(0);
  }
    
   

  UserWelcome();

}

void Screen(bool type){
  // type = true|false // true:login | false:signup


  // Clear the the Screen;
  system("clear");
  printf("Enter UserName: ");scanf("%s", you.name);
  printf("Enter Password: ");scanf("%s", you.pass);

  // printf("%s:%s", you.name,you.pass);
  type?loginUser():addUser();

}

void checkForDB(){
    FILE *f = fopen("db.db","r");
    int i=0;
    if(f==NULL){
       printf("`db.db` Not Found! run command `./%s --init-db`\n","main");
       
       exit(0);
       fclose(f);
    }
    
    
    
}

void welcomeScreen(){
  int choice;
  // Choice's Options
  // 1 for Login
  // 2 for Register
  printf("Welcome !!\n");
  printf("1. For Login\n2. For Register\n");
  printf("Enter Your Choice: ");
  scanf("%d", &choice);

  switch(choice){
    case 1: Screen(true);
    break;
    case 2: Screen(false);
    break;
  }
}

void createNewDB(int argc, char *argv[]){
  if(argc==2)
    if(strcmp(argv[1], "--init-db")==0){
      FILE *f = fopen("db.db","w");
      int i=0;
    fwrite(&i, II, 1,f);
    fclose(f);
    exit(0);
    }
}



int main(int argc, char *argv[]){
  
  createNewDB(argc, argv);
  checkForDB();
  welcomeScreen();
  // viewAllUser(); // uncomment for view all user list
  // printf("%d", db_info.how_many);
  
}
