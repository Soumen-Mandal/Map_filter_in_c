//Header file
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//function f 
void f(void *input,void *output){
    int *a = input;
    int *b = output;
    *b = (*a)*(*a);
}

//map function
void *map(void *w, unsigned int N, size_t domain_elt_size, size_t range_elt_size, void (*f)(void *input ,void *output)){
   void *r = (void*)malloc(N*range_elt_size);
   int i;
     for(i=0; i<N; i++){
           f(w+i*domain_elt_size, r+i*range_elt_size); 
    }
   // printf("%d",L[0]);
   return r;
}

//function g
int g(void *input){
    int *a = input;
    if((*a) %2 == 0){
        return 1;
    }
    else{
        return 0;
    }
}

//filter function
int filter(void *w, unsigned int N, size_t domain_elt_size, size_t range_elt_size, int(*g)(void *input)){
    int i, j=0, k=0;
    void *arr, *odd;
    arr = (void*)malloc(N*domain_elt_size);
    odd = (void*)malloc(N*domain_elt_size);
    for(i=0; i<N; i++){
        if(g(w+i*domain_elt_size) == 1){
            memcpy(arr+j*domain_elt_size,w+i*domain_elt_size,domain_elt_size);
            j++;
        }
        else{
            memcpy(odd+k*domain_elt_size,w+i*domain_elt_size,domain_elt_size);
            k++;
        }
    }    
        for(i=0; i<k; i++){
            memcpy(arr+(i+j)*domain_elt_size,odd+i*domain_elt_size,domain_elt_size);
        }
        for(i=0; i<N; i++){
            printf("%d\t",*((int*)(arr+i*domain_elt_size)));
        }

        return j;
    }

//Driver code

int main()
{
    int L[4] = {1,2,3,4};
    int N = 4, i;
    int domain_elt_size = sizeof(int), range_elt_size = sizeof(int);
    int *T, num;

    T = map(L, N, domain_elt_size, range_elt_size,f);

    for(i=0; i<N; i++){
        printf("%d\t",T[i]);
    }

    printf("\n");

    num = filter(L, N, domain_elt_size, range_elt_size,g);

    printf("\n");
    printf("%d",num);

    return 0;
}