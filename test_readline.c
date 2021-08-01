#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

int main(void)
{
	while (1)
	{
		// 입력 받은 문자열을 prompt로 하여서 한 줄씩 입력을 받음.
		//   (입력을 받을 때, 왼쪽으로 이동하는 키 입력 및 글자 중간에 삽입 등은 모두 라이브러리가 해줌.)
		char *str = readline("$> ");
		printf("str = %s\n", str);
		free(str);
	}
	return 0;
}
