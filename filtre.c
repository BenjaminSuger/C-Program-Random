#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define BUFFER_SIZE 10

char	*my_strjoin(char *s1, char *s2)
{
	char	*result;

	result = malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1));
	if (result == NULL)
		return (free(s1), NULL);
	memcpy(result, s1, strlen(s1));
	memcpy(result +strlen(s1), s2, strlen(s2));
	result[strlen(s1) + strlen(s2)] = '\0'; 
	return (free(s1), result);
}

char	*reading(void)
{
	int	n;
	char	*result;
	char	buffer[BUFFER_SIZE + 1];

	result = malloc(1);
	result[0] = '\0';

	n = read(0, buffer, BUFFER_SIZE);
	if (n <= 0)
		return (NULL);
	while (n > 0)
	{
		buffer[n] = '\0';
		result = my_strjoin(result, buffer);
		if (result == NULL)
			return (NULL);
		n = read(0, buffer, BUFFER_SIZE);
		if (n < 0)
			return (free(result), NULL);
	}
	return (result);
}

void	replace(char *str, char *needle)
{
	char	*ptr;

	ptr = memmem(str, strlen(str), needle, strlen(needle));
	while (ptr)
	{
		for (int i = 0; i < (int) strlen(needle); i++)
			ptr[i] = '*';
		ptr = memmem(str, strlen(str), needle, strlen(needle));
	}
}

int	main(int argc, char **argv)
{
	char	*read;

	if (argc != 2)
		return (1);
	read = reading();
	if (read == NULL)
		return (1);
	printf("le texte avant : %s", read);
	replace(read, argv[1]);
	printf("le texte apres : %s", read);

	free(read);
}
