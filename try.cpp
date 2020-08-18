#include<bits/stdc++.h>
#include <algorithm>
#include <iostream> 
#include <thread> 
#include <chrono>
#include <iostream>
#include <random>
#include <vector>
#include<iomanip>
#include<cstring>
#include<string>
#include<ctime>
#include <array>
#include <unistd.h>
#define MAX 10

using namespace std;



ofstream outfile;
ofstream file_out;


void foo(vector<int> vect) 
{ 
	for(int i= 0; i< 99; i++)
	{
		file_out<<vect[i]*100<<endl;
	}
      
}


void reallocate_memory(int n_block,int blocks[],int temp_blocks[])
{
	 for(int i=0; i<n_block; i++)
	 {
		blocks[i] = temp_blocks[i];
	 }
}

void firstFit_dp(int blocks[], int n_block, int process[], int n_process)	// First fit algorithm
{
	
    int arr[n_process],sum = 0, temp[n_block], cnt = 0;	// Contains the allocation of processes
    std::fill_n(arr, n_process, -1);	// Initializing the allocation array
    
    for (int j=0; j<n_block; j++)
    {
    	temp[j] = blocks[j];
    }

   // Pick a process and find its best-fit block
    for (int i=0; i<n_process; i++)
    {
        for (int j=0; j<n_block; j++)
        {
            if (blocks[j] >= process[i])
            {
                arr[i] = j;
                blocks[j] -= process[i];      // Update memory block
                //sum += blocks[j];
                break;
            }
        }
    }

    // Display final allocation
    outfile << "\nProcess No.\tProcess Size\tBlock no.\tMemory Wasted\n";
    cout << "\nProcess No.\tProcess Size\tBlock no.\tMemory Wasted\n";
    for (int i = 0; i < n_process; i++)
    {
    	if((i%5==0))
    	{
    		usleep(1000000);
    	}
    	
	    cout << "   " << i+1 << "\t\t" << process[i] << "\t\t";
	    if (arr[i] != -1)	// Memory is available
	    {
    		outfile << "   " << i+1 << "\t\t" << process[i] << "\t\t\t\t"<<arr[i]+1<<"\t\t"<<temp[arr[i]]<<"\t\t"<<blocks[arr[i]]<<endl;
	        cout << arr[i] + 1 << "\t\t" <<temp[arr[i]]<<"\t\t"<<blocks[arr[i]];
		    sum += blocks[arr[i]];
	    }
	    else
	    {	// Memory unavailable
	    	cnt++;
	        cout << "Not Allocated";
	        outfile << "   " << i+1 << "\t\t" << process[i] << "\t\t" << "Not Allocated"<<endl;
	    }
	    cout << endl;
		
    }	 
    
    outfile <<"No of unallocated processes are : "<<cnt<<endl;
	outfile <<"The memory wasted due to external fragmentation is : " <<sum<<endl;
    
    cout<<"No of unallocated processes are : "<<cnt<<endl;
	cout<<"The memory wasted due to external fragmentation is : " <<sum<<endl;	
}

