#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include<time.h>
#include<ctype.h>
#include <time.h>
#include <windows.h>
#include <process.h>

#define KEATAS 72
#define KEBAWAH 80
#define KEKIRI 75
#define KEKANAN 77

int panjang;
int bend_no;
int len;
char key;
void record();
void loading();
int nyawa;
void Delay(long double);
void Permaianan();
void makanan();
int Score();
void awalan();
void gotoxy(int x, int y);
void GotoXY(int x,int y);
void Bend();
void Boarder();
void bawah();
void kiri();
void atas();
void kanan();
void keluar();
int Scoreonly();

struct coordinate
{
    int x;
    int y;
    int direction;
};

typedef struct coordinate coordinate; //mendeklarasi bahwa coordinate adalah struct

coordinate kepala, bend[500],food,body[30];//deklarasi setiap struct yang harus ada dan beberapa menggunakan array

int main()
{

    char key;

    awalan();

    system("cls");

    loading();

    panjang=5;

    kepala.x=25;

    kepala.y=20;

    kepala.direction=KEKANAN;//

    Boarder();//Untuk kanvas

    makanan(); //untuk fungsi makanan

    nyawa=3; //banyaknya nyawa

    bend[0]=kepala;

    Permaianan();   //untuk menginisiasi permainan

    return 0;

}

void Permaianan()
{
    int a,i;

    do
    {

        makanan();
        fflush(stdin);

        len=0;

        for(i=0; i<30; i++)//jika melewati batas maka akan mati

        {

            body[i].x=0;

            body[i].y=0;

            if(i==panjang)

                break;

        }

        Delay(panjang);

        Boarder();// memanggil fungsi boarder lagi

        if(kepala.direction==KEKANAN)

            kanan();

        else if(kepala.direction==KEKIRI)

            kiri();

        else if(kepala.direction==KEBAWAH)

            bawah();

        else if(kepala.direction==KEATAS)

            atas();

        keluar();

    }
    while(!kbhit());

    a=getch();

    if(a==27)

    {

        system("cls");

        exit(0);

    }
    key=getch();

    if((key==KEKANAN&&kepala.direction!=KEKIRI&&kepala.direction!=KEKANAN)||(key==KEKIRI&&kepala.direction!=KEKANAN&&kepala.direction!=KEKIRI)||(key==KEATAS&&kepala.direction!=KEBAWAH&&kepala.direction!=KEATAS)||(key==KEBAWAH&&kepala.direction!=KEATAS&&kepala.direction!=KEBAWAH))

    {

        bend_no++;

        bend[bend_no]=kepala;

        kepala.direction=key;

        if(key==KEATAS)

            kepala.y--;

        if(key==KEBAWAH)

            kepala.y++;

        if(key==KEKANAN)

            kepala.x++;

        if(key==KEKIRI)

            kepala.x--;

        Permaianan();

    }

    else if(key==27)//untuk keluar menggunakan esc

    {

        system("cls");

        exit(0);

    }

    else //untuk mengeluarkan suara beep

    {

        printf("\a");

        Permaianan();

    }
}

void gotoxy(int x, int y)
{

    COORD coord;

    coord.X = x;

    coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}
