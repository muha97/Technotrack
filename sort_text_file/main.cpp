#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <stdlib.h>

/*
	* В прототипах пиши содержимое аргументов, чтобы пользователь твоих
	* функций понимал, что требуется на вход. А то такой код сложно понимать.
*/
void strings_number(FILE* ,long long& ,int&);
void creator(FILE* , FILE* ,long long , int , char** &);

/*
	* Если уж ты начал наверху задавать прототипы, то продолжай этот стиль.
	* Перенеси все определения вниз.
*/

int comparator( const char* str, const char* str2 )
{
	int i = 0;
	int j = 0;

	//! Какая-то жуткая логика у этого цикла. Попробуй оптимизировать его.
	while (true)
	{
		//! Есть  isalpha()
		if( ((str[i] < (long)'А') || (str[i] > (long)'я')) && (str[i] != (long)'ё') ) ++i;
		if( ((str2[j] < (long)'А') || (str2[j] > (long)'я')) && (str2[j] != (long)'ё') ) ++j;
		if(str[i] == '\0')
			return -1;
		if(str2[j] == '\0')
			return 1;
		if(str[i] > str2[j])
			return 1;
		else if(str[i] < str2[j])
			return -1;
		else
			{
				++i;
				++j;
			}

	}
}

int compare(const void *a,const void *b)
{
	return (comparator(*(char**)a, *(char**)b));
}

int main()
{
	setlocale(LC_ALL, "Russian");

	/*
		* Как я уже говорил несколько раз на занятиях, логики считывания,
		* разбиения по строкам, сортировки и вывода правильно разделять
		* по непересекающимся функцям.
		* Функция - базовый строительный блок. И она не знает,
		* что происходит вокруг. Она умеет только принимать аргументы, делать
		* свою работу и возрващать какое-то значение.
	*/
	FILE* in = fopen("in.txt","rw"); //! "rb" лучше
	FILE* out = fopen("out.txt","w");

	long long str_num = 0;
	int max_len = 0;
	strings_number(in, str_num, max_len);

	char** arr = {}; //! char** arr = NULL;
	creator(in, out, str_num, max_len, arr);


	qsort(arr, str_num, sizeof(char*), compare);

	//! В отдельную функцию.
	int i = 0, j = 0;
	for(i = 0; i < str_num; ++i)
		for(j = 0; j < max_len; ++j)
		{
			if(arr[i][j] == '\0')
			{
				fprintf(out, "\n");
				break;
			}
			fprintf(out, "%c", arr[i][j]);
		}

	getch();
	return 0;
}


/*
	* creator() и strings_number() можно и нужно совместить в одной функции.
	* Это обязательно переделать.
*/
void strings_number(FILE* file, long long &str_num, int &max_len)
{
	char ch = 0;
	int tmp = 0;
	while( (ch = fgetc(file)) != EOF)
	{
		++tmp;
		if(ch == '\n')
		{
			++str_num;
			if(tmp > max_len)
				max_len = tmp;
			tmp = 0;
		}
	}
	rewind(file);
}

void creator(FILE* file, FILE* out, long long str_num, int max_len, char** &array)
{
	int i = 0, j = 0;
	char c;
	array = (char**)calloc(str_num, sizeof(char*));
	for(i = 0; i < str_num; ++i)
	{
		array[i] = (char*)calloc(max_len, sizeof(char));
		for(j = 0; j < max_len; ++j)
		{
			c = fgetc(file);
			array[i][j] = c;

			if(c == '\n')
			{
				array[i][j] = '\0';
				break;
			}
		}
	}
	rewind(file);
}
