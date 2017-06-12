#include <stdio.h>
#include <fcntl.h>
#include <malloc.h>
struct stroka{
	char name[4];
	int n;
};

int main(){
	int i, p, menu,k;
	struct stroka *spisok;
	int fd;
	while(1){
		printf("Select item  \n");
		printf("1)Create a list  \n");
		printf("2)Add one row  \n");
		printf("3)Remove one row  \n");
		printf("4)List the list  \n");
		printf("5)Exit \n");
		printf("\n");
		scanf("%d",&menu);
		if(menu==1){
			printf("How many items will be in the list?\n");
			scanf("%d",&k);
			spisok=malloc(sizeof(struct stroka)*k);
			for(i=0; i<k; i++){
			   printf("Enter the name  ");
		       scanf("%s", &spisok[i].name);
		       spisok[i].name[4]='\0';
		       printf("Enter the namber  ");
		       scanf("%d", &spisok[i].n); 	
	        }
	        fd=open("spisok2.txt",O_WRONLY | O_CREAT,0666);
	        for(i=0; i<k; i++){
		     write(fd, spisok[i].name, sizeof(char[4]));
		     write(fd, &spisok[i].n, sizeof(int));
	        }
	        close(fd);
		}
		if(menu==2){
			fd=open("spisok2.txt",O_WRONLY);
			struct stroka a;
			printf("Enter the name  ");
			scanf("%s",a.name);
			a.name[4]='\0';
			printf("Enter the namber  ");
			scanf("%d", &a.n); 
			p=lseek(fd,sizeof(struct stroka)*k,SEEK_SET);
			write(fd, a.name, sizeof(char[4]));
		    write(fd, &a.n, sizeof(int));
		    k++;
			close(fd);
		}
		if(menu==3){
		 struct stroka *del;
		 int el;
		 del=malloc(sizeof(struct stroka)*k);
		 FILE *fp;
		 fp=fopen("spisok2.txt","r");
		 fread(del,sizeof(struct stroka),k,fp);
		 fclose(fp);
		 printf("Which item should delete?\n");
		 scanf("%d",&el);
		 for(i=(el-1); i<k-1;i++){
		 	del[i]=del[i+1];
		 }
		 k--;
		 fp=fopen("spisok2.txt","w");
		 fwrite(del,sizeof(struct stroka),k,fp);
		 fclose(fp);
		}
		if(menu==4){
			struct stroka *b;
			b=malloc(sizeof(struct stroka)*k);
			fd=open("spisok2.txt", O_RDONLY);
			for(i=0;i<k;i++){
	 	     read(fd,b[i].name, sizeof(char[4]));
	 	     read(fd,&b[i].n, sizeof(int));
	 	 
	        }
	        for(i=0;i<k;i++)
	          printf("%s %d\n",b[i].name, b[i].n);
	        printf("\n");
	        close(fd);
		}
		if(menu==5){
			break;
		}
	}
}
