#include <obs-module.h>

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE("obs-spice", "en-US")

bool obs_module_load(void) {
    return true;
}
