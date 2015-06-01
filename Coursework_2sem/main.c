#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "medicines.h"

int main()
{
	node *head = NULL;
	int choice;
	while (1)
	{
		printf("\n");
		printf("\n\t\tCHOOSE ONE OF THE OPTIONS!\n\n");
		printf("\t\t1 - Add new medicine\n ");
		printf("\t\t2 - Change the price of a medicine\n");
		printf("\t\t3 - List out of date medicines\n");
		printf("\t\t4 - Print information of medicine\n");
		printf("\t\t0 - Exit the menu\n");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			head = addMedicine(head);
			writeNewMedicine(head);
			head = freeAll(head);
			break;
		case 2:
			head = changePrice(head);
			break;
		case 3:
			head = showOutOfDate(head);
			head = freeAll1(head);
			break;
		case 4:
			printInfo(head);
			break;
		case 0:
			return 0;
			break;
		default:
			system("cls");
			printf("\n\t\t\tWRONG CHOICE!!!!!!\n\n");
			break;
		}
	}
	return 0;
}

node *addMedicine(node *head){
 	node *temp;
	temp = (node *)malloc(sizeof(node));
	node *current;
	current = (node *)malloc(sizeof(node));
	if (temp == NULL){
		printf("\nNot enough memory\n");
		exit(1);
	}
	if (head == NULL){
		head = temp;
		current = head;
		current->val = newMedicine(head);
		current->next = NULL;
	}
	else{
		current->next = current;
		current->val = newMedicine(head);
		temp->next = temp;
		temp;
	}
	return head;
}

MyData newMedicine(node *head){
	MyData val;
	printf("\nEnter medicine name: ");
	scanf("%s", val.name);
	fflush(stdin);
	do{
		printf("\nEnter unique number:");
		scanf("%s", val.Number);
	} while (!nomNumber(head, val.Number));
	fflush(stdin);
	printf("\nEnter price:");
	scanf("%lf", &val.price);
	fflush(stdin);
	do{
		printf("\nRegistration date(DD.MM.YYYY)");
		scanf("%d.%d.%d.", &val.date,&val.month,&val.year);
	} while (!correctDate(val.date, val.month,val.year));
	fflush(stdin);
	return val;
}

void writeNewMedicine(node *head){

	FILE *fp;
	node *current;
	current = head;
	if (head == NULL){
		printf("The list is empty!");
		exit(3);
	}
	if ((fp = fopen("Medicines", "ab")) == NULL){
		printf("\nThe file can't be opened for writing\n");
		exit(4);
	}
	while (current != NULL){
		if ((fwrite(&current->val, sizeof(current->val), 1, fp)) != 1)
            printf("Can't write new data");
		current = current->next;
	}
	printf("\n\nThe data was saved!\n\n");
	fclose(fp);
}

node *readFile(node **head) {
	FILE *fp;
	node *current;
	if ((fp = fopen("Medicines", "rb")) == NULL){
		printf("\nThe file can't be opened!\n");
	}
	else{
		do{
			current = (node*)malloc(sizeof(node));
			current->next = NULL;
			if (!(fread(&(current->val), sizeof(current->val), 1, fp))){
				break;
			}
			current->next = *head;
			*head = current;
		} while (1);
	}
	fclose(fp);
	return *head;
}

int correctDate( int day, int month, int year){
	if (year<1){
		printf("\n-->Wrong year!<--\n");
		return 0;
	}
	else{
		if (year % 4 == 0){
			if (month<1 || month>12){
				printf("\n-->Wrong month!<--\n");
				return 0;
			}
			else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12){
				if (day>31 || day<1){
					printf("\n-->Wrong day!<--\n");
					return 0;
				}
				else {
					return 1;
				}
			}
			else if (month == 2){
				if (day>29 || day<1){
					printf("\n-->Wrong day!<--\n");
					return 0;
				}
				else{
					return 1;
				}
			}
			else{
				if (day>30 || day<1){
					printf("\n-->Wrong day!<--\n");
					return 0;
				}
				else{
					return 1;
				}
			}
		}
		else{
			if (month>12 || month<1){
				printf("\n-->Wrong month!<--\n");
				return 0;
			}
			else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12){
				if (day<1 || day>31){
					printf("\n-->Wrong day!<--\n");
					return 0;
				}
				else {
					return 1;
				}
			}
			else if (month == 2){
				if (day<1 || day>28){
					printf("\n-->Wrong day!<--\n");
					return 0;
				}
				else{
					return 1;
				}
			}
			else {
				if (day<1 || day>30){
					printf("\n-->Wrong day!<--\n");
					return 0;
				}
				else{
					return 1;
				}
			}
		}
	}
}

