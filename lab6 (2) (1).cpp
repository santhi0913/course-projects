/*
LAB 6 : CACHE SIMULATOR
by : CS19B018 , CS19B041 , CS19B055
*/

#include <cmath>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <climits>
#include <string>
#include <bits/stdc++.h> 
#include <unordered_map>
using namespace std;

typedef struct cacheBlock *Position;
typedef struct cacheBlock
{
    int tag;
    int validBit;
    int dirtyBit;
    Position next;
    cacheBlock()
    {
        tag = -1;
        validBit = 0;
        dirtyBit = 0;
        next = NULL;
    }
} cacheBlock;

class List
{
public:
    void insert(cacheBlock a, Position p);
    void delItem(Position p);
    void makeNull();
    void printList(int count);
    cacheBlock retrieve(Position p);
    void update(cacheBlock c, Position p);
    Position end();
    Position first();
    Position next(Position p);

    List(int tag)
    {
        tagBits = tag;
    }

private:
    int tagBits;
    Position listHead;
};
void List::delItem(Position p)
{
    p->next = p->next->next;
}
void List::update(cacheBlock c, Position p)
{
    
    p->next->tag = c.tag;
    p->next->validBit = c.validBit;
    p->next->dirtyBit = c.dirtyBit;
}
void List::makeNull()
{
    listHead = new cacheBlock;
    listHead->next = NULL;
}

void List::insert(cacheBlock a, Position p)
{
    Position temp;
    temp = p->next;
    p->next = new cacheBlock;
    p->next->next = temp;
    p->next->tag = a.tag;

    p->next->validBit = a.validBit;
    p->next->dirtyBit = a.dirtyBit;
}

cacheBlock List::retrieve(Position p)
{
    
    cacheBlock c;
    c = *(p->next);
    return c;
}

void List::printList(int count)
{   //int count =0;
    Position p;
    p = listHead->next;

    if (p == NULL)
    {
        cout << "EMPTY LIST\n";

        return;
    }

    else
    {
        while (p != NULL)
        {   cout << count << ' ';
            cout << p->validBit << " " << p->dirtyBit << " ";

            if (p->tag == -1)
            {
                cout << "NULL";
            }
            else
            {
                cout << p->tag;      
            }

            p = p->next;
        // count++;
        }
        cout << endl;
    }
}

Position List::end()
{
    Position p;
    p = listHead;
    while (p->next->next != NULL)
        p = p->next;
    return (p);
}

Position List::first()
{
    return (listHead);
}

Position List::next(Position p)
{
    return (p->next);
}

long long int BintoDec(int start, int end, int *arr)
{
    long long int dec = 0;
    int count = 0;
    for (int i = start; i < end; i++)
    {
        dec += arr[i] * pow(2, count); 
        count++;
    }

    return dec;
}

/**/

void fully_associative_random(int **address, int N, int indexBits, int offsetBits){
     int tagBits = 32 - indexBits - offsetBits;
    

    List cacheRow(tagBits);
    cacheRow.makeNull();

    int Compulsorymisses = 0;
    int Capacitymisses = 0;
    int Conflictmisses = 0;
    int Readmisses = 0;
    int Writemisses = 0;
    int Dirtyblocksevicted = 0;
    int writeaccesses =0;
    int readaccesses=0;
    for (int i = 0; i < N; i++)
    {

        //read or write
        int operation = address[i][32];

        //tag array
        int k = 0;
        int *tagArr;
        tagArr = new int[tagBits];
        for (int j = 1; j <= tagBits; j++)
        {
            tagArr[k++] = address[i][j];
        }
        int tag = BintoDec(0,tagBits,tagArr);
        Position p;
        p = cacheRow.first();

        if (operation == 0)
        {
            readaccesses++;
            int count = 0;
            int hit = 0;
            while (p->next != NULL)
            {
                cacheBlock c;
                c = cacheRow.retrieve(p);
                if (c.validBit == 0)
                {
                    c.validBit = 1;
                    c.dirtyBit = 0;
                    c.tag = tag;
 
                    cacheRow.update(c, p);
                   
                    Readmisses++;
                    Compulsorymisses++;
                }
                else if (c.validBit == 1)
                {
                    if (c.tag != tag && c.tag != -1 && count < pow(2, indexBits))
                    {
                        p = p->next;
                        count++;
                    }
                    else if (c.tag == tag)
                    {
                        hit = 1;
                    }
                }
            }
            if (p->next == NULL)
            {
                if (count < pow(2, indexBits) && hit == 0)
                {
                    cacheBlock a;
                    a.validBit = 1;
                    a.dirtyBit = 0;
                    a.tag = tag;
                    cacheRow.insert(a, p);
                    Readmisses++;
                    Compulsorymisses++;
                   
                }
                if (count == pow(2, indexBits) && hit == 0)
                {
                    srand(time(0));
                     int x = rand() % indexBits ;
                     Position q = cacheRow.first();
                     while(x--){
                         q = q->next ;
                     }
                    cacheBlock c = cacheRow.retrieve(q);
                    if (c.dirtyBit == 1)
                        Dirtyblocksevicted++;

                    c.validBit = 1;
                    c.dirtyBit = 0;
                    c.tag = tag;

                   
                   
                    cacheRow.update(c,q);
                    Readmisses++;
                    Conflictmisses++;
                    Capacitymisses++;
                }
            }
            
        }

        if (operation == 1)
        {
            writeaccesses++;
            int count = 0;
            int hit = 0;
            while (p->next != NULL)
            {
                cacheBlock c;
                c = cacheRow.retrieve(p);
                if (c.validBit == 0)
                {
                    c.validBit = 1;
                    c.dirtyBit = 1;
                    c.tag = tag;
                    cacheRow.update(c, p);
                    Writemisses++;
                    Compulsorymisses++;
                }
                else if (c.validBit == 1)
                {
                    if (c.tag != tag && c.tag != -1 && count < pow(2, indexBits))
                    {
                        p = p->next;
                        count++;
                    }
                    else if (c.tag == tag)
                    {
                        hit = 1;
                        c.dirtyBit = 1;
                        cacheRow.update(c, p);
                    }
                }
            }
            if (p->next == NULL)
            {
                if (count < pow(2, indexBits) && hit == 0)
                {
                    cacheBlock a;
                    a.validBit = 1;
                    a.dirtyBit = 1;
                    a.tag = tag;
                    cacheRow.insert(a, p);
                    Writemisses++;
                    Compulsorymisses++;
                    
                }
                if (count == pow(2, indexBits) && hit == 0)
                {
                    srand(time(0));
                    int x = rand() % indexBits ;
                    Position q = cacheRow.first();
                    while(x--){
                        q = q->next ;
                    }
                    
                    cacheBlock c = cacheRow.retrieve(q);
                    if (c.dirtyBit == 1)
                        Dirtyblocksevicted++;

                    c.validBit = 1;
                    c.dirtyBit = 1;
                    c.tag = tag;
                    cacheRow.update(c, q);
                    Writemisses++;
                    Conflictmisses++;
                    Capacitymisses++;
                }
            }
            
        }
    }
    
   cout << N << " #Cache accesses"<<endl;
    cout << readaccesses <<" #Read accesses" <<endl;
    cout << writeaccesses <<" #Write accesses" << endl;
    cout << Compulsorymisses + Conflictmisses <<" #Cache misses" << endl;
    cout << Compulsorymisses << " #Compulsory misses"<< endl;
    cout << Capacitymisses << " #Capacity misses"<<endl;
    cout << Conflictmisses <<" #Conflict misses" <<endl;
    cout << Readmisses <<" #Read misses" <<endl;
    cout << Writemisses <<" #Write misses" <<endl;
    cout << Dirtyblocksevicted << " #Dirty blocks evicted"<<endl;
    
   
}

