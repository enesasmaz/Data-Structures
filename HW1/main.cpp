/* @Author
Student Name: Enes Şaşmaz
Student ID: 150170090
Date: 22.10.2019 */

#include <iostream>
#include <fstream>
using namespace std;

struct node
{
    int size;
    int quant;
    node *next;
};

struct stock
{
    node *head;
    node *temp;
    node *n;
    void create();
    void add_stock(int);
    void sell(int);
    void current_stock();
    void clear();
};

void stock::create(){
    head = NULL;
}

void stock::add_stock(int number){
    if(head == NULL || number < head -> size){
        n = new node;
        n -> size = number;
        n -> quant = 1;
        n -> next = NULL;
        n -> next = head;
        head = n;
        return;
    } else if(head != NULL){
        temp = head;
        while (temp -> next && number >= temp -> next -> size)
        {   temp = temp -> next;
        }
                if (number == temp -> size)
                {
                    (temp -> quant)++;
                    return;
                } else {
                    n = new node;
                    n -> size = number;
                    n -> quant = 1;
                    n -> next = NULL;
                    n -> next = temp -> next;
                    temp -> next = n;
                    return;
                } 
    }

}

void stock::sell(int number){
    number = number *(-1);
    int counter = 0;
    temp = head;
    if(number == head -> size){
        if (head -> quant == 1)
        {
            head = temp -> next;
            delete temp;
            return;
        }else if (head -> quant == 0)
        {
            cout<< "NO_STOCK" << endl;
            return;
        }else
        {
            (head -> quant)--;
            return;
        }
 
    }
        node *tail;
        temp = head;
        while (temp != NULL)
        {
          tail = temp;
          temp = temp -> next;
          if(temp == NULL){
            break;
          }else if(temp -> size == number){
            counter++;
            break;
          }
        }
        if(counter == 0){
          cout << "NO_STOCK" << endl;
          return;
        }
        tail -> next = temp -> next;
        if (temp -> quant == 1)
        {
          delete temp;
          return;
        }else{
          (temp -> quant)--;
          return;
        }
        
        
}

void stock::current_stock(){
    temp = head;

    while(temp != NULL){
        cout << temp->size << ":" << temp->quant << endl;
        temp = temp->next;  
    }
}

void stock::clear(){ 

    while(head != NULL){ 

        temp = head;
        head = head -> next;
        delete temp;
    }
}

int main(){
    struct stock stock1;
    ifstream read;
    int index;
    stock1.create();
read.open("input.txt", ios::in);
    while(!read.eof()){
        read >> index;
        if(index > 0){

            stock1.add_stock(index);
        } else if(index == 0){
            stock1.current_stock();
        }
        else{
            stock1.sell(index);
        }
    }
    stock1.clear();
    read.close();
    return 0;
}