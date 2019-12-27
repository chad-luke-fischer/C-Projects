#include "flexCharManager.h"

flexCharManager::flexCharManager()
{
	for(int i = 0; i < BUF_SIZE; i++)
        {
               buffer[i] = '\0'; 
        }
        indexCount = 0;
}

flexCharManager::~flexCharManager()
{
}
             
char* flexCharManager::alloc_chars(int n)
{
	 int counter = 0;
    if(active_requests == used_mem_size)
    {
        //increase size
    }

    if(*used_memory[0]->physical_location-buffer[0] > n)
    {
        active_requests++;
        *used_memory[0]->physical_location = buffer[0];
        used_memory[0]->size = n;
        return &buffer[0];

    }
    
    for(int i = 0; i < active_requests; i++)
    {
        if(*used_memory[i + 1]->physical_location - ((*used_memory[i]->physical_location) + used_memory[i]->size) > n)
        {
            active_requests++;
            *used_memory[i]->physical_location = 
            *used_memory[i]->physical_location + used_memory[i]->size + 1;
            used_memory[i]->size = n;
            return used_memory[i]->physical_location;
        }
    }
    if(buffer[BUF_SIZE] - *used_memory[active_requests-1]->physical_location > n)
    {
        active_requests++;
        used_memory[BUF_SIZE]->physical_location =
        used_memory[BUF_SIZE]->physical_location + used_memory[BUF_SIZE]->size+1;
        used_memory[BUF_SIZE]->size=n;
        return used_memory[active_requests-1]->physical_location;
    }

    for(int i = 0; i < BUF_SIZE;i++)
    {
        if(buffer[i] == '\0'){counter++;}
        if (count == BUF_SIZE-1)
        	{
        		active_requests++;
        		return &buffer[0];
        	}

    }
    return '\0';

}

void flexCharManager::free_chars(char* p)
{
	//if it isnt a valid adress, do nothing
	for(int i = 0; i < active_requests; i++)
	{
		if (p == used_memory[i]->physical_location)
		{
			for(int i = 0; i < used_memory->size; i++)
			{
				*(p+i)= '\0';
			}
		}
		else{break;}
	}



}    