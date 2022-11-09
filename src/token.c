/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:59:07 by kpolojar          #+#    #+#             */
/*   Updated: 2022/11/09 02:37:55 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/assembler.h"

// TYPE-CODES;
// 0: name
// 1: comment
// 2: instruction
// 3: register
// 4: separator
// 5: label
// 6: direct
// 7: direct label

static char g_token_tab[9][14] = 
{
	{"name"}, {"comment"}, {"instruction"}, {"register"}, {"separator"}, {"label"}, {"direct"}, {"direct_label"}
};

void	set_asm_token_tab(t_asm *a)
{
	int i;

	i = 0;
	while(i < 8)
	{
		a->token_tab[i] = g_token_tab[i];
		i++;
	}
}

t_token	*create_token(int type_code, char *content)
{
	ft_putstr("creating token: |");
	ft_putstr(content);
	ft_putstr("| (");
	ft_putnbr(type_code);
	ft_putendl(")");
	t_token	*t;
	t = (t_token *)malloc(sizeof(t_token));
	t->type_code = type_code;
	t->content = ft_strdup(content);
	//ft_putendl("token created");
	return (t);
}

void	print_token(t_token *t, t_asm *a)
{
	ft_putstr(a->token_tab[t->type_code]);
	ft_putstr(": |");
	ft_putstr(t->content);
	ft_putchar('|');
}

void	print_tokens(t_asm *a)
{
	int i;

	ft_putendl("printing tokens");
	i = 0;
	while (a->tokens[i] && i < a->nb_of_tokens)
	{
		print_token(a->tokens[i], a);
		ft_putendl("");
		i++;
	}
}