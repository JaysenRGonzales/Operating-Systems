//Author: Jaysen Gonzales

/*
Write a program that takes a reference string and the number
of frames as inputs to simulate page replacement algorithms. 
Suppose the maximum length of a reference string is 20 and there are 5 diffent
numbers of pages. Randomly generate a reference string, e.g. 2 1 3 4 5 2 3 ... 
Take the number of frames as an input from the user. Find out the different number of page faults 
using the Optimal and LRU algorithms.  If there is a tie, use the FIFO algorithm to break 
the tie. Print out the page replacement process and you can see how LRU differs from 
the optimal. */

#include <iostream>
#include <stdio.h> 
#include <stdlib.h>
#include <ctime>
#include <list> 
#include <iterator> 
#include <vector>


using namespace std;

void fifo(int ref_string[], int frames);
int optimal(int array[], int frames);
int LRU(int ref_string[], int frames);

#define MAX_STRINGS 20


int main()
{
    int x,y;
    //number of frames as an input
    int frames;
    cout<<"WELCOME, please number of frames 1-20:  ";
    cin >> frames;
    cout << endl;

    int ref_string[MAX_STRINGS];

    srand(time(0));

    int random;
    
    cout<<"random reference string generated:\n";
    for(int i =0; i < MAX_STRINGS; i++){

        random = rand() % 5 + 1;
        ref_string[i] =  random;
        cout<< ref_string[i]<< " ";

    }
   

    cout << endl;

    x = LRU(ref_string, frames);
    y = optimal(ref_string, frames);
    if(x==y)
    {
        fifo(ref_string, frames);
    }

   
    return 0;

}

/*



FIFO ALGORITHM



*/

void fifo(int ref_string[], int frames){

    //create table to hold frames  
    list <int> table;

    //creating intial empty table from user input of frames
    //to initialize I set all values to -1
    for(int i = 0; i < frames; i++)
    {
        table.push_back(-1);
    }
    
    int page_fault_fifo = 0;

    //iterator to search table 
    list <int> :: iterator it;
    bool flag;

    cout<<"\n\t---------------------";
    cout<<endl<<"\tFIFO TABLE";
    cout<<"\n\t---------------------\n";
    for(int j = 0; j<MAX_STRINGS; j++){

        flag = false;
        
        //searching table to see if reference string exist in memory
        for(it = table.begin(); it != table.end(); ++it) {
            
            if(*it == ref_string[j])
            {
                flag = true;
            }    
            //cout<<"\t"<<*it<<"\t";
        }
        
        cout<<endl;
        //if page exist, then pop and push no value into table
        if(flag != true)
        {
            cout<<"* -> ";
            table.pop_back();
            table.push_front(ref_string[j]);
            page_fault_fifo++;
        }

        for(it = table.begin(); it != table.end(); ++it) {
              
            cout<<"\t"<<*it<<"\t";
        }

        

    }
    
    cout <<"\nPAGE FAULTS WITH FIFO:  "<< page_fault_fifo<<"\n\n";

    

}

/*

    Optimal Algorithm

*/

int optimal(int array[], int frames){

    // create empty vector
    cout<<"\n\t---------------------";
    cout<<endl<<"\tOPTIMAL TABLE";
    cout<<"\n\t---------------------\n";
    cout<<"\nRan short on time and could not get display to show\n";

    vector<int> future;
    int page_fault = 0;

    for (int i = 0; i <MAX_STRINGS; i++)
    {
        
        int k;
        //if page exists break to next in reference string
        for (k = 0; k < future.size(); k++){
            
            if (future[k] == array[i])
            {
                break;
            }
        }
        
        //We want future to equal amount of frames
        if (k==future.size())
        {
            if (future.size() < frames){

                future.push_back(array[i]);
            }
            //once filled we can look at which value is furthest
            else
            {
                int index=i+1;
                int val = 0; 
                int furth = index;
                for (int r = 0; r < future.size(); r++)
                {
                    int j;
                    for (j = index; j <MAX_STRINGS; j++)
                    {
                        if (future[r] == array[j])
                        {
                            if (j > furth)
                            {
                                val = r;
                                furth = j;
                            }
                            break;
                        }
                    }
                    if (j == MAX_STRINGS)
                    {
                        val = r;
                        break;
                    }
                }
                future[val] = array[i];

            }
            page_fault++;
            cout<<i<<" round has"<<"page fault when loading page "<<array[i]<<"\n\n";
        }
        
        
        
        
       
    }
    cout<<"OPTIMAL PAGE FAULTS: "<<page_fault<<"\n\n";
    return page_fault;


}

/*

LRU algorithm


*/


int LRU(int ref_string[], int frames){
    
    int page_fault = 0;
    int i;
    //initialize memory table and table for recently used tracker
    int frame[frames],rec_used[frames];

    cout<<"\n\t----------------------\n";
    cout<<"\t LRU TABLE";
    cout<<"\n\t----------------------\n";
    
    //fill table with empty values = -1
    for(int i = 0; i<frames;i++)
    {
        frame[i]= -1;
        rec_used[i] = 0;
    }

    i=0;


    while(i<MAX_STRINGS)
    {

        int j=0;
        bool flag= false;

        // search memory to see if reference page
        while(j<frames)
        {
            //checking if page is in current memory
            if(ref_string[i]==frame[j]){  
                flag=true;
                // if it is then increment its recently used value
                rec_used[j]=i+1;

            }
            j++;

        }   

        j=0;  

        //if page doesnt exist in memory we search for LRU in memory table
        if(flag==false)
        {
            int min=0,k=0;
            while(k<frames-1)
            {
                //searching for minimum value in recently used table
                if(rec_used[min]>rec_used[k+1]) 
                {
                    min=k+1;
                }
                k++;

            }

            //replace LRU with current page needed for memory 
            frame[min]=ref_string[i]; 

            //increment so this frame is not LRU anymore.
            rec_used[min]=i+1;    

            page_fault++;          
            cout<<"* -> ";

            
        }
        while(j<frames)
        {

                
            cout<<"\t"<<frame[j]<<"\t";
            j++;

        }
        cout<<endl;
        
        //increment for next page.
        i++; 
    }

    cout <<"\nPAGE FAULTS WITH LRU:  "<< page_fault<<"\n\n";
    return page_fault;
}