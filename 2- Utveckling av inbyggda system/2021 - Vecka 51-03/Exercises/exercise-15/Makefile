CC := g++
CFLAGS := -Werror -DDEVENV

LIB_DIR := lib
TEST_DIR := test
TEST_EXE := test
BUILD_DIR := build

INCLUDES := $(LIB_DIR)/$(MODULE) $(TEST_DIR)/$(MODULE)
INCLUDES := $(addprefix -I./, $(INCLUDES:%/=%))

OBJECTS := $(notdir $(wildcard $(LIB_DIR)/$(MODULE)/*.cpp) $(wildcard $(TEST_DIR)/$(MODULE)/*.cpp))
OBJECTS := $(addprefix $(BUILD_DIR)/, $(OBJECTS:.cpp=.o))

all: clean .mkbuild
	@echo ""
	@echo "************ The Targets ************************************"
	@echo "** clean: to clean the project"
	@echo "** check MODULE=[module name]: to build and run a module test"
	@echo "*************************************************************"
	@echo ""

$(BUILD_DIR)/$(TEST_EXE): $(OBJECTS)
	@$(CC) $^ -lunity -lgcov -o $@

$(BUILD_DIR)/%.o: $(LIB_DIR)/$(MODULE)/%.cpp
	@$(CC) -MMD $(CFLAGS) --coverage -o $@ $(INCLUDES) -c $<

$(BUILD_DIR)/%.o : $(TEST_DIR)/$(MODULE)/%.cpp
	@$(CC) -MMD $(CFLAGS) -o $@ $(INCLUDES) -c $<

check: clean .mkbuild $(BUILD_DIR)/$(TEST_EXE)
	@echo ""
	@echo "**************************************"
	@echo "********** Run The Test **************"
	@echo "**************************************"
	@echo ""
	@./$(BUILD_DIR)/$(TEST_EXE); \
	gcovr -r . --html-details -o $(BUILD_DIR)/index.html

# Include automatically generated dependencies
-include $(OBJECTS:.o=.d)

.PHONY: clean .mkbuild check all

clean:
	@rm -rf $(BUILD_DIR)

.mkbuild:
	@mkdir -p $(BUILD_DIR)
