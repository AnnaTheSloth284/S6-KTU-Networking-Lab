//
//  leakybucket.c
//  nw_lab
//
//  Created by Anna Ann Mathew on 11/07/24.
//

#include <stdio.h>
int main(){
    int in,out,bsize,n,bucket=0;
    printf("Enter bucket size: ");
    scanf("%d",&bsize);
    printf("Enter n(inputs): ");
    scanf("%d",&n);
    printf("Enter pkt outgoing rate: ");
    scanf("%d",&out);
    
    while(n!=0){
        printf("\nEnter incoming pkt rate: ");
        scanf("%d",&in);
        printf("Incoming pkt size: %d\n",in);
        
        if(in<=(bsize-bucket)){
            bucket+=in;
            printf("Bucket sts: %d out of %d\n",bucket,bsize);
        }
        else{
            printf("Dropped pkts: %d\n",in-(bsize-bucket));
            printf("Bucket sts: %d out of %d\n",bucket,bsize);
            bucket = bsize;
        }
        bucket -= out;
        printf("After outgoing, Bucket sts: %d out of %d\n",bucket,bsize);
        n--;
    }
}
