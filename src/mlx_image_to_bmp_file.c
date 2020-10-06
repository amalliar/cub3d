/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_image_to_bmp_file.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 20:15:52 by amalliar          #+#    #+#             */
/*   Updated: 2020/10/06 18:05:58 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

#define BYTES_PER_PIXEL			4
#define FILE_HEAD_SZ			14
#define INFO_HEAD_SZ			40

static char		*gen_file_name(void)
{
	time_t		rawtime;
	struct tm	*timeinfo;
	char		*fname;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	if (!(fname = malloc(64)))
		exit_failure("%s\n", strerror(errno));
	strftime(fname, 64, "Screen Shot %F at %I.%M.%S %p.bmp", timeinfo);
	return (fname);
}

unsigned char	*create_bmp_file_header(int height, int stride)
{
	int						file_size;
	static unsigned char	file_header[FILE_HEAD_SZ] = {0};

	file_size = FILE_HEAD_SZ + INFO_HEAD_SZ + (stride * height);
	file_header[0] = (unsigned char)('B');
	file_header[1] = (unsigned char)('M');
	file_header[2] = (unsigned char)(file_size);
	file_header[3] = (unsigned char)(file_size >> 8);
	file_header[4] = (unsigned char)(file_size >> 16);
	file_header[5] = (unsigned char)(file_size >> 24);
	file_header[10] = (unsigned char)(FILE_HEAD_SZ + INFO_HEAD_SZ);
	return (file_header);
}

unsigned char	*create_bmp_info_header(int height, int width)
{
	static unsigned char	info_header[INFO_HEAD_SZ] = {0};

	info_header[0] = (unsigned char)(INFO_HEAD_SZ);
	info_header[4] = (unsigned char)(width);
	info_header[5] = (unsigned char)(width >> 8);
	info_header[6] = (unsigned char)(width >> 16);
	info_header[7] = (unsigned char)(width >> 24);
	info_header[8] = (unsigned char)(height);
	info_header[9] = (unsigned char)(height >> 8);
	info_header[10] = (unsigned char)(height >> 16);
	info_header[11] = (unsigned char)(height >> 24);
	info_header[12] = (unsigned char)(1);
	info_header[14] = (unsigned char)(8 * BYTES_PER_PIXEL);
	return (info_header);
}

int				mlx_image_to_bmp_file(t_mlx_image *mi)
{
	static unsigned char	padding[3] = {0, 0, 0};
	char					*fname;
	int						y;
	t_bmp_data				bd;

	fname = gen_file_name();
	if ((bd.fd = open(fname, O_CREAT | O_WRONLY | O_TRUNC, \
		S_IRUSR | S_IWUSR)) == -1)
		return (-1);
	free(fname);
	bd.width_in_bytes = mi->width * mi->bits_per_pixel / 8;
	bd.padding_size = (4 - (bd.width_in_bytes) % 4) % 4;
	bd.stride = bd.width_in_bytes + bd.padding_size;
	write(bd.fd, create_bmp_file_header(mi->height, bd.stride), FILE_HEAD_SZ);
	write(bd.fd, create_bmp_info_header(-mi->height, mi->width), INFO_HEAD_SZ);
	bd.img = (unsigned char *)mi->addr;
	y = 0;
	while (y < mi->height)
	{
		write(bd.fd, bd.img + (y * mi->line_size), mi->width * 4);
		write(bd.fd, padding, bd.padding_size);
		++y;
	}
	close(bd.fd);
	return (0);
}
