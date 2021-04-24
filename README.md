# Figure Out SSS in "C"


Codechef Link to question:
<a href="https://www.codechef.com/IPTS2019/problems/CTS1">here</a>


Q.

The applet should accept a byte array of size 32. 
For eg - private byte[] secret = new byte[32]; The applet should form 4 shares where the secret could be reconstructed from any 2 shares. 
Apply Shamir secret sharing scheme to each byte separately and use Galois Field(256) as the underlying finite field. 
Y coordinate corresponding to the same X coordinates shall be stored in the same byte array for each share. 
The applet should accept M number of byte array and reconstruct the original secret using Shamir’s Algorithm. 
Notes: The applicant is free to do research about the algorithm online. 
No external library (accept for generating random numbers) shall be used.


What I understood from the question and implemented:

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




Code uploaded in this repository
