/*
Made By Nikhil Kumar 
Question is:
Aim: To create C/C++ program implementing Shamir Secret Sharing Algorithm with the following features:

The applet should accept a byte array of size 32. 
For eg - private byte[] secret = new byte[32]; The applet should form 4 shares where the secret could be reconstructed from any 2 shares. 
Apply Shamir secret sharing scheme to each byte separately and use Galois Field(256) as the underlying finite field. 
Y coordinate corresponding to the same X coordinates shall be stored in the same byte array for each share. 
The applet should accept M number of byte array and reconstruct the original secret using Shamir’s Algorithm. 
Notes: The applicant is free to do research about the algorithm online. 
No external library (accept for generating random numbers) shall be used.


What I understood from the question:

-	The upper and lower limit of 1 and 255 is taken ensure Gaolis Field(256) as the underlying finite field. 
-	There is a while loop that will run m times, which is to accept m byte array and reconstruct them one by one.
-	Taking seed for random number as current time to give random result every time.
-   We have to take a byte array as input, and C provides us only one byte datatype and that is "char", So I took input as a char array of 32 size.
-   Since It is a char array, I assume every byte as a number in range (0 to 9)
-   I made the code specialized for this case only with total 4 shares and minimum required to get secret is 2 share. 
	It can't be used for any case other than this.
-	The 4 shares for every byte is stored in 2 2D arrays named x and y to store x and y value of share respectively.
-	Calculating lagrange for each byte to reconstruct them one by one
-   While calculating lagrange for interpolation, I took x as 0, as that will only give us our secret key and ignore other coefficients with non zero degree of x.
-	stored result in an array of char named "ans".





*/





#include <stdio.h>
#include <stdlib.h>
#include<time.h>


int f(int x1, int x2, int j){
    return (x1+(x2*j));
}


int main() {
	int m;
	srand(time(0));
	scanf("%d", &m);
	int upper = 255;										//for Gaolis Field(256)
	int lower = 1;											//we can't take 0, as x=0 will give the y as true secret key, which is unacceptable.
	while(m--){    											//to accept m byte array and reconstruct them one by one.
	    char byteArr[32];
	    scanf("%s", &byteArr);
	    
	    /*
		
		Process to make shares begin
		
		*/
	    
	    
	    int xf[32][4], yf[32][4];
	    for( int i=0;i<32;i+=1){
	        int x[4], y[4];
	        int curr = byteArr[i] - '0';
	        int randnum = (rand() %(upper - lower + 1)) + lower;			//Generating a random coefficient of x
            //printf("\n %d ", randnum);
            for (int j=1;j<=4;j++){                                        //Loop to find 4 share for values of j in 1 to 4, 
                x[j-1] = j;												   //this can be randomized but I kept it this way for simplicity
                y[j-1] = f(curr, randnum, j);
            }
            
            for (int t=0;t<4;t++){												//Storing the shares of each byte in x and y
            	//printf("\n share is for %d is x %d, y %d",curr,  x[t], y[t]);
                xf[i][t] = x[t];
                yf[i][t] = y[t];
            }
	    }
	    
	    /*
		
		Process to reconstruct byteArray begins
		
		*/
	    
	    
	    char ans[32];														
	    for( int i=0;i<32;i+=1){
	        int xn[4], yn[4];
	        for (int t=0;t<4;t++){											//To extract all the shares of i'th byte
                xn[t] = xf[i][t];
                yn[t] = yf[i][t];
            }
            int first = (rand() % 4);										//Selecting first share of byte available
            int second = (rand() % 4);										//Selecting second share of byte available
            while(second==first){											//Making sure both shares are not same
                second = (rand() % 4);
            }
            int x0 = xn[first], y0=yn[first], x1 = xn[second], y1 = yn[second];				
            float l1 = float(float(0-x1)/float(x0-x1));									//computing lagrange1
            float l2 = float(float(0-x0)/float(x1-x0));									//computing lagrange2
            int secret = l1*y0 + l2*y1;													// Finalising lagranges to get secret code
            char x = secret+'0';
            //printf("\n secret in %d th byte is char %c and int %d and l1 l2 is %f, %f and x0, y0 is %d %d and x1 y1 is %d %d", i, x, secret, l1, l2, x0, y0, x1, y1);
            ans[i]=x;
	    }
	    printf("\n ans is %s \n", ans);
	}
	return 0;
}
