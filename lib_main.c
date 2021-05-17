#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
#include<time.h>
#include<conio.h>
#include<unistd.h>
#include<ctype.h>

/*########################################### Documentation###################################################

=> USAGE : gcc lib_project.c
         : ./a.exe [On Windows system]
         : ./a.out [On Linux system]

=> FILES : user_details.txt
         : record.txt
         : book_details.txt

=> LAST MODIFIED : 1 April 2020

=> AUTHORS : Kavya S Jain
           : Keertana .V.
           : Akankshya Singh
           : Kavya E

###############################################################################################################
*/

# define MAX_USERS 1
# define MAX_PASSWORD 20
# define MAX_NAMESIZE 50

void create_account();
void frontpage();
void MainMenu();
void display();
void borrow();
void ViewBook();
void AddBook();
void login();
void init();
void date();
void ReturnBook();
void fine();

char categories[][15]={"Computer","Electronics","Electrical","Civil","Mechanical","Architecture"};

struct details
{
    int libid;
    char name[MAX_NAMESIZE];
    char password[MAX_PASSWORD];
    char phonenumber[10];
};

struct issue_book
{
    int libid;
    int bookid;
    char book_name[50];
    char *category;
    int dd,mm,yy;
    int dr,mr,yr;
    int fine;    
};
struct issue_book b;

struct books
{
	int id;
	char stname[20];
	char name[50];
	int quantity;
	char *cat;
};
struct books a;

int main()
{
	init();
	return 0;
}

void frontpage()
{
    system("cls");
    printf("\n\n\n\n\n");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t        =                 WELCOME                   =");
    printf("\n\t\t\t        =                   TO                      =");
    printf("\n\t\t\t        =                 LIBRARY                   =");
    printf("\n\t\t\t        =               MANAGEMENT                  =");
    printf("\n\t\t\t        =                 SYSTEM                    =");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\n\n\t\t\t Enter any key to continue.....");
    getch();
    MainMenu();
}

void MainMenu()
{
	system("cls");
	int i;
	printf(":::::::::::: LIBRARY MANAGEMENT SYSTEM ::::::::::::");
	printf("\n:::::::: 1=> Display account details");
	printf("\n:::::::: 2=> Add a new book");
    printf("\n:::::::: 3=> View available books");
    printf("\n:::::::: 4=> Issue a book");
    printf("\n:::::::: 5=> Return a book");
	printf("\n:::::::: 6=> Exit");
	printf("\n:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::");
	printf("\nEnter your choice: ");
	switch(getch())
    {
        case '1':
			display();
			break;
		case '2':
			AddBook();
			break;
		case '3':
			ViewBook();
			break;
		case '4':
			borrow();
			break;
        case '5':
       		ReturnBook();
       		break;
		case '6':
		{
			system("cls");
			printf("\tLibrary Management System\n");
			printf("\n\t\t\t\t\t\tProject by:\n");
            printf("\n\t\t\t\t\t  Kavya.S.Jain\n");
            printf("\n\t\t\t\t\t  Keertana\n");
            printf("\n\t\t\t\t\t  Kavya.E\n");
            printf("\n\t\t\t\t\t  Akankshya\n");
			//printf("::::::::::::::::::::::::::::\n");
			printf("\t\tThank you !");
            usleep(10000);
			exit(0);
		}
    }
}

