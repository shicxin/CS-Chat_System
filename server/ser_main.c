#include<stdio.h>
#include"init.h"
#include"user.h"

int main(int argc, char** argv)
{
	bool* ID_linked_list;
	HEAD head;
	init_file();
	init_sys(&head);
	add_user(&head);
	return 0;
}