#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct llist {
	char *value;
	struct llist *next;
};

char cislo[100];
int num=-1;

int compare(struct llist *one, struct llist *two)
{
	return strcmp(one->value, two->value);
}

void add(struct llist **pp, char *value, int(*cmp)(struct llist *l, struct llist *r)) {
	int i = 0,j = 0,k=0,m=0;
	char val[1000];
	int l = strlen(value),bol=0;
	for (i = 0; i <= l; i++)
	{
		if (i > 0 && val[j-1] > 0) bol = 1;
		if (value[i] == ' ' && bol==0)
		{
			continue;
		}
		else if (value[i] > 47 && value[i] < 58 && bol == 0)
		{
			k = i;
			while (value[k] >= 0)
			{
				cislo[m++] = value[k++];
			}
			num = atoi(cislo);
			break;
		}else
		{
			val[j++] = value[i];
		}
	}

	struct llist *new;
	new = malloc(sizeof(*new));
	new->value = _strdup(val);
	l = strlen(val);
	new->value[l-1] = 0;

	for (; *pp != NULL; pp = &(*pp)->next) {
		if (cmp(*pp, new) > 0) break;
	}

	new->next = *pp;
	*pp = new;
}

void display(struct llist *ptr) {
	int i;
	for (i = 0; ptr != NULL || i==num; ptr = ptr->next)
	{
		if (i == num)
		{
			printf("%s\n", ptr->value);
			break;
		}
		if (ptr->next == NULL)
		{
			printf("Vstup neobsahuje prvok %d", num);
			break;
		}
		i++;
	}
}

int main(void) {
	struct llist *root = NULL;
	int i = 0, bol = 0;
	char buff[1000],buff2[1000], c;
	while ((fgets(buff, 1000, stdin)) != NULL)
	{
		add(&root, &buff, compare);
		if (num >= 0) break;
	}

	display(root);
	while (scanf("%d", &num) == 1)
	{
		display(root);
	}


	return 0;
}