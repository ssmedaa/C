#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 30
#define fieldLength 200


#define diskFile "diskFile.dat"
#define courseFile "course.txt"

struct db_type
{
   char name[fieldLength];
   int age;
   char course1[fieldLength];
   char course2[fieldLength];
   char status[fieldLength];
 };

struct courseInfo
{ 
  char code [20]; // e.g., EECS2030
  char title [fieldLength];
  char  date [20];
  char time_start [20];
  char time_end [20];
  char  location [20]; 
};

 
struct courseInfo courseArr[SIZE]; // global variable  array of struc
     

char prompt_menu(void);
void init_list(struct db_type * pArr[]); 
void clearDB(struct db_type * pArr[]);
void init_courseArr(void);
void enterNew(struct db_type *pArr[]);
void writeDisk(struct db_type * pArr[]); 
void emptyDisk(void); 
void loadDisk(struct db_type * pArr[]); 

void displayCourses(void);
//void enterNew(struct db_type *pArr[]);
void displayDB(struct db_type *pArr[]);
void removeRecord(struct db_type *pArr[]);
void swap(struct db_type *pArr[]);
void sort(struct db_type *pArr[]);



int main(int argc, char *argv[])
{
    
    struct db_type * db_pArr[SIZE];  // main db storage

    init_list(db_pArr);  // set to NULL
    
    init_courseArr();  // load course from diskfile
    
    char choice;
    for(; ;){
   
      choice = prompt_menu();
      switch (choice)
      {
         case 'n': enterNew(db_pArr); break;
         case 'd': displayDB(db_pArr); break;
         case 'w': writeDisk(db_pArr);  break;    
         case 'l': loadDisk(db_pArr); break;
         case 's': sort(db_pArr); break;
     
         case 'c': clearDB(db_pArr); break;  
         case 'e': emptyDisk();break;

         case 'v': displayCourses();break;
         case 'p': swap(db_pArr); break;
         case 'r': removeRecord(db_pArr);break;
         
         case 'q': exit(1); // terminate the whole program
       }
  
     }
     return 0;
}

void init_list(struct db_type * pArr[]){
  int t;
  for (t=0; t<SIZE; t++)
  { 
     pArr[t]= NULL;
  }
}

void clearDB(struct db_type * pArr[]){
   char c3[3];
   printf("are you sure to clear db? (y) or (n)? ");
 
   fgets(c3,3,stdin);
   
   if(! strcmp(c3, "y\n"))  
      init_list(pArr);
}


char prompt_menu(void){
  char s[80];
  while(1){
    printf("\n-----------------------------------------------------------------\n");
    printf("|    %-20s","(N)ew record");
    printf("%-20s","(R)emove record");
    printf("Swa(p) records\t|\n");
    printf("|    %-20s","(S)ort database");
    printf("%-20s","(C)lear database");
    printf("(D)isplay db\t|\n");
  
    printf("|    %-20s","(L)oad disk");
    printf("%-20s","(W)rite disk");
    printf("(E)mpty disk\t|\n");
  
    printf("|    %-20s", "(V)iew courses");//|\tSwa(p) record\t(Q)uit\t\t\t\t|\n");
    printf("%-20s","(Q)uit");
    printf("*Case Insensitive*\t|\n");
    printf("-----------------------------------------------------------------\n");
    printf("choose one: ");
  
    fgets(s,50, stdin); // \n added
   
    if (strlen(s) == 2 && strchr("edlsuqrcwnvpr", tolower(*s))) 
       return tolower(*s); // s[0], return the first character of s  
    //else
    printf("not a valid input!\n");
   
 }
}

