#include "shell.h"

/**
 *  _getenv - gets the value of an environ variable.
 * @info: structure containing potential arguments, used to maintain.
 * @name: env var name.
 *
 * Return: the value.
 */

char *_getenv(ino_t *ino, const char *name)
{
	list_t *node = ino->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * populate_env_list - populates env linked list.
 * @info: structure containing potential arguments, used to maintain
 * constant function prototype.
 *
 * Return: always 0.
 */

int populate_env_list(ino_t *ino)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	ino->env = node;
	return (0);
}

/**
 * _myenv - prints the current environment.
 * @info: structure containing potential arguments, used to maintain
 * constant function prototype.
 *
 * Return: always 0.
 */

int _myenv(ino_t *ino)
{
	print_list_str(ino->env);
	return (0);
}

/**
 * _mysetenv - initialize a new environment variable, or modify
 * an existing one.
 * @info: structure containing potential arguments, used to maintain
 * constant function prototype.
 *
 * Return: always 0.
 */

int _mysetenv(ino_t *ino)
{
	if (ino->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(ino, ino->argv[1], ino->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - remove an environment variable.
 * @info: structure containing potential arguments, used to maintain
 * constant function prototype.
 *
 * Return: always 0.
 */

int _myunsetenv(ino_t *ino)
{
	int i;

	if (ino->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= ino->argc; i++)
		_unsetenv(ino, ino->argv[i]);

	return (0);
}
