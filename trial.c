// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>
struct Subject{
    char *name;
    int marks;
};
struct Student{
    int PRN;
    char *Name;
    int numsub;
    struct Subject *subject;
};
int main()
{
    int n,i,j,k,temp[10];
    printf("Enter number of student");
    scanf("%d",&n);
    struct Student s[n];
    struct Subject t[10];
    for(i=0; i<n;i++){
    printf("Enter student NAME");
    s[i].Name = malloc(50 * sizeof(char));
    scanf("%s", s[i].Name);
    printf("Enter number of subjects");
    scanf("%d", &s[i].numsub);
    s[i].subject = malloc(s[i].numsub * sizeof(struct Subject));
    ////name loop//
    for(j=0;j<s[i].numsub;j++){
    printf("Enter Subject Name");
    t[j].name = malloc(50 * sizeof(char));
    scanf("%s",&t[i].name);
    for(k=0;k<s[i].numsub;k++)
    printf("ENter marks for each subject");
    t[k].marks = malloc(t[k].marks*sizeof(struct Subject));
    scanf("%d",t[k].marks);
    
        
    }
    
    
    
    
    }
return 0;
}

