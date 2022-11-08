/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 19:06:30 by kpolojar          #+#    #+#             */
/*   Updated: 2022/11/08 23:43:19 by kpolojar         ###   ########.fr       */
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

int	handle_direct_label(char *input, t_token **tokens, int nb_of_tokens)
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
			tokens[nb_of_tokens] = create_token(7, label);
			nb_of_tokens++;
			return (i);	
		}
	}
	return (0);
}

int handle_direct(char *input, t_token **tokens, int nb_of_tokens)
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
		tokens[nb_of_tokens] = create_token(6, label);
		nb_of_tokens++;
		return (len);
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
			//ft_putendl("handling label");
			label = ft_strsub(input, 0, i + 2);
			tokens[nb_of_tokens] = create_token(5, label);
			return (i + 3);	
		}
		i++;
	}
	return (0);
}

int	handle_separator(char *input, t_token **tokens, int nb_of_tokens)
{
	char	*separator;

	//ft_putendl(input);
	if (input[0] == SEPARATOR_CHAR)
	{
		//ft_putendl("handling separator");
		separator = ft_strnew(1);
		separator[0] = SEPARATOR_CHAR;
		tokens[nb_of_tokens] = create_token(4, ft_strdup(separator));
		free(separator);
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
		//ft_putendl("handling register");
		r = ft_atoi(input + i + 1);
		if (r > 16 || r < 0)
			exit_program(-1, "Invalid register index!");
		if (r < 10)
		{
			tokens[nb_of_tokens] = create_token(3, ft_strsub(input, 0, 2));
			return (2);
		}
		else
		{
			tokens[nb_of_tokens] = create_token(3, ft_strsub(input, 0, 3));
			return (3);
		}
	}
	return (0);
}

int	handle_instruction(t_asm *a, char *input, t_token **tokens, int nb_of_tokens)
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
			tokens[nb_of_tokens] = create_token(2, ft_strsub(input, 0, l));
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
	tokens[nb_of_tokens] = create_token(token_type, dest);
	nb_of_tokens++;
	//ft_putstr("chars: " );
	//ft_putnbr(i + n + 1);
	//ft_putendl("");
	return (i + n + 1);
}

int	parse_inputs(char **input, t_token **t, t_asm *a)
{
	static int		nb_of_tokens;
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
				i += handle_quote(input[l] + i + 5, t, 1, nb_of_tokens) + 5;
			else if (!ft_strncmp(input[l] + i, ".comment", 8))
				i += handle_quote(input[l] + i + 8, t, 2, nb_of_tokens) + 8;
			i += handle_instruction(a, input[l] + i, t, nb_of_tokens);
			i += handle_register(input[l] + i, t, nb_of_tokens);
			i += handle_label(input[l] + i, t, nb_of_tokens);
			i += handle_direct_label(input[l] + i, t, nb_of_tokens);
			i += handle_direct(input[l] + i, t, nb_of_tokens);
			//ft_putstr("i: ");
			//ft_putnbr(i);
			//ft_putendl("");
			i += handle_separator(input[l] + i, t, nb_of_tokens);
			if (i == old_i)
				i++;
		}
		l++;
	}
	print_tokens(t, a);
	return (0);
}
