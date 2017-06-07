#include <stdio.h>
#include <fcntl.h>
#include <malloc.h>
struct stroka {
 char name[4];
 int  n;
};

int main(){
 struct stroka spisok[5];
 int i, fd, p, menu, l=5;
 char k;
 FILE*fp; 

while(1){
 printf("What should be done?\n");
 printf("1)Create list\n ");
 printf("2)Add note\n");
 printf("3)List output\n");
 printf("4)Print one row\n");
 printf("5)Exit\n");
 scanf("%d", &menu);
 if(menu==1){
   for(i=0; i<5; i++){
     scanf("%s", spisok[i].name);
     spisok[i].name[4]='\0';
     scanf("%d",&spisok[i].n);
   }
   fp=fopen("spisok2.txt","w");
   fwrite(spisok,sizeof(struct stroka), 5,fp);
   fclose(fp);
 }
  if(menu==3){
   struct stroka *sp;
   sp=malloc(sizeof(struct stroka)*l);
   fp=fopen("spisok2.txt","r");
   fread(sp, sizeof(struct stroka), l, fp);
   	for(i=0; i<l; i++){
    		printf("%s  %d\n", sp->name, sp->n);
		sp++;
	}
   fclose(fp);

  }
  if(menu==5)
   break;
  if(menu==2){
   fd=open("spisok2.txt",O_WRONLY);
   struct stroka a;
   printf("Enter Name: ");
   scanf("%s", a.name);
   printf("Enter Namber: ");
   scanf("%d", &a.n);
   a.name[4]='\0';
   p=lseek(fd,sizeof(struct stroka)*l,SEEK_SET);
   write(fd,a.name, sizeof(char[4]));
   write(fd,&a.n,sizeof(int));
   l++;
   close(fd);
  }
  if(menu==4){
   fd=open("spisok2.txt", O_RDONLY);
   struct stroka b;
   printf("Which entry?\n");
   scanf("%d",&p);
   lseek(fd, sizeof(struct stroka)*(p-1), SEEK_SET);
   read(fd,b.name, sizeof(char[4]));
   read(fd,&b.n, sizeof(int));
   printf("%s %d\n", b.name, b.n);
   close(fd);
  }
 }
}
