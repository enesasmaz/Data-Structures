/*
PLEASE, DO NOT CHANGE void display(bool verbose, bool testing), int getUsableDay() and int getUsableTime() FUNCTIONS.
YOU HAVE TO WRITE THE REQUIRED  FUNCTIONS THAT IS MENTIONED ABOVE. YOU CAN ADD NEW FUNCTIONS IF YOU NEED.
*/

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <iomanip>

#include "task_management_tool.h"

using namespace std; 


void WorkPlan::display(bool verbose,bool testing)
{
	string inone="***";
	if (head!=NULL)
	{
		Task *pivot =new Task;
		Task *compeer =new Task;
			
		pivot=head;
		do
		{
			if(testing)
				inone+=" ";
			else
				cout << pivot->day <<". DAY"<< endl;
			compeer=pivot;
			while(compeer!=NULL)
			{
				string PREV= compeer->previous!=NULL?compeer->previous->name:"NULL";
				string NEXT=compeer->next!=NULL?compeer->next->name:"NULL";
				string CONT=compeer->counterpart!=NULL?compeer->counterpart->name:"NULL";
				if (testing)
					inone+=compeer->name;
				else
					if(verbose)
						cout<<"\t"<<setw(2)<< compeer->time <<":00\t"<< PREV<<"\t<- "<< compeer->name <<"("<< compeer->priority <<")->\t"<<NEXT <<"\t |_"<<CONT<<endl;
					else
						cout<<"\t"<<setw(2)<< compeer->time <<":00\t"<< compeer->name <<"("<< compeer->priority <<")"<<endl;				
				compeer=compeer->counterpart;
			}
			pivot=pivot->next;
		}while(pivot!=head);
		if(testing)
		{
			cout<<inone<<endl;
			cout<<"(checking cycled list:";
			if (checkCycledList())
				cout<<" PASS)"<<endl;
			else
				cout<<" FAIL)"<<endl;
		}
	}
	else
		cout<<"There is no task yet!"<<endl;
}

int WorkPlan::getUsableDay()
{
	return usable_day;
}

int WorkPlan::getUsableTime()
{
	return usable_time;
}


void WorkPlan::create()
{
	head = NULL;
}

void WorkPlan::close()
{
	while (head != NULL)
	{
		remove(head);
	}
}

