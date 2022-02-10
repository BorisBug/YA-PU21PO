# A Makefile to build and run the test

CC := gcc
CFLAGS := -Wall

LIB_DIR := stack
TEST_DIR := test
BUILD_DIR := build
TEST_EXE := stack_test

INCLUDES := $(addprefix -I./, $(LIB_DIR))

OBJECTS := $(notdir $(wildcard $(LIB_DIR)/*.c) $(wildcard $(TEST_DIR)/*.c))
OBJECTS := $(addprefix $(BUILD_DIR)/,$(OBJECTS:.c=.o))

all: .mkbuild $(TEST_EXE)
	@echo ""
	@echo "************ The Targets ************"
	@echo "** clean: to clean"
	@echo "** check: to run the test"
	@echo "*************************************"

$(TEST_EXE): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -lunity -o $(BUILD_DIR)/$@

$(BUILD_DIR)/%.o: $(LIB_DIR)/%.c
	$(CC) -MMD $(CFLAGS) -o $@ -c $<

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) -MMD $(CFLAGS) -o $@ $(INCLUDES) -c $<

check: .mkbuild $(TEST_EXE)
	@echo ""
	@echo "**************************************"
	@echo "********** Run The Test **************"
	@echo "**************************************"
	@echo ""
	@./$(BUILD_DIR)/$(TEST_EXE)

# Include the automatically generated dependencies
-include $(OBJECTS:.o=.d)

.PHONY: clean .mkbuild check all

clean:
	@rm -rf $(BUILD_DIR)

.mkbuild:
	@mkdir -p $(BUILD_DIR)
