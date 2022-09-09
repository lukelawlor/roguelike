SRC_DIR := ./src
BUILD_DIR := ./build

SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

CC := gcc
CFLAGS := -Wall -Wextra -Werror -g
DEPFLAGS := -MMD -MP
LDFLAGS := -lncurses

BINNAME := adventure
BINPATH := $(BUILD_DIR)/$(BINNAME)

all: $(BINPATH)

$(BINPATH): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

.DELETE_ON_ERROR:
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

-include $(DEPS)
