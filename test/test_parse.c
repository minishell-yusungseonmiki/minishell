#include "../include/minishell.h"

/* TEST */
// static char	test_state[8][20] = {
// 	"START",				// 명령어의 시작
// 	"CMD",
// 	"FNAME",
// 	"PIPE",					// |
// 	"IN_REDIR",				// <
// 	"OUT_REDIR",			// >
// 	"HEREDOC",				// << limiter
// 	"PAIR_OUT_REDIR",		// >>
// };

void	leak(void)
{
	system("leaks --list minishell");
}

void	print_tokens(t_list *lst)
{
	int	cnt = 0;

	printf("\033[1;37m");
	while (lst != NULL)
	{
		printf("%d: %s\nstate: %d\n", cnt, ((t_token *)(lst->content))->elem, ((t_token *)(lst->content))->type);
		lst = lst->next;
		++cnt;
	}
	printf("\033[1;30m");
	printf("\ndivided into %d tokens\n", cnt);
	printf("\033[0m");
}

char	*testcase[100] =
{
	/* # quote */

	// "ls",																		// ls
	//"\'ls\'",																	// 'ls'
	//"\"ls\"",																	// "ls"
	//"\'l\'\'s\'",																// 'l''s'
	//"\'l\"\"s\'",																// 'l""s'
	//"\'l\'\'\'\'\'\'\'\'s\'",													// 'l''''''''s'
	//"\"l\"\"\"\"\"\"\"\"s\"",													// "l""""""s"
	//"ls -a",																	// ls -a
	//"\"ls -a\"",																// "ls -a"
	//"\"\"gre\"p\" \"a\"",														// ""gre"p" "a"
	//"\"gr\"ep\" a\"",															// "gr"ep" a"
	//"ls|grep a",																// ls|grep a
	//"ls| grep a",																// ls| grep a
	//"ls |grep a",																// ls |grep a
	//"ls | grep a",																// ls | grep a
	//"\'l\'\'\'\'\'\'s\'|grep\"\" \"a\"",										// 'l''''''s'|grep"" "a"
	//"\'ls\'|\"grep\" \"a\"",													// 'ls'|"grep" "a"
	//"\'ls\'|\"grep\" \"a\"|\"cat\"",											// 'ls'|"grep" "a"|"cat"
	//"\'ls\'|\"grep\" \"a\"|\"cat\"|\"wc\"",										// 'ls'|"grep" "a"|"cat"|"wc"
	//"\'ls\'|\"grep\" \"a\"|\"cat\"|\"wc\"|\"wc\"",								// 'ls'|"grep" "a"|"cat"|"wc"|"wc"

//	/* # redirection */
//	"> infile ls | > outfile ls",												// > infile ls | > outfile ls
//	"< infile ls | < outfile ls",												// < infile ls | < outfile ls
//
//	/* # environment variable */
//
//	"export a=1 && echo $a",				// export a=1 && echo $a
//	// result : 1
//	"export a=1 | echo $a",					// export a=1 | echo $a
//	// result : '\0'
//	// reason : export a=1는 빌트인 함수이지만 |를 만났기 때문에 자식 프로세스에서 실행되어 환경변수가 적용되지 않음
//
//	// if ABC="ab cd"
//	"cat $ABCabc",							// cat $ABC
//	// cat: ab: No such file or directory
//	// cat: cd: No such file or directory
//	"cat \"$ABC\"",							// cat "$ABC"
//	// cat: ab cd: No such file or directory
//	"cat $ABC\"efg\"",						// cat $ABC"efg" => ab cdefg
//	// cat: ab: No such file or directory
//	// cat: cdefg: No such file or directory
//	"cat \"$ABC\"efg",						// cat "$ABC"efg => ab cdefg
//	// cat: ab cdefg: No such file or directory
//
//	/* #awk */
//	"awk \'{print}\' file.txt",				// awk '{print}' file.txt
//	"awk \'BEGIN { print \"TITLE : Field value 1,2\"} {print $1, $2} END {print \"Finished\"}\' file.txt", // awk 'BEGIN { print "TITLE : Field value 1,2"} {print $1, $2} END {print "Finished"}' file.txt
	"<<<",
	"<<\'<\'",
	NULL
};

#define START 20
#define END 21

int	main(void)
{
	system("clear");
	for (size_t i = 0; testcase[i] != NULL; i++)
	{
		// if (!(START <= i && i <= END)) // if you want to test specific test case, uncomment this line
		// 	continue;
		printf("\033[1;36m");
		printf("=================================\n");
		printf("\t  Test Case #%zu\n", i);
		printf("=================================\n\n");
		printf("\033[0m");

		printf("\033[1;33m");
		printf("Input String:\n");
		printf("\033[0m");

		printf("\033[1;37m");
		printf("%s\n\n", testcase[i]);
		printf("\033[0m");

		printf("\033[1;33m");
		printf("Your Parse Function Result:\n");
		printf("\033[0m");

		tokenize(testcase[i]);
		print_tokens(tokenize(testcase[i]));			// your function
		// syntax_check(tokenize(testcase[i]));			// syntax check

		usleep(700000);
	}
	return (0);
}

// int main(int argc, char **argv)
// {
// 	printf("%s\n", argv[1]);
// 	if (argc == 2)
// 		tokenize(argv[1]);
// 	return (0);
// }
