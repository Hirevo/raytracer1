/*
** util.c for raytracer in /home/nicolaspolomack/graphical/raytracer1
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Thu Feb  9 02:33:42 2017 Nicolas Polomack
** Last update Thu Feb  9 02:34:41 2017 Nicolas Polomack
*/

int	is_a_number(char *str)
{
  int	i;

  i = 1;
  if (str[0] != '-' && (str[0] < '0' || str[0] > '9'))
    return (-1);
  while (str[i] && str[i] != ':')
    {
      if (str[i] < '0' || str[i] > '9')
        return (-1);
      i += 1;
    }
  return (i);
}

int	get_number(char *str)
{
  int	i;
  int	result;
  int	factor;

  result = 0;
  factor = 1;
  i = (str[0] == '-');
  while (str[i] && str[i] != ':')
    {
      i += 1;
      factor *= 10;
    }
  if (i == (str[0] == '-'))
    return (-1);
  factor /= 10;
  i = (str[0] == '-');
  while (str[i] && str[i] != ':')
    {
      result += (str[i] - '0') * factor;
      factor /= 10;
      i += 1;
    }
  return ((str[0] == '-') ? -result : result);
}
