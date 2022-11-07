/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:59:07 by kpolojar          #+#    #+#             */
/*   Updated: 2022/11/07 20:58:25 by kpolojar         ###   ########.fr       */
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

t_token	*create_token(int type_code, char *content)
{
	t_token	*t;
	t = (t_token *)malloc(sizeof(t_token));
	t->type_code = type_code;
	t->content = ft_strdup(content);
	return (t);
}