void writeWholeFile(node *head){
	FILE *fp;
	node *current;
	current = head;
	if (head == NULL){
		printf("The list is empty!");
		exit(3);
	}
	if ((fp = fopen("Medicines", "wb")) == NULL){
		printf("\nThe file can't be opened for writing!\n");
		exit(4);
	}
	while (current != NULL){
		if ((fwrite(&current->val, sizeof(current->val), 1, fp)) != 1)
            printf("Can't write new data!");
		current = current->next;
	}
	printf("The data was saved!");
	fclose(fp);
}

MyData *freeAll(node *head)
{
	node *temp, *p;
	for (temp = head; temp->next != NULL;){
		p = temp;
		temp = p->next;
		free(p);
	}
	return NULL;
}

MyData *freeAll1(struct nodeElement *head){
    	node *temp, *p;
	for (temp = head; temp!= NULL;temp=temp->next){
		p = temp;
		temp = p->next;
		free(p);
	}
	return NULL;
}

int nomNumber(node *head, char *Number){
	int flag = 0;
	node *current = NULL;
	head = readFile(&head);
	current = head;
	while (current !=NULL){
		if (!strcmp(current->val.Number, Number)){
			printf("\nThere is a medicine with the same ID!\n");
			flag = 0;
		}
		else{
			flag = 1;
		}
		current = current->next;
		return flag;
	}
}

node *changePrice(node *head)
{
	node *current;
	head = readFile(&head);
	current = head;
	double newPrice = 0;
	char searched[30];
	printf("Enter name or the ID of the drug:");
	scanf("%s", &searched);
	while (current){
	if (!(strcmp(current->val.name, searched))|| !(strcmp(current->val.Number, searched)))
	{
		printf("Enter the new price:");
		scanf("%lf", &newPrice);
		current->val.price = newPrice;
		printf("The new price of the medicine is: %.2lf", current->val.price);
		printf("\n");
	}
	current = current->next;}
	writeWholeFile(head);
}

node *showOutOfDate(node *head)
{
    node *current;
	head = readFile(&head);
	current = head;
	int dayNow;
	int mounthNow;
	int yearNow;
	int exp;
    printf("Enter expiration period: ");
	scanf("%d", &exp);
	printf("\nEnter current date in this format:(DD.MM.YY): ");
	scanf("%d.%d.%d", &dayNow, &mounthNow, &yearNow);
    yearNow=yearNow-exp;
    while (current){
	if (yearNow >= current->val.year)
	{
		printf("\nMedicine:%s\nNumber:%s\nPrice:%.2lf\nRegistration date:%d.%d.%d\n\n", current->val.name, current->val.Number, current->val.price, current->val.date, current->val.month, current->val.year);
	}
	current = current->next;
}
}

void printInfo(node *head){
	node *current;
	head = readFile(&head);
	current = head;
	char mName[30];
	while (1){
		if (!current){
			printf("\n-->The list is emtpy!<--\n\n");
			break;
		}
		printf("\nEnter ID of the medicine: ");
		scanf("%s", &mName);
		while (current){
			if (strcmp(mName, current->val.Number) == 0){
				printf("\nMedicine:%s\nNumber:%s\nPrice:%.2lf\nRegistration date:%d.%d.%d\n", current->val.name, current->val.Number, current->val.price, current->val.date, current->val.month, current->val.year);
			}
			current = current->next;
		}
		break;
	}
}
