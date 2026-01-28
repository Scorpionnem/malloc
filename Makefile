ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

CC = gcc
DEBUG = 0
CFLAGS = -Wall -Wextra -Werror -MMD -MP -g -fno-builtin-calloc -DMALLOC_DEBUG=$(DEBUG)

INCLUDES = -I includes

NAME = libft_malloc_$(HOSTTYPE).so
NAMELINK = libft_malloc.so

SRCS =	src/malloc.c\
		src/free.c\
		src/realloc.c\
		src/block.c\
		src/zone.c\
		src/utils.c\
		src/show_alloc_mem.c\
		src/memdup.c\
		src/memconstruct.c\
		src/calloc.c\

OBJDIR = obj
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)
DEPS = $(SRCS:%.c=$(OBJDIR)/%.d)

all: $(NAME) $(NAMELINK)

debug:
	make re DEBUG=1

re: fclean all

$(NAMELINK):
	@echo Created symbolic link $(NAMELINK)
	@ln -s $(NAME) $(NAMELINK)

$(NAME): $(OBJS)
	@echo Compiling $(NAME)
	@$(CC) -shared $(CFLAGS) $(INCLUDES) -o $@ $^

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo Compiling $<
	@$(CC) -fPIC $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo Cleaning objects
	@rm -rf $(OBJDIR)

fclean: clean
	@echo Cleaning $(NAME)
	@rm -rf $(NAME)
	@rm -rf $(NAMELINK)

run: $(NAME)
	./$(NAME)

.PHONY: all clean fclean run re bonus compile

-include $(DEPS)
