/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 19:07:18 by kpolojar          #+#    #+#             */
/*   Updated: 2022/11/10 01:52:16 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/assembler.h"

char	**read_from_stdin(int fd)
{
	int		ret;
	int		i;
	char	*line;
	char	**lines;

	i = 0;
	line = NULL;
	lines = (char **)malloc(sizeof(char *) * (MAX_LINES + 1));
	ret = ft_get_next_line(fd, &line);
	while (ret)
	{
		lines[i] = ft_strdup(line);
		free(line);
		ret = ft_get_next_line(fd, &line);
		i++;
		if (i > MAX_LINES)
			exit_program(-1, "Too many lines!");
	}
	if (i == 0)
		exit_program(-1, "No lines!");
	free(line);
	lines[i] = NULL;
	return (lines);
}

t_asm *new_asm(void)
{
	t_asm	*a;
	t_token	**t;

	a = (t_asm *)malloc(sizeof(t_asm));
	t = (t_token **)malloc(sizeof(t_token *) * (MAX_TOKENS + 1));

	t[MAX_TOKENS] = '\0';
	a->tokens = t;
	a->nb_of_tokens = 0;
	set_asm_op_tab(a);
	set_asm_token_tab(a);
	return (a);
}

int	main(int argc, char **argv)
{
	t_asm		*a;
	char		**lines;
	int 		fd;

	if (argc != 2)
		exit_program(-1, "wrong number of aruments");
	a = new_asm();
	fd = open(argv[1], O_RDONLY);
	lines = read_from_stdin(fd);
	parse_inputs(lines, a);
}