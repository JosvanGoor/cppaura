EXECUTABLE		= cppaura

BUILD_DIR		= build
SOURCE_DIR		= src

COMPILER		= g++
FLAGS			= -O3 -Wall -ggdb -Wextra -pedantic -std=c++2a -flto
# libraries

SOURCES			= $(shell find $(SOURCE_DIR) -name *.cc -printf "%P\n")
OBJECTS			= $(addprefix $(BUILD_DIR)/,$(SOURCES:.cc=.o))
DEPENDENCIES	= $(OBJECTS:.o=.d)

# builds executable, is default.
$(EXECUTABLE): folders $(OBJECTS)
	$(COMPILER) $(FLAGS) $(OBJECTS) -o $@

# builds individual object files (-MMD -MP builds dependency files)
$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cc
	$(COMPILER) $(FLAGS) -c $< -o $@ -MMD -MP

# include dependency files if they exists
-include $(OBJECTS:.o=.d)

#phony rules
.PHONY: folders clean rebuild

folders:
	@mkdir -p build/
	@mkdir -p $(filter-out %./,$(dir $(OBJECTS)))

clean:
	rm -rf $(EXECUTABLE)
	rm -rf build/

rebuild:
	make clean
	make -j 12