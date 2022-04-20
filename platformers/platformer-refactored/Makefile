CXX    := g++
OBJDIR := obj
IDIRS  := -I/usr/include/raylib_extras/ -I$(PWD)
IFLAGS := -lraylib
CFLAGS := -g
SRCS   := $(wildcard *.cpp)
OBJS   := $(SRCS:%.cpp=$(OBJDIR)/%.o)

TARGET := platformer

.PHONY: clean echo debug

$(TARGET): $(OBJS) 
	@echo "[LD] $@"
	@mkdir -pv build
	@$(CXX) $(CFLAGS) $(IDIRS) $(IFLAGS) -o build/$@ $^

$(OBJDIR)/%.o: %.cpp | $(OBJDIR) 
	@echo "[CXX]  $@"
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
	@rm -rf build/
	@rm -rf obj/


debug: $(TARGET)
	@curl http://127.0.0.1:5550/api/runtime/run
