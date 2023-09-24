Name	=	minishell

EXE_P = executer

EXE_LIBF = executer/libft

SRC_EXE_LIBFT = $(EXE_LIBF)/ft_strcmp.c $(EXE_LIBF)/ft_putchar_fd.c $(EXE_LIBF)/ft_putstr_fd.c $(EXE_LIBF)/ft_putendl_fd.c $(EXE_LIBF)/ft_memcpy.c \
			$(EXE_LIBF)/ft_memset.c $(EXE_LIBF)/ft_strdup.c $(EXE_LIBF)/ft_strchr.c $(EXE_LIBF)/ft_isalpha.c \
			$(EXE_LIBF)/ft_isdigit.c $(EXE_LIBF)/ft_atoi.c $(EXE_LIBF)/ft_itoa.c $(EXE_LIBF)/ft_substr.c $(EXE_LIBF)/ft_strncmp.c

SRC_EXECUTER = $(EXE_P)/executer_utils.c $(EXE_P)/executer_utils2.c $(EXE_P)/ft_execute.c $(EXE_P)/ft_utils.c $(EXE_P)/builtins_utils.c $(EXE_P)/ft_builtins.c $(EXE_P)/ft_echo.c  $(EXE_P)/ft_cd.c $(EXE_P)/ft_pwd.c $(EXE_P)/ft_export.c \
			$(EXE_P)/ft_unset.c $(EXE_P)/ft_env.c $(EXE_P)/ft_exit.c $(EXE_P)/mr_clean.c $(EXE_P)/executer_utils3.c

SRCS	=	main.c main2.c ft_split.c ft_strlen.c ft_strtrim.c ft_strjoin.c utils.c utils/utils1.c utils/utils2.c utils/utils3.c utils/utils4.c utils/utils5.c utils/utils6.c utils/utils7.c\
			utils/utils8.c utils/expand_utils.c utils/expand_utils2.c utils/herdoc_utils.c utils/quotes_utils.c utils/tokens_utils.c utils/tokens_utils2.c \
			utils/tokens_utils3.c utils/tokens_utils4.c utils/tokens_utils5.c utils/cleaning.c $(SRC_EXE_LIBFT) $(SRC_EXECUTER) ft_signals.c

OBJS	=	$(SRCS:.c=.o)

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror
#-fsanitize=address

# PATH	= /goinfre/efarhat/.brew/opt/readline
PATH	= $(shell brew --prefix readline)

all:		$(Name)

# $(Name):	$(OBJS)
# 			$(CC) $(CFLAGS) -lreadline $(OBJS) -o $(Name)

$(Name):	$(OBJS)
			$(CC) $(CFLAGS) -lreadline -L $(PATH)/lib $(OBJS) -o $(Name)

# %.o : %.c minishell.h
# 	$(CC) $(CFLAGS) -c $< -o $@

%.o : %.c minishell.h
	$(CC) $(CFLAGS) -I $(PATH)/include -c $< -o $@


clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(Name)

re:			fclean all
