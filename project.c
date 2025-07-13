#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
struct trans
{
    char type[20],category[20];
    int amount; 
};
struct budget
{
    float balance;
    struct  trans t[100];
    int tc; //transactionCount;
};
void authentication()
{
int inpin;
int attempts=3,pin=1234;
while(attempts>0)
{
    printf("enter 1234 to continue \n");
    scanf("%d",&inpin);
    if(pin==inpin)
    {
        printf("acess granted");
        return;
    }
        attempts--;
        printf("incoreect pin %d attempts are left \n",attempts);
}
printf("Too many incoreect attempts \n acess denied");
exit(1);
}
float loadbalance()//file bata balance load garxa
{
    FILE *a;
    a=fopen("balance.txt","r");
    float balance=0.0;//file ma value xaina vane 0 return hunxa
    if (a!=NULL)
    {
        fscanf(a,"%f",&balance);
        fclose(a);
    }
    return balance;
}
void savebalance(float sbalance)
{
    FILE *a;
    a= fopen("balance.txt","w");
    if(a)//if(a!=NULL) jastai kam garxa
    {
        fprintf(a,"%f",sbalance);
        fclose(a);
    }
}
void addtransaction(struct trans t)
{
    FILE *a;
    a=fopen("history.txt","a");
    if(a)
    {
        fprintf(a,"%s %d %s\n",t.type,t.amount,t.category);
        fclose(a);
    }
}
void deposit(struct budget *b)
    {
        float amount,balance;
        printf("enter deposited amount");
        scanf("%f",&amount);
        balance=loadbalance();
        balance=balance+amount;
        printf("\n%f amount is sucessfully deposited\n your new balance is %f",amount,balance);
        savebalance(balance);
        struct trans t;
        strcpy(t.type,"deposit"); //string lai dirct char ko array ma asiign garna mildaina so
        t.amount=amount;
        strcpy(t.category,"income");
        addtransaction(t);
        b->tc++;
    }
void withdraw(struct budget *b)
    {
        float amount,balance;
        printf("enter withdrawn amount");
        scanf("%f",&amount);
        balance=loadbalance();
        if (amount>balance)
        {
           printf("\ninsufficient balance \n");
           return;
        }
        balance=balance-amount;
        printf("\n%f amount is sucessfully withdrawn\n your new balance is %f",amount,balance);
        savebalance(balance);
        struct trans t;
        strcpy(t.type,"withdraw"); 
        t.amount=amount;
        strcpy(t.category,"expense");
        addtransaction(t);
        b->tc++;
    }
void  transactionhistory(struct budget *b)
{
 FILE *a;
 a=fopen("history.txt","r");
 if (a==NULL)
 {
   printf("no transaction hitory found");
   return;
 }
struct trans t;
printf("Transaction history is \n");
while(fscanf(a,"%s %d %s",t.type,&t.amount,t.category)!=EOF)
{
    printf("Type:%s\n amount:%d \n category:%s\n",t.type,t.amount,t.category);
}    
fclose(a);
}
void financialsummary(struct budget *b)
 {
    float income = 0.0, expense = 0.0;
    int i;
    for (i = 0; i < b->tc; i++)// Use 'b->tc' to access transaction count
    {
        if (strcmp(b->t[i].category, "income") == 0)
         {  
            income += b->t[i].amount; 
        } 
        else if (strcmp(b->t[i].category, "expense") == 0)
         {  
            expense += b->t[i].amount;  
        }
    }
    printf("\nFinancial Summary:\n");
    printf("Total Income: %.2f\n", income);
    printf("Total Expense: %.2f\n", expense);
    printf("Balance: %.2f\n", b->balance);  
}
int main()
{
authentication();
    int choice;
    struct budget b;
    b.tc=0;
    b.balance = loadbalance(); 
    do {
        printf("\nSmart Budget Tracker\n");
        printf("1. Deposit Money\n");
        printf("2. Withdraw Money\n");
        printf("3. View Transaction History\n");
        printf("4. View Financial Summary\n");
        printf("5. Exit\n");
        printf("Enter your choice: "); 
        scanf("%d", &choice);
        switch (choice) 
        {
            case 1:
            deposit(&b);
            break;
            case 2:
            withdraw(&b);
            break;
            case 3:
            transactionhistory(&b);
            break;
            case 4:
            financialsummary(&b); //passing budget instance
            break;
            case 5:
            printf("exting program.......");
            exit(1);
            break;
            default:
            printf("Invalid choice,please try again");
            break;
        }
}while(choice!=5);
return 0;
}
