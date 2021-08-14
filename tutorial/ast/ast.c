#include <list.h>
#include <strbuf.h>
#include <ft_memory.h>
#include <ft_string.h>
#include <ft_error.h>
#include <ft_bool.h>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct	s_token
{
	int		type;
	char	data;
} t_token;

typedef struct	s_word
{
	int		variable;
	char	*str;
} t_word;

typedef struct	s_command
{
	int		type;
	t_list	args;
	t_word	*name;
} t_command;

typedef struct	s_job
{
	t_command		*cmd;
	struct s_job	*pipe_job;
} t_job;

typedef struct	s_parser
{
	t_list	*list;
	t_elem	*cur;
} t_parser;


enum e_token
{
	Token_Unknown,
	Token_Character,
	Token_Bar,
	Token_Greater,
	// Lesser <
	Token_Dollar,
	Token_Whitespace
	// Quote '
	// DoubleQuote "
};

enum e_commandtype
{
	Command_Normal,
	Command_Write
	// Append (>>)
	// Read (<)
	// ReadDelim (<<) (주의: 이 경우, 뒤 EOF 문구는 변수 Expand 되지 않음.)
};

static void	add_token(t_list *list, int type, char dat)
{
	t_token	*tkn = malloc(sizeof(t_token));
	tkn->type = type;
	tkn->data = dat;
	list_add(list, tkn, &free);
}

static void skip_whitespaces(t_parser *parser)
{
	t_token		*token;

	while (parser->cur != NULL)
	{
		token = parser->cur->data;
		if (token->type != Token_Whitespace)
			break ;
		parser->cur = parser->cur->next;
	}
}

static t_word	*get_word(t_parser *parser)
{
	t_word		*word;
	t_strbuf	strbuf;
	t_token		*token;
	int			is_variable;

	is_variable = -1;
	ft_memset(&strbuf, 0, sizeof(t_strbuf));

	// 맨 앞에 나오는 공백은 모두 건너뛰기 (ltrim 과 동일)
	skip_whitespaces(parser);

	// 토큰을 다 읽었을 경우 끝냄.
	while (parser->cur != NULL)
	{
		token = parser->cur->data;

		// 문자 또는 $가 아닐 경우 반복문 중단.
		if (token->type != Token_Character && token->type != Token_Dollar)
			break ;

		// 맨 처음 나오는 토큰이 $인지, 일반 단어인지 결정.
		if (is_variable == -1)
		{
			is_variable = (token->type == Token_Dollar);
			if (is_variable)
				parser->cur = parser->cur->next;
			continue;
		}

		// 나오는 문자들을 버퍼에 쌓음.
		if (is_variable)
		{
			// a-zA-Z0-9_ 이외는 변수 명으로 부적절.
			if (ft_isalnum(token->data) || token->data == '_')
				strbuf_append(&strbuf, token->data);
			else
				break ;
		}
		else
		{
			strbuf_append(&strbuf, token->data);
		}
		parser->cur = parser->cur->next;
	}

	// 버퍼에 쌓인 문자들이 없다면 NULL을 반환.
	if (strbuf_length(&strbuf) == 0)
		return (NULL);

	// t_word 구조체를 만들어서 반환.
	word = malloc(sizeof(t_word));
	ft_memset(word, 0, sizeof(t_word));
	word->variable = is_variable;
	word->str = strbuf_get(&strbuf, TRUE);
	return word;
}

static void		free_word(void *ptr)
{
	t_word		*word;

	word = (t_word *)ptr;
	free(word->str);
	free(word);
}

static int		is_acceptable(t_elem *elem, int type)
{
	t_token		*token;

	if (elem == NULL)
		return 0;
	token = (t_token *)elem->data;
	return token->type == type;
}

static t_command	*next_command(t_parser *parser)
{
	t_command	*ret;
	t_word		*word;

	ret = malloc(sizeof(t_command));
	ft_memset(ret, 0, sizeof(t_command));
	ret->type = Command_Normal;
	while (parser->cur != NULL)
	{
		// 다음 word를 읽어옴.
		word = get_word(parser);

		// word를 읽어올 수 없었다면, 반복문을 종료.
		if (word == NULL)
			break;

		// 읽어온 word가 있다면, words의 args 연결리스트에 읽어온 word를 추가.
		list_add(&ret->args, word, &free_word);
	}

	// 누적된 읽어온 word가 하나도 없다면, t_command를 free하고 NULL 리턴. (에러)
	if (ret->args.length == 0)
	{
		free(ret);
		return NULL;
	}

	// 공백을 모두 건너뜀
	skip_whitespaces(parser);

	// > 가 나오면, word를 하나 읽어, 작성될 파일 이름으로 지정함.
	if (is_acceptable(parser->cur, Token_Greater))
	{
		parser->cur = parser->cur->next;
		ret->type = Command_Write;
		ret->name = get_word(parser);
		// 파일 이름에 해당될 word를 읽어온 것이 없다면, t_command를 free하고 NULL 리턴. (에러)
		if (ret->name == NULL)
		{
			free(ret);
			return NULL;
		}
	}

	return ret;
}