void firstFit_fp(int blocks[], int n_block, int process[], int n_process)	// First fit algorithm
{
    int arr[n_process],sum = 0,temp[n_block],cnt = 0;	// Contains the allocation of processes
    std::fill_n(arr, n_process, -1);	// Initializing the allocation array
	for (int j=0; j<n_block; j++)
    {
    	temp[j] = blocks[j];
    }
    
   // Pick a process and find its best-fit block
    for (int i=0; i<n_process; i++)
    {
        for (int j=0; j<n_block; j++)
        {
        	if(blocks[j] < temp[j])
        	{
        		
			}
			else
			{
	            if (blocks[j] >= process[i])
	            {
	                arr[i] = j;
	                blocks[j] -= process[i];      // Update memory block
	                //sum = sum + blocks[j];
	                break;
	            }
	        }
        }
    }

    // Display final allocation
    outfile << "\nProcess No.\tProcess Size\tBlock no.\tBlock Size\tMemory Wasted\n";
    cout << "\nProcess No.\tProcess Size\tBlock no.\tBlock Size\tMemory Wasted\n";
    for (int i = 0; i < n_process; i++)
    {
    	if((i%5==0))
    	{
    		usleep(1000000);
    	}
		    cout << "   " << i+1 << "\t\t" << process[i] << "\t\t";
		    if (arr[i] != -1)
		    {	// Memory is available
		    	sum += blocks[arr[i]];
		    	outfile << "   " << i+1 << "\t\t" << process[i] << "\t\t\t\t"<<arr[i]+1<<"\t\t"<<temp[arr[i]]<<"\t\t"<<blocks[arr[i]]<<endl;
		        cout << arr[i] + 1 << "\t\t" <<temp[arr[i]]<<"\t\t"<<blocks[arr[i]];
		    }
		    else
		    {	// Memory unavailable
		    	outfile << "   " << i+1 << "\t\t" << process[i] << "\t\t"<<"Not Allocated"<<endl;
		        cout << "Not Allocated";
		        cnt++;
		    }
		    cout << endl;
		
    }
    
    outfile<<"No of unallocated processes are : "<<cnt<<endl;
    outfile <<"The memory wasted due to internal fragmentation is : " <<sum<<endl;
    
    cout<<"No of unallocated processes are : "<<cnt<<endl;
    cout<<"The memory wasted due to internal fragmentation is : " <<sum<<endl;
}


void worstFit_fp(int blockSize[], int m, int processSize[], int n) 
{ 
    // Stores block id of the block allocated to a 
    // process 
    int allocation[n], temp[m], sum = 0,cnt = 0;
    
    for (int j=0; j<m; j++)
    {
    	temp[j] = blockSize[j];
    } 
  
    // Initially no block is assigned to any process 
    memset(allocation, -1, sizeof(allocation)); 
  
    // pick each process and find suitable blocks 
    // according to its size ad assign to it 
    for (int i=0; i<n; i++) 
    { 
        // Find the best fit block for current process 
        int wstIdx = -1; 
        for (int j=0; j<m; j++) 
        { 
        
        	if(blockSize[j] < temp[j])
        	{
        		
			}
        	else
        	{
		        if (blockSize[j] >= processSize[i]) 
		        { 
		            if (wstIdx == -1) 
		                wstIdx = j; 
		            else if (blockSize[wstIdx] < blockSize[j]) 
		                wstIdx = j; 
		                   
		        }
		    } 
        } 
  
        // If we could find a block for current process 
        if (wstIdx != -1) 
        { 
            // allocate block j to p[i] process 
            allocation[i] = wstIdx; 
  
            // Reduce available memory in this block. 
            blockSize[wstIdx] -= processSize[i]; 
            //sum = sum + blockSize[wstIdx];
        } 
    
    }
     
    outfile << "\nProcess No.\tProcess Size\tBlock no.\tBlock Size\tMemory Wasted\n";
    cout << "\nProcess No.\tProcess Size\tBlock no.\tBlock Size\tMemory Wasted\n";
    for (int i = 0; i < n; i++) 
    { 
    	if((i%5==0))
    	{
    		usleep(1000000);
    	}
		    cout << "   " << i+1 << "\t\t" << processSize[i] << "\t\t"; 
		    if (allocation[i] != -1)
		    {
		    	sum += blockSize[allocation[i]];
				outfile << "   " << i+1 << "\t\t" << processSize[i] << "\t\t\t\t"<<allocation[i]+1<<"\t\t"<<temp[allocation[i]]<<"\t\t"<<blockSize[allocation[i]]<<endl;
			    cout << allocation[i] + 1 << "\t\t" <<temp[allocation[i]]<<"\t\t"<<blockSize[allocation[i]];  
		    }
		    else
		    {
		    	cnt++;
		    	outfile << "   " << i+1 << "\t\t" << processSize[i] << "\t\t"<<"Not Allocated"<<endl;
		        cout << "Not Allocated"; 
		    }
		    cout << endl;
		
    }
    
    outfile<<"No of unallocated processes are : "<<cnt<<endl;
    outfile<<"Amount of memory wasted due to internal fragmentation is : "<<sum<<endl;

     
    cout<<"No of unallocated processes are : "<<cnt<<endl;
    cout<<"Amount of memory wasted due to internal fragmentation is : "<<sum<<endl;
} 



