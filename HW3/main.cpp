/* @Author
Student Name: Enes Şaşmaz
Student ID: 150170090
Date: 20.12.2019 */

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
using namespace std;

struct Dtm_node
{
    int data;
    int parent;
    Dtm_node* first;
    Dtm_node* next;
    Dtm_node* phones;
};

struct Dtm
{
    Dtm_node* root;
    Dtm_node* temp;
    Dtm_node* pivot;
    int i;
    int j;
    int x;
    int y;
    int traversing[256];
    void create();
    void add_BS(int a, int b);
    void add_MH(int a, int b);
    int search_BS(Dtm_node* temp, int bsdata);
    int search_MH(Dtm_node* temp, string message, int mhdata);
    int search_in_BS(Dtm_node* temp, int bsdata);
    int search_in_MH(Dtm_node* temp, string message, int mhdata);
};

void Dtm::create() {
    root = NULL;
    Dtm_node* t = new Dtm_node;
    t->data = 0;
    t->first = NULL;
    t->next = NULL;
    t->phones = NULL;
    t->parent = 0;
    root = t;
    return;
}

int Dtm::search_in_BS(Dtm_node* temp, int bsdata) {
    temp = root;
    return search_BS(temp, bsdata);
}

int Dtm::search_in_MH(Dtm_node* temp, string message, int mhdata) {
    i = 0;
    j = 0;
    temp = root;
    return search_MH(temp, message, mhdata);
}

int Dtm::search_BS(Dtm_node* temp, int bsdata) {
    int rtrn = 0;

    if (temp->data == bsdata)
    {
        pivot = temp;
        return 1;

    }
    else {
        if (temp->first != NULL)
        {
            rtrn = search_BS(temp->first, bsdata);
        }
        if (temp->next != NULL && rtrn != 1)
        {
            rtrn = search_BS(temp->next, bsdata);
        }

    }
    return rtrn;
}

int Dtm::search_MH(Dtm_node* temp, string message, int mhdata) {

    int counter = 0;
    Dtm_node* travel;
    if (temp->phones != NULL) {
        travel = temp->phones;
        while (travel != NULL)
        {
            if (travel->data == mhdata)
            {
                counter++;
            }
            travel = travel->next;
        }
    }

    while (j == 0)
    {
        cout << "Traversing:";
        j++;
    }

    cout << temp->data << " ";

    int rtrn = 0;

    if (counter == 1)
    {
        x = search_in_BS(temp, temp->data);
        while (pivot->data != 0)
        {
            traversing[i] = pivot->data;
            y = search_in_BS(temp, pivot->parent);
            i++;
        }
        cout << endl;
        cout << "Message:" << message << " To:0 ";
        i--;
        for (; 0 <= i; i--)
        {
            cout << traversing[i] << " ";
        }
        cout << "mh_" << mhdata << endl;
        return 1;

    }
    else {
        if (temp->first != NULL)
        {
            rtrn = search_MH(temp->first, message, mhdata);
        }
        if (temp->next != NULL && rtrn != 1)
        {
            rtrn = search_MH(temp->next, message, mhdata);
        }
    }
    return rtrn;
}


void Dtm::add_BS(int a, int b) {

    if (root != NULL)
    {
        x = search_in_BS(temp, b);

        if (pivot->first == NULL)
        {
            Dtm_node* t = new Dtm_node;
            t->data = a;
            t->first = NULL;
            t->next = NULL;
            t->phones = NULL;
            t->parent = b;
            pivot->first = t;
            return;
        }
        else if (pivot->first->next == NULL)
        {
            Dtm_node* t = new Dtm_node;
            t->data = a;
            t->first = NULL;
            t->next = NULL;
            t->phones = NULL;
            t->parent = b;
            pivot->first->next = t;
            return;
        }
        else if (pivot->first->next != NULL)
        {
            pivot = pivot->first;
            while (pivot->next != NULL)
            {
                pivot = pivot->next;
            }
            Dtm_node* t = new Dtm_node;
            t->data = a;
            t->first = NULL;
            t->next = NULL;
            t->phones = NULL;
            t->parent = b;
            pivot->next = t;
        }
    }
}

void Dtm::add_MH(int a, int b) {
    x = search_in_BS(temp, b);
    if (pivot->phones == NULL)
    {
        Dtm_node* t = new Dtm_node;
        t->data = a;
        t->first = NULL;
        t->next = NULL;
        t->phones = NULL;
        t->parent = b;
        pivot->phones = t;
        return;
    }
    else if (pivot->phones->next == NULL)
    {
        Dtm_node* t = new Dtm_node;
        t->data = a;
        t->first = NULL;
        t->next = NULL;
        t->phones = NULL;
        t->parent = b;
        pivot->phones->next = t;
    }
    else if (pivot->phones->next != NULL)
    {
        pivot = pivot->phones;
        while (pivot->next != NULL)
        {
            pivot = pivot->next;
        }
        Dtm_node* t = new Dtm_node;
        t->data = a;
        t->first = NULL;
        t->next = NULL;
        t->phones = NULL;
        t->parent = b;
        pivot->next = t;
    }
}

int main(int argc, char** argv) {
    struct Dtm dtm;
    dtm.i = 1;
    ifstream fileread;
    string reading_bs;
    string reading_mh1;
    string reading_mh2;
    int first;
    int second;
    int msg;
    dtm.create();
    fileread.open(argv[1]);
    while (!fileread.eof())
    {
        fileread >> reading_bs;
        fileread >> first;
        fileread >> second;
        if (reading_bs == "BS")
        {
            dtm.add_BS(first, second);

        }
        else if (reading_bs == "MH")
        {
            dtm.add_MH(first, second);
        }
    }
    fileread.close();
    fileread.open(argv[2]);
    while (!fileread.eof())
    {
        getline(fileread, reading_mh1, '>');
        getline(fileread, reading_mh2);
        msg = stoi(reading_mh2);
        int mh = dtm.search_in_MH(dtm.temp, reading_mh1, msg);
        if (mh == 0)
        {
            cout << endl;
            cout << "Can not be reached the mobile host mh_" << msg << " at the moment" << endl;
        }
    }

    return 0;
}