/* display all or specified course */
void displayCourses(void){  
    char input[80];
    char beg[80];
    strcpy(beg, "EECS");
    int i;
  

    printf("course code (or 'a')? ");
    //the user gets the input from user and store it in char input
    fgets(input,50, stdin);
    sscanf(input,"%s", input);
    // checks if the inputed char is 'a', which mean it will store all the courses in the database 
    if(strchr("a", *input)){
        for (i=0; i<=20; i++){
            printf("%s\t%-40s%-5s %s-%s     %s\n", courseArr[i].code, courseArr[i].title, courseArr[i].date, courseArr[i].time_start, courseArr[i].time_end, courseArr[i].location);
        }
    }
    // if the user inputs just the course number, it will add the number after the char beg which already is storing 'EECS'
   if(strlen(input) ==4){
       strcat(beg, input);
      
   }
    //loop checks if the inputed course char input or beg is stored in the courses data base, if so it will print the course and the loop breaks 
    for (i=0; i<=20; i++){
        
        if((strcmp (courseArr[i].code , input)==0) | strcmp(courseArr[i].code, beg)==0)  {
            printf("1. %s\t%-40s%-5s %s-%s     %s\n", courseArr[i].code, courseArr[i].title, courseArr[i].date, courseArr[i].time_start, courseArr[i].time_end, courseArr[i].location);
            break;
            }
        

         }
    


  // the provide sample.out uses "%s\t%-40s%-5s %s-%s   %s\n" as formatting string for printing each course info
      
}



/* input items into the list */
void enterNew(struct db_type * pArr[SIZE]){  
 
    char num[200]= {0};
  
    int i;
    int  n;

    pArr[i]= malloc(sizeof(struct db_type));
    //name is asked and then make sure there isn't \n when fgets is used and change it to '\0'
    printf("name: ");
    if(fgets((*pArr[i]).name, sizeof((*pArr[i]).name), stdin)!=0){
      (*pArr[i]).name[strcspn((*pArr[i]).name, "\n")]= '\0';

    }
    //age is asked and uses fgets, I used char num to store the inputed age and then change it to a int value before adding it to pArr[i]->age 

    printf("age:");
    if(fgets(num, 200, stdin)!=0){
      pArr[i]->age= atoi(num);

    }   
    //course1 is asked and then make sure there isn't \n when fgets is used and change it to '\0'
    printf("course-1:");
    if(fgets(pArr[i]->course1, sizeof(pArr[i]->course1), stdin)!=0 ){
      pArr[i]->course1[strcspn(pArr[i]->course1, "\n")]='\0';
    }
    while(1){
      char nullS[199]={'\0'};
      char beg[200];
      strcpy(beg, "EECS");
      //if the user just inputed the course number instead of EECS####
      if(strlen(pArr[i]->course1) ==4){
        //char beg contain sting 'EECS' so it with strcat it adds the number the user inputed to change #### to EECS####
        strcat(beg,pArr[i]->course1);
        //We also need to change pArr[i]->course1 inputed so it stores the right format of how courses should be displayed (starting with EECS follow by pArr[i]->course1 which stores the digit of the course)
       // to do so, we first change pArr[i]->course1 to equal '\0' which is stored in char nullS and then uses strcat to add the beg char into pArr[i]->course1
        //and char beg at this point contains EECS followed by the inputed digits for the course
        strcpy(pArr[i]->course1, nullS);
        strcat(pArr[i]->course1, beg);
   
      }  
      //loops checks if inputed course is stored in the course data base (courseArr[]), if true loop end  
      for (n=0; n<=20; n++){

        if((strcmp (courseArr[n].code , pArr[i]->course1)==0) | strcmp(courseArr[n].code, beg)==0)  {
          break;
        
        }
  
      }
      //the program would ask the user for another course if the previous course inputed isn't stored in the course data base
      if(n> 20){
        printf("course does not exist, enter again:");
        if(fgets(pArr[i]->course1, sizeof(pArr[i]->course1), stdin)!=0 ){
          pArr[i]->course1[strcspn(pArr[i]->course1, "\n")]='\0';
        }
      }
      //loop breaks when the inputed course is stored in the course data base (courseArr[])
      else
      {
        break;
      }

    }
    // code for course 2 is the same format/layout as course 1
   
    printf("course-2:");
    if(fgets(pArr[i]->course2, sizeof(pArr[i]->course2), stdin)!=0 ){
      pArr[i]->course2[strcspn(pArr[i]->course2, "\n")]='\0';
    }
    int j;
    

    while(1){
      char beg[200];
      char nullS[199]={"\0"};
      strcpy(beg, "EECS");
      if(strlen(pArr[i]->course2) ==4){
        
        strcat(beg,pArr[i]->course2);
        
        //printf("%s\n ", beg);
        strcpy(pArr[i]->course2, nullS);
        strcat(pArr[i]->course2, beg);
        //printf("p %s\n", pArr[i]->course2);
      
      }      
      for (j=0; j<=20; j++){

        if((strcmp (courseArr[j].code , pArr[i]->course2)==0) | strcmp(courseArr[j].code, beg)==0)  {
          
          break;
        
        }
  
      }
      if(j>20){
        printf("course does not exist, enter again:");
        if(fgets(pArr[i]->course2, sizeof(pArr[i]->course2), stdin)!=0 ){
          pArr[i]->course2[strcspn(pArr[i]->course2, "\n")]='\0';
        }
      }
      else {
        break;
      }
   
    }
  // checks if course1 end time is equal to course2 start time or if course1 end time is > than course2 and this is done by converting the char times to a integer type
  if( ((strcmp(courseArr[n].time_end, courseArr[j].time_start)==0 | atoi(courseArr[n].time_end)> atoi(courseArr[j].time_start)))){

      strcpy(pArr[i]->status, "ATTENTION! time conflict");
      printf("%s", pArr[i]->status);
    }   
   
  
  
  else{
      strcpy(pArr[i]->status, "SUCCESSFUL! no time conflict");
      printf("%s", pArr[i]->status);
    }
 
// i increase if there is going to be another new record going to be entered into pArr[i]
  i++;
        

    
}
/* display records */
void displayDB(struct db_type * pArr[]){
  int i, n;
  //loops unitl Null which is the end of the array
   for( i=0; pArr[i]!= NULL; i++){
    
    printf("name: %s\n", (*pArr[i]).name);
    printf("age: %d\n", pArr[i]->age);
   //loop checks which pArr[i]->course1 equals to a course in courseArr[n], so it can print the whole course information (code,name,date,times, and locations)
    for( n=0; n<=SIZE; n++){
      if((strcmp (courseArr[n].code , pArr[i]->course1)==0) ) {
        printf("%s\t%-40s%-5s %s-%s     %s\n", courseArr[n].code, courseArr[n].title, courseArr[n].date, courseArr[n].time_start, courseArr[n].time_end, courseArr[n].location);
      }
      if((strcmp (courseArr[n].code , pArr[i]->course2)==0)){
        printf("%s\t%-40s%-5s %s-%s     %s\n", courseArr[n].code, courseArr[n].title, courseArr[n].date, courseArr[n].time_start, courseArr[n].time_end, courseArr[n].location);
      }
    }
    printf("remarks: %s\n", pArr[i]->status);
    printf("\n");
  }
 
}


