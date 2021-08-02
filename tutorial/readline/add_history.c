#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
	while (1)
	{
		// add_history 함수를 호출하면 readline을 할 때, 실제 셸 처럼 방향키로 추가된 history를 읽어낼 수 있음.
		char *str = readline("$> ");
		printf("str = %s\n", str);
		if (str && strlen(str) > 0) // TODO: 공백만으로 이루어진 문자열은 add_history 처리 하면 안됨.
			add_history(str);
		free(str);
	}
	return 0;
}
