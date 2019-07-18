#include<stdio.h> 
//Author: Jaysen Gonzales JRG301@txstate.edu

struct Student 
{
   char firstname[20];
   double gpa;

};

  
int main() 
{
   struct Student list[50];
   int counter = 0;
   int i = 0;
   printf("Enter in '[Student name] [gpa]', press Crtl-D when done with entries\n");
   //creating the list of students 
   while(scanf("%s%lf", list[i].firstname, &list[i].gpa) != EOF){
      counter++;
      i++;
     
   }
   //searching for students with 3.0 gpa and greater
   for(i =0; i < counter; i++)
      if(list[i].gpa >= 3.0){
         printf("%s\n",list[i].firstname);
        
      }
   

  return 0;

}
