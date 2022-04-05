CXX ?= g++

# path #
SRC_PATH = src
DB_PATH = db
BUILD_PATH = build
BIN_PATH = $(BUILD_PATH)/bin
DB_BUILD_PATH = $(BIN_PATH)/db




# executable # 
BIN_NAME = lds

# extensions #
SRC_EXT = cpp

# code lists #
# Find all source files in the source directory, sorted by
# most recently modified
SOURCES = $(shell find $(SRC_PATH) -name '*.$(SRC_EXT)' | sort -k 1nr | cut -f2-)
# Set the object file names, with the source directory stripped
# from the path, and the build path prepended in its place
OBJECTS = $(SOURCES:$(SRC_PATH)/%.$(SRC_EXT)=$(BUILD_PATH)/%.o)
# Set the dependency files that will be used to add header dependencies
DEPS = $(OBJECTS:.o=.d)

# flags #
COMPILE_FLAGS = -std=c++17 -Wall -Wextra -ggdb
INCLUDES = -I src/
# Space-separated pkg-config libraries used by this project
LIBS =

.PHONY: default_target
default_target: all

.PHONY: dirs
dirs:
	@echo "Creating directories"
	@echo cp /db/props-test.csv $(DB_PATH)/props-test.csv
	@mkdir -p $(dir $(OBJECTS))
	@mkdir -p $(BIN_PATH)
	@mkdir -p $(DB_BUILD_PATH)
	@cp $(DB_PATH)/props.csv $(DB_BUILD_PATH)/props.csv
	@cp $(DB_PATH)/rooms.csv $(DB_BUILD_PATH)/rooms.csv
	

.PHONY: clean
clean:
	@echo "Deleting directories"
	@$(RM) -r $(BUILD_PATH)
	@$(RM) -r $(BIN_PATH)
	@$(RM) -r $(DB_BUILD_PATH)

# checks the executable and symlinks to the output
.PHONY: all
all: export CXXFLAGS := $(CXXFLAGS) $(COMPILE_FLAGS)
all: dirs $(BIN_PATH)/$(BIN_NAME)

# Creation of the executable
$(BIN_PATH)/$(BIN_NAME): $(OBJECTS)
	@echo "Linking: $@"
	$(CXX) -ggdb $(OBJECTS) -o $@ ${LIBS}

# Add dependency files, if they exist
-include $(DEPS)

# Source file rules
# After the first compilation they will be joined with the rules from the
# dependency files to provide header dependencies
$(BUILD_PATH)/%.o: $(SRC_PATH)/%.$(SRC_EXT)
	@echo "Compiling: $< -> $@"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MP -MMD -c $< -o $@
