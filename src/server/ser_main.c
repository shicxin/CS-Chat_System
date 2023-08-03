#include<stdio.h>
#include"../lib/init.h"
#include"../lib/user.h"

int main(int argc, char** argv)
{
	bool* ID_linked_list;
	HEAD head;
	init_ser_file();
	init_ser_sys(&head);
	add_user(&head);
	return 0;
}