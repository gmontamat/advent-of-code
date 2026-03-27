CC := cc
CFLAGS := -O2 -Wall -Wextra -pedantic -std=c23

.PHONY: compile run clean

# OpenSSL (only used for DAY=04)
OPENSSL_PREFIX := $(shell (command -v brew >/dev/null 2>&1 && brew --prefix openssl@3 2>/dev/null) || \
                          (command -v pkg-config >/dev/null 2>&1 && pkg-config --variable=prefix openssl 2>/dev/null) || \
                          echo /usr)
OPENSSL_CFLAGS := -I"$(OPENSSL_PREFIX)/include" -Wno-deprecated-declarations
OPENSSL_LDFLAGS := -L"$(OPENSSL_PREFIX)/lib" -lcrypto

ifeq ($(DAY),04)
  EXTRA_CFLAGS := $(OPENSSL_CFLAGS)
  EXTRA_LDFLAGS := $(OPENSSL_LDFLAGS)
else ifeq ($(DAY),07)
  EXTRA_CFLAGS := -Wno-unsequenced
  EXTRA_LDFLAGS :=
else
  EXTRA_CFLAGS :=
  EXTRA_LDFLAGS :=
endif

# Build only
compile:
	@cd $(DAY) && $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -o solution$(PART).out solution$(PART).c $(EXTRA_LDFLAGS)

# Build + run
run: compile
	@cd $(DAY) && ./solution$(PART).out $(IN)

clean:
	@find . -type f -name '*.out' -exec rm -f {} +
