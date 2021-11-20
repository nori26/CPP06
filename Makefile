NAME		:= form
CXX			:= clang++
CXXFLAGS	:= -Wall -Werror -Wextra -MMD -MP -std=c++98
SRCDIR		:= .
VPATH 		:= $(shell find $(SRCDIR) -type d | awk '{print $$0":"}')
OBJDIR		:= ./obj
INCLUDE		:= $(shell find $(SRCDIR) -type d | awk '{print "-I " $$0}')
SRCS		:= $(shell find $(SRCDIR) -type f -name "*.cpp" | xargs basename -a)
OBJS		:= $(SRCS:%.cpp=$(OBJDIR)/%.o)
DEPENDS		:= $(OBJS:.o=.d)
SHELL		:= /bin/bash
PURPLE		:= \033[1;35m
GREEN		:= \033[1;32m
RESET		:= \033[0;39m

# ifdef WITH_BONUS
# NAME	= philo_bonus
# OBJS	= $(shell basename -a $(B_SRCS:.c=.o) $(LIBSRCS:.c=.o) | awk -v o=$(OBJDIR) '{print o"/"$$0}')
# DEPENDS	= $(shell basename -a $(B_SRCS:.c=.d) $(LIBSRCS:.c=.d) | awk -v o=$(OBJDIR) '{print o"/"$$0}')
# endif

all		: $(NAME)

-include $(DEPENDS)

$(OBJDIR)/%.o : %.cpp
	@if [ ! -d $(OBJDIR) ];then mkdir $(OBJDIR); fi
	@$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@
	@echo -e "	""$(GREEN)$@$(RESET)"

$(NAME)	: $(OBJS)
	@$(CXX) $(CXXFLAGS) $(INCLUDE) $(OBJS) -o $@
	@echo -e "\n$(PURPLE) build	$(GREEN)$@$(RESET)"

test	:
clean	: rm_reloc
#	# @make b_clean WITH_BONUS=1

fclean	: clean rm_exec
#	@make b_fclean WITH_BONUS=1

# bonus	:
# 	@make WITH_BONUS=1

b_clean	: rm_reloc

b_fclean: rm_exec

rm_reloc:
	$(RM) -r $(OBJDIR)

rm_exec	:
	$(RM) $(NAME)

re		: fclean all

debug	: CXXFLAGS += -g -fsanitize=address
debug	: re

.PHONY	: all clean fclean re bonus add norm rm_exec rm_reloc b_clean b_fclean head test