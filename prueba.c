#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/limits.h>

int     main(int argc, char **argv, char **envp)
{
    char    *str[2];
    int     ret;
    int	    fd;

    str[0] = "../../minishell";
    str[1] = NULL;

    ret = access(str[0], F_OK);
	if (ret == 0)
        printf("existo [%s]\n", str[0]);
    else
        printf("NOexisto [%s]\n", str[0]);
    fd = open(str[0], O_RDONLY);
    if (fd < 0)
    {
	    printf("NO abro [%s]\n", str[0]);
    }
    else
        printf("abro [%s]\n", str[0]);

    chdir("/");
	char    path_pwd[PATH_MAX];

	getcwd(path_pwd, PATH_MAX);
    printf("chdir [%s]\n", path_pwd);

    // execve(str[0], str, envp);
    return (0);
}
