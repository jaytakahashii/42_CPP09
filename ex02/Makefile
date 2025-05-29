MAKEFILE 		= Makefile

NAME				= PmergeMe

SRC_DIR			= src/
OBJ_DIR			= .obj/

INCLUDE_DIR	= include/
INCLUDE			= -I $(INCLUDE_DIR)
HEADERS			= color.hpp \
							utils.hpp \
							utils.tpp \
							MergeInsertionSortVector.hpp \
							MergeInsertionSortVectorDebug.hpp \
							MergeInsertionSortDeque.hpp \

HEADER			= $(addprefix $(INCLUDE_DIR), $(HEADERS))

DEPS				= $(HEADER) $(MAKEFILE)

CXX					= c++
CXXFLAGS		= -Wall -Wextra -Werror -std=c++98
PEDANT			= -pedantic
SANITIZE		= -fsanitize=address -g3

RM					= rm -rf

SRC_DIR			= src/
SRC_FILES		=	main.cpp \
							MergeInsertionSortVector.cpp \
							MergeInsertionSortDeque.cpp \

D_SRC_FILES	= main.debug.cpp \
							MergeInsertionSortVectorDebug.cpp \

SRCS				= $(addprefix $(SRC_DIR), $(SRC_FILES))
D_SRCS			= $(addprefix $(SRC_DIR), $(D_SRC_FILES))
OBJS				= $(addprefix $(OBJ_DIR), $(SRC_FILES:.cpp=.o))
D_OBJS			= $(addprefix $(OBJ_DIR), $(D_SRC_FILES:.cpp=.o))

# color ************
Y		= "\033[33m"
R		= "\033[31m"
G		= "\033[32m"
B		= "\033[34m"
X		= "\033[0m"
UP	= "\033[A"
CUT	= "\033[K"
# ******************

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS) $(DEPS)
	@echo $(Y) "src files successfully compiled.\n" $(X)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@echo $(G) "!! $(NAME) created !!\n" $(X)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)
	@echo $(R) "$(OBJ_DIR) has been removed.\n" $(X)

fclean:
	$(RM) $(OBJ_DIR)
	$(RM) $(NAME)
	@echo $(R) "$(NAME) and $(OBJ_DIR) has been removed.\n" $(X)

re: fclean all

pedant: CXXFLAGS += $(PEDANT)
pedant: re
	@echo $(G) "pedantic mode activated.\n" $(X)

leaks: CXXFLAGS += $(SANITIZE)
leaks: re
	@echo $(G) "leaks mode activated.\n" $(X)

debug: $(OBJ_DIR) $(D_OBJS) $(DEPS)
	@echo $(Y) "src files successfully compiled.\n" $(X)
	$(CXX) $(CXXFLAGS) $(D_OBJS) -o $(NAME)
	@echo $(G) "!! $(NAME) created !!\n" $(X)
	@echo $(B) "debug mode activated.\n" $(X)

.PHONY: all clean fclean re pedant leaks debug
