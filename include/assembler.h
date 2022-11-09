/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 22:48:41 by kpolojar          #+#    #+#             */
/*   Updated: 2022/11/09 02:37:29 by kpolojar         ###   ########.fr       */
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

// TYPE-CODES;
// 0: name
// 1: comment
// 2: instruction
// 3: register
// 4: separator
// 5: label
// 6: direct
// 7: direct label

typedef struct			s_token
{
	char 	*content;
	int		type_code;
} t_token;

typedef struct s_asm
{
	t_op	op_tab[17];
	char	*token_tab[8];
	t_token	**tokens;
	int		nb_of_tokens;
} t_asm;

// Assembler
t_asm	*new_asm(void);
void	set_asm_token_tab(t_asm *a);

// Parser
int	parse_inputs(char **input, t_asm *a);

//Token
t_token	*create_token(int type_code, char *content);
void	print_token(t_token *t, t_asm *a);
void	print_tokens(t_asm *a);

// Utils
void	exit_program(int ret, char *msg);

int		get_id_by_name(char *name, t_asm *a);
void	set_asm_op_tab(t_asm *a);

#endif