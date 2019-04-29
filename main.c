#include<stdio.h>
#include<string.h>

struct POWER{
	char _read : 1,
		_exe : 1,
		_change : 1,
		_del : 1,
		_new : 1,
		_other_1 : 1,
		_other_2 : 1,
		_other_3 : 1;
};

void operator1(struct POWER* t, const struct POWER temp) {
	t->_read = temp._read;
	t->_change = temp._change;
	t->_exe = temp._exe;
	t->_del = temp._del;
	t->_new = temp._new;
	t->_other_1 = temp._other_1;
	t->_other_2 = temp._other_2;
	t->_other_3 = temp._other_3;
}

struct ROLE{
	char r_name[10];
	unsigned int short r_id;
	struct POWER r_power;
};

void operator2(struct ROLE* t,const struct ROLE temp){
                t->r_id = temp.r_id;
                int i =0 ;
                while(i<10){
                        t->r_name[i]=temp.r_name[i];
                        i++;
                }
                operator1(&(t->r_power),temp.r_power);
        };


struct ROLE W1 = {
	.r_name = "Work_A_B",
	.r_id = 0,
	.r_power = {
		._read = 1,
		._exe = 1,
		._change = 0,
		._del = 0,
		._new = 0,
		._other_1 = 0,
		._other_2 = 0,
		._other_3 = 0
	}
};

struct ROLE W2 = {
        .r_name = "work_C_D",
        .r_id = 1,
        .r_power = {
                ._read = 1,
                ._exe = 0,
                ._change = 1,
                ._del = 0,
                ._new = 1,
                ._other_1 = 0,
                ._other_2 = 0,
                ._other_3 = 0
        }
};

struct ROLE M1 = {
        .r_name = "M1",
        .r_id = 2,
        .r_power = {
                ._read = 1,
                ._exe = 1,
                ._change = 0,
                ._del = 1,
                ._new = 0,
                ._other_1 = 0,
                ._other_2 = 0,
                ._other_3 = 0
        }
};

struct ROLE M2 = {
        .r_name = "M2",
        .r_id = 3,
        .r_power = {
                ._read = 1,
                ._exe = 0,
                ._change = 1,
                ._del = 1,
                ._new = 1,
                ._other_1 = 0,
                ._other_2 = 0,
                ._other_3 = 0
        }
};

struct ROLE BOSS = {
        .r_name = "BOSS",
        .r_id = 4,
        .r_power = {
                ._read = 1,
                ._exe = 1,
                ._change = 1,
                ._del = 1,
                ._new = 1,
                ._other_1 = 1,
                ._other_2 = 1,
                ._other_3 = 1
        }
};

struct object{
	char o_name[8];
	unsigned int short o_id;
	char o_accout[8];
	char o_passwd[8];
	struct ROLE o_role;
};

struct object object_list[100];
unsigned int short object_number = 0;

void create_object(int id) {
	printf("please input the name\n");
	scanf("%s", object_list[object_number].o_name);
	printf("Please input the account\n");
	scanf("%s", object_list[object_number].o_accout);
	object_list[object_number].o_id = object_number;
	object_list[object_number].o_passwd[0]='0';
	object_number++;
}


int main(){
	char resource_name[] = "data.txt";
	char command[8];
	char passwd[8];
	printf("******************************************\n");
	printf("*             WELCOME HERE               *\n");
	printf("******************************************\n");
	printf("------------------------------------------\n");
	printf("-----YOU ARE A MANAGER OF THIS SYSTEM-----\n");
	printf("------YOU ARE A BOSS OF THIS COMPANY------\n");
	printf("------------------------------------------\n\n");
	printf("First,You need a account \n\n");
	create_object(0);
	operator2(&(object_list[0].o_role), BOSS);
	int j = 0;
	while (1) {
		printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
		printf("^^^^^^^^^^WELCOME INTO SYSTEM^^^^^^^^^^^^^\n");
		printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n");
		printf("You need to LOGIN\n\n");
		printf("Account:");
		scanf("%s", command);
		printf("Password(default 0):");
		scanf("%s", passwd);
		for (j = 0; j < object_number; j++) {
			if (strcmp(object_list[j].o_accout, command) == 0) {
				if (strcmp(object_list[j].o_passwd, passwd) == 0) {
					printf("Login success!!!\n");
					while (1) {
						printf("\nPlease choose your work:\n0:modify the password\n1:add the workers\n2:read the resource\n3:execute the resource\n4:new the resource\n5:delete the resource \n6:change the resource \n8:exit\n");
						fflush(stdin); 
						scanf("%c", command);
						if (command[0] == '8') {
							break;
						}
						switch (command[0]) {
						case '0':
							printf("NEW PASSWORD:");
							scanf("%s", passwd);
							strcpy(object_list[j].o_passwd, passwd);
							break;
						case '1':
							while (1) {
								printf("\n0:Work_A_B\n1:Work_C_D\n2:M1\n3:M2\n4:BOSS\n5:exit\nYOUR CHOOSE:");
								fflush(stdin); 
								scanf("%c", command);
								if (command[0] == '5')
									break;
								switch (command[0]) {
								case '0':
									printf("%d\n",object_list[j].o_role.r_id) ;
									if (object_list[j].o_role.r_id != 2 && object_list[j].o_role.r_id != 4) {
										printf("You are not permitted\n");
										break;
									}
									create_object(0);
									operator2(&(object_list[object_number - 1].o_role), W1);
									break;
								case '1':
									if (object_list[j].o_role.r_id != 3 && object_list[j].o_role.r_id != 4) {
										printf("You are not permitted\n");
										break;
									}
									create_object(0);
									operator2(&(object_list[object_number - 1].o_role), W2);
									break;
								case '2':
									if (object_list[j].o_role.r_id != 4) {
										printf("You are not permitted\n");
										break;
									}
									create_object(0);
									operator2(&(object_list[object_number - 1].o_role), M1);
									break;
								case '3':
									if (object_list[j].o_role.r_id != 4) {
										printf("You are not permitted\n");
										break;
									}
									create_object(0);
									operator2(&(object_list[object_number - 1].o_role), M2);
									break;
								case '4':
									if (object_list[j].o_role.r_id != 4) {
										printf("You are not permitted\n");
										break;
									}
									create_object(0);
									operator2(&(object_list[object_number - 1].o_role), BOSS);
									break;
								default:
									break;
								}
							}
							break;
						case '2':
							if (object_list[j].o_role.r_power._read == 0) {
								printf("You are not permitted!\n");
								break;
							}
							printf("OK\n");
							break;
						case '3':
							if (object_list[j].o_role.r_power._exe == 0) {
								printf("You are not permitted!\n");
								break;
							}
							printf("OK\n");
							break;
						case '4':
							if (object_list[j].o_role.r_power._new == 0) {
								printf("You are not permitted!\n");
								break;
							}
							printf("OK\n");
							break;
						case '5':
							if (object_list[j].o_role.r_power._del == 0) {
								printf("You are not permitted!\n");
								break;
							}
							printf("OK\n");
							break;
						case '6':
							if (object_list[j].o_role.r_power._change == 0) {
								printf("You are not permitted!\n");
								break;
							}
							printf("OK\n");
							break;
						case '7':
							if (object_list[j].o_role.r_power._other_1 == 0) {
								printf("You are not permitted!\n");
								break;
							}
							printf("OK\n");
							break;
						default:
							break;
						}
					}
					break;
				}
				printf("passwd error!\n");
				break;
			}
		}
		
	}
}

