# Makefile for UberPaint: 4P, a pixel pushing paint program
#
#  http://umlautllama.com/projects/4p
#  Scott Lawrence
#  4p@umlautllama.com
#

############################################################
prog:
all:
############################################################
NAME    := uberpaint
VERSION := 0.12

# only "en" is supported for now
# to make other languages, follow the template in source/strings.h.en
LANG    := en

ARCH 	:= $(shell uname -s)

EXENAME := 4p
TARGET	:= Release/$(EXENAME)

SRCS := \
        src/main.c			\
        src/prefs.c			\
        src/log.c			\
        src/testdlgs.c			\
        src/splash.c			\
        \
        src/ini/jstr.c			\
        src/ini/ini.c			\
        \
        src/jsui/utils.c		\
        src/jsui/gui/active.c		\
        src/jsui/gui/jsuibase.c		\
        src/jsui/gui/msg.c		\
        src/jsui/gui/uievents.c		\
        src/jsui/gui/placement.c	\
        src/jsui/gui/widgets/3dbox.c	\
        src/jsui/gui/widgets/buttons.c	\
        src/jsui/gui/widgets/editbox.c	\
        src/jsui/gui/widgets/frame.c	\
        src/jsui/gui/widgets/image.c	\
        src/jsui/gui/widgets/listbox.c	\
        src/jsui/gui/widgets/menu.c	\
        src/jsui/gui/widgets/palette.c	\
        src/jsui/gui/widgets/progress.c	\
        src/jsui/gui/widgets/slider.c	\
        src/jsui/gui/widgets/text.c	\
        src/jsui/gui/widgets/widgets.c	\
        src/jsui/gfx/floodfil.c		\
        src/jsui/gfx/font.c		\
        src/jsui/gfx/gfx_base.c		\
        src/jsui/gfx/gfx_prim.c		\
        src/jsui/gfx/page.c		\
        src/jsui/gfx/palette.c		\
        src/jsui/gfx/pen.c		\
        src/jsui/gfx/timing.c		\
        \
        src/dialogs/manager.c		\
        src/dialogs/acceptor.c		\
        src/dialogs/fontreq.c		\
        src/dialogs/filereq.c		\
        src/dialogs/menus.c		\
        src/dialogs/palette.c		\
        src/dialogs/resolutn.c		\
        src/dialogs/toolbar.c		\
        src/dialogs/toolbar_gfx.c	\
        src/dialogs/brushes.c		\
        src/dialogs/brushes_gfx.c	\
        \
	src/paint/menus.c		\
        src/paint/brushes.c		\
        src/paint/cursors.c		\
        src/paint/events.c		\
        src/paint/paint.c		\
        src/paint/tool_cb.c		\
        src/paint/tools.c		\
        src/paint/zoom.c		\
	\
        src/fileio/fileio.c		\
        src/fileio/endian.c		\
        src/fileio/iff/blockio.c	\
        src/fileio/iff/iff_load.c	\
        src/fileio/iff/iff_save.c	\
        src/fileio/iff/iff_type.c	\
        \
        src/paint/tools/airbrush.c	\
        src/paint/tools/brush.c		\
        src/paint/tools/brushgeo.c	\
        src/paint/tools/circle.c	\
        src/paint/tools/color.c		\
        src/paint/tools/draw.c		\
        src/paint/tools/drawmode.c	\
        src/paint/tools/fill.c		\
        src/paint/tools/rectangl.c	\
        src/paint/tools/screen.c	\
        src/paint/tools/text.c		\
        src/paint/tools/ui.c		\
	src/paint/tools/vector.c

NOTYETS:= \
	src/fileio/pcx/pcx.c

GENS := src/strings.h

OBJS := $(SRCS:%.c=%.o)

HDRS := 


#CXXFLAGS := -O -DNDEBUG=1
CXXFLAGS := -g
CPPFLAGS := 

# Since my personal belief is that if your build has any warnings
# at all, then you've done something wrong, I have used the two
# directives, -Wall and -pedantic-errors
#
# Due to the fact that the people working on libSDL don't agree
# with this, I had to also use the -Wno-long-long, since they use
# the type 'long long'.


CFLAGS  := -g \
	-funroll-loops -fomit-frame-pointer -ffast-math \
	-Isrc -Isrc/dialogs -Isrc/fileio -Isrc/fileio/iff \
	-Isrc/jsui -Isrc/jsui/gui -Isrc/jsui/gfx \
	-Isrc/paint \
	-Isrc/paint/iff -Isrc/paint/tools \
	`sdl-config --cflags`   

############################################################
include archs/$(ARCH)/variables.GNU
############################################################

all: 	prog filecopy

prog:	$(GENS) $(TARGET) $(DATA)

clean:
	@echo - removing target, object, and generated files
	@-rm -f $(TARGET)
	@-rm -f $(OBJS)
	@-rm -f $(GENS)

filecopy:
	@echo + copying files into Release directory
	@-rm -rf Release/Palettes Release/Images
	@-mkdir Release/Palettes
	@-mkdir Release/Images
	@cp -r Palettes/*.ppm Release/Palettes/
	@cp -r Images/*.iff Release/Images/

.PHONY: filecopy

############################################################

$(TARGET):	$(OBJS)
	@echo L Linking to $(TARGET)
	@-$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS) $(LIBS)

#	$(STRIP) $@


############################################################

%.o:	%.cpp
	@echo C++ $<
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

%.o:	%.c
	@echo CC $<
	@$(CC) $(CFLAGS) -c -o $@ $<

Release/bin/$(ARCH)/Images/%:	Images/%
	@echo C Copying file $< to $@
	@cp -p $< $@

############################################################

test:	prog
	./Release/$(EXENAME) \
		-quick \
		-debug \
		-img0 Images/Venus.iff \
		-img1 Images/StarFlight.iff

############################################################

BAK_NAME := $(NAME)_$(VERSION)

backup: clean
	@echo + Generating ../$(BAK_NAME).tar.gz
	@touch ../$(BAK_NAME).tar.gz
	@mv ../$(BAK_NAME).tar.gz ../$(BAK_NAME)_old.tar.gz
	@cd .. ; tar -cf $(BAK_NAME).tar $(NAME)/* ; gzip $(BAK_NAME).tar

.PHONY: backup
############################################################


%.c: src/strings.h

src/strings.h:
	@echo using language file strings.h.$(LANG)
	@-cp src/strings.h.$(LANG) src/strings.h

############################################################

.PHONY: all
.PHONY: prog
.PHONY: size
.PHONY: clean
.PHONY: tidy

.SECONDARY: $(OBJS)
.SECONDARY: $(SRCS)
.SECONDARY: $(HDRS)

############################################################
