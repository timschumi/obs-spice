#include <obs-module.h>

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE("obs-spice", "en-US")

// Implemented in obs-spice-source.c
extern struct obs_source_info obs_spice_source;

bool obs_module_load(void) {
	obs_register_source(&obs_spice_source);
	return true;
}