void create_account()
{
	FILE *fptr,*fp;
    printf("\t\t\t\t\tWelcome\n");
    printf("\n");
    fp=fopen("user_details.txt","r");
    fptr = fopen("user_details.txt","a");
    struct details* ptr;
    ptr=(struct details*)malloc((MAX_USERS)*sizeof(struct details));
    char *pointer;
    char str[45];
    pointer=str;
    const char ch= ',';
    char res[5];
    int i;
    while((fgets(str,sizeof(str),fp)!= NULL))
    {
        pointer=fgets(str,sizeof(str),fp);
    }
    strcpy(res,strrchr(str,ch));
    for(i=0; i<4; i++)
        {
            res[i] = res[i + 1];
        }
    i=atoi(res);
    ptr->libid = i+1;

    if(fptr == NULL)
        {
            printf("Error!");   
            exit(0);          
        }

    printf("Enter your name: ");
    scanf("%s", (ptr)->name);
    fprintf(fptr,"\n");
    fprintf(fptr,"%s,",(ptr)->name);

    char repassword[MAX_PASSWORD];
    do
    {
    printf("Enter a password: ");
    scanf("%s", (ptr)->password);
    printf("Renter password: ");
    scanf("%s",repassword);
    if(strcmp(ptr->password,repassword)!=0)
        {
            printf("Passwords do not match\n"); // Do some special error handling
            system("cls");
        }
    }while(strcmp(ptr->password,repassword)!=0);
    fprintf(fptr,"%s,",ptr->password);

    do
    {
    printf("Enter your phone number: ");
    scanf("%10s", ptr->phonenumber);
    if(strnlen(ptr->phonenumber,10) != 10)
        {
            printf("Invalid phone number\n"); // Do some special error handling
        }
    }while(strnlen(ptr->phonenumber,10) != 10);
    fprintf(fptr,"%s,",ptr->phonenumber);

    //fprintf(fptr,"NULL,");
    fprintf(fptr,"%d",ptr->libid);

    printf("Your LIBID is %d\n",ptr->libid);
    usleep(999000);
    fclose(fp);
    fclose(fptr);
    system("cls");
    login();
}

void display()
{
    FILE *fp,*fp2;
    int flag=-1;
    fp=fopen("user_details.txt","r");
    int temp;
    char str[45];
    char * ptr;
    ptr=str;
    char ch= ',';
    char res[5];
    int id;
    int i;
    int entered_id;
    char password[MAX_PASSWORD];
    system("cls");
    printf("Enter your LIBID : ");
    scanf("%d",&entered_id);
    while((fgets(str,sizeof(str),fp) != NULL))
    {
        ptr=fgets(str,sizeof(str),fp);
        strcpy(res,strrchr(str,ch));
        for(i=0; i<4; i++)
        {
            res[i] = res[i + 1];
        }
        id=atoi(res);
        int i = 0;
        char *p = strtok (str,",");
        char *array[4];

        while (p != NULL)
        {
            array[i++] = p;
            p = strtok (NULL, ",");
        }
        if(entered_id==id)
        {
                printf("Enter password : ");
                scanf("%s",&password);
                if(strcmp(password,array[1])==0)
                { 
            	    printf("NAME : %s\n",array[0]);
            	    printf("CONTACT NO : %s\n",array[2]);
            	    printf("LIBID : %s\n",array[3]);
            	    fp2=fopen("record.txt","r");
            	    fseek(fp2,0,SEEK_SET);
            	    while(fread(&b,sizeof(b),1,fp2)==1)
            	    {
            	    	if(entered_id==b.libid)
            	    	{
            	    		flag=0;
            	    		printf("\nBORROWED BOOK: %s",b.book_name);
            	    		printf("\nBORROWED BOOK ID:  %d",b.bookid);
                            printf("\nISSUE DATE: %d/%d/%d",b.dd,b.mm,b.yy);
                            printf("\nRETURN DATE: %d/%d/%d",b.dr,b.mr,b.yr);
            	    		printf("\n\nPress Enter to go back to Main Menu..... ");
							getch();
							MainMenu();
							break;
						}
					}
					if(flag==-1)
					{
						printf("\n\nNo book borrowed....... ");
						printf("\nPress enter to go back to Main Menu..... ");
						getch();
						MainMenu();
					}
            	    temp=1;
            	    break;
                }
                else
                {
                    printf("Incorrect password \n");
                } 
        }
        else
        {
            temp=0;
            continue;
        }
    }
    if(temp=0)
    {
        printf("LIBID not found !\n");
        usleep(25000);
        MainMenu();
    }
    fclose(fp);
}

