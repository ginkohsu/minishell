/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arenalloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 20:45:58 by aloimusa          #+#    #+#             */
/*   Updated: 2025/09/29 20:45:59 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_chunk
{
    struct  s_chunk *prev;
    size_t     used;
    char    data[];
}   t_chunk;

#define CHUNKSIZE 8192
#define BLOCKSIZE 8

static t_chunk *g_chunk_head = NULL;

void *arenalloc(size_t n)
{
    t_chunk *chunk;
    void    *ptr;

    if (n == 0)
        return (NULL);
    n = (n + BLOCKSIZE - 1) & ~(BLOCKSIZE - 1);
    chunk = g_chunk_head;
    while (chunk && CHUNKSIZE - chunk->used < n)
        chunk = chunk->prev;
    if (!chunk)
    {
        if (n > CHUNKSIZE)
            chunk = ft_calloc(sizeof(t_chunk) + n, 1);
        else
            chunk = ft_calloc(sizeof(t_chunk) + CHUNKSIZE, 1);
        if (!chunk)
            exit(EXIT_FAILURE);
        chunk->used = 0;
        chunk->prev = g_chunk_head;
        g_chunk_head = chunk;
    }
    ptr = &chunk->data[chunk->used];
    chunk->used += n;
    return (ptr);
}

void    free_arena(void)
{
    t_chunk *head;
    t_chunk *neck;

    head = g_chunk_head;
    while (head)
    {
        neck = head->prev;
        free(head);
        head = neck;
    }
    g_chunk_head = NULL;
}
