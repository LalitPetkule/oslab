#include <iostream>
using namespace std;
int main()
{
      int referenceString[20], pageFaults = 0, m, n, hits, pages, frames;
      cout<<"\nEnter the number of Pages:";
      cin>>pages;
      cout<<"\nEnter reference string values:\n";
      for(int m = 0; m < pages; m++)
      {
            cout<<"Value No:", m + 1;
            cin>>referenceString[m];
      }

      cout<<"\n What are the total number of frames:\t";
      cin>>frames;

      int temp[frames];
      for(m = 0; m < frames; m++)
      {
            temp[m] = -1;
      }
      for(m = 0; m < pages; m++)
      {
            hits = 0;
            for(n = 0; n < frames; n++)
            {
                  if(referenceString[m] == temp[n])
                  {
                        hits++;
                        pageFaults--;
                  }
            }
            pageFaults++;
            if((pageFaults <= frames) && (hits == 0))
            {
                  temp[m] = referenceString[m];
            }
            else if(hits == 0)
            {
                  temp[(pageFaults - 1) % frames] = referenceString[m];
            }
            cout<<"\n";
            for(n = 0; n < frames; n++)
            {
                  cout<<"\t"<<temp[n];
            }
      }
      cout<<"\nTotal Page Faults:\t\n"<<pageFaults;
      return 0;
}
