#include <iostream>

#include "HashTable.h"

using std::cout,std::endl;

/*
 * list model
 *                                                 iter
 *                                                   |
 * initptr   ->    node0(kv,node1ptr)    ->    node1(kv,node2ptr)     ->      node2(kv,null)
 * iter=node1ptr but change to iter not affect node1ptr
 */

int HashTable::hash(int key)
{
    return key % BUCKET_SIZE;
}

void HashTable::Insert(int key, int value)
{
    // TODO
    int hash_index=hash(key);
    HashNode *iter=bucket[hash_index];
    HashNode *new_node;

    if(iter==nullptr)
    {
        new_node=new HashNode(key,value,nullptr);
        bucket[hash_index]=new_node;
        return;
    }

    while (1)
    {
        if(iter->key==key)
        {
            iter->val=value;
            return;
        }

        if(iter->next==nullptr)
            break;
        iter=iter->next;
    }

    new_node=new HashNode(key,value,nullptr);
    iter->next=new_node;
}

void HashTable::Search(int key)
{
    // TODO
    int hash_index=hash(key);
    HashNode *iter=bucket[hash_index];
    int list_index=0;

    while (iter!=nullptr)
    {
        if(iter->key==key)
        {
            cout<<"bucket "<<hash_index
                <<" index "<<list_index
                <<" key "<<key
                <<" value "<<iter->val
                <<endl;
            return;
        }
        list_index++;
        iter=iter->next;
    }

    cout<<"Not Found"<<endl;
}

void HashTable::Delete(int key)
{
    // TODO
    int hash_index=hash(key);
    HashNode *iter=bucket[hash_index];
    HashNode *prev_delete_node;

    if(iter==nullptr)
        return;

    if(iter->key==key)
    {
        bucket[hash_index]=iter->next;
        delete iter;
        return;
    }

    prev_delete_node=bucket[hash_index];
    iter=iter->next;
    while (iter!=nullptr)
    {
        if(iter->key==key)
        {
            prev_delete_node->next=iter->next;
            delete iter;
            return;
        }
        iter=iter->next;
        prev_delete_node=prev_delete_node->next;
    }
}

void HashTable::Display()
{
    for (int i = 0; i < BUCKET_SIZE; ++i)
    {
        std::cout << "|Bucket " << i << "|";
        HashNode *node = bucket[i];
        while (node)
        {
            std::cout << "-->(" << node->key << "," << node->val << ")";
            node = node->next;
        }
        std::cout << "-->" << std::endl;
    }
}