/* remove an existing item */
void removeRecord (struct db_type * pArr[]) 
{
 char removeName[fieldLength];
 char nullS[19]={"\0"};
 //ask for the name that user wishes to remove and uses fgets and uses strcspn to not have '\n' added
 printf("enter full name to remove: ");
 if(fgets(removeName, fieldLength, stdin)!=0){
    removeName[strcspn(removeName,"\n")]= '\0';

  }
 int i,j;
 int n=0;
 //loop until pArr[i] equals Null
for(i=0; pArr[i]!= NULL; i++){
  //if inputed name is stored in pArr[i].name then it will use strcpy to change pArr[i].name to '\0'
  // then shift information after the inforamtion that is needed to be removed into that index
  if(strcmp((*pArr[i]).name, removeName)==0){
    strcpy((*pArr[i]).name,nullS );
    pArr[i] = pArr[i+1];
    pArr[i+1]= pArr[i+2];
    pArr[i+2]=NULL;
    
  
  
    printf("record [%s] removed sucessfully.", removeName);
    n++;
  }

 
}

  

}


/* swap records */
void swap(struct db_type * pArr[]){
  int i=0,n=i+1;
  //loops until pArr[n] equals Null, which means its a the end of the array
  while(pArr[n]!=NULL){
    struct db_type tmp = *pArr[i];
    *pArr[i]= *pArr[n];
    *pArr[n]= tmp;
    i= n+1;
    n=i+1;
  }

  
} 
/* load from course.txt, store into (global) array of courses  */
void init_courseArr(void){ 
 
   FILE *fr; //file pointer
   fr = fopen (courseFile, "r");
   char arr[50];  
   int count = 0;
   while ((fgets(arr,100,fr)) != NULL)
   {  
     strncpy(courseArr[count].code,  arr, strlen(arr)-1); // remove \n  
     courseArr[count].code[strlen(arr)-1] = '\0';  //to be safe
   
     fgets(arr,100,fr);  
     strncpy(courseArr[count].title ,  arr, strlen(arr)-1);
     courseArr[count].title[strlen(arr)-1] = '\0';  //to be safe
     
          
     fgets(arr,100,fr); 
     strncpy(courseArr[count].date,  arr, strlen(arr)-1);
     courseArr[count].date[strlen(arr)-1] = '\0';  //to be safe
     
     // other ways, remove \n before
     fgets(arr,100,fr);
     arr[strlen(arr)-1] = '\0';
     strcpy(courseArr[count].time_start,  arr);
      
     fgets(arr,100,fr);
     arr[strlen(arr)-1] = '\0';
     strcpy(courseArr[count].time_end,  arr);
      
     fgets(arr,100,fr);
     arr[strlen(arr)-1] = '\0';
     strcpy(courseArr[count].location,  arr); 
    
     count++;
     fgets(arr,100,fr); // read the empty line
   }

   strcpy(courseArr[count].code, "EECS0000"); // a terminator token structure

   fclose(fr);
   
 }
    