//FULLY ASSOCIATIVE LRU

void fully_associative(int **address, int N, int indexBits, int offsetBits)
{
    
    int tagBits = 32 - indexBits - offsetBits;

    List cacheRow(tagBits);
    cacheRow.makeNull();

    int Compulsorymisses = 0;
    int Capacitymisses = 0;
    int Conflictmisses = 0;
    int Readmisses = 0;
    int Writemisses = 0;
    int Dirtyblocksevicted = 0;
    int writeaccesses =0;
    int readaccesses=0;
    
    for (int i = 0; i < N; i++)
    {
        int operation = address[i][32];

        int k = 0;
        int *tagArr;
        tagArr = new int[tagBits];
        for (int j = 1; j <= tagBits; j++)
        {
            tagArr[k++] = address[i][j];
        }
        int tag = BintoDec(0,tagBits,tagArr);
        Position p;
        p = cacheRow.first();

        if (operation == 0)
        {
            readaccesses++;
            int count = 0;
            int hit = 0;
            while (p->next != NULL)
            {
                cacheBlock c;
                c = cacheRow.retrieve(p);
                if (c.validBit == 0)
                {
                    c.validBit = 1;
                    c.dirtyBit = 0;
                    c.tag = tag;
                    
                    cacheRow.update(c, p);
   
                    Readmisses++;
                    Compulsorymisses++;
 
                }
                else if (c.validBit == 1)
                {
                    if (c.tag != tag && c.tag != -1 && count < pow(2, indexBits))
                    {
                        p = p->next;
                        count++;
                    }
                    else if (c.tag == tag)
                    {
                        hit = 1;
                       
                    }
                }
            }
            if (p->next == NULL)
            {
                if (count < pow(2, indexBits) && hit == 0)
                {
                    cacheBlock a;
                    a.validBit = 1;
                    a.dirtyBit = 0;
                    a.tag = tag;
                    cacheRow.insert(a, p);
                    Readmisses++;
                    Compulsorymisses++;
                   
                }
                if (count == pow(2, indexBits) && hit == 0)
                {
                    cacheBlock c = cacheRow.retrieve(cacheRow.end());
                    if (c.dirtyBit == 1)
                        Dirtyblocksevicted++;

                    c.validBit = 1;
                    c.dirtyBit = 0;
                    c.tag = tag;
                    cacheRow.update(c, cacheRow.end());
                    Readmisses++;
                    Conflictmisses++;
                    Capacitymisses++;
                }
            }
            
        }

        if (operation == 1)
        {
            writeaccesses++;
            int count = 0;
            int hit = 0;
            while (p->next != NULL)
            {
                cacheBlock c;
                c = cacheRow.retrieve(p);
                if (c.validBit == 0)
                {
                    c.validBit = 1;
                    c.dirtyBit = 1;
                    c.tag = tag;
                    cacheRow.update(c, p);
                    Writemisses++;
                    Compulsorymisses++;
                }
                else if (c.validBit == 1)
                {
                    if (c.tag != tag && c.tag != -1 && count < pow(2, indexBits))
                    {
                        p = p->next;
                        count++;
                    }
                    else if (c.tag == tag)
                    {
                        hit = 1;
                        c.dirtyBit = 1;
                        
                        cacheRow.update(c, p);
                    }
                }
            }
            if (p->next == NULL)
            {
                if (count < pow(2, indexBits) && hit == 0)
                {
                    cacheBlock a;
                    a.validBit = 1;
                    a.dirtyBit = 1;
                    a.tag = tag;
                    cacheRow.insert(a, p);
                    Writemisses++;
                    Compulsorymisses++;
                    
                }
                if (count == pow(2, indexBits) && hit == 0)
                {
                    cacheBlock c = cacheRow.retrieve(cacheRow.end());
                    if (c.dirtyBit == 1)
                        Dirtyblocksevicted++;

                    c.validBit = 1;
                    c.dirtyBit = 1;
                    c.tag = tag;
                    cacheRow.delItem(cacheRow.end());
                    cacheRow.insert(c, cacheRow.first());
                    Writemisses++;
                    Conflictmisses++;
                    Capacitymisses++;
                }
            }
            
        }
    }
//     25	 #Cache accesses
// 12	 #Read accesses
// 13	 #Write accesses
// 25	 #Cache misses
// 25	 #Compulsory misses
// 0	 #Capacity misses
// 0	 #Conflict misses
// 12	 #Read misses
// 13	 #Write misses
// 2 	 #Dirty blocks evicted
    
     cout << N << " #Cache accesses"<<endl;
    cout << readaccesses <<" #Read accesses" <<endl;
    cout << writeaccesses <<" #Write accesses" << endl;
    cout << Compulsorymisses + Conflictmisses <<" #Cache misses" << endl;
    cout << Compulsorymisses << " #Compulsory misses"<< endl;
    cout << Capacitymisses << " #Capacity misses"<<endl;
    cout << Conflictmisses <<" #Conflict misses" <<endl;
    cout << Readmisses <<" #Read misses" <<endl;
    cout << Writemisses <<" #Write misses" <<endl;
    cout << Dirtyblocksevicted << " #Dirty blocks evicted"<<endl;
    
    
    //for (int i = 0; i < N; i++)
    //cacheRow.printList();
}
/*
void set_associative_pseudo(int assoc, int N, int **address, int indexBits, int offsetBits)
{
    int tagBits = 32 - indexBits - offsetBits;
    BinaryTree PseudoTree[pow(2, indexBits)];
    List *cacheRow;
    cacheRow = (List *)malloc(sizeof(List) * pow(2, indexBits));
    for (int i = 0; i < pow(2, indexBits); i++)
    {
        cacheRow[i] = List(tagBits);
        cacheRow[i].makeNull();
        for(int j=0;j<assoc;j++){
            cacheBlock c;
            cacheRow[i].insert(c,cacheRow[i].first());
        }
        PseudoTree[i].buildTree(assoc);
    }
    
    int Compulsorymisses = 0;
    int Capacitymisses = 0;
    int Conflictmisses = 0;
    int Readmisses = 0;
    int Writemisses = 0;
    int Dirtyblocksevicted = 0;
    int countValid = 0;
    for (int i = 0; i < N; i++)
    {
        int operation = address[i][32];

        //tag array
        int k = 0;
        int *tag;
        tag = new int[tagBits];
        for (int j = 0; j < tagBits; j++)
        {
            tag[k++] = address[i][j];
        }
        int tag = BintoDec(0,tagBits,tagArr);
        //index decimal value
        int idx = BintoDec(tagBits, tagBits + indexBits, address[i]); // here do we convert index bits from 0th index ? , isnt that bit for rd/write
        Position p;
        p = cacheRow[idx].first();
        if (operation == 0)
        {
            int count = 0;
            int hit = 0;
            int cacheIndex = BinaryTree[idx].traverseHelper();
            while(cacheIndex--)
            p=p->next;

            cacheBlock c;
            c = cacheRow[idx].retrieve(p);
            if (c.validBit == 0)
                {
                    c.validBit = 1;
                    c.dirtyBit = 0;
                    c.tag = tag;
                    
                    cacheRow[idx].update(c,p);
                    Readmisses++;
                    Compulsorymisses++;
                    countValid++;
                    //compMiss++
                }
            
            while (p->next != NULL)
            {
                cacheBlock c;
                c = cacheRow[idx].retrieve(p);
                if (c.validBit == 0)
                {
                    c.validBit = 1;
                    c.dirtyBit = 0;
                    c.tag = tag;
                    cacheRow[idx].delItem(p);
                    cacheRow[idx].insert(c, cacheRow[idx].first());
                    
                    Readmisses++;
                    Compulsorymisses++;
                    countValid++;
                    //compMiss++
                }
                else if (c.validBit == 1)
                {
                    //read hits++;
                    if (c.tag != tag && c.tag != -1 && count < assoc)
                    {
                        p = p->next;
                        count++;
                    }
                    else if (c.tag == tag)
                    {
                        hit = 1;
                        cacheRow[idx].delItem(p);
                        cacheRow[idx].insert(c, cacheRow[idx].first());
                    }
                }
            }
            if (p->next == NULL)
            {
                if (count < assoc && hit == 0)
                {
                    //read miss++
                    cacheBlock a;
                    a.validBit = 1;
                    a.dirtyBit = 0;
                    a.tag = tag;
                    cacheRow[idx].insert(a, cacheRow[idx].first());
                    Readmisses++;
                    Compulsorymisses++;
                    countValid++;
                }
                if (count == assoc && hit == 0)
                {
                    //read miss++
                    //cache replacement
                    //search for invalid bit =0 or replace least recently accssed which is at list.end
                    //LRU
                    c = cacheRow[idx].retrieve(cacheRow[idx].end());
                    if (c.dirtyBit == 1)
                        Dirtyblocksevicted++;

                    c.validBit = 1;
                    c.dirtyBit = 0;
                    c.tag = tag;
                    cacheRow[idx].delItem(p);
                    cacheRow[idx].insert(c, cacheRow[idx].first());
                    Readmisses++;
                    Conflictmisses++;
                }
            }
            if (countValid == (pow(2, indexBits) * assoc))
                Capacitymisses++;
        }

        if (operation == 1)
        {
            int count = 0;
            int hit = 0;
            while (p->next != NULL)
            {
                cacheBlock c;
                c = cacheRow[idx].retrieve(p);
                if (c.validBit == 0)
                {
                    c.validBit = 1;
                    c.dirtyBit = 1;
                    c.tag = tag;
                    cacheRow[idx].delItem(p);
                    cacheRow[idx].insert(c, cacheRow[idx].first());
                    cout << "in if" << '\n';
                    Writemisses++;
                    Compulsorymisses++;
                    countValid++;
                    //compMiss++
                }
                else if (c.validBit == 1)
                {
                    //read hits++;
                    if (c.tag != tag && c.tag != -1 && count < assoc)
                    {
                        p = p->next;
                        count++;
                    }
                    else if (c.tag == tag)
                    {
                        hit = 1;
                        c.dirtyBit = 1;
                        cacheRow[idx].delItem(p);
                        cacheRow[idx].insert(c, cacheRow[idx].first());
                    }
                }
            }
            if (p->next == NULL)
            {
                if (count < assoc && hit == 0)
                {
                    //read miss++
                    cacheBlock a;
                    a.validBit = 1;
                    a.dirtyBit = 1;
                    a.tag = tag;
                    cacheRow[idx].insert(a, cacheRow[idx].first());
                    Writemisses++;
                    Compulsorymisses++;
                    countValid++;
                }
                if (count == assoc && hit == 0)
                {
                    //read miss++
                    //cache replacement
                    //search for invalid bit =0 or replace least recently accssed which is at list.end
                    //LRU
                    c = cacheRow[idx].retrieve(cacheRow[idx].end());
                    if (c.dirtyBit == 1)
                        Dirtyblocksevicted++;

                    c.validBit = 1;
                    c.dirtyBit = 1;
                    c.tag = tag;
                    cacheRow[idx].delItem(p);
                    cacheRow[idx].insert(c, cacheRow[idx].first());
                    Writemisses++;
                    Conflictmisses++;
                }
            }
            if (countValid == (pow(2, indexBits) * assoc))
                Capacitymisses++;
        }
    }

    cout << Compulsorymisses << " compulsory misses" << endl;
    cout << Capacitymisses << " Capacitymisses" << endl;
    cout << Conflictmisses << " Conflict misses" << endl;
    cout << Readmisses << " Read misses" << endl;
    cout << Writemisses << " Write misses" << endl;
    cout << Dirtyblocksevicted << " Dirtyblocksevicted" << endl;

    for (int i = 0; i < pow(2, indexBits); i++)
        cacheRow[i].printList();
}
*/
//SET ASSOCIATIVE RANDOM

