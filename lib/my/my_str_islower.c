/*
** my_strupcase.c for my_strupcase in /home/nicolas.polomack/CPool_Day06
** 
** Made by Nicolas POLOMACK
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Oct 10 12:10:37 2016 Nicolas POLOMACK
** Last update Mon Oct 10 19:59:58 2016 Nicolas POLOMACK
*/

int	my_str_islower(char *str)
{
  int	count;

  count = 0;
  while (str[count] != '\0')
    {
      if ((str[count] < 97 || str[count] > 122))
	return (0);
      count = count + 1;
    }
  return (1);
}
