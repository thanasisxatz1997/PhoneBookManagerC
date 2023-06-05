#include <stdio.h>
#include <stdlib.h>
#include "Functions.h"


int main(int argc, char *argv[]) {

	FILE * fp;
	int option;
	printf("Enter Your Option\n\n");
	printf("Your options are:\n1.Create New Book\n2.Create New Contact\n3.Show Entry\n4.Change Entry\n5.Delete Entry\n6.Delete All\n7.Show Entries\n\n");
	scanf("%d",&option);
	scanf("%*c");
   	switch (option){
	case 1:
		CreateNewBook();
	break;
	case 2:
		CreateNewContact();
	break;
	case 3:
		ShowEntry();
	break;
	case 4:
		ChangeEntry();
	break;
	case 5:
		DeleteEntry(); 
	break;
	case 6:
		 DeleteAll();
	break;
	case 7:
		ShowEntries();	
		break;
	default:
		printf("This cannot be selected!");
	}
	return 0;
}





