/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 19:06:30 by kpolojar          #+#    #+#             */
/*   Updated: 2022/11/09 02:44:18 by kpolojar         ###   ########.fr       */
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

static int	calculate_token_len(char *input)
{
	int i;

	i = 0;
	//ft_putendl(input);
	while (input[i])
	{
		if (ft_iswhitespace(input[i]) || input[i] == SEPARATOR_CHAR)
			break ;
		i++;
	}
	//ft_putstr("len: ");
	//ft_putnbr(i);
	//ft_putendl("");
	return (i);
}

int	handle_direct_label(char *input, t_asm *a)
{
	int		i;
	char	*label;

	if (input[0] == DIRECT_CHAR)
	{
		if (input[1] == LABEL_CHAR)
		{
			//ft_putendl("handling direct label");
			i = 2;
			//ft_putendl(input);
			while (ft_strchr(LABEL_CHARS, input[i]) || ft_iswhitespace(input[i]))
			{
				//ft_putendl(input + i);
				i++;
			}
			//ft_putstr("chars: ");
			//ft_putnbr(i);
			//ft_putendl("");
			label = ft_strsub(input, 0, i);
			a->tokens[a->nb_of_tokens++] = create_token(7, label);
			return (i);	
		}
	}
	return (0);
}

int handle_direct(char *input, t_asm *a)
{
	char	*label;
	int		len;

	if (input[0] == DIRECT_CHAR)
	{
		//ft_putendl("handling direct");
		//ft_putendl(input);
		len = calculate_token_len(input + 1) + 1;
		//ft_putstr("chars: ");
		//ft_putnbr(len);
		//ft_putendl("");
		label = ft_strsub(input, 0, len);
		a->tokens[a->nb_of_tokens++] = create_token(6, label);
		return (len);
	}
	return (0);
}

int handle_label(char *input, t_asm *a)
{
	int i;
	char *label;

	i = 0;
	while (ft_strchr(LABEL_CHARS, input[i]))
	{
		if (input[i + 1] == LABEL_CHAR)
		{
			//ft_putendl("handling label");
			label = ft_strsub(input, 0, i + 2);
			a->tokens[a->nb_of_tokens++] = create_token(5, label);
			return (i + 3);	
		}
		i++;
	}
	return (0);
}

int	handle_separator(char *input, t_asm *a)
{
	char	*separator;

	//ft_putendl(input);
	if (input[0] == SEPARATOR_CHAR)
	{
		//ft_putendl("handling separator");
		separator = ft_strnew(1);
		separator[0] = SEPARATOR_CHAR;
		a->tokens[a->nb_of_tokens++] = create_token(4, ft_strdup(separator));
		free(separator);
		return(1);
	}
	return (0);
}

int handle_register(char *input, t_asm *a)
{
	int i;
	int r;

	i = 0;
	if (input[i] == 'r' && ft_isdigit(input[i + 1]))
	{
		//ft_putendl("handling register");
		r = ft_atoi(input + i + 1);
		if (r > 16 || r < 0)
			exit_program(-1, "Invalid register index!");
		if (r < 10)
		{
			a->tokens[a->nb_of_tokens++] = create_token(3, ft_strsub(input, 0, 2));
			return (2);
		}
		else
		{
			a->tokens[a->nb_of_tokens++] = create_token(3, ft_strsub(input, 0, 3));
			return (3);
		}
	}
	return (0);
}

int	handle_instruction(t_asm *a, char *input)
{
	int i;
	int	l;

	i = 1;
	l = calculate_token_len(input);
	while (i < 17 && l > 1)
	{
		if (!ft_strcmp(ft_strsub(input, 0, l), a->op_tab[i].name))
		{	
			//ft_putendl("handling instruction");
			//ft_putendl(a->op_tab[i].name);
			//ft_putendl(input);
			a->tokens[a->nb_of_tokens++] = create_token(2, ft_strsub(input, 0, l));
			return (l);
		}
		i++;
	}
	return (0);
}

int handle_quote(char *src, int token_type, t_asm *a)
{
	int		i;
	int		n;
	char	*dest;

	//ft_putendl("Handling quote");
	i = 0;
	while (ft_iswhitespace(src[i]))
		i++;
	//ft_putstr("char: |");
	//ft_putchar(src[i]);
	//ft_putendl("|");
	if (src[i++] != '\"')
		exit_program(-1, "invalid input string(1)");
	n = ft_strchr(src + i, '\"') - src;
	if (!n)
		exit_program(-1, "invalid input string(2)");
	dest = ft_strnew(n);
	ft_memcpy(dest, src + i - 1, n + 1);
	//ft_putendl(dest);
	a->tokens[a->nb_of_tokens++] = create_token(token_type, dest);
	//ft_putstr("chars: " );
	//ft_putnbr(i + n + 1);
	//ft_putendl("");
	return (i + n + 1);
}

int	parse_inputs(char **input, t_asm *a)
{
	int				i;
	int				l;
	int				old_i;

	l = 0;
	while (input[l])
	{
		//ft_putstr("new line: ");
		//ft_putendl(input[l]);
		i = 0;
		while (input[l][i])
		{
			old_i = i;
			if (input[l][i] == COMMENT_CHAR)
				break ;
			while (ft_iswhitespace(input[l][i]))
				i++;
			if (!ft_strncmp(input[l] + i, ".name", 5))
				i += handle_quote(input[l] + i + 5, 0, a) + 5;
			else if (!ft_strncmp(input[l] + i, ".comment", 8))
				i += handle_quote(input[l] + i + 8, 1, a) + 8;
			i += handle_instruction(a, input[l] + i);
			i += handle_register(input[l] + i, a);
			i += handle_label(input[l] + i, a);
			i += handle_direct_label(input[l] + i, a);
			i += handle_direct(input[l] + i, a);
			//ft_putstr("i: ");
			//ft_putnbr(i);
			//ft_putendl("");
			i += handle_separator(input[l] + i, a);
			if (i == old_i)
				i++;
		}
		l++;
	}
	ft_free_array(input);
	print_tokens(a);
	return (0);
}
