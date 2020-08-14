/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_image_to_bmp_file.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 20:15:52 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/13 21:04:00 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define BYTES_PER_PIXEL		4
#define FILE_HEADER_SIZE	14
#define INFO_HEADER_SIZE	40

unsigned char	*create_bitmap_file_header(int height, int stride)
{
	int 					file_size; 
	static unsigned char 	file_header[] = { \
		0,0, \
		0,0,0,0, \
		0,0,0,0, \
		0,0,0,0
	};

	file_size = FILE_HEADER_SIZE + INFO_HEADER_SIZE + (stride * height); 
	file_header[0] = (unsigned char)('B');
	file_header[1] = (unsigned char)('M');
	file_header[2] = (unsigned char)(file_size);
	file_header[3] = (unsigned char)(file_size >> 8);
	file_header[4] = (unsigned char)(file_size >> 16);
	file_header[5] = (unsigned char)(file_size >> 24);
	file_header[10] = (unsigned char)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);
	return (file_header);
}

unsigned char	*create_bitmap_info_header(int height, int width)
{
	static unsigned char info_header[] = { \
		0,0,0,0, \
		0,0,0,0, \
		0,0,0,0, \
		0,0, \
		0,0, \
		0,0,0,0, \
		0,0,0,0, \
		0,0,0,0, \
		0,0,0,0, \
		0,0,0,0, \
		0,0,0,0
	};

	info_header[0] = (unsigned char)(INFO_HEADER_SIZE);
	info_header[4] = (unsigned char)(width);
	info_header[5] = (unsigned char)(width >> 8);
	info_header[6] = (unsigned char)(width >> 16);
	info_header[7] = (unsigned char)(width >> 24);
	info_header[8] = (unsigned char)(height);
	info_header[9] = (unsigned char)(height >> 8);
	info_header[10] = (unsigned char)(height >> 16);
	info_header[11] = (unsigned char)(height >> 24);
	info_header[12] = (unsigned char)(1);
	info_header[14] = (unsigned char)(BYTES_PER_PIXEL * 8);
	return (info_header);
}

int		mlx_image_to_bmp_file(t_mlx_image *mi, const char *name)
{
	static unsigned char	padding[3] = {0, 0, 0};
	unsigned char			*file_header;
	unsigned char			*info_header;
	unsigned char			*img;
	int						width_in_bytes;
	int						padding_size;
	int						stride;
	int						fd;

	width_in_bytes = mi->width * mi->bits_per_pixel / 8;
	padding_size = (4 - (width_in_bytes) % 4) % 4;
	stride = width_in_bytes + padding_size;
	if ((fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR)) == -1)
		return (-1);
	file_header = create_bitmap_file_header(mi->height, stride);
	if (write(fd, file_header, FILE_HEADER_SIZE) == -1)
		return (-1);
	info_header = create_bitmap_info_header(-mi->height, mi->width);
	if (write(fd, info_header, INFO_HEADER_SIZE) == -1)
		return (-1);
	img = (unsigned char *)mi->addr;
	for (int y = 0; y < mi->height; y++)
	{
		if (write(fd, img + (y * mi->line_length), mi->line_length) == -1)
			return (-1);
		if (write(fd, padding, padding_size) == -1)
			return (-1);
	}
	close(fd);
	return (0);
}