void borrow()
{
	FILE *fp,*fp2,*fp3,*ft;
    fp=fopen("user_details.txt","r");
    int temp;
    int flag=-1;
    char str[45];
    char * ptr;
    ptr=str;
    char ch= ',';
    char res[5];
    int id;
    int i;
    int entered_id;
    int d;
    system("cls");
    printf("\nEnter your LIBID : ");
    scanf("%d",&entered_id);
    while((fgets(str,sizeof(str),fp) != NULL))
    {
        ptr=fgets(str,sizeof(str),fp);
        strcpy(res,strrchr(str,ch));
        for(i=0; i<4; i++)
        {
            res[i] = res[i + 1];
        }
        id=atoi(res);
        int i = 0;
        char *p = strtok (str,",");
        char *array[4];

        while (p != NULL)
        {
            array[i++] = p;
            p = strtok (NULL, ",");
        }
        if(entered_id==id)
        {
                printf("Enter book id : ");
                scanf("%d",&d);
                fp2=fopen("book_details.txt","a+");
                fseek(fp2,0,SEEK_SET);
                while(fread(&a,sizeof(a),1,fp2)==1)
				{
					if(a.id==d)
					{
						if(a.quantity==0)
						{
							printf("\nInsufficient quantity of the book..... ");
							printf("\nPress Enter to go back to Main Menu...... ");
							getch();
							MainMenu();
						}
						else
						{
							strcpy(b.book_name,a.name);
							b.bookid=a.id;
							b.libid=id;
	                        date();
							flag=0;
							fp3=fopen("record.txt","a+");
							fseek(fp3,0,SEEK_END);
							fwrite(&b,sizeof(b),1,fp3);
							fclose(fp3);
							rewind(fp2);
							ft=fopen("temp.txt","a+");
							while(fread(&a,sizeof(a),1,fp2)==1)
							{
								if(a.id==d)
								{
									a.quantity-=1;
									fwrite(&a,sizeof(a),1,ft);
								}
								else
								{
									fwrite(&a,sizeof(a),1,ft);
								}
							}
							fclose(ft);
							fclose(fp2);
							remove("book_details.txt");
							rename("temp.txt","book_details.txt");
							printf("\nPress Enter to go back to Main Menu...... ");
							getch();
							MainMenu();
							//date(b.di,b.mi,b.yi);
							break;
						}
					}
				}
				if(flag==-1)
				{
					printf("\nIncorrect book id..... ");
				}
				temp=1;
				break;
        }
        else
        {
            temp=0;
            continue;
        }
    }
    if(temp=0)
    {
        printf("LIBID not found !\n");
    }
    fclose(fp);
    fclose(fp2);
}

void login()
{
    FILE *fp;
    fp=fopen("user_details.txt","r");
    char str[45];
    char * ptr;
    ptr=str;
    char ch= ',';
    char res[5];
    int id,i;
    int entered_id;
    char password[MAX_PASSWORD];
    printf("Enter your LIBID : ");
    scanf("%d",&entered_id);
    while((fgets(str,sizeof(str),fp) != NULL))
    {
        ptr=fgets(str,sizeof(str),fp);
        strcpy(res,strrchr(str,ch));
        for(i=0; i<4; i++)
        {
            res[i] = res[i + 1];
        }
        id=atoi(res);
        int i = 0;
        char *p = strtok (str,",");
        char *array[4];

        while (p != NULL)
        {
            array[i++] = p;
            p = strtok (NULL, ",");
        }
        if(entered_id==id)
        {
                printf("Enter password : ");
                scanf("%s",&password);
                if(strcmp(password,array[1])==0)
                {
                    usleep(2000);
                    printf("\n");
                    printf("Welcome %s !", array[0]);
                    frontpage();
                    break;
                }   
                else
                {
                    printf("Incorrect password \n");
                    usleep(800000);
                    system("cls");
                    login();
                }       
        }
        else
        {
            continue;
        }
    }
    fclose(fp);
}

void init()
{ 
    system("cls"); 
    printf("Are you an existing user(Y/N)");
    char c;
    c = getch();
    if(c=='n' || c=='N')
    {
        printf("\nPress 1 to create a new account ");
        printf("\nPress 2 to Exit ");
        if(getch()=='1')
        {
            system("cls");
            printf("\nCREATE ACCOUNT\n");
            printf("\n");
            create_account();
        }
        else
        {
            exit(0);
        }
        
    }
    else if(c=='y' || c=='Y')
    {
        printf("\nPress 1 to LOGIN ");
        printf("\nPress 2 to Exit ");
        if(getch()=='1')
        {
            system("cls");
            printf("\n\t\t\t\tPLEASE LOGIN\n");
            login();
        }
        else
        {
            exit(0);
        }
    }
    else
    {
        printf("\nbye bye !\n");
        exit (0);
    } 
}

