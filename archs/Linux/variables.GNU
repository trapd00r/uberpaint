############################################################
CXX := c++
STRIP := strip
LIBS := `sdl-config --libs`
############################################################
MKDIR_CMD = test -d $(@D) || mkdir -p $(@D)
############################################################
CFLAGS += -Wno-long-long #-Wall -pedantic-errors -Wno-long-long    
