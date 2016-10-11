#include "get_next_line.h"
#include <stdio.h>
#include "libft.h"

int			main(int argc, char **argv)
{
	//char	*str;
	char	*line;
	// int		out;
	// int		p[2];
	int		fd;
	int		res;

	if (argc != 2 || !argv[0])
		return (1);
	res = 0;
	// str = (char*)ft_memalloc(4096);
	// out = dup(1);
	// pipe(p);

	// fd = 1;
	// dup2(p[1], fd);
	// write(fd, "Déjà vu\n", 8);
	// close(p[1]);
	// dup2(out, fd);

	// out = dup(1);
	// pipe(p);
	// //get_next_line(p[0], &line);
	// //printf("0 %s %d\n", line, strcmp(line, "Déjà vu"));

	// fd = 1;
	// dup2(p[1], fd);
	// write(fd, "abcdéfgh\n", 9);
	// write(fd, "ijklmnop\n", 9);
	// write(fd, "qrstuvwx\n", 9);
	// write(fd, "yzabcdef\n", 9);
	// write(fd, "ghijklmn\n", 9);
	// write(fd, "opqrstuv\n", 9);
	// write(fd, "wxyzabcd\n", 9);
	// close(p[1]);
	// dup2(out, fd);
	// get_next_line(p[0], &line);
	// printf("1 %s %d\n", line, strcmp(line, "abcdéfgh"));
	// get_next_line(p[0], &line);
	// printf("2 %s %d\n", line, strcmp(line, "ijklmnop"));
	// get_next_line(p[0], &line);
	// printf("3 %s %d\n", line, strcmp(line, "qrstuvwx"));
	// get_next_line(p[0], &line);
	// printf("4 %s %d\n", line, strcmp(line, "yzabcdef"));
	// get_next_line(p[0], &line);
	// printf("5 %s %d\n", line, strcmp(line, "ghijklmn"));
	// get_next_line(p[0], &line);
	// printf("6 %s %d\n", line, strcmp(line, "opqrstuv"));
	// get_next_line(p[0], &line);
	// printf("7 %s %d\n", line, strcmp(line, "wxyzabcd"));

	// out = dup(1);
	// pipe(p);

	// fd = 1;
	// dup2(p[1], fd);
	// write(fd, "abcdefgh\n", 9);
	// write(fd, "ijklmnop\n", 9);
	// write(fd, "qrstuvwx\n", 9);
	// write(fd, "yzabcdef\n", 9);
	// write(fd, "ghijklmn\n", 9);
	// write(fd, "opqrstuv\n", 9);
	// write(fd, "wxyzabcd\n", 9);
	// write(fd, "abcd\n", 5);
	// write(fd, "efgh\n", 5);
	// close(p[1]);
	// dup2(out, fd);
	//strcat(str, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur in leo dignissim, gravida leo id, imperdiet urna. Aliquam magna nunc, maximus quis eleifend et, scelerisque non dolor. Suspendisse augue augue, tempus");
	//strcat(str, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur in leo dignissim, gravida leo id, imperdiet urna. Aliquam magna nunc, maximus quis eleifend et, scelerisque non dolor. Suspendisse augue augue, tempus");
	//strcat(str, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur in leo dignissim, gravida leo id, imperdiet urna. Aliquam magna nunc, maximus quis eleifend et, scelerisque non dolor. Suspendisse augue augue, tempus");
	//printf("%s\n", str);
	// get_next_line(p[0], &line);
	// printf("1 %s %d\n", line, strcmp(line, "abcdefgh"));
	// get_next_line(p[0], &line);
	// printf("2 %s %d\n", line, strcmp(line, "ijklmnop"));
	// get_next_line(p[0], &line);
	// printf("3 %s %d\n", line, strcmp(line, "qrstuvwx"));
	// get_next_line(p[0], &line);
	// printf("4 %s %d\n", line, strcmp(line, "yzabcdef"));
	// get_next_line(p[0], &line);
	// printf("5 %s %d\n", line, strcmp(line, "ghijklmn"));
	// get_next_line(p[0], &line);
	// printf("6 %s %d\n", line, strcmp(line, "opqrstuv"));
	// get_next_line(p[0], &line);
	// printf("7 %s %d\n", line, strcmp(line, "wxyzabcd"));
	// get_next_line(p[0], &line);
	// printf("1 %s %d\n", line, strcmp(line, "abcd"));
	// get_next_line(p[0], &line);
	// printf("2 %s %d\n", line, strcmp(line, "efgh"));
	fd = open(argv[1], O_RDONLY);
	// //int i = 2;
	if ((fd) > 0)
		while (/*i-- &&*/ (res = get_next_line(fd, &line) > 0))
			printf("%s\n", line);
	//printf("%d\n%s\n", fd, line);
	if ((fd > 0 && (close(fd) == -1 || res != 0)) || fd < 0)
	{
		if (!line)
			write(1, "error\n", 6);
		return (1);
	}

	return (0);
}