void AddBook()
{
    FILE *fp,*ft,*fs;
    int s;
    char findbook='f';
	system("cls");
	int i;
	printf("::::::::::::::::::::CATEGORIES::::::::::::::::::::");
	printf("\n:::::: 1=> Computer");
	printf("\n:::::: 2=> Electronics");
	printf("\n:::::: 3=> Electrical");
	printf("\n:::::: 4=> Civil");
	printf("\n:::::: 5=> Mechanical");
	printf("\n:::::: 6=> Architecture");
	printf("\n:::::: 7=> Back to Main Menu");
	printf("\nEnter your choice: ");
	scanf("%d",&i);
	if(i==7)
	{
		MainMenu();
	}
	else
	{
		system("cls");
		fp=fopen("book_details.txt","a+");
		fseek(fp,0,SEEK_END);
		printf("\nBook id:");
		scanf("%d",&a.id);
		printf("\nBook name: ");
		fflush(stdin);
		gets(a.name);
		printf("\nQuantity: ");
		scanf("%d",&a.quantity);
		a.cat=categories[i-1];
		fseek(fp,0,SEEK_END);
		fwrite(&a,sizeof(a),1,fp);
        fclose(fp);
        printf("\nDo you want to enter more records(Y/N)......");
        if(getch()=='n' || getch()=='N')
        {
    		MainMenu();
        }
        else
        {
            AddBook();
        }
	}
}

void ViewBook()
{
    FILE *fp,*ft,*fs;
    int s;
    char findbook='f';
	system("cls");
	fp=fopen("book_details.txt","r");
	rewind(fp);
	while(fread(&a,sizeof(a),1,fp)==1)
	{
		printf("CATEGORY: %s\n",a.cat);
		printf("BOOK ID: %d \n",a.id);
		printf("BOOK NAME: %s\n ",a.name);
		printf("QUANTITY: %d\n ",a.quantity);
        printf("\n");

	}
	fclose(fp);
	printf("\nEnter any key to return to main menu...... ");
	getch();
	MainMenu();
}

void date()
{
    printf("\nEnter date of issuance of the book (in dd-mm-yyyy): ");
    scanf("%d-%d-%d",&b.dd,&b.mm,&b.yy);
    if ((b.mm==1||b.mm==3||b.mm==5||b.mm==7||b.mm==8||b.mm==10||b.mm==12)&&b.dd<=31)
    {
        if (b.dd==31&&b.mm!=12)
        {
          printf("\nDate of returning the book: %d-%d-%d",7,b.mm+1,b.yy);
          b.dr=7;
          b.mr=b.mm+1;
          b.yr=b.yy;

        }
		else if (b.dd==31&&b.mm==12)
        {
            printf("\nDate of returning the book: %d-%d-%d",7,1,b.yy+1);
            b.dr=7;
            b.mr=1;
            b.yr=b.yy+1;
        }
        else
        {
            printf("\nDate of returning the book: %d-%d-%d",b.dd+7,b.mm,b.yy);
            b.dr=b.dd+7;
            b.mr=b.mm;
            b.yr=b.yy;
        }
    
        
    }
    else if ((b.mm==4||b.mm==6||b.mm==9||b.mm==11)&&b.dd<=30)
    {
        if (b.dd<30)
            {
            printf("\nDate of returning the book: %d-%d-%d",b.dd+7,b.mm,b.yy);
            b.dr=b.dd+7;
            b.mr=b.mm;
            b.yr=b.yy;

            }
        else
            {
            printf("\nDate of returning the book: %d-%d-%d",07,b.mm+1,b.yy);
            b.dr=b.dd+7;
            b.mr=b.mm;
            b.yr=b.yy;
            }
            
    }
    else if(b.mm==2)
    {
        if(b.yy%4==0)
        {
            if(b.dd==29)
            {
                printf("\nDate of returning the book: %d-%d-%d ",7,b.mm+1,b.yy);
                b.dr=7;
                b.mr=b.mm+1;
                b.yr=b.yy;
            }
        }
        else if(b.dd==28)
        {
            printf("\nDate of returning the book: %d-%d-%d",07,b.mm+1,b.yy);
            b.dr=7;
            b.mr=b.mm+1;
            b.yr=b.yy;
        }
        else
        {
            printf("\nDate of returning the book: %d-%d-%d",b.dd+7,b.mm,b.yy);
            b.dr=b.dd+7;
            b.mr=b.mm;
            b.yr=b.yy;
        }
    }       
    
}