void WorkPlan::add(Task *task)
{
    nd = new Task;
	nd -> name = new char[strlen(task -> name) + 1];
    strcpy(nd -> name, task -> name);
    nd -> day = task -> day;
    nd -> time = task -> time;
    nd -> priority = task -> priority;
    
    if(head == NULL){
        head = nd;
        nd -> next = NULL;
        nd -> previous = NULL;
        nd -> counterpart = NULL;
        nd -> next = head;
        nd -> previous = head;
        return;
    }
    
    else if(nd -> day <= head -> day){
		
		if(nd -> time < head -> time && nd -> day == head -> day && head -> next == head){
			
			temp = head;
            nd -> counterpart = temp;
            nd -> previous = temp -> previous;
			head = nd;
            temp -> next = NULL;
            temp -> previous = NULL;
			return;
			
		}
	
		
        else if(nd -> time < head -> time && nd -> day == head -> day){
            
            temp = head;
            nd -> counterpart = temp;
            nd -> previous = temp -> previous;
            temp -> previous -> next = nd;
            nd -> next = temp -> next;
            temp -> next -> previous = nd;
            head = nd;
            temp -> next = NULL;
            temp -> previous = NULL;
			return;
        }
        else if(nd -> day < head -> day){
        
            temp = head;
            temp -> previous -> next = nd;
            nd -> previous = temp -> previous;
            nd -> next = temp;
            temp -> previous = nd;
            nd -> counterpart = NULL;
            head = nd;
			return;
            
        } else if (nd -> time == head -> time && nd -> day == head -> day){
			temp = head;
			if(nd -> priority > head -> priority){
				if (head -> next == head)
				{
					checkAvailableNextTimesFor(temp);
					temp -> next = nd;
					temp -> previous = nd;
					nd -> counterpart = temp -> counterpart;
					head = nd;
					temp -> next = NULL;
					temp -> previous = NULL;
					temp->day=getUsableDay();
					temp->time=getUsableTime();
					add(temp);
					return;
				} else {

					checkAvailableNextTimesFor(temp);
					temp -> previous -> next = nd;
					temp -> next -> previous = nd;
					nd -> previous = temp -> previous;
					nd -> next = temp -> next;
					nd -> counterpart = temp -> counterpart;
					head = nd;
					temp -> next = NULL;
					temp -> previous = NULL;
					temp->day=getUsableDay();
					temp->time=getUsableTime();
					add(temp);
					return;
				}
			} else {
				checkAvailableNextTimesFor(nd);
				nd->day=getUsableDay();
				nd->time=getUsableTime();	
				add(nd);
				return;
			}
			
		}
		
        
        else{
                temp = head;
                pivot = temp;
                
                while(pivot -> counterpart != NULL && nd -> time > pivot -> counterpart -> time){
                  
                  pivot = pivot -> counterpart;
            
                }
				if (nd -> priority > pivot -> priority)
				{
					checkAvailableNextTimesFor(pivot);
					nd -> counterpart = pivot -> counterpart -> counterpart;
					pivot -> counterpart = nd;
					pivot->day=getUsableDay();
					pivot->time=getUsableTime();	
					add(pivot);
					return;
				} else if (nd -> priority < pivot -> priority){
					checkAvailableNextTimesFor(nd);
					nd->day=getUsableDay();
					nd->time=getUsableTime();	
					add(nd);
					return;
				} else {
					nd -> counterpart = pivot -> counterpart;
                	pivot -> counterpart = nd;
				}
				
				
				
                return;
            }
    }
    else{
        
        temp = head;
        
        while(temp -> next != head && temp -> next -> day <= nd -> day){

            temp = temp -> next;
        }    

        if(nd -> day == temp -> day){

            if(nd -> time < temp -> time){

                temp -> previous -> next = nd;
                nd -> previous = temp -> previous;
                nd -> next = temp -> next;
                temp -> next -> previous = nd;
                nd -> counterpart = temp;
                temp -> next = NULL;
                temp -> previous = NULL;
                temp = nd;
                return;
                
            } else if (nd -> time == temp -> time)
			{
				if(nd -> priority > temp -> priority){
					checkAvailableNextTimesFor(temp);
					temp -> next -> previous = nd;
					temp -> previous -> next = nd;
					nd -> next = temp -> next;
					nd -> previous = temp -> previous;
					nd -> counterpart = temp -> counterpart;
					temp->day=getUsableDay();
					temp->time=getUsableTime();
					add(temp);
					return;
				} else {
					checkAvailableNextTimesFor(nd);
					nd->day=getUsableDay();
					nd->time=getUsableTime();	
					add(nd);
					return;
				}
			}
			
			else{
				
                pivot = temp;
                
                while(pivot -> counterpart != NULL && nd -> time > pivot -> counterpart -> time){

                    pivot = pivot -> counterpart;
            
                }
				if (nd -> priority > pivot -> priority && nd -> time == pivot -> time)
				{
					checkAvailableNextTimesFor(pivot);
					nd -> counterpart = pivot -> counterpart;
					pivot -> counterpart = nd;
					pivot->day=getUsableDay();
					pivot->time=getUsableTime();	
					add(pivot);
					return;
				} else if (nd -> priority < pivot -> priority && nd -> time == pivot -> time)
				{
					checkAvailableNextTimesFor(nd);
					nd->day=getUsableDay();
					nd->time=getUsableTime();	
					add(nd);
					return;
				} else {
					nd -> counterpart = pivot -> counterpart;
					pivot -> counterpart = nd;
				}
				
				
				return;
            }
            
        }else{
            
            temp -> next -> previous = nd;
            nd -> next = temp -> next;
            nd -> previous = temp;
            temp -> next = nd;
            nd -> counterpart = NULL;
            return;  
        }
    }
} 

Task * WorkPlan::getTask(int day, int time)
{
	temp = head;
	do{
		pivot = temp;
		if (day == temp -> day)
		{
			do{
				if (pivot -> time == time)
				{
					return pivot;
				}
				pivot = pivot -> counterpart;
			}while (pivot != NULL);
		}
		temp = temp -> next;
	}while (temp != head);
	return 0;
}


void WorkPlan::checkAvailableNextTimesFor(Task *delayed)	
{
	temp = head;
	Task *check = getTask(delayed -> day, delayed -> time);
	while (temp -> day != check -> day)
	{
		temp = temp -> next;
	}
	pivot = check;
	do
	{	
		while (pivot != NULL)
		{
			if (pivot -> time != check -> time)
			{
				usable_day = (check -> day);
				usable_time = (check -> time);
				return;
			}
			(check -> time)++;
			pivot = pivot -> counterpart;
		}
		(check -> day)++;
		(check -> time) = 8;
		temp = temp -> next;
		pivot = temp;
		

	} while (temp != head);
	usable_time = 8;
	usable_day = (check -> day);
	return;	
}

