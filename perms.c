#include <stdio.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdlib.h>
#include <grp.h>

int main(int argc, char const *argv[])
{
	__uid_t my_uid = getuid();

	struct passwd * ps = getpwuid(my_uid);

	if(ps == NULL)
	{
		printf("getpwuid() error !");
		exit(1);
	}

	int ngroups;


	getgrouplist(ps->pw_name, ps->pw_gid, NULL, &ngroups);
	printf("The number of groups is %d \n", ngroups);

	__gid_t groups[ngroups];

	int i=0;
	
	getgrouplist(ps->pw_name, ps->pw_gid, groups, &ngroups);

	
	char * gr;


	printf("The secondary groups are : \n");

	for(; i<ngroups; i++)
	{
		struct group* grps;
		grps = getgrgid(groups[i]);
		if(!grps)
		{
			printf("getgrgid() error ! ");
			exit(1);
		}
		gr = grps->gr_name;
		printf("%s \n", gr);
	}



	printf("%d is the real user ID\n", getuid());
	printf("%d is the real group ID\n", getgid());

 
	char *logged_user;
	logged_user = NULL;
	logged_user = (char *)malloc(10);

	if(!logged_user){
		printf("malloc() error !");
		exit(1);
	}

	getlogin_r(logged_user, 10);

	printf("%d is The Effective user ID\n", geteuid());
	printf("%d is the Effective group ID\n", getegid());


	if(logged_user != NULL)
		printf("%s is the login UID\n", logged_user);
	else
		printf("NO LOGGED USED !\n");
	return 0;
}
