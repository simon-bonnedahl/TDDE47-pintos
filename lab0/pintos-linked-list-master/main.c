#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
	char *name;
	struct list_elem elem;
};

void insert (struct list *student_list) {
	//take input from user of the student name
	char *name = malloc(10);

	printf("Enter student name:\n");
	scanf("%s", name);

	struct student *new_student = malloc(sizeof(struct student));
	new_student->name = name;
	//insert the student in the list
	list_push_back(student_list, &new_student->elem);

}

void delete (struct list *student_list) {
	printf("Enter student name:\n");
	char *name = malloc(10);
	scanf("%s", name);
	struct list_elem *e;
	struct student *s;
	for (e = list_begin (student_list); e != list_end (student_list); e = list_next (e)) {
		s = list_entry (e, struct student, elem);
		if (strcmp(s->name, name) == 0) {		
			list_remove(e);
			free(s);
			return;
		}
	}
	printf("Student not found\n");
}

void list (struct list *student_list) {
	struct list_elem *e;
	struct student *s;
	for (e = list_begin (student_list); e != list_end (student_list); e = list_next (e)) {
		s = list_entry (e, struct student, elem);
		printf("%s", s->name);
		printf("\n");
	}

}

void quit (struct list *student_list) {
	while(!list_empty(student_list)) {
		struct list_elem *e = list_pop_front(student_list);
		struct student *s = list_entry (e, struct student, elem);
		free(s->name);
		free(s);
	}
	exit(0);
}

int main() {
	struct list student_list;
	list_init (&student_list);
	int opt;

	do {
		printf("Menu:\n");
		printf("1 - Insert student\n");
		printf("2 - Delete student\n");
		printf("3 - List students\n");
		printf("4 - Exit\n");
		scanf("%d", &opt);
		switch (opt) {
			case 1:
				{
					insert(&student_list);
					break;
				}
			case 2:
				{
					delete(&student_list);
					break;
				}
			case 3:
				{
					list(&student_list);
					break;
				}

			case 4:
				{
					quit(&student_list);
					break;
				}
			default:
				{
					printf("Quit? (1/0):\n");
					scanf("%d", &opt);
					if (opt)
						quit(&student_list);
					break;
				}
		}
	} while(1);
		
	return 0;
}
