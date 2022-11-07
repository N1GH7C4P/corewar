#Variables

ASSEMBLER				= asm
INCLUDE					= -I include
LIBFT_LIB				= ./libft/libft.a
LIBFT					= libft
SRC_DIR					= src/
OBJ_DIR					= src/
TEST_DIR				= test/
TEST_EXE				= run_test
CC						= gcc
CFLAGS					= -Wall -Wextra -Werror -O3 # -fsanitize=address
RM						= rm -f

# Colors

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

ASSEMBLER_SRC_FILES	= assembler op parser utils token
TEST_FILES	=	*

ASSEMBLER_SRC 	= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(ASSEMBLER_SRC_FILES)))
ASSEMBLER_OBJ 	= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(ASSEMBLER_SRC_FILES)))
TEST 			= 	$(addprefix $(TEST_DIR), $(addsuffix .test.c, $(TEST_FILES)))

all:				$(ASSEMBLER)

$(ASSEMBLER)	:	$(ASSEMBLER_OBJ)
					@make -C $(LIBFT)
					${CC} $(CFLAGS) -o $(ASSEMBLER) $(ASSEMBLER_OBJ) $(LIBFT_LIB) $(INCLUDE)
					@echo "$(GREEN)lem-in compiled!$(DEF_COLOR)"


clean:
					@$(RM) -rf $(ASSEMBLER_OBJ)
					@echo "$(BLUE) lem-in object files cleaned!$(DEF_COLOR)"
					@make clean -C $(LIBFT)
					@echo "$(BLUE)libft object files cleaned!$(DEF_COLOR)"

fclean:				clean
					@$(RM) -f $(ASSEMBLER)
					@echo "$(CYAN)lem-in binary files cleaned!$(DEF_COLOR)"
					@make clean -C $(LIBFT)
					@echo "$(CYAN)libft binary files cleaned!$(DEF_COLOR)"

re:					fclean all
					@echo "$(GREEN)Rebuilt all!$(DEF_COLOR)"
			
.PHONY:				all clean fclean re