static t_job	*next_job(t_parser *parser)
{
	t_job		*ret;
	t_command	*cmd;

	// Command를 하나 읽어옴.
	cmd = next_command(parser);

	// 읽어올 수 없었다면, NULL을 반환.
	if (cmd == NULL)
		return NULL;

	// 모든 공백 건너뛰기
	skip_whitespaces(parser);

	// 초기화
	ret = malloc(sizeof(t_job));
	ret->cmd = cmd;
	ret->pipe_job = NULL;

	// | 가 나오면, | 이후의 t_job을 하나 읽어옴. (재귀 구문 분석)
	if (is_acceptable(parser->cur, Token_Bar))
	{
		parser->cur = parser->cur->next;
		ret->pipe_job = next_job(parser);

		// | 가 있었음에도, job 읽기 실패시 NULL 반환.
		if (ret->pipe_job == NULL)
			return NULL;
	}
	return ret;
}

static void print_ast(t_job *job)
{
	t_elem	*cur;
	t_word	*word;

	cur = job->cmd->args.head;
	printf("[ ");
	printf("(");
	while (cur != NULL)
	{
		word = cur->data;
		printf(" ");
		if (word->variable)
			printf("$");
		printf("%s", word->str);
		cur = cur->next;
	}
	if (job->cmd->type == Command_Write)
	{
		printf(" > ");
		if (job->cmd->name->variable)
			printf("$");
		printf("%s", job->cmd->name->str);
	}
	printf(" )");
	if (job->pipe_job != NULL)
	{
		printf(" | ");
		print_ast(job->pipe_job);
	}
	printf(" ]");
}

static void process_line(char *input)
{
	t_list	tokens;

	ft_memset(&tokens, 0, sizeof(t_list));

	// [[INPUT]]
	//  echo hello | $abc > smile.log
	//
	// --------------------------------------------------------------------
	//   Parsing Tokens
	// --------------------------------------------------------------------
	//
	//  e,c,h,o, ,h,e,l,l,o, ,|, ,$,a,b,c, ,>, ,s,m,i,l,e,.,l,o,g
	//
	//const char	*input = "echo hello | $abc > smile.log";
	int			i = 0;

	while (input[i] != '\0')
	{
		if (input[i] == '|')
			add_token(&tokens, Token_Bar, input[i]);
		else if (input[i] == '>')
			add_token(&tokens, Token_Greater, input[i]);
		else if (input[i] == '$')
			add_token(&tokens, Token_Dollar, input[i]);
		else if (input[i] == ' ' || input[i] == '\t')
			add_token(&tokens, Token_Whitespace, input[i]);
		else
			add_token(&tokens, Token_Character, input[i]);
		i++;
	}

	// --------------------------------------------------------------------
	//   Parsing AST
	// --------------------------------------------------------------------
	//
	// W: 표시는 word의 리스트를 의미함.
	// w: 표시는 word 단독 구조체를 의미함.
	// [] 표시는 문자열 배열(또는 리스트)을 의미함.
	//
	//  Word:     char*                          (String)
	//            $ + char*                      (Variable)
	//
	//  Command:  t_word, t_word, ...            (Command_Normal)
	//            t_word, t_word, ... > t_word   (Command_Write)
	//            t_word, t_word, ... < t_word   (Command_Read)
	//            t_word, t_word, ... >> t_word  (Command_Append)
	//            t_word, t_word, ... << char*   (Command_ReadDelim)
	//
	//  Job:      t_command                      (Job_Normal)
	//            t_command | t_job              (Job_Pipe)
	//
	//             Job(Pipe)
	//            /         \
	//           /           \
	//          /             \
	//  Command(Normal)       Job(Normal)
	//       |                    |
	//       |                    |
	//W:[echo,hello,]       Command(Write)
	//                      /            \
	//                     /              \
	//                    /                \
	//                Command            w:smile.log
	//                   |
	//                W:[$abc,]

	t_parser	parser;

	parser.list = &tokens;
	parser.cur = tokens.head;

	t_job	*job = next_job(&parser);
	if (job != NULL)
		print_ast(job);
	else
		printf("syntax parse error");
	printf("\n");
	list_free(&tokens);
	//TODO free ast
}

int main(void)
{
	char *input;

	while (TRUE)
	{
		input = readline("AST$ ");
		if (input == NULL)
			break;
		process_line(input);
		add_history(input);
		free(input);
	}
	return 0;
}