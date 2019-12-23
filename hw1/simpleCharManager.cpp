#include <cstddef>
#include "simpleCharManager.h"
#include <iostream>



simpleCharManager::simpleCharManager()
{
        for(int i = 0; i < BUF_SIZE; i++)
        {
               buffer[i] = '\0'; 
        }
        indexCount = 0;
        new Mem_Block* used_memory;
}

simpleCharManager::~simpleCharManager()
{

}
             
char* simpleCharManager::alloc_chars(int n)
{
   // if too much memory required...return NULL
        if(indexCount + n > BUF_SIZE){return NULL;}
        // alloc chars if memory exists 
        else
        {
                char* ptr = &buffer[indexCount];
                free_place = &buffer[indexCount + n];
                indexCount += n;
                return ptr;
        }

}


void simpleCharManager::free_chars(char* p)
{
        int deleted = 0;
        while(p != free_place)
        {
                std::cout << "test: " << *p << std::endl;
                *p = '\0';
                p++;
                deleted++;
        }
        indexCount -= deleted;
        free_place = &buffer[indexCount];
}       


