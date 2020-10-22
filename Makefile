# **DO NOT MODIFY**

ifeq ($(NAME),)
$(error Should make in each lab's directory)
endif

SRCS   := $(shell find . -maxdepth 1 -name "*.c")
DEPS   := $(shell find . -maxdepth 1 -name "*.h") $(SRCS)
CFLAGS += -O0 -std=gnu11 -ggdb -Wall -Werror -Wno-unused-result
#优化级别根据反汇编代码改变

#SRC_DIR ?= ./
#BINARY ?= $(SRC_DIR)$(NAME)-64$(SO)
#WORKBENCH_EXEC :=$(BINARY)

.PHONY: all git test clean commit-and-make

.DEFAULT_GOAL := commit-and-make
commit-and-make: git all

$(NAME)-64: $(DEPS) # 64bit binary
	gcc -m64 $(CFLAGS) $(SRCS) -o $@ $(LDFLAGS)

#run-env:$(NAME)-64

#run:run-env
#	$(WORKBENCH_EXEC)

clean:
	rm -f $(NAME)-64