/************************ DISK IO *****************************************************************/

void writeDisk(struct db_type * pArr[]){
  FILE *fp;
  int i;

  if ( (fp=fopen(diskFile,"ab")) == NULL)
  {
    printf("cannot open file\n");
    return;
  }

  
  for (i=0; i< SIZE ; i++)
  {
     if ( pArr[i] != NULL)
     {  
       if (fwrite( pArr[i], sizeof(struct db_type), 1, fp) != 1)
       { 
          printf("file write error\n");
       }
     } 
   }
   fclose(fp);

}

void emptyDisk(void){

  FILE *fp;
  
  char c3[3];
  printf("are you sure to empty disk? (y) or (n)? ");
  fgets(c3,3,stdin);
  if(strcmp(c3, "y\n"))  
     return;
 
  //else
  if ( (fp = fopen(diskFile,"w")) == NULL)
  {
     printf("no file to open\n");
     return;
  }
  fclose(fp); // open close, will empty the file
}


void loadDisk(struct db_type * pArr[]){
  FILE *fp;
  int i;
  char c3[3];
  printf("will overwrite current records. are you sure to load disk? (y) or (n)? ");
  fgets(c3,3,stdin);
  if(strcmp(c3, "y\n"))  
     return;

  struct db_type * tmp;  
  
  if ( (fp = fopen(diskFile,"r")) == NULL)
  {
    printf("cannot open file\n");
    return;
  }

  init_list(pArr);
  for (i=0; i < SIZE ; i++)
  {    
     
     tmp =  (struct db_type *) malloc (sizeof(struct db_type));   
     
     if (fread( tmp, sizeof(struct db_type), 1, fp) != 1)
     {
       if (feof(fp))
       { fclose(fp); 
         return;
       }
       printf("file read error\n");
     }
     else pArr[i] = tmp;
  }
}

/****bonus*************************************************************************************/

/* sort the records by ages */
void sort(struct db_type * pArr[])
{
  int i;
  for (i=0; pArr[i]!= NULL; i++){
    int j; int small=i;
    for(j=i+1; pArr[j]!=NULL; j++){
      if (pArr[j]->age < pArr[small]->age){
        small= j;
      }
    }
    //swap the pArr informations so its sorted from smallest to biggest
    struct db_type tmp = *pArr[i];
    *pArr[i]= *pArr[small];
    *pArr[small]= tmp;
   
     }
} 
