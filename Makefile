NAME = libgzip.a

CC = g++ -std=c++14

AR = ar

RANLIB = ranlib

CLFAGS = -Wall -Wextra -Werror -Ofast -pipe -march=x86-64 -mtune=generic -flto=8

INCLUDES_PATH = -I src
INCLUDES_PATH+= -I lib/zlib

SRCS_PATH = src/

SRCS_NAME = GZipInputStream.cpp \
			GZipOutputStream.cpp

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))

OBJS_PATH = obj/

OBJS_NAME = $(SRCS_NAME:.cpp=.opp)

OBJS = $(addprefix $(OBJS_PATH), $(OBJS_NAME))

all: odir $(NAME)

$(NAME): $(OBJS)
	@echo " - Making $(NAME)"
	@$(AR) -rc $(NAME) $(OBJS)
	@$(RANLIB) $(NAME)

$(OBJS_PATH)%.opp: $(SRCS_PATH)%.cpp
	@echo " - Compiling $<"
	@$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDES_PATH)

odir:
	@mkdir -p $(OBJS_PATH)

clean:
	@echo " - Cleaning objs"
	@rm -f $(OBJS)

fclean: clean
	@echo " - Cleaning lib"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