void set_associative_random(int assoc, int N, int **address, int indexBits, int offsetBits)
{   unordered_map<long long int, int> map;
    long long int dec_address[N];
    for(int i=0; i< N; i++){
         dec_address[i] = BintoDec(0, 32, address[i]);
         map[dec_address[i]] = 0;
    }
    int tagBits = 32 - indexBits - offsetBits;

    List *cacheRow;
    cacheRow = (List *)malloc(sizeof(List) * pow(2, indexBits));
    for (int i = 0; i < pow(2, indexBits); i++)
    {
        cacheRow[i] = List(tagBits);
        cacheRow[i].makeNull();
    }
    
    int Compulsorymisses = 0;
    int Capacitymisses = 0;
    int Conflictmisses = 0;
    int Readmisses = 0;
    int Writemisses = 0;
    int Dirtyblocksevicted = 0;
    int writeaccesses =0;
    int readaccesses=0;
    
    for (int i = 0; i < N; i++)
    {
        int operation = address[i][32];

        //tag array
        int k = 0;
        int *tagArr;
        tagArr = new int[tagBits];
        for (int j = 0; j < tagBits; j++)
        {
            tagArr[k++] = address[i][j];
        }
        // tag decimal value
        int tag = BintoDec(0,tagBits,tagArr);
        //index decimal value
        int idx = BintoDec(tagBits, tagBits + indexBits, address[i]); 
        Position p;
        p = cacheRow[idx].first();
        if (operation == 0)
        {
            readaccesses++;
            int count = 0;
            int hit = 0;
            while (p->next != NULL)
            {
                cacheBlock c;
                c = cacheRow[idx].retrieve(p);
                if (c.validBit == 0)
                {
                    c.validBit = 1;
                    c.dirtyBit = 0;
                    c.tag = tag;
                    
                    cacheRow[idx].update(c, p);
                    
                    Readmisses++;
                    Compulsorymisses++;
                    map[dec_address[i]] = 1;
                    
                }
                else if (c.validBit == 1)
                {if(map[dec_address[i]] == 0){
                        Compulsorymisses++;
                        map[dec_address[i]] = 1;
                    }
                    else{
                    
                        Conflictmisses++;
                    }
                    if (c.tag != tag && c.tag != -1 && count < assoc)
                    {
                        p = p->next;
                        count++;
                    }
                    else if (c.tag == tag)
                    {
                        hit = 1;
                       
                    }
                }
            }

            if (p->next == NULL)
            {
                if (count < assoc && hit == 0)
                {
                    cacheBlock a;
                    a.validBit = 1;
                    a.dirtyBit = 0;
                    a.tag = tag;
                    cacheRow[idx].insert(a, p);
                    Readmisses++;
                    Compulsorymisses++;
                    map[dec_address[i]] = 1;
                }
                if (count == assoc && hit == 0)
                {if(map[dec_address[i]] == 0){
                        Compulsorymisses++;
                        map[dec_address[i]] = 1;
                    }
                    else{
                   
                        Conflictmisses++;
                    }
                    srand(time(0));
                    int x = rand() % assoc ;
                    Position q = cacheRow[idx].first();
                    while (x--){
                           q = q->next ;
                    }
                    cacheBlock c = cacheRow[idx].retrieve(q);
                    if (c.dirtyBit == 1)
                        Dirtyblocksevicted++;

                    c.validBit = 1;
                    c.dirtyBit = 0;
                    c.tag = tag;
                    cacheRow[idx].update(c,q);
                    Readmisses++;
                    //Conflictmisses++;
                }
            }
            
        }

        if (operation == 1)
        {
            writeaccesses++;
            int count = 0;
            int hit = 0;
            while (p->next != NULL)
            {
                cacheBlock c;
                c = cacheRow[idx].retrieve(p);
                if (c.validBit == 0)
                {
                    c.validBit = 1;
                    c.dirtyBit = 1;
                    c.tag = tag;
                    
                    cacheRow[idx].update(c, p);
                    
                    Writemisses++;
                    Compulsorymisses++;
                         map[dec_address[i]] = 1;
                }
                else if (c.validBit == 1)
                {if(map[dec_address[i]] == 0){
                        Compulsorymisses++;
                        map[dec_address[i]] = 1;
                    }
                    else{
                    k=0;
                        //cout <<"address "<< i <<'\t';
                        for (int j = 0; j < tagBits; j++)
                        {
                            tagArr[k] = address[i][j];
                            //cout <<tagArr[k] ;
                            k++;
                        }
                        int tag = BintoDec(0,tagBits,tagArr);
                        int idx = BintoDec(tagBits, tagBits + indexBits, address[i]); 
                        // cout << ' ' << tag << "   index: " << idx;
                        // cout << '\n';
                        k=0;
                        Conflictmisses++;
                    }
                    if (c.tag != tag && c.tag != -1 && count < assoc)
                    {
                        p = p->next;
                        count++;
                    }
                    else if (c.tag == tag)
                    {
                        hit = 1;
                        c.dirtyBit = 1;
                        cacheRow[idx].update(c, p);
                    }
                }
            }
            if (p->next == NULL)
            {
                if (count < assoc && hit == 0)
                {
                    cacheBlock a;
                    a.validBit = 1;
                    a.dirtyBit = 1;
                    a.tag = tag;
                    cacheRow[idx].insert(a, p);
                    Writemisses++;
                    Compulsorymisses++;
                    map[dec_address[i]] = 1;
                }
                if (count == assoc && hit == 0)
                {if(map[dec_address[i]] == 0){
                        Compulsorymisses++;
                        map[dec_address[i]] = 1;
                    }
                    else{
                   
                        Conflictmisses++;
                    }
                    srand(time(0));
                    int x = rand() % assoc ;
                    Position q = cacheRow[idx].first();
                    while (x--){
                           q = q->next ;
                    }
                    cacheBlock c = cacheRow[idx].retrieve(q);
                    if (c.dirtyBit == 1)
                        Dirtyblocksevicted++;

                    c.validBit = 1;
                    c.dirtyBit = 1;
                    c.tag = tag;
                    cacheRow[idx].update(c, q);
                    Writemisses++;
                    //Conflictmisses++;
                }
             }
        }
    }

  cout << N << " #Cache accesses"<<endl;
    cout << readaccesses <<" #Read accesses" <<endl;
    cout << writeaccesses <<" #Write accesses" << endl;
    cout << Compulsorymisses + Conflictmisses <<" #Cache misses" << endl;
    cout << Compulsorymisses << " #Compulsory misses"<< endl;
    cout << Capacitymisses << " #Capacity misses"<<endl;
    cout << Conflictmisses <<" #Conflict misses" <<endl;
    cout << Readmisses <<" #Read misses" <<endl;
    cout << Writemisses <<" #Write misses" <<endl;
    cout << Dirtyblocksevicted << " #Dirty blocks evicted"<<endl;
}


