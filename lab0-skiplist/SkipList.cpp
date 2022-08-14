#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include "SkipList.h"

using std::cout,std::endl;

double SkipList::my_rand()
{
    s = (16807 * s) % 2147483647ULL;
    return (s + 0.0) / 2147483647ULL;
}

int SkipList::randomLevel()
{
    int result = 1;
    while (result < MAX_LEVEL && my_rand() < 0.5)
    {
        ++result;
    }
    return result;
}

void SkipList::Insert(int key, int value)
{
    // TODO
    SKNode *iter=head;
    int level=MAX_LEVEL;    //1~MAX_LEVEL
    SKNode *new_node;
    int new_level;
    std::vector<SKNode *> prev_nodes;

    while (1)
    {
        //rightwards
        while (iter->forwards[level-1]->key<key)
            iter=iter->forwards[level-1];
        prev_nodes.push_back(iter);

        //downwards
        if(level==1)
            break;
        while (level>1)
        {
            level--;
            //when level ==1,pushback must happen in rightwards for downwards is broken.
            //to prevent duplict pushback,not pushback in downwards
            if(iter->forwards[level-1]->key>=key && level!=1) 
                prev_nodes.push_back(iter);
            else
                break;
        }
    }
    
    if(iter->forwards[level-1]->key==key)
    {
        iter->forwards[level-1]->val=value;
        return;
    }

    new_node=new SKNode(key,value,SKNodeType::NORMAL);
    new_level=randomLevel();

    for(level=1;level<=new_level;level++)
    {
        new_node->forwards.push_back(prev_nodes[MAX_LEVEL-level]->forwards[level-1]);
        prev_nodes[MAX_LEVEL-level]->forwards[level-1]=new_node;
    }
}

void SkipList::Search(int key)
{
    // TODO
    int level=MAX_LEVEL;    //1~MAX_LEVEL
    SKNode *iter=head;
    cout<<level<<','<<"h ";
    
    while (1)
    {
        //rightwards
        while (iter->forwards[level-1]->key<key)
        {
            iter=iter->forwards[level-1];
            cout<<level<<','<<iter->key<<' ';
        }

        //downwards
        if(level==1)
            break;
        while (level>1 && iter->forwards[level-1]->key>=key)
        {
            level--;
            cout<<level<<',';
            if(iter->type==SKNodeType::HEAD)
                cout<<"h ";
            else
                cout<<iter->key<<' ';
        }
    }
    
    if(iter->forwards[level-1]->key==key)
    {
        cout<<level<<','<<key<<' '<<iter->forwards[level-1]->val<<endl;
        return;
    }

    if(iter->forwards[level-1]->type!=SKNodeType::NIL)
        cout<<level<<','<<iter->forwards[level-1]->key<<" Not Found"<<endl;
    else
        cout<<level<<",N Not Found"<<endl;
}

void SkipList::Delete(int key)
{
    // TODO
    SKNode *iter=head;
    int level=MAX_LEVEL;    //1~MAX_LEVEL
    SKNode *delete_node;
    int delete_level;
    std::vector<SKNode *> prev_nodes;

    while (1)
    {
        //rightwards
        while (iter->forwards[level-1]->key<key)
            iter=iter->forwards[level-1];
        prev_nodes.push_back(iter);

        //downwards
        if(level==1)
            break;
        while (level>1)
        {
            level--;
            //when level ==1,pushback must happen in rightwards for downwards is broken.
            //to prevent duplict pushback,not pushback in downwards
            if(iter->forwards[level-1]->key>=key && level!=1) 
                prev_nodes.push_back(iter);
            else
                break;
        }
    }
    
    if(iter->forwards[level-1]->key==key)
    {
        delete_level=iter->forwards[level-1]->forwards.size();
        delete_node=iter->forwards[level-1];

        for(level=1;level<=delete_level;level++)
            prev_nodes[MAX_LEVEL-level]->forwards[level-1]=delete_node->forwards[level-1];

        delete delete_node;
    }
}

void SkipList::Display()
{
    for (int i = MAX_LEVEL - 1; i >= 0; --i)
    {
        std::cout << "Level " << i + 1 << ":h";
        SKNode *node = head->forwards[i];
        while (node->type != SKNodeType::NIL)
        {
            std::cout << "-->(" << node->key << "," << node->val << ")";
            node = node->forwards[i];
        }

        std::cout << "-->N" << std::endl;
    }
}