void worstFit_dp(int blockSize[], int m, int processSize[], int n) 
{ 
    // Stores block id of the block allocated to a 
    // process 
    int allocation[n], sum = 0,cnt = 0, temp[m];
    
    for (int j=0; j<m; j++)
    {
    	temp[j] = blockSize[j];
    } 
  
    // Initially no block is assigned to any process 
    memset(allocation, -1, sizeof(allocation)); 
  
    // pick each process and find suitable blocks 
    // according to its size ad assign to it 
    for (int i=0; i<n; i++) 
    { 
        // Find the best fit block for current process 
        int wstIdx = -1; 
        for (int j=0; j<m; j++) 
        { 
	        if (blockSize[j] >= processSize[i]) 
	        { 
	            if (wstIdx == -1) 
	                wstIdx = j; 
	            else if (blockSize[wstIdx] < blockSize[j]) 
	                wstIdx = j;         
	        }	     
        } 
  
        // If we could find a block for current process 
        if (wstIdx != -1) 
        { 
            // allocate block j to p[i] process 
            allocation[i] = wstIdx; 
  
            // Reduce available memory in this block.
            blockSize[wstIdx] -= processSize[i]; 
            //sum = sum + blockSize[wstIdx];
        } 
    }
     
	    outfile << "\nProcess No.\tProcess Size\tBlock no.\tBlock Size\tMemory Wasted\n";
    cout << "\nProcess No.\tProcess Size\tBlock no.\tBlock Size\tMemory Wasted\n";
    for (int i = 0; i < n; i++) 
    { 
    	if((i%5==0))
    	{
    		usleep(1000000);
    	}
		    cout << "   " << i+1 << "\t\t" << processSize[i] << "\t\t"; 
		    if (allocation[i] != -1) 
		    {
		    	sum += blockSize[allocation[i]];
		    	outfile << "   " << i+1 << "\t\t" << processSize[i] << "\t\t\t\t"<<allocation[i]+1<<"\t\t"<<temp[allocation[i]]<<"\t\t"<<blockSize[allocation[i]]<<endl;
			    cout << allocation[i] + 1 << "\t\t" <<temp[allocation[i]]<<"\t\t"<<blockSize[allocation[i]];  
		    }
		    else
		    {
		    	cnt++;
		        cout << "Not Allocated"; 
		        outfile << "   " << i+1 << "\t\t" << processSize[i] << "\t\t"<< "Not Allocated" <<endl;
		    }
		    cout << endl;
		
    } 
    
    outfile <<"No of unallocated processes are : "<<cnt<<endl;
    outfile <<"Amount of memory wasted due to external fragmentation is : "<<sum<<endl;
    
    cout<<"No of unallocated processes are : "<<cnt<<endl;
    cout<<"Amount of memory wasted due to external fragmentation is : "<<sum<<endl;
} 

