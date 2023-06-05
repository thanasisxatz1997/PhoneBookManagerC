#ifndef FILE_FUNCTIONS
#define FILE_FUNCTIONS

void CreateNewBook();
char* ReadLineFromFile(FILE*fp);
int LineCount(FILE *fp);
void CreateNewContact();
int FileExist(char* fileName);
char* ReadAlphanumeric();
struct contact* ReadFromFile(char* fileName);
char* GetNameFromLine(char* line);
char* GetNumberFromLine(char* line);
struct contact* SortContacts(struct contact* contacts,int contactCount);
int BinarySearchForName(struct contact* contacts,char* newName,int contactCount);
void PrintContactsToFile(struct contact* contacts,int contactCount,char* fileName);
void ShowEntry();
void ChangeEntry();
void DeleteEntry();
void DeleteAll();
void ShowEntries();

struct contact* RemoveContact(struct contact* oldContacts,int pos,int count);

struct contact{
	char* name;
	char* number;
		
};

char* ReadAlphanumeric(){
	char* alphanumeric=NULL;
	alphanumeric=(char*)malloc(1*sizeof(char));
	char ch;
	int i=0;
	scanf("%c",&ch);
	while(ch!='\n'){
		alphanumeric[i]=ch;
		i++;
		realloc((char*)alphanumeric,(i+1)*sizeof(char));
		scanf("%c",&ch);
	}
	alphanumeric[i]='\0';
	return alphanumeric;
}

//dhmioyrgia arxeioy Ê

void CreateNewBook(){
	printf("Enter Fhe File Name\n");
	char* fileName= ReadAlphanumeric();
	FILE *fp;
	fp= fopen(fileName,"w");
	fclose(fp);
}

//elegxei an yparxei to arxeio

int FileExist(char* fileName){
	FILE* fp;
	fp= fopen(fileName,"r");
	if(fp==NULL){
		return -3;
	}
	else{
		return 0;
	}
	fclose(fp);
}

void CreateNewContact(){
	printf("Give The File Name\n");
	char* fileName=ReadAlphanumeric();
	if(FileExist(fileName)==-3){
		printf("File cannot be found errorcode:-3 \n");
		return;
	}
	FILE*fp;
	fp=fopen(fileName,"r");
	struct contact* contacts=ReadFromFile(fileName);
	int contactCount=LineCount(fp);
	contacts=SortContacts(contacts,contactCount);
	int i;
	printf("Give new name\n");
	char* newName=ReadAlphanumeric();
	printf("Give new number\n");
	char* newNumber=ReadAlphanumeric();
	int pos=BinarySearchForName(contacts,newName,contactCount);
	if(pos!=-1){
		printf("Entry already exists, error code:-1\n");
		return;
	}
	fclose(fp);
	contactCount++;
	realloc((struct contact*)contacts,contactCount*sizeof(struct contact*));
	contacts[contactCount-1].name=newName;
	contacts[contactCount-1].number=newNumber;
	PrintContactsToFile(contacts,contactCount,fileName);
}

void PrintContactsToFile(struct contact* contacts,int contactCount,char* fileName){
	FILE*fp;
	fp=fopen(fileName,"w");
	int i;
	for(i=0;i<contactCount;i++){
		fprintf(fp,"%s,%s\n",contacts[i].name,contacts[i].number);
	}
	fclose(fp);
}


int BinarySearchForName(struct contact* contacts,char* newName,int contactCount){
	int pos=-1,top=0,bot=contactCount-1,mid;
	while(top<=bot && pos==-1){
		mid=(top+bot)/2;
		if(strcmp(newName,contacts[mid].name)==0){
			pos=mid;
		}
		else if(strcmp(newName,contacts[mid].name)<0){
			bot=mid-1;
		}else{
			top=mid+1;
		}
	}
	return pos;
}


//poses grammes exei to arxeio

int LineCount(FILE *fp){
	fseek(fp,0,SEEK_SET);
	int count=0;
	char ch;
	fscanf(fp,"%c",&ch);
	while(ch!=EOF){
		if(feof(fp)){
			break;
		}
		if(ch=='\n'){
			count++;
		}
		fscanf(fp,"%c",&ch);		
	}
	fseek(fp,0,SEEK_SET);
	return count;
}

//diabazei kai epistrefei enan pinaka me ta periexomena mias grammhs toy arxeioy

char* ReadLineFromFile(FILE*fp){
	char* line=NULL;
	char ch;
	line=(char*)malloc(1*sizeof(char));
	fscanf(fp,"%c",&ch);
	int i=0;
	while(ch!='\n'){
		if(feof(fp)){
			break;
		}
		line[i]=ch;
		i++;
		realloc((char*)line,(i+1)*sizeof(char));
		fscanf(fp,"%c",&ch);
	}
	line[i]='\0';
	return line;
}

//to function ftiaxnei kai epistrefei pinaka typou struct contact o opoios periexei ta onomata kai ta thl olvn tcn epafvn

struct contact* ReadFromFile(char* fileName){
	FILE*fp;
	fp=fopen(fileName,"r");
	fseek(fp,0,SEEK_SET);
	int lines=LineCount(fp);
	int i;
	struct contact* contacts;
	contacts=(struct contact*)malloc(lines*sizeof(struct contact));
	for(i=0;i<lines;i++){
		char* lineStr=NULL;
		lineStr=ReadLineFromFile(fp);
		char* lineName=GetNameFromLine(lineStr);
		char* lineNumber=GetNumberFromLine(lineStr);
		contacts[i].name=lineName;
		contacts[i].number=lineNumber;
	}
	fclose(fp);
	return contacts;
}

