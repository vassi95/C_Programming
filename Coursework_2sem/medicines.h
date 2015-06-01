typedef struct{
	char Number[30];
	char name[30];
	double price;
	int date;
	int month;
	int year;
}MyData;
typedef struct nodeElement
{
	MyData val;
	struct nodeElement *next;
}node;

void writeNewMedicine(node *head);
node *addMedicine(node *head);
MyData newMedicine(struct nodeElement *head);
node *readFile(node **head);
void writeWholeFile(node *head);
void printInfo(node *head);
MyData *freeAll(struct nodeElement *head);
MyData *freeAll1(struct nodeElement *head);
int nomNumber(node *head, char *Number);
node *changePrice(node *head);
node *showOutOfDate(node *head);
int correctDate( int day, int month,int year);

