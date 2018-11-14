NAME = libgzip.a

CC = g++

ARCH =

AR = gcc-ar

ARFLAGS =

RANLIB = gcc-ranlib

RANLIBFLAGS =

CLFAGS = -std=c++14 -g -Wall -Wextra -Werror -O3 -pipe -fno-rtti

INCLUDES_PATH = -I src
INCLUDES_PATH+= -I lib/zlib/include

SRCS_PATH = src/

SRCS_NAME = InputStream.cpp \
	    OutputStream.cpp \
	    FileInputStream.cpp \
	    FileOutputStream.cpp \
	    MemoryInputStream.cpp \
	    MemoryOutputStream.cpp \

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))

OBJS_PATH = obj/

OBJS_NAME = $(SRCS_NAME:.cpp=.opp)

OBJS = $(addprefix $(OBJS_PATH), $(OBJS_NAME))

all: odir $(NAME)

headers:
	@find $(SRCS_PATH) -name \*.gch -exec rm {} \;
	@find $(SRCS_PATH) -name \*.h -exec $(CC) {} \;

$(NAME): $(OBJS)
	@echo " - Making $(NAME)"
	@$(AR) -rc $(ARFLAGS) $(NAME) $(OBJS)
	@$(RANLIB) $(RANLIBFLAGS) $(NAME)

$(OBJS_PATH)%.opp: $(SRCS_PATH)%.cpp
	@echo " - Compiling $<"
	@$(CC) $(ARCH) $(CFLAGS) -o $@ -c $< $(INCLUDES_PATH)

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
