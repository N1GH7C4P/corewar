/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 19:06:30 by kpolojar          #+#    #+#             */
/*   Updated: 2022/11/08 01:20:50 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/assembler.h"

int	handle_direct_label(char *input, t_token **tokens, int nb_of_tokens)
{
	int		i;
	char	*label;

	if (input[0] == DIRECT_CHAR)
	{
		if (input[1] == LABEL_CHAR)
		{
			i = 0;
			while (ft_strchr(LABEL_CHARS, input[i]))
				i++;
			label = ft_strsub(input, 0, i + 2);
			tokens[nb_of_tokens++] = create_token(7, label);
			return (i + 2);	
		}
	}
	return (0);
}

int handle_direct(char *input, t_token **tokens, int nb_of_tokens)
{
	int		i;
	char	*label;

	i = 0;
	while (ft_strchr(LABEL_CHARS, input[i]))
	{
		if (input[i + 1] == DIRECT_CHAR)
		{
			label = ft_strsub(input, 0, i + 1);
			tokens[nb_of_tokens++] = create_token(6, label);
			return (i + 1);	
		}
		i++;
	}
	return (0);
}

int handle_label(char *input, t_token **tokens, int nb_of_tokens)
{
	int i;
	char *label;

	i = 0;
	while (ft_strchr(LABEL_CHARS, input[i]))
	{
		if (input[i + 1] == LABEL_CHAR)
		{
			label = ft_strsub(input, 0, i);
			tokens[nb_of_tokens++] = create_token(5, label);
			return (i + 1);	
		}
		i++;
	}
	return (0);
}

int	handle_separator(char *input, t_token **tokens, int nb_of_tokens)
{
	if (input[0] == SEPARATOR_CHAR)
	{
		tokens[nb_of_tokens++] = create_token(4, "SEPARATOR");
		return(1);
	}
	return (0);
}

int handle_register(char *input, t_token **tokens, int nb_of_tokens)
{
	int i;
	int r;

	i = 0;
	if (input[i] == 'r' && ft_isdigit(input[i + 1]))
	{
		r = ft_atoi(input + i + 1);
		if (r > 16 || r < 0)
			exit_program(-1, "Invalid register index!");
		if (r < 10)
		{
			tokens[nb_of_tokens++] = create_token(3, ft_strsub(input, 0, 3));
			return (3);
		}
		else
		{
			tokens[nb_of_tokens++] = create_token(3, ft_strsub(input, 0, 2));
			return (2);
		}
	}
	return (0);
}

int	handle_instruction(t_asm *a, char *input, t_token **tokens, int nb_of_tokens)
{
	int i;
	int	l;

	i = 0;
	while (i < 17)
	{
		l = ft_strlen(a->op_tab[i].name);
		if (!ft_strncmp(input, a->op_tab[i].name, l))
		{	
			tokens[nb_of_tokens++] = create_token(3, ft_strsub(input, 0, l));
			return (l);
		}
		i++;
	}
	return (0);
}

int handle_quote(char *src, t_token **tokens, int token_type, int nb_of_tokens)
{
	int		i;
	int		n;
	char	*dest;

	ft_putendl("Handling quote");
	i = 0;
	while (ft_iswhitespace(src[i]))
		i++;
	ft_putstr("char: |");
	ft_putchar(src[i]);
	ft_putendl("|");
	if (src[i++] != '\"')
		exit_program(-1, "invalid input string(1)");
	n = ft_strchr(src + i, '\"') - src;
	if (!n)
		exit_program(-1, "invalid input string(2)");
	dest = ft_strnew(n);
	ft_memcpy(dest, src + i - 1, n + 1);
	ft_putendl(dest);
	tokens[nb_of_tokens++] = create_token(token_type, dest);
	ft_putstr("chars: " );
	ft_putnbr(i + n + 1);
	ft_putendl("");
	return (i + n + 1);
}

int	parse_inputs(char **input, t_token **t, t_asm *a)
{
	static int		nb_of_tokens;
	int				i;
	int				l;

	l = 0;
	while (input[l])
	{
		ft_putstr("line: ");
		ft_putendl(input[l]);
		i = 0;
		while (input[l][i])
		{
			if (input[l][i] == COMMENT_CHAR)
				break ;
			while (ft_iswhitespace(input[l][i]))
				i++;
			if (!ft_strncmp(input[l], ".name", 5))
				i += handle_quote(input[l] + 5, t, 1, nb_of_tokens) + 5;
			else if (!ft_strncmp(input[l], ".comment", 8))
				i += handle_quote(input[l] + 8, t, 2, nb_of_tokens) + 8;
			i += handle_instruction(a, input[l], t, nb_of_tokens);
			i += handle_register(input[l], t, nb_of_tokens);
			i += handle_label(input[l], t, nb_of_tokens);
			i += handle_direct(input[l], t, nb_of_tokens);
			i += handle_direct_label(input[l], t, nb_of_tokens);
			i++;
		}
		l++;
	}
	return (0);
}
