/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:06:13 by jinxu             #+#    #+#             */
/*   Updated: 2025/09/17 17:38:19 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

typedef struct s_chunk
{
    struct  s_chunk *prev;
    int     used;
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
            chunk = ft_calloc(sizeof(t_chunk *) + n, 1);
        else
            chunk = ft_calloc(sizeof(t_chunk *) + CHUNKSIZE, 1);
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

void    *free_arena(void)
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

#define STAY    (1 << 0)
#define P_OBJ   (1 << 1)
#define F_OBJ   (1 << 2)
#define F_MSG   (1 << 3)
#define P_ARRAY   (1 << 4)
#define F_ARRAY   (1 << 5)
#define F_ARENA   (1 << 6)

void	exit_error(void *obj, char *msg, int code, int action)
{
    void *ptr;

    if (obj && (action & P_OBJ))
        ft_fprintf(2, obj);
    if (obj && (action & F_ARRAY))
    {
        ptr = obj;
        while (*(char **)ptr)
        {
            free(*(char **)ptr);
            ptr = (char **)ptr + 1;
        }
    }
    if (obj && ((action & F_OBJ) || (action & F_ARRAY)))
        free(obj);
    if (msg)
        ft_fprintf(2, msg);
    if (msg && (action & F_MSG))
        free(msg);
    if (action & F_ARENA)
        free_arena();
	if (action & STAY)
		return ;
    exit(code);
}