//SET ASSOCIATIVE LRU 

void set_associative(int assoc, int N, int **address, int indexBits, int offsetBits)
{

    int tagBits = 32 - indexBits - offsetBits;
    unordered_map<long long int, int> map;
    List *cacheRow;
    cacheRow = (List *)malloc(sizeof(List) * pow(2, indexBits));
    for (int i = 0; i < pow(2, indexBits); i++)
    {
        cacheRow[i] = List(tagBits);
        cacheRow[i].makeNull();
    }
    long long int dec_address[N];
    for(int i=0; i< N; i++){
         dec_address[i] = BintoDec(0, 32, address[i]);
         map[dec_address[i]] = 0;
    }

    int Compulsorymisses = 0;
    int Capacitymisses = 0;
    int Conflictmisses = 0;
    int Readmisses = 0;
    int Writemisses = 0;
    int Dirtyblocksevicted = 0;
    int writeaccesses =0;
    int readaccesses=0;


    int check=0;
    for (int i = 0; i < N; i++)
    {

        int operation = address[i][32];

        //tag array
        int k = 0;
        int *tagArr;
        tagArr = new int[tagBits];
        for (int j = 0; j < tagBits; j++)
        {
            tagArr[k++] = address[i][j];
        }
        // tag decimal value
        int tag = BintoDec(0,tagBits,tagArr);
        //index decimal value
        int idx = BintoDec(tagBits, tagBits + indexBits, address[i]); 

        Position p;
        p = cacheRow[idx].first();
        if (operation == 0)
        {   
            readaccesses++;
            int count = 0;
            int hit = 0;
            while (p->next != NULL)
            {
                cacheBlock c;
                c = cacheRow[idx].retrieve(p);
                if (c.validBit == 0)
                {
                    c.validBit = 1;
                    check++; //changed 
                    c.dirtyBit = 0;
                    c.tag = tag;
                    cacheRow[idx].delItem(p);
                    cacheRow[idx].insert(c, cacheRow[idx].first());
                    // //changed
                    // cacheRow[idx].update(c,p);
                    Readmisses++;
                    Compulsorymisses++;
                    
                    map[dec_address[i]] = 1;
                    break;
                }
                else if (c.validBit == 1)
                    {
                    //     if(map[dec_address[i]] == 0){
                    //         Compulsorymisses++;
                    //         map[dec_address[i]] = 1;
                    //     }
                    //  else{
                    //      Conflictmisses++;
                    //  }
                    if (c.tag != tag && c.tag != -1 && count < assoc)
                    {
                        
                        p = p->next;
                        count++;
                    }
                    else if (c.tag == tag)
                    {
                        hit = 1;
                        //Dirtyblocksevicted++;
                        cacheRow[idx].delItem(p);
                        cacheRow[idx].insert(c, cacheRow[idx].first());
                          break;
                    }
                }
            }

            if (p->next == NULL)
            {
                if (count < assoc && hit == 0)
                {
                    cacheBlock a;
                    a.validBit = 1;
                    check++;//changed
                    a.dirtyBit = 0;
                    a.tag = tag;
                    //changed
                    cacheRow[idx].insert(a, cacheRow[idx].first());
                    Readmisses++;
                    Compulsorymisses++;
                    map[dec_address[i]] = 1;
                    
                }
                if (count == assoc && hit == 0)
                {   if(map[dec_address[i]] == 0){
                        Compulsorymisses++;
                        map[dec_address[i]] = 1;
                    }
                    else{
    
                        Conflictmisses++;
                    }
                    cacheBlock c = cacheRow[idx].retrieve(cacheRow[idx].end());
                    if (c.dirtyBit == 1)
                        Dirtyblocksevicted++;

                    c.validBit = 1;
                    
                    c.dirtyBit = 0;
                    c.tag = tag;
                    cacheRow[idx].delItem(cacheRow[idx].end());
                    cacheRow[idx].insert(c, cacheRow[idx].first());
                    //cacheRow[idx].update(c,cacheRow[idx].end());
                    Readmisses++;
                    //Conflictmisses++;
                }
            }
           
        }

        if (operation == 1)
        {
            writeaccesses++;
            int count = 0;
            int hit = 0;
            while (p->next != NULL)
            {
                cacheBlock c;
                c = cacheRow[idx].retrieve(p);
                if (c.validBit == 0)
                {
                    c.validBit = 1;
                    check++; //changed
                    c.dirtyBit = 1;
                    c.tag = tag;
                    
                    cacheRow[idx].delItem(p);
                    cacheRow[idx].insert(c, cacheRow[idx].first());  
                    //cacheRow[idx].update(c,p);   
                    Writemisses++;
                    Compulsorymisses++;
                    map[dec_address[i]] = 1;
                }
                else if (c.validBit == 1)
                    
                {
                    // if(map[dec_address[i]] == 0){
                    //         Compulsorymisses++;
                    //         map[dec_address[i]] = 1;
                    //     }
                    //  else{
                    //      Conflictmisses++;
                    //  }
                    if (c.tag != tag && c.tag != -1 && count < assoc)
                    {
                        // if(c.dirtyBit==1)
                        //Dirtyblocksevicted++;
                        c.dirtyBit=1;
                        p = p->next;
                        count++;
                    }
                    else if (c.tag == tag)
                    {
                        hit = 1;
                        c.dirtyBit = 1;
                        
                        //Dirtyblocksevicted++;
                        cacheRow[idx].delItem(p);
                        cacheRow[idx].insert(c, cacheRow[idx].first());
                        //cacheRow[idx].update(c,p);
                    }
                }
            }
            if (p->next == NULL)
            {
                if (count < assoc && hit == 0)
                {
                    cacheBlock a;
                    a.validBit = 1;
                    check++;//changed
                    a.dirtyBit = 1;
                    a.tag = tag;

                    cacheRow[idx].insert(a, cacheRow[idx].first());
                    //cacheRow[idx].insert(a, p);
                    Writemisses++;
                    Compulsorymisses++;
                    map[dec_address[i]] = 1;
                }
                if (count == assoc && hit == 0)
                {
                    if(map[dec_address[i]] == 0){
                        Compulsorymisses++;
                        map[dec_address[i]] = 1;
                    }
                    else{
                        Conflictmisses++;
                    }
 
                    cacheBlock c = cacheRow[idx].retrieve(cacheRow[idx].end());
                    if (c.dirtyBit == 1)
                        Dirtyblocksevicted++;

                    c.validBit = 1;
                    c.dirtyBit = 1;
                    c.tag = tag;
                    
                    cacheRow[idx].delItem(cacheRow[idx].end());
                    cacheRow[idx].insert(c, cacheRow[idx].first());
                    Writemisses++;
                    //Conflictmisses++;
                }
            }
            
        }

        if(check == assoc*pow(2, indexBits))
        Capacitymisses++;
    }
    
     cout << N << " #Cache accesses"<<endl;
    cout << readaccesses <<" #Read accesses" <<endl;
    cout << writeaccesses <<" #Write accesses" << endl;
    cout << Compulsorymisses + Conflictmisses <<" #Cache misses" << endl;
    cout << Compulsorymisses << " #Compulsory misses"<< endl;
    cout << Capacitymisses << " #Capacity misses"<<endl;
    cout << Conflictmisses <<" #Conflict misses" <<endl;
    cout << Readmisses <<" #Read misses" <<endl;
    cout << Writemisses <<" #Write misses" <<endl;
    cout << Dirtyblocksevicted << " #Dirty blocks evicted"<<endl;

}

