#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Freddie Liu, 260551011, freddie.liu@mail.mcgill.ca


// Record / Node for the linked list.
// You MUST use the exact structure. No modification allowed.
typedef struct PersonalInfoRecord
{
        char id[10];
        char ptype;
        char name[31];

        union
        {
                struct
                {
                        char dept[31];
                        int hireyear;
                        char tenured;
                }prof;
                struct
                {
                        char faculty[31];
                        int admyear;
                }stud;
        }info;

        struct PersonalInfoRecord *next;
} PersonalInfoRecord;
//
// Use this in your code as
// PersonalInfoRecord pir; PersonalInfoRecord *pirp; etc ...
// Whatever other functions you need.

//sort list by acsending order
void sortedInsert(struct PersonalInfoRecord** head_ref,
                  struct PersonalInfoRecord* new_node)
{
    struct PersonalInfoRecord* current;

    // empty/head/tail list
    if (*head_ref == NULL
        || atoi((*head_ref)->id)
               >= atoi(new_node->id)) {
        new_node->next = *head_ref;
        *head_ref = new_node;
    }
    //navigate node before insertion
    else {
        current = *head_ref;
        while (current->next != NULL
               && atoi(current->next->id) < atoi(new_node->id)) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

//delete a node
void deleteNode(struct PersonalInfoRecord** head_ref, char del_id[]) {
  struct PersonalInfoRecord *temp = *head_ref, *prev;

  if (temp != NULL && atoi(temp->id) == atoi(del_id)) {
  *head_ref = temp->next;
  free(temp);
  return;
  }
  // Find the id to be deleted
  while (temp != NULL && atoi(temp->id) != atoi(del_id)) {
  prev = temp;
  temp = temp->next;
  }

  // If the id is not present
  if (temp == NULL) return;

  // Remove the node
  prev->next = temp->next;

  free(temp);
}

//search a node
int searchNode(struct PersonalInfoRecord** head_ref, char ser_id[]) {
  struct PersonalInfoRecord* current = *head_ref;

  while (current != NULL) {
  if (atoi(current->id) == atoi(ser_id)) return 1;
  current = current->next;
  }
  return 0;
}

//update a node for prof
//Remark: The id and type of a person will never change, and any "update" input will always contain those two fields.
void updateProf(struct PersonalInfoRecord** head_ref, char uprof_id[], char uprof_name[], char uprof_dept[], int uprof_hireyear, char uprof_tenured[]) {
  struct PersonalInfoRecord* current = *head_ref;

  while (current != NULL) {
  if (atoi(current->id) == atoi(uprof_id)){
          //it's just empty char, not neccessary a null pointer.
          //no need to consider ptype as per instruction.
	  /*for the last input, if we don't modify, no additional comma/space,
           * just press enter/newline. hooray! we allow to input space now!
           * hooray again!!!*/
          if(uprof_name[0] != '\0') strncpy(current->name, uprof_name, 30);
          if(uprof_dept[0] != '\0') strncpy(current->info.prof.dept, uprof_dept, 30);
          if(uprof_hireyear != '\0') current->info.prof.hireyear = uprof_hireyear;
          /* 2 conditions here to restrict tenure updates (no modification cases)
           * since the idea of \0 doesn't work
           * (1) not press ENTER directly
           * (2) input has no space 
           * if we don't presee enter directly AND no space detected, then modify
           */
	  if(uprof_tenured[0] != '\n' && strchr(uprof_tenured,' ') == NULL) strncpy(&current->info.prof.tenured, uprof_tenured, 1);
          return;
  }
  current = current->next;
  }
}

//update a node for stud
//Remark: The id and type of a person will never change, and any "update" input will always contain those two fields.
void updateStud(struct PersonalInfoRecord** head_ref, char ustud_id[], char ustud_name[], char ustud_faculty[], int ustud_admyear) {
  struct PersonalInfoRecord* current = *head_ref;

  while (current != NULL) {
  if (atoi(current->id) == atoi(ustud_id)){
          //it's just empty char, not neccessary a null pointer.
          //no need to consider ptype as per instruction.
          if(ustud_name[0] != '\0') strncpy(current->name, ustud_name, 30);
          if(ustud_faculty[0] != '\0') strncpy(current->info.stud.faculty, ustud_faculty, 30);
          if(ustud_admyear != '\0') current->info.stud.admyear = ustud_admyear;
          return;
  }
  current = current->next;
  }
}

//create node for prof
struct PersonalInfoRecord* newProf(char prof_id[], char prof_ptype[], char prof_name[], char prof_dept[], int prof_hireyear, char prof_tenured[])
{
    //allocate node 
    struct PersonalInfoRecord* new_node
= (struct PersonalInfoRecord*)malloc(
sizeof(struct PersonalInfoRecord));

    //put in the data 
    strncpy(new_node->id, prof_id, 10);
    strncpy(&new_node->ptype, prof_ptype, 1);
    strncpy(new_node->name, prof_name, 30);
    strncpy(new_node->info.prof.dept, prof_dept, 30);
    new_node->info.prof.hireyear = prof_hireyear;
    strncpy(&new_node->info.prof.tenured, prof_tenured, 1);
    new_node->next = NULL;
    //checkpoint
    /*
    printf("%s,%c,%s,%s,%d,%c\n", new_node->id,new_node->ptype,new_node->name,new_node->info.prof.dept,new_node->info.prof.hireyear,new_node->info.prof.tenured);*/
    return new_node;

}

//create node for stud
struct PersonalInfoRecord* newStud(char stud_id[], char stud_ptype[], char stud_name[], char stud_faculty[], int stud_admyear)
{
    //allocate node
    struct PersonalInfoRecord* new_node
= (struct PersonalInfoRecord*)malloc(
sizeof(struct PersonalInfoRecord));

    //put in the data
    strncpy(new_node->id, stud_id, 10);
    strncpy(&new_node->ptype, stud_ptype, 1);
    strncpy(new_node->name, stud_name, 30);
    strncpy(new_node->info.stud.faculty, stud_faculty, 30);
    new_node->info.stud.admyear = stud_admyear;
    new_node->next = NULL;
    //checkpoint
    /*
    printf("%s,%c,%s,%s,%d\n", new_node->id,new_node->ptype,new_node->name,new_node->info.stud.faculty,new_node->info.stud.admyear);
    */
    return new_node;

}

//print list
void printList(struct PersonalInfoRecord* head)
{
    char prptype[2];
    struct PersonalInfoRecord* temp = head;
    //checkpoint
    /*
    printf("reached in the function\n");*/
    //empty list
    if(temp == NULL) printf("\n");
    //not empty
    while (temp != NULL) {
            strncpy(prptype,&temp->ptype,1);
            if(strcmp(prptype,"P") == 0){
                printf("%s,%c,%s,%s,%d,%c\n", temp->id,temp->ptype,temp->name,temp->info.prof.dept,temp->info.prof.hireyear,temp->info.prof.tenured);
            }
            else if(strcmp(prptype,"S") == 0){
                printf("%s,%c,%s,%s,%d\n", temp->id,temp->ptype,temp->name,temp->info.stud.faculty,temp->info.stud.admyear);
            }
        temp = temp->next;
    }
}

//import data to file
void fileprintList(struct PersonalInfoRecord* head, FILE* rptfile)
{
    char fprptype[2];
    struct PersonalInfoRecord* temp = head;
    //checkpoint
    /*
    printf("reached in the function\n");*/
    //empty list
    if(temp == NULL) fprintf(rptfile,"\n");
    //not empty
    while (temp != NULL) {
            strncpy(fprptype,&temp->ptype,1);
            if(strcmp(fprptype,"P") == 0){
                fprintf(rptfile, "%s,%c,%s,%s,%d,%c\n", temp->id,temp->ptype,temp->name,temp->info.prof.dept,temp->info.prof.hireyear,temp->info.prof.tenured);
            }
            else if(strcmp(fprptype,"S") == 0){
                fprintf(rptfile, "%s,%c,%s,%s,%d\n", temp->id,temp->ptype,temp->name,temp->info.stud.faculty,temp->info.stud.admyear);
            }
        temp = temp->next;
    }
}

//free list
void freeList(struct PersonalInfoRecord* head){
    struct PersonalInfoRecord* current;
    while (head != NULL){
        current = head;
        head = head->next;
        free(current);
    }
}

// The main of your application
int main(int argc, char *argv[])
{
        char inputbuffer[100], *input; // to store each input line;
        char indicator[2],ptype[2],hyr[5],ayr[5],tenured[2];
        const char *Insert = "I";
        const char *Delete = "D";
        const char *Prof = "P";
        const char *Stud = "S";
        struct PersonalInfoRecord* head = NULL;/*ALWAYS remember to declare 
					        *outside of the loop*/
        struct PersonalInfoRecord* new_node;

        // declare other variables as needed, etc.
        // do not forget to check input arguments...
        if (argc != 2) { // check correct number of arguments
        fprintf(stderr, "Error, please pass the database filename as the argument.\nUsage ./pimapp <dbfile>\n");
        exit(1);
        }
        else{
                while (fgets(input=inputbuffer, 100, stdin) != NULL) // Get each input line.
                {
                        //data input
                        if(strncmp(input, "LIST", 4) != 0 && strncmp(input, "END", 3) != 0){
                                struct PersonalInfoRecord pir;
                                snprintf(indicator,sizeof(indicator),"%s",strsep(&input, ","));
                                snprintf(pir.id,sizeof(pir.id),"%s",strsep(&input, ","));
                                snprintf(&pir.ptype,sizeof(2),"%s",strsep(&input, ","));
                                //use &pir.ptype as a buffer
                                //if we need to print it, printf("%c",pir.ptype)
                                strncpy(ptype,&pir.ptype,1);
                                snprintf(pir.name,sizeof(pir.name),"%s",strsep(&input, ","));
                                //checkpoints for first 4 elements
                                /*
                                printf("%s\n", indicator);
                                printf("%s\n", pir.id);
                                printf("%s\n", ptype);
                                printf("%s\n", pir.name);
                                */

                                //insert prof
				if(strcmp(indicator,Insert) == 0 && strcmp(ptype,Prof) == 0){
                                        snprintf(pir.info.prof.dept,sizeof(pir.info.prof.dept),"%s",strsep(&input, ","));
                                        snprintf(hyr,sizeof(hyr),"%d",atoi(strsep(&input, ",")));
                                        pir.info.prof.hireyear = atoi(hyr);
                                        snprintf(tenured,sizeof(tenured),"%s",strsep(&input, ","));
                                        strncpy(&pir.info.prof.tenured,tenured,1);
					//check if ID already existed in the list
                                        //if yes, update, if not, create new.
                                        if (searchNode(&head, pir.id)) {
                                                updateProf(&head, pir.id,pir.name,pir.info.prof.dept,pir.info.prof.hireyear,&pir.info.prof.tenured);
                                                //checkpoint
                                                /*
                                                printf("%s is found\n", pir.id);*/
                                        }
                                        else{
                                                new_node = newProf(pir.id,&pir.ptype,pir.name,pir.info.prof.dept,pir.info.prof.hireyear,&pir.info.prof.tenured);
                                                sortedInsert(&head, new_node);
                                        }
                                        //checkpoints for profs
                                        /*
                                        printf("%s\n", pir.info.prof.dept);
                                        printf("%d\n", pir.info.prof.hireyear);
                                        printf("%s\n", &pir.info.prof.tenured);
                                        printf("good\n");*/
                                }
				//insert stud
                                else if(strcmp(indicator,Insert) == 0 && strcmp(ptype,Stud) == 0){
                                        snprintf(pir.info.stud.faculty,sizeof(pir.info.stud.faculty),"%s",strsep(&input, ","));
                                        snprintf(ayr,sizeof(ayr),"%d",atoi(strsep(&input, ",")));
                                        pir.info.stud.admyear = atoi(ayr);
                                        //check if ID already existed in the list
                                        //if yes, update, if not, create new.
					if (searchNode(&head, pir.id)) {
                                                updateStud(&head, pir.id,pir.name,pir.info.stud.faculty,pir.info.stud.admyear);
                                                //checkpoint
                                                /*
                                                printf("%s is found\n", pir.id);*/
                                        }
					else{
                                        new_node = newStud(pir.id,&pir.ptype,pir.name,pir.info.stud.faculty,pir.info.stud.admyear);
                                        sortedInsert(&head, new_node);
                                        }
                                        //checkpoints for studs
                                        /*
                                        printf("%s\n", pir.info.stud.faculty);
                                        printf("%d\n", pir.info.stud.admyear);
                                        printf("good\n");*/
                                }
				//deletion
                                else if(strcmp(indicator,Delete) == 0){
                                        deleteNode(&head, pir.id);
                                        //checkpoint
                                        /*
                                        printf("delete %s successfully\n",pir.id);*/
                                }

                        }
                        //LIST
                        else if(strncmp(input, "LIST", 4) == 0){
                                //checkpoint
                                /*
                                printf("reached IF condition\n");
                                */
                                printList(head);
                        }
                        //END
                        else if(strncmp(input, "END", 3) == 0){  // We are asked to terminate.
                                FILE *dbfile = fopen(argv[1], "wt");
                                if (dbfile == NULL) { // error if dbfile cannot be read
                                        fprintf(stderr, "Error, unable to open %s for writing.\n", argv[1]);
                                        exit(3);
                                }
                                else{
                                        fileprintList(head,dbfile);
                                }
                                //clean up
				fclose(dbfile);
				freeList(head);
				break;
                        }
		}
        }

        return 0; // Appropriate return code from this program.

}
