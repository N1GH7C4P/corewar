/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 22:48:41 by kpolojar          #+#    #+#             */
/*   Updated: 2022/11/08 00:47:27 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSEMBLER_H
# define ASSEMBLER_H

# include "../libft/libft.h"
# include "./op.h"
# include <unistd.h>
# include <stdio.h>
// open
 #include <fcntl.h>

# define MAX_TOKENS	100
# define MAX_LINES 1000

typedef struct s_asm
{
	t_op	op_tab[17];
} t_asm;

// type codes
// 1 : name
// 2 : comment


typedef struct			s_token
{
	char 	*content;
	int		type_code;
} t_token;

// Assembler
t_asm *new_asm(void);

// Parser
int	parse_inputs(char **input, t_token **t, t_asm *a);
int	handle_quote(char *src, t_token **tokens, int token_type, int nb_of_tokens);
int	handle_instruction(t_asm *a, char *input, t_token **tokens, int nb_of_tokens);
int	handle_separator(char *input, t_token **tokens, int nb_of_tokens);

//Token
t_token	*create_token(int type_code, char *content);

// Utils
void	exit_program(int ret, char *msg);

int		get_id_by_name(char *name, t_asm *a);
void	set_asm_op_tab(t_asm *a);

#endif