void ReturnBook()
{
	system("cls");
	FILE *fp,*fp2,*ft2;
	fp=fopen("record.txt","a+");
	fseek(fp,0,SEEK_SET);
	int d1,d2,flag=-1;
	char ch;
	printf("\nEnter your LIBID: ");
	scanf("%d",&d1);
	printf("\nEnter BOOK ID: ");
	scanf("%d",&d2);
	while(fread(&b,sizeof(b),1,fp)==1)
	{
		if(d1==b.libid && d2==b.bookid)
		{
			flag=0;
			printf("\nDo you want to return the book (Y/N) ?");
			fflush(stdin);
			scanf("%c",&ch);
		}
	}
	if(flag==-1)
	{
		printf("\nInvalid book or user id...... ");
		fclose(fp);
		printf("\nPress Enter to go to main menu..... ");
		getch();
		MainMenu();
	}
	if(ch=='Y' || ch=='y')
	{
		FILE *ft;
		rewind(fp);
		ft=fopen("temp.txt","a+");
		fseek(ft,0,SEEK_SET);
		while(fread(&b,sizeof(b),1,fp)==1)
		{
			if(d1!=b.libid && d2!=b.bookid)
			{
				fseek(ft,0,SEEK_CUR);
				fwrite(&b,sizeof(b),1,ft);
			}
		}
		fp2=fopen("book_details.txt","a+");
		fseek(fp2,0,SEEK_SET);
		while(fread(&a,sizeof(a),1,fp2)==1)
		{
			if(a.id==d2)
			{
			//	a.quantity+=1;
				ft2=fopen("temp2.txt","a+");
				rewind(fp2); 
				while(fread(&a,sizeof(a),1,fp2)==1)
				{
					if(a.id==d2)
					{
						a.quantity+=1;
						fwrite(&a,sizeof(a),1,ft2);
					}
					else
					{
						fwrite(&a,sizeof(a),1,ft2);
					}
				}
				fclose(fp2);
				fclose(ft2);
				remove("book_details.txt");
				rename("temp2.txt","book_details.txt");
				break;
			}
		}
		fclose(fp);
		fclose(ft);
		remove("record.txt");
		rename("temp.txt","record.txt");
		fine();
		printf("\nDo you want to return another book (Y/N) ? ");
		if(getch()=='Y' || getch()=='y')
		{
			ReturnBook();
		}
		else
		{
			MainMenu();
		}
	}
}

void fine()
{
    int day1,mon1,year1;
    int day2,mon2,year2;
    int day_diff,mon_diff,year_diff;
    int fine=0;
    b.fine=fine;
    
    day1=b.dr;
    mon1=b.mr;
    year1=b.yr;
    printf("Enter the date of return in dd-mm-yyyy format: ");
    scanf("%d-%d-%d",&day2,&mon2,&year2);

    if(day2<day1)
    {
    if(mon2==3)
        {
        if((year2%4==0 && year2%100!=0)||(year2%400==0))
        {
        day2 += 29;
        }
        else
        {
        day2 += 28;
        }
    }
    else if(mon2==5||mon2==7||mon2==10||mon2==12)
        {
        day2 +=30;
        }
    else
        {
        day2 += 31;
        }
        mon2 = mon2-1;
    }
    if (mon2<mon1)
    {
    mon2 += 12;
    year2 -= 1;
    }
    day_diff=day2-day1;
    mon_diff=mon2-mon1;
    year_diff=year2-year1;
    //printf("total number of days: %dyears %02d months %02d days.",year_diff, mon_diff, day_diff);

    //calculating the fine
    if(mon_diff==0 && year_diff==0){
    if(day_diff>14 && day_diff<=24)
    {
        b.fine=day_diff*2;
    }
    else if(day_diff>24)
    {
        b.fine=20+(day_diff-10)*5;
    }
    else
    {
        b.fine=0;
        //printf("Fine to be paid= %d", b.fine);
    }
    }
    else
    {
    b.fine=(day_diff*5)+(mon_diff*20)+(year_diff*100);
    }
    printf("\nThe total fine to be paid is: %d\n",b.fine);
}