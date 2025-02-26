/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:24:15 by ppeckham          #+#    #+#             */
/*   Updated: 2025/02/26 13:54:32 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <fcntl.h>

// tipo para la estructura de lista enlazada
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

// te llena n bytes en memoria de null.
void	ft_bzero(void *s, size_t n);
// si es carácter alfa-numérico te devuelve 1, si no 0.
int		ft_isalnum(int ch);
// si es carácter del abecedario te devuelve 1, si no 0 (depende de locale).
int		ft_isalpha(int ch);
// si etá en la tabla ascii te devuelve 1, si no 0.
int		ft_isascii(int ch);
// si es carácter numérico te devuelve 1, si no 0.
int		ft_isdigit(int ch);
// si es carácter imprimible te devuelve 1, si no 0.
int		ft_isprint(int ch);
// te llena count bytes en memoria de de lo que indiques en c.
void	*ft_memset(void *ptr, int c, size_t count);
// te devuelve la longitud de un string.
int		ft_strlen(const char *str);
// se utiliza para copiar una cadena de n bytes a otro espacio de memoria.
// Si hay solapamiento no lo gestiona bien.
void	*ft_memcpy(void *dest, const void *src, size_t n);
// igual que memcopy pero si hay solapamiento recorre las cadenas de adelante
// hacia atrás o viceversa en función de dónde empiece cada cadena en memoria.
void	*ft_memmove(void *dest, const void *src, size_t n);
// copia size caracteres de src a dest, añade /0 al final y retorna el tamaño
// original de src.
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
// concatena src al final de dest siempre que dejes suficiente espacio con
// destsize. Siempre deja un byte libre al final para el \0, si no corta la
// cadena.
size_t	ft_strlcat(char *dest, const char *src, size_t destsize);
// recibe un caracter tipo ascii ejem: 'h' y te devuelve el entero
// correspondiente a su mayúscula en la tabla ascii. Si no recibe una letra
//  minúscula, te devuelve el caracter que le has pasado.
int		ft_toupper(int c);
// igual que toupper, pero te convierte una mayúscula en su valor entero ascii
// en minúscula.
int		ft_tolower(int c);
// te busca la primera ocurrencia de un caracter en una cadena y te devuelve su
// dirección de memoria. Si se le pasa como arg '\0', te devuelve su dirección
// de mem.
char	*ft_strchr(const char *str, int c);
// igual que strchr, pero te devuelve la dirección de memoria de la última
// ocurrencia de c.
char	*ft_strrchr(const char *str, int c);
// compara, caracter a caracter hasta llegar a n, dos str y si cada caracter
// es igual o se llega al final, devuelve 0. Si no, devuelve la diferencia
// ascii entre los dos caracteres comparados.
int		ft_strncmp(const char *s1, const char *s2, size_t n);
// te busca la dirección de memoria de value en un bloque de memoria (*ptr).
// num se usa para limitar los bytes que quieres escanear. Le da igual tipos.
void	*ft_memchr(const void *ptr, int value, size_t num);
// te compara cada caracter en dos bloques de memoria hasta llegar a num o el
// final. Si son iguales te devuelve 0, si no, te da un numero positivo o
// negativo restando los valores asciis del caracter diferente.
int		ft_memcmp(const void *ptr1, const void *ptr2, size_t num);
// busca la cadena needle completa dentro de n caracteres de la cadena  
// haystack. Si está, devuelve dire de memoria del primer caracter de needle. 
// Si no está, n es demasiado pequeño, o llegamos al final de haystack, 
// devuelve nulo.
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
// convierte caracteres ascii (pasados en una cadena) a entero. Ignora espacios
// y similares al principio de la cadena, y reconoce el símbolo (+ o -).
int		ft_atoi(const char *str);
// utilizando malloc, asigna un bloque de memoria con num elementos, de tamaño
// size, e inicializa cada elemento a 0.
void	*ft_calloc(size_t num, size_t size);
// se usa para generar una copia de un str. Se calcula el tamaño de str, se
// asigna memoria usando malloc, se copia cada carácter y se añade siempre '\0'
// al final.
char	*ft_strdup(const char *str);
// se genera una copia de un str, pero limitado por start (desde qué indice de
// str empieza) y por len (cuantos caracteres se copian a partir de start).
// Devuelve el string duplicado, o null si falla.
char	*ft_substr(char const *s, unsigned int start, size_t len);
// concatena s1 y s2 añadiendo '\0' al final. Primero asiga un espacio de 
// memoria con malloc.
char	*ft_strjoin(char const *s1, char const *s2);
// concatena s1 y s2 y los libera devolviendo un string nuevo.
char	*ft_join_free(char *s1, char *s2);
// elimina del principio y del final del string s1 todos los caracteres conte-
// nidos en el string set. Si no coinciden ninguno, devuelve la cadena
// completa. Utiliza malloc para asignar la memoria exacta.
char	*ft_strtrim(char const *s1, char const *set);
// corta la cadena 's' cada vez que ocurra 'c' y guarda cada segmento, sin el
// caracter 'c', en una lista. En la ultima posicion de esta nueva lista pone
// un NULL, y devuelve finalmente el puntero a la direccion de ese NULL.
char	**ft_split(char const *s, char c);
// convierte un int a un string de caracteres. Si la reserva de memoria falla,
// retorna null. Si no, devulve la cadena, con su signo correcto, y termina en
// '\0'.
char	*ft_itoa(int n);
// aplica una funcion 'f' a cada caracter de una cadena 's'. si hay algun fallo
// devuelve NULL. Por ejemplo, convierte cada caracter de s en mayuscula usando
// ft_toupper. Debes castear los tipos de los argumentos con una función
// intermedia si no coinciden con los que pide 'f'.
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
// aplica una funcion 'f' a cada caracter de una cadena 's'. Detecta fallos,
// pero no devuelve nada. Solo usa la dirección de memoria de cada caracter
// como argumento.
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
// escribe un caracter en un archivo llamado 'fd' (file descriptor). En vez de
// imprimir en la terminal, ahora abrimos un archivo (creandolo si no existe),
// escribimos llamando a la funcion (que tiene un write) y se cierra al final.
void	ft_putchar_fd(char c, int fd);
// igual que el anterior, pero escribe la cadena completa en el fd.
void	ft_putstr_fd(char *s, int fd);
// igual que el anterior, solo que termina con un salto de línea, por lo que
// siempre tendrás una linea vacía al final del 'fd' (o al final de lo que
// acabas de escribir).
void	ft_putendl_fd(char *s, int fd);
// te escribe un numero entero en un archivo .txt. Gestiona correctamente los
// numeros negativos y el entero mas pequeño.
void	ft_putnbr_fd(int n, int fd);
// te crea un nuevo nodo, o el primero de una lista enlazada. Se inicializa 
// content con el contenido del parámetro que le pasamos como argumento, y 
// next con NULL (puntero nulo 'de momento').
t_list	*ft_lstnew(void *content);
// te añade un nodo al principio de una lista enlazada, apuntando desde ese
// nodo a lo que antes era el primer nodo, y apunta la cabeza de la lista
// enlazada a este nuevo nodo. No devuelve nada.
void	ft_lstadd_front(t_list **lst, t_list *new);
// cuenta el numero de nodos de una lista y te lo devuelve en formato int.
int		ft_lstsize(t_list *lst);
// devuelve el ultimo nodo de la lista (su direccion de memoria).
t_list	*ft_lstlast(t_list *lst);
// insierta un nuevo nodo *new al final de la lista **lst
void	ft_lstadd_back(t_list **lst, t_list *new);
// libera el contenido del lst utilizando la función de eliminación que tu le
// pases además de liberar el nodo. Next no lo elimina.
void	ft_lstdelone(t_list *lst, void (*del)(void*));
// elimina y libera el nodo lst y todos los consecutivos aplicando la función
// del que tu le pases. Al final, hay un puntero NULL.
void	ft_lstclear(t_list **lst, void (*del)(void*));
// itera por cada elemento de una lista, y aplica una función a cada elemento
// hasta el final.
void	ft_lstiter(t_list *lst, void (*f)(void *));
// itera por cada elemento de una lista y aplica una función a cada elemento,
// devolviendo NULL si hay algún error, eliminando el contenido con del, y si
// no hay ningún error, devuelve la nueva lista.
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

// GET NEXT LINE HAS IT'S OWN LIBRARY IN: get_next_line/get_next_line.h

#endif
