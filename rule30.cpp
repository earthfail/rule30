#include<stdio.h>
#include<stdlib.h>
//the algorithem in words
/*1- make three arrays of type bool
  2.1- the first is all zeros but in the middle
  2.2- receive the input(number between 0-255 inclusive)
  2.3- convert the input to binary and put the true in the right place in the third array
  and false else where
  3- for each element in the first array
  3.1 get the state of the three neighbors and bin search based on the number
  3.2 get the state in the appropriate place
  3.3 put it in the second array
  4- yank the data from the second array to the first
  5- print the first array*/
#define SLOTS 8

void print_arr(int *arr,int len)
{
  for(int i=0;i<len;i++)
    {
      if(arr[i])
        printf("#");
      else
        printf(" ");
    }
  printf("\n");
}
int main()
{
  int *output,*swap,data[SLOTS]={0},len=184;
  int rule=30,pow2=128;//power of 2(pow2) maximum is 128 because 2^(8-1)=128
  int iterations=91,numit=0,low,high,d,i;//variables for iterations and each iteration
  //which are used frequently
   //receive rule number
  // printf("please Enter a number between 0-255(default=30):");
  // scanf("%d",&rule);
  //receive number of cells
  // printf("please Enter the number of cells(default=15):");
  // scanf("%d",&len);
  // printf("please Enter the number of iterations(default=5):");
  // scanf("%d",&iterations);
  //initializing first and second array
  output=(int*)malloc(len*sizeof(int));
  swap=(int*)malloc(len*sizeof(int));
  //initializing first array
  for(i=0;i<len;i++)
    output[i]=0;
  output[len/2]=1;
  //initializing array data with rule according to the binary representation
  for(int i=SLOTS-1;i>-1;i--)
    {
      if(rule-pow2>=0)
        {
          data[i]=1;
          rule-=pow2;
        }else
        data[i]=0;
      pow2/=2;//decrease the power
    }
  //printing data to check if it is right
  printf("data array:\n");
  print_arr(data,SLOTS);
  //for extra clarity
  for(i=0;i<SLOTS;i++)
    printf("%d",data[i]);
  printf("\n");
  printf("len=%d iterations=%d\n",len,iterations);
  //printing
  printf("your diagram is\n");
  while(numit<iterations)
    {
      //printing arrays
      print_arr(output,len);
      //setting up swap (putting the data in swap)
      for(i=0;i<len;i++)
        {
          //bin search for the appropriate slot in data
          low=0;
          high=SLOTS-1;
          for(d=-1;d<=1;d++)
            {
              if(d+i<0 || d+i>=len || output[d+i]==0)
                high=(low+high)/2;
              else
                low=(low+high)/2+1;//plus one exclude the unwanted cells
            }
          //high and low now meet in the same place let's call it pos
          //now we have the position in data where swap[i] should be data[pos]
          swap[i]=data[high]; //could choose low or high doesn't matter
        }
      //copying swap to output in the next iteration if there is any
      for(i=0;i<len;i++)
        output[i]=swap[i];
      numit++;
    }
  print_arr(output,len);
}