void GotoXY(int x, int y)
{
    HANDLE a;
    COORD b;
    fflush(stdout);
    b.X = x;
    b.Y = y;
    a = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(a,b);
}
void loading()
{
    int row,col,r,c,q;
    gotoxy(36,14);
	printf("\033[0; 36m");
    printf("Sebentar...");
	printf("\033[0m");
    gotoxy(30,15);
    for(r=1; r<=20; r++)
    {
        for(q=0; q<=100000000; q++); //to display the character slowly
		printf("\033[1; 36m");
        printf(" ");
		printf("\033[0m");
    }
    getch();
}
void bawah()
{
    int i;
    for(i=0; i<=(kepala.y-bend[bend_no].y)&&len<panjang; i++)
    {
        GotoXY(kepala.x,kepala.y-i);
        {
            if(len==0)
                printf("v");
            else
                printf("*");
        }
        body[len].x=kepala.x;
        body[len].y=kepala.y-i;
        len++;
    }
    Bend();
    if(!kbhit())
        kepala.y++;
}
void Delay(long double k)
{
    Score();
    long double i;
    for(i=0; i<=(10000000); i++);
}
void keluar()
{
    int i,check=0;
    for(i=4; i<panjang; i++) //starts with 4 because it needs minimum 4 element to touch its own body
    {
        if(body[0].x==body[i].x&&body[0].y==body[i].y)
        {
            check++;    //check's value increases as the coordinates of head is equal to any other body coordinate
        }
        if(i==panjang||check!=0)
            break;
    }
    if(kepala.x<=10||kepala.x>=70||kepala.y<=10||kepala.y>=30||check!=0)
    {
        nyawa--;
        if(nyawa>=0)
        {
            kepala.x=25;
            kepala.y=20;
            bend_no=0;
            kepala.direction=KEKANAN;
            Permaianan();
        }
        else
        {
            system("cls");
            printf("Nyawa Habis\nBetter Luck Next Time!!!\nTekan apapun untuk keluar\n");
            record();
            exit(0);
        }
    }
}
void makanan()//fungsi untuk menginisiasi makanan dan jika memakan makanan
{
    if(kepala.x==food.x&&kepala.y==food.y)//jika koordinat kepala dan makanan sama
    {
        panjang++;
        time_t a;
        a=time(0);
        srand(a);
        food.x=rand()%70;
        if(food.x<=10)
            food.x+=11;
        food.y=rand()%30;
        if(food.y<=10)

            food.y+=11;
    }
    else if(food.x==0)/*Untuk memunculkan makanan secara random dengan fungsi random*/
    {
        food.x=rand()%70;
        if(food.x<=10)
            food.x+=11;
        food.y=rand()%30;
        if(food.y<=10)
            food.y+=11;
    }
}
void kiri()
{
    int i;
    for(i=0; i<=(bend[bend_no].x-kepala.x)&&len<panjang; i++)
    {
        GotoXY((kepala.x+i),kepala.y);
        {
            if(len==0)
                printf("<");
            else
                printf("*");
        }
        body[len].x=kepala.x+i;
        body[len].y=kepala.y;
        len++;
    }
    Bend();
    if(!kbhit())
        kepala.x--;

}
void kanan()
{
    int i;
    for(i=0; i<=(kepala.x-bend[bend_no].x)&&len<panjang; i++)
    {
     
        body[len].x=kepala.x-i;
        body[len].y=kepala.y;
        GotoXY(body[len].x,body[len].y);
        {
            if(len==0)
                printf(">");
            else
                printf("*");
        }
        
        len++;
    }
    Bend();
    if(!kbhit())
        kepala.x++;
}
void Bend()
{
    int i,j,diff;
    for(i=bend_no; i>=0&&len<panjang; i--)
    {
        if(bend[i].x==bend[i-1].x)
        {
            diff=bend[i].y-bend[i-1].y;
            if(diff<0)
                for(j=1; j<=(-diff); j++)
                {
                    body[len].x=bend[i].x;
                    body[len].y=bend[i].y+j;
                    GotoXY(body[len].x,body[len].y);
                    printf("*");
                    len++;
                    if(len==panjang)
                        break;
                }
            else if(diff>0)
                for(j=1; j<=diff; j++)
                {
                    body[len].x=bend[i].x;
                    body[len].y=bend[i].y-j;
                    GotoXY(body[len].x,body[len].y);
                    printf("*");
                    len++;
                    if(len==panjang)
                        break;
                }
        }
        else if(bend[i].y==bend[i-1].y)
        {
            diff=bend[i].x-bend[i-1].x;
            if(diff<0)
                for(j=1; j<=(-diff)&&len<panjang; j++)
                {
                    /*GotoXY((bend[i].x+j),bend[i].y);
                    printf("*");*/
                    body[len].x=bend[i].x+j;
                    body[len].y=bend[i].y;
                    GotoXY(body[len].x,body[len].y);
                    printf("*");
                    len++;
                    if(len==panjang)
                        break;
                }
            else if(diff>0)
                for(j=1; j<=diff&&len<panjang; j++)
                {
                    body[len].x=bend[i].x-j;
                    body[len].y=bend[i].y;
                    GotoXY(body[len].x,body[len].y);
                    printf("*");
                    len++;
                    if(len==panjang)
                        break;
                }
        }
    }
}
void Boarder()
{
    system("cls");
    int i;
    GotoXY(food.x,food.y);   /*muculkan makanan melalui GotoXY untuk struct food*/
    printf("M");
    for(i=10; i<71; i++) //Memunculkan border atas dan bawah sebanyak 71 
    {
        GotoXY(i,10);//koordinat y 10 untuk atas
		printf("\033[1;31m");
        printf("=");
        GotoXY(i,30);
        printf("*");
		printf("\033[0m;");
    }
    for(i=10; i<31; i++)//Memunculkan border kiri kanam
    {
        GotoXY(10,i);//koordinat x 10 untuk kiri
		printf("\033[1;31m");
        printf("#");
        GotoXY(70,i);
        printf("!");
		printf("\033[0m;");
    }
}
void awalan()
{
    //GotoXY(10,12);
    printf("\t============================================================\n\tSelamat Datang.(selahkan tekan tombol apa saja)\n\t============================================================\n");
    getch();
    system("cls");
    printf("\Cara bermain:\n");
    printf("\n======================================================================\n-> Gunakan arrow keys untuk bermain.\n\n-> Makanan akan muncul dilayar, dan harus dimakan.\n\n-> Terdapat tiga nyawa disetiap permainan. \n\n-> Gunakan tombol apa saja untuk memberhentikan permaian. Tekan lagi untuk memulai\n\n-> Esc untuk keluar. \n======================================================================\n");
    printf("\n\nLanjut ... ?");
    if(getch()==27)
        exit(0);
}
void record()
{
    char plname[20],nplname[20],cha,c;
    int i,j,px;
    FILE *info;
    info=fopen("record.txt","a+");
    getch();
    system("cls");
    printf("Masukan Nama\n");
    scanf("%[^\n]",plname);
    //************************
    for(j=0; plname[j]!='\0'; j++) //Mengubah nama pemain menjadi awalan dengan kapital
    {
        nplname[0]=toupper(plname[0]);
        if(plname[j-1]==' ')
        {
            nplname[j]=toupper(plname[j]);
            nplname[j-1]=plname[j-1];
        }
        else nplname[j]=plname[j];
    }
    nplname[j]='\0';
    
    fprintf(info,"Nama Pemain :%s\n",nplname);
    //for date and time

    time_t mytime;
    mytime = time(NULL);
    fprintf(info,"Tanggal Bermain:%s",ctime(&mytime));
    //**************************
    fprintf(info,"Score:%d\n",px=Scoreonly());//Menampilkan score 
    
    for(i=0; i<=50; i++)
        fprintf(info,"%c",'_');
    fprintf(info,"\n");
    fclose(info);
    printf("Mau melihat record permaian 'y'\n");
    cha=getch();
    system("cls");
    if(cha=='y')
    {
        info=fopen("record.txt","r");
        do
        {
            putchar(c=getc(info));
        }
        while(c!=EOF);
    }
    fclose(info);
}
int Score()
{
    int score;
    GotoXY(20,8);
    score=panjang-5;
	printf("\033[1;33m");
    printf("SCORE : %d",(panjang-5));
    score=panjang-5;
    GotoXY(50,8);
    printf("Nyawa : %d",nyawa);
	printf("\033[0m");
    return score;
}
int Scoreonly()
{
    int score=Score();
    system("cls");
    return score;
}
void atas()
{
    int i;
    for(i=0; i<=(bend[bend_no].y-kepala.y)&&len<panjang; i++)
    {
        GotoXY(kepala.x,kepala.y+i);
        {
            if(len==0)
                printf("^");
            else
                printf("*");
        }
        body[len].x=kepala.x;
        body[len].y=kepala.y+i;
        len++;
    }
    Bend();
    if(!kbhit())
        kepala.y--;
}
