'''
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

char data[37] = "abcdefghijklmnopqrstuvwxyz0123456789";
char *goalPass = "$1$AAODv...$gXPqGkIO3Cu6dnclE";
char mypwd[10];
int minlen = 1; //min password length
int maxlen = 3; //max password length

void subgenerate(int index, int pwdlen){
	if (index == pwdlen)
		return;
	int i;
	for (i = 0; i < 36; i++){
		mypwd[index] = data[i];
		memset(mypwd + index + 1, data[0], pwdlen - index - 1);
		if (i != 0)	{
			//printf("%s      ",mypwd);
			if(!strcmp(goalPass,crypt(mypwd,"$1$AAODv...$"))){
				printf("find password:%s", mypwd);
				exit(0);
			}
		}
		subgenerate(index + 1, pwdlen);
	}
}

void generate(int pwdlen, int start,int end)
{
	int i;
	for (i=start;i<end; i++){ // 多线程可分段
		mypwd[0] = data[i];
		memset(mypwd + 1, data[0], pwdlen - 1); //填充长度
		//printf("%s      ",mypwd);
		if(!strcmp(goalPass,crypt(mypwd,"$1$AAODv...$"))){
			printf("find password:%s", mypwd);
			exit(0);
		}
		subgenerate(1,pwdlen);
	}
}


int main(){
	char mypwd[10];
	if (maxlen > 9) puts("max password length must little then 9");
	int i,threadnum= 10;
	for (i = minlen; i <= maxlen; i++)
	{
		printf("/npassword length:%d/n",i);
		//password length
		memset(mypwd, 0, 10);
		generate(i, 0, 36); //留作多线程
	}
	puts("password not found");
	return 0;
}
'''
import crypt
import threading

def check_passwd(info, passwd):
    """
    info: one user's information in /etc/shadow
    passwd: the passwd you want to check
    """
    user = info.split(':')[0].strip('')
    code = info.split(':')[1].strip('')
    salt = code[:code.rfind('$')]
    new_code = crypt.crypt(passwd, salt)

    if new_code == code:
        print("The password of " + user + " is " + passwd + ".")

def main():
    info = "hugo:$6$TAri.obg$xWVUeKQBgfSy5Zro0go.mdqih5.6LA4v/H6ONWMbZcq.v4KTVQJ/oy7ATh.hVDvRVP.D6T/J66NQAILIVzbE4/:17596:0:99999:7:::"
    passFile = open("passwords.txt", 'r')
    for line in passFile.readlines():
        passwd = line.strip('\n')
        t = threading.Thread(target=check_passwd, args=(info, passwd))
        t.start()

if __name__ == '__main__':
    main()
