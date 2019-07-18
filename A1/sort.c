#include<stdio.h>
#include<string.h> 
//author: Jaysen Gonzales JRG301

struct Student{
    char firstname[20];
};

int main(){
    struct Student list[20];
    int counter = 0;
    int i = 0;
    int j = 0;
    struct Student temp;
    
    while(scanf("%s", list[i].firstname) != EOF){
        counter++;
        i++;
    }
    
    for(i = 0; i < counter; i++){
       
        for(j = i; j < counter; j++){
            //compare using strcmp >0 for first char that does not match has a greater value in i than j
            if(strcmp(list[i].firstname, list[j].firstname) > 0){
                //store name in temp struct
                strcpy(temp.firstname, list[i].firstname);
                //place current higher alphabetic letter in current position
                strcpy(list[i].firstname, list[j].firstname);
                //swap temp into lower alphabetic position 
                strcpy(list[j].firstname, temp.firstname);
            }
        }
    }

    //display alphabetically results
    for(i = 0; i < counter; i++){
        printf("%s\n", list[i].firstname);
    }
    
    return 0;
}