//DIRECT MAPPED 
void direct_mapped(int **address, int N, int indexBits, int offsetBits)
{   
    int tagBits = 32 - indexBits - offsetBits;
    unordered_map<long long int, int> map;
    List *cacheRow;
    cacheRow = (List *)malloc(sizeof(List) * pow(2, indexBits));
    for (int i = 0; i < pow(2, indexBits); i++)
    {
        cacheRow[i] = List(tagBits);
        cacheRow[i].makeNull();
        cacheBlock a;
        cacheRow[i].insert(a, cacheRow[i].first()); 
    }
    
    // empty table created

    
    /* In a row(index)
    keep a track of number of valid bits?
    #validbits == indexBits and there is a confictMiss -> capacity miss?
    1) Reading
        a) tag is empty: v=1, d =0, tag = tag: compMiss++
        b) tag is non empty , and d = 0
            i) tag == tag -> d =0, v =1 : hit++
            ii) tag != tag -> v =1, d =0, tag = tag  : Conflmiss++
        c) tag is non empty , and d = 1
            i) tag != tag -> d = 0, tag = tag : miss++
            ii) tag == tag -> d =1, hit++
    2) writing
        a) tag == NULL , v =1, d =1, tag = tag
        b) tag != NULL , v=1, d=1, tag = tag*/
    //read input
    int Compulsorymisses = 0;
    int Capacitymisses = 0;
    int Conflictmisses = 0;
    int Readmisses = 0;
    int Writemisses = 0;
    int Dirtyblocksevicted = 0;
    int writeaccesses=0;
    int readaccesses=0;
    long long int dec_address[N];
    for(int i=0; i< N; i++){
         dec_address[i] = BintoDec(0, 32, address[i]);
         map[dec_address[i]] = 0;
    }
    
    for (int i = 0; i < N; i++)
    {
        
        
        //read or write
        int operation = address[i][32];
       //cout<<operation<<endl;
        //tag array
        int k = 0;
        int *tagArr;
        tagArr = new int[tagBits];
        for (int j = 0; j < tagBits; j++)
        {
            tagArr[k++] = address[i][j];
        }
        // tag decimal value
        int tag = BintoDec(0,tagBits,tagArr);
        //index decimal value
        int idx = BintoDec(tagBits, tagBits + indexBits, address[i]); 
        
        
        cacheBlock val;
        Position head;
        head = cacheRow[idx].first();
        val = cacheRow[idx].retrieve(head);

        
        //READ
        if (operation == 0)
        {
            readaccesses++;
            if (val.validBit == 0)
            {
                val.validBit = 1;
               
                val.dirtyBit = 0;
                val.tag = tag;
                Compulsorymisses++;
                Readmisses++;
                map[dec_address[i]] = 1;
                
            }
            else if (val.validBit == 1)
                
            {   if(map[dec_address[i]] == 0){
                        Compulsorymisses++;
                        map[dec_address[i]] = 1;
                    }
                    else{
                    
                        Conflictmisses++;
                    }
                if (val.tag != tag && val.tag != -1)
                {
                    if (val.dirtyBit == 1)
                        {Dirtyblocksevicted++;
                         }
                    
                    
                    val.validBit = 1;
                    val.dirtyBit = 0;
                    val.tag = tag;
                    Readmisses++;
                }

            }
            
        }

        
    

    //WRITE
    else //operation ==1
    {
        writeaccesses++;
        if (val.validBit == 0)
        {
            map[dec_address[i]] = 1;
            val.validBit = 1;
            
            val.dirtyBit = 1;
            val.tag = tag;
            Compulsorymisses++;
            Writemisses++;
        }
        else if (val.validBit == 1)
        {
            if(map[dec_address[i]] == 0){
                        Compulsorymisses++;
                        map[dec_address[i]] = 1;
                    }
                    else{
                   
                        Conflictmisses++;
                    }
            if (val.tag != tag && val.tag != -1)
            {
                if (val.dirtyBit == 1)
                    {Dirtyblocksevicted++;
                                }
                
                         

                val.validBit = 1;
                val.dirtyBit = 1;
                val.tag = tag;
                Writemisses++;
            }

        }
        
    }
    
    
    cacheRow[idx].update(val, cacheRow[idx].first());
    }
    cout << N << " #Cache accesses"<<endl;
    cout << readaccesses <<" #Read accesses" <<endl;
    cout << writeaccesses <<" #Write accesses" << endl;
    cout << Compulsorymisses + Conflictmisses <<" #Cache misses" << endl;
    cout << Compulsorymisses << " #Compulsory misses"<< endl;
    cout << Capacitymisses << " #Capacity misses"<<endl;
    cout << Conflictmisses <<" #Conflict misses" <<endl;
    cout << Readmisses <<" #Read misses" <<endl;
    cout << Writemisses <<" #Write misses" <<endl;
    cout << Dirtyblocksevicted << " #Dirty blocks evicted"<<endl;


}
/**/