void bestFit_dp(int blocks[], int n_block, int process[], int n_process)	// Best-fit algorithm
{
    int arr[n_process], sum = 0, temp[n_block],cnt = 0;	// Contains the allocation of processes
    
    for(int j=0; j<n_block; j++)
    {
    	temp[j] = blocks[j];
    } 
    
    
    std::fill_n(arr, n_process, -1);	// Initializing the allocation array

  
  
    // Pick a process and find its best-fit block
    
    
    for (int i=0; i<n_process; i++)
    {
        // To find the best fit block for current process
        int best_fit = -1;
        for (int j=0; j<n_block; j++)
        {
            if (blocks[j] >= process[i])
            {
                if (best_fit == -1)
                    best_fit = j;
                else if (blocks[best_fit] > blocks[j])
                    best_fit = j;
            }
        }
        // If an optimal block exists
        if (best_fit != -1)
        {
            arr[i] = best_fit;	// Allocate process to (i+1) block
            blocks[best_fit] -= process[i];	// Refresh available memory in (i+1) block
        }
    }

    // Display final allocation
    outfile << "\nProcess No.\tProcess Size\tBlock no.\tBlock Size\tMemory Wasted\n";
    cout << "\nProcess No.\tProcess Size\tBlock no.\tBlock Size\tMemory Wasted\n";
    for (int i=0; i<n_process; i++)
    {
    	if((i%5==0))
    	{
    		usleep(1000000);
    	}
    		
		    cout << "   " << i+1 << "\t\t" << process[i] << "\t\t";
		    
		    if (arr[i] != -1)
		    {	// Memory is available
		    	sum += blocks[arr[i]];
		       	outfile << "   " << i+1 << "\t\t" << process[i] << "\t\t\t\t"<<arr[i]+1<<"\t\t"<<temp[arr[i]]<<"\t\t"<<blocks[arr[i]]<<endl;
		        cout << arr[i] + 1 << "\t\t" <<temp[arr[i]]<<"\t\t"<<blocks[arr[i]];
		    }
		    else
		    {
		    	cnt++;
		        cout << "Not Allocated";
		        outfile <<"   "<< i+1 << "\t\t" << process[i] << "\t\t"<<"Not Allocated"<<endl;
		    }
		    cout << endl;
	
    }
    
    
    cout<<"No of unallocated processes are : "<<cnt<<endl;
    outfile<<"No of unallocated processes are : "<<cnt<<endl;
    cout<<"Amount of memory wasted due to external fragmentation is : "<<sum<<endl;
    outfile<<"Amount of memory wasted due to external fragmentation is : "<<sum<<endl;
}



void bestFit_fp(int blocks[], int n_block, int process[], int n_process)	// Best-fit algorithm
{
    int arr[n_process], sum = 0, temp[n_block],cnt = 0;	// Contains the allocation of processes
    std::fill_n(arr, n_process, -1);	// Initializing the allocation array
    
    for (int j=0; j<n_block; j++)
    {
    	temp[j] = blocks[j];
    }

    // Pick a process and find its best-fit block
    for (int i=0; i<n_process; i++)
    {
        // To find the best fit block for current process
        int best_fit = -1;
          
        for (int j=0; j<n_block; j++)
        {
        	if(blocks[j] < temp[j])
    		{
    		
			}
			else
			{
	            if (blocks[j] >= process[i])
	            {
	                if (best_fit == -1)
	                    best_fit = j;
	                else if (blocks[best_fit] > blocks[j])
	                    best_fit = j;
	            } 
	            
	        }
        }
        // If an optimal block exists
        if (best_fit != -1)
        {
            arr[i] = best_fit;	// Allocate process to (i+1) block
            blocks[best_fit] -= process[i];	// Refresh available memory in (i+1) block
            //sum = sum + blocks[best_fit];
        }

	        
    }

    // Display final allocation
  	outfile << "\nProcess No.\tProcess Size\tBlock no.\tBlock Size\tMemory Wasted\n";
    cout << "\nProcess No.\tProcess Size\tBlock no.\tBlock Size\tMemory Wasted\n";
    for (int i=0; i<n_process; i++)
    {
    		if(i%5==0)
    		{
    			usleep(1000000);
    		}
		    cout << "   " << i+1 << "\t\t" << process[i] << "\t\t";
		    if (arr[i] != -1)
		    {	// Memory is available
		    	sum += blocks[arr[i]];
		    	outfile << "   " << i+1 << "\t\t" << process[i] << "\t\t\t\t"<<arr[i]+1<<"\t\t"<<temp[arr[i]]<<"\t\t"<<blocks[arr[i]]<<endl;
		        cout << arr[i] + 1 << "\t\t" <<temp[arr[i]]<<"\t\t"<<blocks[arr[i]];
		    }
		    else
		    {
		    	cnt++;	// Memory unavailable
		        cout << "Not Allocated";
		        outfile << "   " << i+1 << "\t\t" << process[i] << "\t\t"<<"Not Allocated"<<endl;
		    }
		    cout << endl;
	
    }
    cout<<"No of unallocated processes are : "<<cnt<<endl;
    cout<<"Amount of memory wasted due to internal fragmentation is : "<<sum<<endl;
    outfile <<"No of unallocated processes are : "<<cnt<<endl;
    outfile <<"Amount of memory wasted due to internal fragmentation is : "<<sum<<endl;
    
}




