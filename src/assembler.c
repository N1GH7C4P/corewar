/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 19:07:18 by kpolojar          #+#    #+#             */
/*   Updated: 2022/11/08 01:08:24 by kpolojar         ###   ########.fr       */
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
	t_asm *a;

	a = (t_asm *)malloc(sizeof(t_asm));
	set_asm_op_tab(a);
	return (a);
}

int	main(int argc, char **argv)
{
	t_token		**t;
	t_asm		*a;
	char		**lines;
	int 		fd;

	if (argc != 2)
		exit_program(-1, "wrong number of aruments");
	t = (t_token **)malloc(sizeof(t_token *) * (MAX_TOKENS + 1));
	t[MAX_TOKENS] = NULL;
	a = new_asm();
	fd = open(argv[1], O_RDONLY);
	lines = read_from_stdin(fd);
	parse_inputs(lines, t, a);
}