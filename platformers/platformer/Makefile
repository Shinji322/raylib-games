CXX    := g++
OBJDIR := obj
IDIRS  := -I/usr/include/raylib_extras/ -I$(PWD)
IFLAGS := -lraylib
SRCS   := $(wildcard *.cpp)
OBJS   := $(SRCS:%.cpp=$(OBJDIR)/%.o)

TARGET := platformer

.PHONY: clean echo

$(TARGET): $(OBJS) 
	@echo "[LD] $@"
	@mkdir -p build
	@$(CXX) $(IDIRS) $(IFLAGS) -o build/$@ $^

$(OBJDIR)/%.o: %.cpp | $(OBJDIR) 
	@echo "[CXX]  $@"
	@$(CXX) -c $(IDIRS) $(IFLAGS) -o $@ $<

$(OBJDIR):
	@mkdir -p $(OBJDIR)

echo:
	@echo "CXX = $(CXX)"
	@echo "OBJDIR = $(OBJDIR)"
	@echo "IDIRS = $(IDIRS)"
	@echo "IFLAGS = $(IFLAGS)"
	@echo "SRCS = $(SRCS)"
	@echo "OBJS = $(OBJS)"


clean:
	@rm -rf obj
	@rm -rf build
