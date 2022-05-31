#include<iostream>
using namespace std;
 
int findLRU(int time[], int n)
{
    int i, minimum = time[0], pos = 0;
 	for(i = 1; i < n; ++i)
	{
        if(time[i] < minimum)
		{
            minimum = time[i];
            pos = i;
        }
    }
    return pos;
}
 
int main()
{
    int no_of_frames, no_of_pages, frames[10], pages[30], counter = 0, time[10], flag1, flag2, i, j, pos, faults = 0;
    cout<<"Enter number of frames: ";
    cin>>no_of_frames;
    
    cout<<"Enter number of pages: ";
    cin>>no_of_pages;
    
    cout<<"Enter reference string: ";
    
    for(i = 0; i < no_of_pages; ++i)
	{
        cin>>pages[i];
    }
    
    for(i = 0; i < no_of_frames; ++i)
	{
        frames[i] = -1;
    }
    
    for(i = 0; i < no_of_pages; ++i)
	{
        flag1 = flag2 = 0;
        
        for(j = 0; j < no_of_frames; ++j)
		{
            if(frames[j] == pages[i])
			{
                counter++;
                time[j] = counter;
                flag1 = flag2 = 1;
                break;
            }
        }
        
        if(flag1 == 0)
		{
            for(j = 0; j < no_of_frames; ++j)
			{
                if(frames[j] == -1)
				{
                    counter++;
                    faults++;
                    frames[j] = pages[i];
                    time[j] = counter;
                    flag2 = 1;
                    break;
                }
            }    
        }
        
        if(flag2 == 0)
		{
            pos = findLRU(time, no_of_frames);
            counter++;
            faults++;
            frames[pos] = pages[i];
            time[pos] = counter;
        }
        
        cout<<"\n";
        
        for(j = 0; j < no_of_frames; ++j)
		{
            cout<<"\t"<<frames[j];
        }
    }
    
    cout<<"\n\nTotal Page Faults ="<<faults;
    return 0;
}