int log_a_to_base_b(int a, int b)
{
    return log(a) / log(b);
}

// Hexadecimal to binary converter
int *HexToBin(vector<char> hexdec)
{

    long int i = 0;
    string dec;
    while (i < 8)
    {

        switch (hexdec[i])
        {
        case '0':
            dec += "0000";
            //cout <<
            break;
        case '1':
            dec += "0001";
            break;
        case '2':
            dec += "0010";
            break;
        case '3':
            dec += "0011";
            break;
        case '4':
            dec += "0100";
            break;
        case '5':
            dec += "0101";
            break;
        case '6':
            dec += "0110";
            break;
        case '7':
            dec += "0111";
            break;
        case '8':
            dec += "1000";
            break;
        case '9':
            dec += "1001";
            break;
        case 'A':
        case 'a':
            dec += "1010";
            break;
        case 'B':
        case 'b':
            dec += "1011";
            break;
        case 'C':
        case 'c':
            dec += "1100";
            break;
        case 'D':
        case 'd':
            dec += "1101";
            break;
        case 'E':
        case 'e':
            dec += "1110";
            break;
        case 'F':
        case 'f':
            dec += "1111";
            break;
        default:
            break;
        }
        i++;
    }
    dec += hexdec[i];
    int *bin;
    bin = new int[33];
    for (int i = 0; i < 33; i++)
    {
        if (dec[i] == '1' || dec[i]=='w')
            bin[i] = 1;
        else 
            bin[i] = 0;
    }
    // for (int i = 0; i < 33; i++)
    // {
    //     cout<<bin[i];
    // }
    // cout<<endl;
    return bin;
}

