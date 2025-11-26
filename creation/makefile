PROJECT := creation
CONFIG  ?= debug

ifneq ($(filter debug release,$(CONFIG)),$(CONFIG))
	$(error CONFIG must be 'debug' or 'release', got '$(CONFIG)')
endif

OBJDIR := obj
SRCDIR := src

C_SRCS := $(wildcard $(SRCDIR)/*.c)
CPP_SRCS := $(wildcard $(SRCDIR)/*.cc)
ASM_SRCS := $(wildcard $(SRCDIR)/*.S)

OBJS := $(patsubst $(SRCDIR)/%.c,  $(OBJDIR)/%.o, $(C_SRCS))
OBJS += $(patsubst $(SRCDIR)/%.cc, $(OBJDIR)/%.o, $(CPP_SRCS))
OBJS += $(patsubst $(SRCDIR)/%.S,  $(OBJDIR)/%.o, $(ASM_SRCS))

DEPS := $(OBJS:%.o=%.d)

MAKEFLAGS += --no-print-directory CONFIG=$(CONFIG)

ELF = $(PROJECT).elf
FILE := $(CURDIR)/$(ELF)

RM  := rm -f
RMD := rm -rf

include ee-toolchain.defs

all: $(ELF)

header:
	@echo "/> Creation project"
	@echo "/> Build config: $(CONFIG)"
	@echo "/> EE C Compiler: $(EE_CC)"
	@echo "/> EE C++ Compiler: $(EE_CXX)"

$(OBJDIR):
	@mkdir -p $@

$(ELF): header $(OBJDIR) $(OBJS)
	@echo "/> Makefile -> $(ELF)"
	@$(EE_LD) -o $@ $(OBJS) $(EE_LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo "/> $(notdir $<)"
	@$(EE_CC) $(EE_CFLAGS) -o $@ -c $< > /dev/null

$(OBJDIR)/%.o: $(SRCDIR)/%.cc
	@echo "/> $(notdir $<)"
	@$(EE_CXX) $(EE_CXXFLAGS) -o $@ -c $< > /dev/null

$(OBJDIR)/%.o: $(SRCDIR)/%.S
	@echo "/> $(notdir $<)"
	@$(EE_AS) $(EE_CFLAGS) -D__ASSEMBLY__ -o $@ -c $< > /dev/null

-include $(DEPS)

clean: header
	@echo "/> Clean project"
	@$(RMD) $(OBJDIR)
	@$(RM) $(ELF)

run_emulator:
	@echo "/> Running target on PlayStation 2 emulator"
	@pcsx2-qt -- $(FILE)