void WorkPlan::delayAllTasksOfDay(int day)
{
	temp = head;
	Task *newone = new Task();
	Task *oldone = new Task();
	while (temp -> day != day)
	{
		temp = temp -> next;
	}	
	if (day == head -> day)
	{
		head -> next = temp -> next;
		temp -> next -> previous = head;
		head -> previous = temp -> previous;
		temp -> previous -> next = head;
		head -> counterpart = temp -> counterpart;		
		pivot = temp;
		do{
			oldone = pivot;
			oldone = getTask(pivot -> day, pivot -> time);
			newone->name=new char [strlen(pivot->name)];
			newone->name=pivot->name;
			newone->priority=pivot->priority;
			checkAvailableNextTimesFor(oldone);
			newone->day=getUsableDay();
			newone->time=getUsableTime();
			remove(oldone);
			add(newone);
			pivot = pivot -> counterpart;
		}while (pivot != NULL || newone -> day != day);
		return;
	}else{	
		pivot = temp;
		do{
			oldone = pivot;
			oldone = getTask(pivot -> day, pivot -> time);
			newone->name=new char [strlen(pivot->name)];
			newone->name=pivot->name;
			newone->priority=pivot->priority;
			checkAvailableNextTimesFor(oldone);
			newone->day=getUsableDay();
			newone->time=getUsableTime();
			remove(oldone);
			add(newone);
			pivot = pivot -> counterpart;
		}while (pivot != NULL || newone -> day != day);
		return;
	}
}

void WorkPlan::remove(Task *target)
{
	temp = head;
	pivot = temp;
	do{
		if(head -> next == head && head -> previous == head && head -> counterpart == NULL){

            delete head;
            head = NULL;
            return;
        } else if (target -> day == head -> day && target -> time == head -> time && head -> counterpart != NULL){
			if (head -> next == head)
			{
				head = head -> counterpart;
				delete(temp);
				head -> next = head;
				head -> previous = head;
				return;
			}
			
			head -> previous -> next = head -> counterpart;
			head -> next -> previous = head -> counterpart;
			head -> counterpart -> next = head -> next;
			head -> counterpart -> previous = head -> previous;
			head = head -> counterpart;
			delete temp;
			return;
		}else if (target -> day == head -> day && target -> time == head -> time && head -> counterpart == NULL){
			head -> previous -> next = head -> next;
			head -> next -> previous = head -> previous;
			head = head -> next;
			delete temp;
			return;
		}else if(target -> day == temp -> day){
			if(target -> time == temp -> time && temp -> counterpart !=NULL){
				temp -> previous -> next = temp -> counterpart;
				temp -> next -> previous = temp -> counterpart;
				temp -> counterpart -> previous = temp -> previous;
				temp -> counterpart -> next = temp -> next;
				delete temp;
				return;
			}else if(target -> time == temp -> time && temp -> counterpart ==NULL){
				temp -> previous -> next = temp -> next;
				temp -> next -> previous = temp -> previous;
				delete temp;
				return;
			}
		}else if (target -> day == temp -> day){
			pivot = temp;
			do{
				if (pivot -> time == target -> time)
				{
					tail -> counterpart = tail -> counterpart -> counterpart;
					delete pivot;
					return;
				}else if(pivot -> counterpart == NULL){
					tail -> counterpart = NULL;
					delete pivot;
					return;
				}	
				tail = pivot;
				pivot = pivot -> counterpart;
			}while (pivot != NULL);
		}	
		temp = temp -> next;
		
	}while (temp != head);
}


bool WorkPlan::checkCycledList()
{
	Task *pivot=new Task();
	pivot=head;
	int patient=100;
	bool r=false;
	while (pivot!=NULL&&patient>0)
	{		
		patient--;
		pivot=pivot->previous;
		if(pivot==head)
		{
			r=true;
			break;
		}
	}
	cout<<"("<<100-patient<<")";
	patient=100;
	bool l=false;
	while (pivot!=NULL&&patient>0)
	{		
		patient--;
		pivot=pivot->next;
		if(pivot==head)
		{
			l=true;
			break;
		}
	}
	return r&l;
}
