# Builds and runs the LVGL PC simulator (apps/lv_port_pc_vscode) with the
# Claude faces (apps/arduino/src/Claudy) wired in as the demo screen,
# instead of the stock lv_demo_widgets() the upstream template ships with.
#
#   make setup   installs deps, links faces into the simulator, configures cmake
#   make build   compiles the simulator (implies setup)
#   make run     builds and launches ./bin/main (implies build)
#   make clean   removes the build dir and binary

SIM_DIR    := apps/lv_port_pc_vscode
BUILD_DIR  := $(SIM_DIR)/build
FACES_DIR  := $(SIM_DIR)/src/faces
SIM_PATCH  := patches/lv_port_pc_vscode.patch

# The face sources (claude_face_v2*) and the design's Silkscreen/IBM Plex
# Mono bitmap fonts they need live in apps/arduino/src/Claudy -- the Arduino
# sketch dir, which has to stay flat for the Arduino IDE -- alongside
# firmware files the simulator can't compile (ESP32 display/touch/I2C
# drivers). Symlink in just the files the simulator needs, individually,
# rather than the whole directory.
FACE_SRC_DIR := apps/arduino/src/Claudy
FACE_FILES   := claude_face_config.h claude_face_v2.h claude_face_v2_faces.h \
                claude_face_v2.cpp claude_face_v2_start.cpp claude_face_v2_idle.cpp \
                claude_face_v2_done.cpp claude_face_v2_fail.cpp \
                claude_face_v2_danger.cpp claude_face_v2_subagent.cpp claude_face_v2_end.cpp \
                claude_face_v2_attention.cpp claude_face_v2_ratelimit.cpp \
                silkscreen_13.cpp silkscreen_17.cpp silkscreen_20.cpp silkscreen_34.cpp \
                ibmplexmono_11.cpp ibmplexmono_13.cpp

.PHONY: all setup deps link-faces patch-sim configure build run clean

all: build

setup: deps link-faces patch-sim configure

deps:
ifeq ($(shell uname -s),Darwin)
	brew install sdl2 cmake make
else
	@echo "Non-macOS: install SDL2, cmake and make manually — see $(SIM_DIR)/README.md"
endif

# Re-run safely any time -- e.g. if $(SIM_DIR) ever gets reset from upstream.
link-faces:
	@mkdir -p "$(FACES_DIR)"; \
	for f in $(FACE_FILES); do \
		if [ -L "$(FACES_DIR)/$$f" ] || [ -e "$(FACES_DIR)/$$f" ]; then \
			echo "already linked: $(FACES_DIR)/$$f"; \
		else \
			ln -s ../../../../$(FACE_SRC_DIR)/$$f "$(FACES_DIR)/$$f"; \
			echo "linked $(FACE_SRC_DIR)/$$f -> $(FACES_DIR)/$$f"; \
		fi; \
	done

# $(SIM_DIR) is an upstream checkout (its own git repo); the faces demo needs
# three changes to it (see patches/lv_port_pc_vscode.patch) -- swap the demo
# screen for the Claude faces, wire src/faces into the CMake build, and turn
# on ThorVG. Safe to re-run: skips if already applied, e.g. from a fresh
# clone where the fix is baked in, or a re-run after $(SIM_DIR) was reset.
patch-sim:
	@if git -C $(SIM_DIR) apply --check -R $(CURDIR)/$(SIM_PATCH) >/dev/null 2>&1; then \
		echo "already patched: $(SIM_DIR)"; \
	elif git -C $(SIM_DIR) apply --check $(CURDIR)/$(SIM_PATCH) >/dev/null 2>&1; then \
		git -C $(SIM_DIR) apply $(CURDIR)/$(SIM_PATCH); \
		echo "patched $(SIM_DIR) from $(SIM_PATCH)"; \
	else \
		echo "error: $(SIM_PATCH) doesn't apply to $(SIM_DIR) -- upstream may have changed, reconcile by hand"; \
		exit 1; \
	fi

configure: link-faces patch-sim
	cmake -S $(SIM_DIR) -B $(BUILD_DIR)

build: configure
	cmake --build $(BUILD_DIR) -j

run: build
	$(SIM_DIR)/bin/main

clean:
	rm -rf $(BUILD_DIR) $(SIM_DIR)/bin