struct contact* SortContacts(struct contact* contacts,int contactCount){
	int i,j;
	struct contact temp;
	for(i=0;i<contactCount;i++){
		for(j=contactCount-1;j>i;j=j-1){
			if(strcmp(contacts[j].name,contacts[j-1].name)<0){
				temp=contacts[j-1];
				contacts[j-1]=contacts[j];
				contacts[j]=temp;
			}	
		}
	}
	return contacts;
}

//to function auto pairnei to name apo thn grammh kai to epistrefei

char* GetNameFromLine(char* line){
	char* name=NULL;
	name=(char*)malloc(1*sizeof(char));
	int i=0;
	while(line[i]!=','){
		name[i]=line[i];
		i++;
		realloc((char*)name,(i+1)*sizeof(char));
	}
	name[i]='\0';
	return name;
}

//epistrefei ton ariumo mias epafhs apo ena line

char* GetNumberFromLine(char* line){
	char* number=NULL;
	number=(char*)malloc(1*sizeof(char));
	int i=0;
	while(line[i]!=','){
		i++;
	}
	int j=0;
	i++;
	while(line[i]!='\0'){
		number[j]=line[i];
		i++;
		j++;
		realloc((char*)number,(j+1)*sizeof(char));
	}
	number[j]='\0';
	return number;
}


void ShowEntry(){
	printf("Give File Name\n");
	char* fileName=ReadAlphanumeric();
	int errorCode=FileExist(fileName);
	if (errorCode==-3){
		printf("File cannot be found, errorcode:-3");
		return;
	}
	printf("Give Contact Name\n");
	char* name=ReadAlphanumeric();
	struct contact* contacts=ReadFromFile(fileName);
	FILE*fp;
	fp=fopen(fileName,"r");
	int count=LineCount(fp);
	SortContacts(contacts,count);
	int pos=BinarySearchForName(contacts,name,count);
	if(pos==-1){
		printf("Entry does not exist, errorcode:-2\n");
		return;
	}
	printf("The contact is %s %s\n",contacts[pos].name,contacts[pos].number);
	fclose(fp);
}


void ChangeEntry(){
	printf("Give File Name\n");
	char* fileName=ReadAlphanumeric();
	int errorCode=FileExist(fileName);
	if(errorCode==-3){
		printf("File cannot be found, errorcode:-3\n");
		return;
	}
	printf("Give Contact Name\n");
	char* name=ReadAlphanumeric();
	struct contact* contacts=ReadFromFile(fileName);
	FILE*fp;
	fp=fopen(fileName,"r");
	int count=LineCount(fp);
	SortContacts(contacts,count);
	int pos=BinarySearchForName(contacts,name,count);
	if(pos==-1){
		printf("Name cannot be found, errorcode:-2\n");
		return;
	}
	printf("Give new number\n");
	char* newNumber=ReadAlphanumeric();
	contacts[pos].number=newNumber;
	printf("The contacts number has changed\n");
	fclose(fp);
	PrintContactsToFile(contacts,count,fileName);
}

void DeleteEntry(){
	printf("Give File Name\n");
	char* fileName=ReadAlphanumeric();
	int errorCode=FileExist(fileName);
	if(errorCode==-3){
		printf("File cannot be found, errorcode:-3\n");
		return;
	}
	printf("Give Contact Name\n");
	char* name=ReadAlphanumeric();
	struct contact* contacts=ReadFromFile(fileName);
	FILE*fp;
	fp=fopen(fileName,"r");
	int count=LineCount(fp);
	SortContacts(contacts,count);
	int pos=BinarySearchForName(contacts,name,count);
	if(pos==-1){
		printf("Name cannot be found, errorcode:-1\n");
		return;
	}
	fclose(fp);	
	struct contact* newContacts;
	newContacts=RemoveContact(contacts,pos,count);
	count=count-1;
	PrintContactsToFile(newContacts,count,fileName);
	printf("The contact has been deleted\n");
}


struct contact* RemoveContact(struct contact* oldContacts,int pos,int count){
	struct contact* contacts=(struct contact*)malloc((count-1)*sizeof(struct contact));
	int i,j=0;
	for(i=0;i<count;i++){
		if(i!=pos){
			contacts[j]=oldContacts[i];
			j++;
		}
	}
	return contacts;
}

void DeleteAll(){
	printf("Give File Name\n");
	char* fileName=ReadAlphanumeric();
	int errorCode=FileExist(fileName);
	if(errorCode==-3){
		printf("File cannot be found, errorcode:-3\n");
		return;
	}
	FILE*fp;
	fp=fopen(fileName,"w");
	fclose(fp);
	printf("All contacts have been deleted");
}

void ShowEntries(){
	printf("Give File Name\n");
	char* fileName=ReadAlphanumeric();
	int errorCode=FileExist(fileName);
	if(errorCode==-3){
		printf("File cannot be found, errorcode:-3\n");
		return;
	}
	struct contact* contacts=ReadFromFile(fileName);
	FILE*fp;
	fp=fopen(fileName,"r");
	int count=LineCount(fp);
	int i;
	printf("All Entries:\n");
	for(i=0;i<count;i++){
		printf("%s %s\n",contacts[i].name,contacts[i].number);
	}
	
}

#endif