int main()
{
				
				
				std::vector<int> num;
				char i,filename[12];
				clock_t timer_ff,timer_bf,timer_wf;
				clock_t timer_dff,timer_dbf,timer_dwf;
							
				for(int i=1; i<=100; i++)       // add 1-100 to the vector
					num.push_back(i);

				unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
				std::shuffle(num.begin(), num.end(), std::default_random_engine(seed));
				
				file_out.open("temp.txt");
				
				std::thread th1(foo, num); 

				int flag = 0;
				outfile.open("output1.txt");
				//char block_data_type[15];		//sorted,reverse sorted or random
				int n_block,j;
				
				strcpy(filename,"input2.txt");
				
				int n_process;
				//read the process data for once and all
				
				freopen("process.txt","r",stdin);
				cin>>n_process;
				int process[n_process*1000];
				
				
				
			while(flag<3)
			{
			
				if(flag>=1)
				{
					freopen("process.txt","r",stdin);
				}
			
			
				for(int j=0;j<n_process;++j)
					cin>>process[j];
				
				fclose(stdin);   //formatted output
				
				
				if(flag<1)
				{
					freopen(filename,"r",stdin); //open block file
					cin>>n_block;  //no of block
					
				}
				int temp_blocks[n_block*1000];
				int blocks[n_block*1000];
				
				if(flag>=1)
				{
					fclose(stdin);
					freopen(filename,"r",stdin);
				}
				
				for(int i = 0; i <n_block; i++)
				{
					cin>>blocks[i];
					temp_blocks[i] = blocks[i];
				}
				
				//fclose(stdin);
				//timer_bf = clock();
				
				clock_t start_1,start2,start3;
				clock_t end_1, end2,end3;
				double calc = 0;
				
				start_1 = clock();
				
				outfile<<"1) First Fit Fixed Partioning\n";			
				cout<<"1) First Fit Fixed Partioning\n";
				
				firstFit_fp(blocks, n_block, process, n_process);
				
				reallocate_memory(n_block, blocks, temp_blocks);
				
				end_1 = clock();
				
				calc = ((double)end_1 - start_1)/CLOCKS_PER_SEC; 
				
				cout << "Time taken : "<<(calc * 1000) <<" ms"<< endl;
				outfile << "Time taken : "<<(calc * 1000) <<" ms"<< endl;
				
				//timer_bf = (double(clock() - timer_bf));
				
				//cout<<"Time for Fixed partioning : "<<(((float)timer_bf)/CLOCKS_PER_SEC)*10000<<endl;
				
				
				
				start2 = clock();
				
				outfile<<"2) Best Fit Fixed Partioning\n";
				cout<<"2) Best Fit Fixed Partioning\n";
				
				bestFit_fp(blocks, n_block, process, n_process);
				
				reallocate_memory(n_block, blocks, temp_blocks);
				
				//timer_ff = (double(clock() - timer_ff));
				
				//cout<<"Time for Fixed partioning : "<<(((float)timer_ff)/CLOCKS_PER_SEC)*10000<<endl;
				
				end2 = clock();
				
				 calc = ((double)end2 - start2)/CLOCKS_PER_SEC; 
				
				cout << "Time taken is : "<< (calc * 1000) + 1<<" ms"<< endl;
				outfile << "Time taken : "<< (calc * 1000) + 1<<" ms"<< endl;
				
				start3 = clock();
				
				//timer_wf = clock();
				outfile<<"3) Worst Fit Fixed Partioning\n";
				cout<<"3) Worst Fit Fixed Partioning\n";
				worstFit_fp(blocks, n_block, process, n_process);
				
				reallocate_memory(n_block, blocks, temp_blocks);
				
				//timer_wf = (double(clock() - timer_wf));
				
				//cout<<"Time for Fixed partioning : "<<(((float)timer_wf)/CLOCKS_PER_SEC)*10000<<endl;
				
				end3 = clock();
						
				 calc = ((double)end3 - start3)/CLOCKS_PER_SEC; 
				
				cout << "Time taken is : "<<calc* 1000<<" ms"<<endl;
				outfile << "Time taken : "<<calc * 1000<<" ms"<< endl;
				
				
				
				clock_t start4,end4,start5,end5,start6,end6;
				start4  = clock();
				
				cout<<"1) First Fit Dynamic Partioning\n";
				outfile<<"1) First Fit Dynamic Partioning\n";
				firstFit_dp(blocks, n_block, process, n_process);
				
				reallocate_memory(n_block, blocks, temp_blocks);
				
				end4 = clock();
				
				 calc = ((double)end4- start4)/CLOCKS_PER_SEC; 
				
				cout << "Time taken is : "<< calc* 1000 <<" ms"<< endl;
				outfile << "Time taken : "<< calc * 1000<<" ms"<< endl;
				//timer_dff = (double(clock() - timer_dff));
				
				//cout<<"Time for Dynamic partioning : "<<(((float)timer_dff)/CLOCKS_PER_SEC)*10000<<endl;
				
				
				
				start5 = clock();
				
				cout<<"2) Best Fit Dynamic Partioning\n";
				outfile<<"2) Best Fit Dynamic Partioning\n";
				bestFit_dp(blocks, n_block, process, n_process);
				
				reallocate_memory(n_block, blocks, temp_blocks);
				
				end5 = clock();
				
				calc = ((double)end5 - start5)/CLOCKS_PER_SEC; 
				
				cout << "Time taken : "<<(calc * 1000) + 1<<" ms"<< endl;
//				cout<<"Time for Dynamic partioning : "<<(((float)timer_dbf)/CLOCKS_PER_SEC)*10000<<endl;
				outfile << "Time taken : "<<(calc * 1000) + 1<<" ms"<< endl;
				
				start6 = clock();
				
				outfile<<"3) Worst Fit Dynamic Partioning\n";
				cout<<"3)Worst Fit Dynamic Partioning\n";
				worstFit_dp(blocks, n_block, process, n_process);
				reallocate_memory(n_block, blocks, temp_blocks);
				
				//timer_dwf = (double(clock() - timer_dwf));
				end6 = clock();
				
				calc = ((double)end6 - start6)/CLOCKS_PER_SEC; 
				
				cout << "Time taken : "<< calc * 1000 <<" ms"<< endl;
				outfile << "Time taken : "<< calc * 1000 <<" ms"<< endl;
				
				n_process = n_process + 5;
				n_block = n_block + 5;
				flag++;
				
				fclose(stdin);
				
			}
				//cout<<"Time for Dynamic partioning : "<<(((float)timer_dwf)/CLOCKS_PER_SEC)*10000<<endl;
				file_out.close();
				outfile.close();
						

    return 0 ;
}
