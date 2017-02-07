/*
** my_strncmp.c for my_strncmp in /home/nicolas.polomack/CPool_Day06
** 
** Made by Nicolas POLOMACK
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Oct 10 09:38:55 2016 Nicolas POLOMACK
** Last update Fri Oct 14 15:24:03 2016 Nicolas POLOMACK
*/

int	my_strncmp(char *str1, char *str2, int n)
{
  while (*str1 == *str2 && n >= 0)
    {
      str1 = str1 + 1;
      str2 = str2 + 1;
      n = n - 1;
    }
  return (*str2 - *str1);
}