int main()
{
    // no. of sets = c/b
    // cache table - set
    int cSize;  //cache size in bytes
    int bSize;  // block size in bytes
    int assoc;  // 0 - fully , 1 - direct mapped , 2/4/8/16/32 - set assoc
    int repPol; //replacement policy - 0 random , 1- lru , 2 - plru
     
    cin >> cSize >> bSize >> assoc >> repPol;
    string name;
    cin>>name;
//     cout << cSize << bSize << assoc << repPol;
// cout<<name;
   ifstream  traces(name);
  

    string in;
    
     int i, j;
     char c;
     int inputNum =0;
     char **address_hex;
    
    vector<vector<char>> mem;
    while(getline(traces,in))
    {
       c=in[in.size()-1];
       //traces >> in;
       
       //cout<<in<<endl;
      //cout<<c<<endl;
    
       vector<char> str;
        if(in.size() == 12){
            int k = 2 ;
            while(k<10)
            {
                str.push_back(in[k]);
                k++;
            }
            str.push_back(c);
          
            mem.push_back(str);


        }


      //cout<<"----";
        if(in.size() <12){

            
             //vector<char> str;
            int pad = 12-in.size();
            while(pad--){
                str.push_back('0');
            }
            int k = 2;
            while(k<in.size()-2){
                
                str.push_back(in[k]);
                k++;
            }
            
            str.push_back(c);
            
            mem.push_back(str);
        }
       
       //cout<<"///";   
        
        inputNum++;
        //cout<<inputNum<<endl;
    }
    traces.close();
    int **address= new int *[inputNum];
    
    for ( j = 0; j < inputNum; j++)
    {
        address[j] = new int[33];
        address[j] = HexToBin(mem[j]);
    }

        
       
    

   
  
    cout <<cSize<< " Cache Size" << endl;
    cout <<bSize<< " Cache line Size"<< endl;
    long long int dec_address[inputNum];
    for( i=0; i< inputNum; i++){
         dec_address[i] = BintoDec(0, 32, address[i]);
         
    }
    
    int set = log_a_to_base_b(cSize / bSize, 2);
    int offset = log_a_to_base_b(bSize, 2);
    int tagBits = 32 - set - offset;
    int* tagArr = new int[tagBits];
 
        

    switch (assoc)
    {
    case 1: //direct mapped
        cout<<"Direct-mapped cache"<<endl;
        cout<<"LRU Replacement"<<endl;
        direct_mapped(address, inputNum, set, offset);
        break;

    case 0: //fully assoc
        cout<<"Fully associative cache"<<endl;
        if(repPol==0){
            cout<<"Random Replacement"<<endl;
           fully_associative_random(address,inputNum ,set,offset); 
        }
        
        else if (repPol==1){
            cout<<"LRU Replacement"<<endl;
           fully_associative(address,inputNum,set,offset);
        }
        
        break;
        

    default: // set associative
        cout<<"Set associative cache"<<endl;
        if(repPol==0){
            cout<<"Random Replacement"<<endl;
            set_associative_random(assoc,inputNum,address,set,offset); 
        }
        else if (repPol==1){
            cout<<"LRU Replacement"<<endl;
            set_associative(assoc,inputNum,address,set,offset);
        }
       
        break;
    }
    return 0;

}