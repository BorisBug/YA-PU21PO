CC := g++
CFLAGS := -Werror -DDEVENV

LIB_DIR := lib
TEST_DIR := test
TEST_EXE := test
BUILD_DIR := build

ifdef MODULE
	THE_TEST := $(MODULE)
	INCLUDES := $(LIB_DIR)/$(MODULE) $(TEST_DIR)/$(THE_TEST)
	INCLUDES := $(addprefix -I./, $(INCLUDES))

	OBJECTS := $(notdir $(wildcard $(LIB_DIR)/$(MODULE)/*.cpp) $(wildcard $(TEST_DIR)/$(THE_TEST)/*.cpp))
	OBJECTS := $(addprefix $(BUILD_DIR)/, $(OBJECTS:.cpp=.o))
else
	MODULE := terminal
	THE_TEST := integration
	LED_DRIVER := led_driver

	INCLUDES := $(LIB_DIR)/$(LED_DRIVER) $(LIB_DIR)/$(MODULE) $(TEST_DIR)/$(THE_TEST)
	INCLUDES := $(addprefix -I./, $(INCLUDES))

	OBJECTS := $(notdir $(wildcard $(LIB_DIR)/$(MODULE)/*.cpp) $(wildcard $(LIB_DIR)/$(LED_DRIVER)/*.cpp) $(wildcard $(TEST_DIR)/$(THE_TEST)/*.cpp))
	OBJECTS := $(addprefix $(BUILD_DIR)/, $(OBJECTS:.cpp=.o))
endif

all: clean .mkbuild
	@echo ""
	@echo "************ The Targets ************************************"
	@echo "** clean: to clean the project"
	@echo "** check: to build and run the integration test"
	@echo "** check MODULE=[module name]: to build and run a module test"
	@echo "*************************************************************"
	@echo ""

$(BUILD_DIR)/$(TEST_EXE): $(OBJECTS)
	@$(CC) $^ -lunity -lgcov -o $@

$(BUILD_DIR)/%.o: $(LIB_DIR)/$(LED_DRIVER)/%.cpp
	@$(CC) -MMD $(CFLAGS) --coverage -o $@ $(INCLUDES) -c $<

$(BUILD_DIR)/%.o: $(LIB_DIR)/$(MODULE)/%.cpp
	@$(CC) -MMD $(CFLAGS) --coverage -o $@ $(INCLUDES) -c $<

$(BUILD_DIR)/%.o : $(TEST_DIR)/$(THE_TEST)/%.cpp
	@$(CC) -MMD $(CFLAGS) -o $@ $(INCLUDES) -c $<

check: clean .mkbuild $(BUILD_DIR)/$(TEST_EXE)
	@echo ""
	@echo "**************************************"
	@echo "********** Run The Test **************"
	@echo "**************************************"
	@echo ""
	@./$(BUILD_DIR)/$(TEST_EXE); \
	gcovr -r . --html-details -o $(BUILD_DIR)/index.html

# Include the automatically generated dependencies
-include $(OBJECTS:.o=.d)

.PHONY: clean .mkbuild check all

clean:
	@rm -rf $(BUILD_DIR)

.mkbuild:
	@mkdir -p $(BUILD_DIR)
