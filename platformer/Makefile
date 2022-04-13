CXX    := g++
OBJDIR := build
IDIRS  := -I/usr/include/raylib_extras/ -I$(PWD)
IFLAGS := -lraylib
SRCS   := $(wildcard *.cpp)
OBJS   := $(SRCS:%.cpp=$(OBJDIR)/%.o)

TARGET := platformer

.PHONY: clean echo

$(TARGET): $(OBJS)
	@echo [LD] $@
	@$(CXX) $(IDIRS) $(IFLAGS) -o $(OBJDIR)/$@ $^

$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	@echo [CXX]  $@
	@$(CXX) -c $(IDIRS) $(IFLAGS) -o $@ $<

$(OBJDIR):
	@mkdir -pv $(OBJDIR)

echo:
	@echo "CXX = $(CXX)"
	@echo "OBJDIR = $(OBJDIR)"
	@echo "IDIRS = $(IDIRS)"
	@echo "IFLAGS = $(IFLAGS)"
	@echo "SRCS = $(SRCS)"
	@echo "OBJS = $(OBJS)"


clean:
	@rm -f build/*.o
	@rm -f build/$(TARGET)
	@rmdir build
