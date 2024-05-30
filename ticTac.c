#include <stdio.h>
#include <stdbool.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

bool check(int arr[], double* a) {
    int count=0;
    // Row checker;
    for(int i=0;i<9;i+=3) {
        for(int j=0;j<3;++j) {
            if(arr[i+j]==1) {++count;}
        }
        if(count==2) {*a=1.0+(((i/3.0)+1.0)/10.0);return false;}
        count=0;
    }
    
    // Column Checker
    for(int i=0;i<3;++i) {
        for(int j=0;j<9;j+=3) {
            if(arr[i+j]==1) {++count;}
        }
        if(count==2) {*a=2.0+(((i/3.0)+2)/10.0);return false;}
        count=0;
    }
    
    // Criss Cross Checker
    for(int j=1;j<=2;++j) {
        for(int i=(2*(j-1));i<9;i+=4/j) {
            if(arr[i]==1) {++count;}
        }
        if(count==2) {*a=3.0;return false;};
        count=0;
    }
}

void printType(double a) {
    printf(ANSI_COLOR_RESET);
    if(a==3.0) {
        printf("    Unsuccessful due to diagonal");
    }
    else if(a>=2.0&&a<3.0) {
        printf("    Unsuccessful due to column %1.0f",((a-2.0)*10.0));
    }
    else if(a>=1.0&&a<=2.0){
        printf("    Unsuccessful due to row %1.0f",((a-1.0)*10.0));
    }
    printf(ANSI_COLOR_RED);
}

void printA(int arr[],int counter[]) {
    // Checker wether it is a valid solution or not
    double a;
    if(!check(arr,&a)) {printf(ANSI_COLOR_RED);++counter[0];}
    else {printf(ANSI_COLOR_GREEN);++counter[1];} 


    // Prints in tic tac toe organization
    for(int i=0;i<9;i+=3) {
        // Outputs the iteration
        if(i==3){printf(ANSI_COLOR_RESET"%-5d"ANSI_COLOR_RED,counter[0]);}
        else {printf("     ");}

        // Converts 1=X and 0=O
        for(int j=0;j<3;++j) {
            if(j!=0) {printf("|");}
                
            if(arr[i+j]==0) {printf("O");}
            else {printf("X");}
        }
        if(i==3){printType(a);}
        if(i!=6){printf("\n     -----\n");}
    }
    printf(ANSI_COLOR_RESET "\n--------------------------------------------------\n");
}
void reset(int arr[]) {
    for(int i=0;i<9;++i) {
        arr[i]=0;
    }
}

int main() {
    // Write C code here
    int ticTac[9]={0};
    int counter[2]={0};
    for(int a=0;a<6;++a) {
        for(int b=0;b<(6-a);++b) {
            for(int c=0;c<(6-a-b);++c) {
                for(int d=0;d<(6-a-b-c);++d) {
                    ticTac[a]=1;
                    ticTac[b+1+a]=1;
                    ticTac[c+2+a+b]=1;
                    ticTac[d+3+a+b+c]=1;
                    
                    printA(ticTac,counter);
                    reset(ticTac);
                }
            }
        }
    }
    printf("%d total combinations = %d unsuccessful combinations + %d successful combinations\n",counter[0]+counter[1],counter[0],counter[1]);
    return 0;
}

