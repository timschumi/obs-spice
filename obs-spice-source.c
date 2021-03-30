#include <obs-module.h>

struct spice_source {
	obs_source_t *source;
};

static const char *spice_source_name(void *type) {
	return obs_module_text("SpiceInput");
}

static void spice_source_update(void *data, obs_data_t *settings) {
	struct spice_source *context = data;
}

static void *spice_source_create(obs_data_t *settings, obs_source_t *source) {
	struct spice_source *context = bzalloc(sizeof(struct spice_source));
	context->source = source;
	return context;
}

static void spice_source_destroy(void *data) {
	struct spice_source *context = data;
	bfree(context);
}

static uint32_t spice_source_width(void *data) {
	struct spice_source *context = data;
	return 0;
}

static uint32_t spice_source_height(void *data) {
	struct spice_source *context = data;
	return 0;
}

static void spice_source_render(void *data, gs_effect_t *effect) {
	struct image_source *context = data;
}

struct obs_source_info obs_spice_source = {
	.id           = "obs_spice_source",
	.type         = OBS_SOURCE_TYPE_INPUT,
	.output_flags = OBS_SOURCE_VIDEO,
	.get_name     = spice_source_name,
	.create       = spice_source_create,
	.destroy      = spice_source_destroy,
	.update       = spice_source_update,
	.video_render = spice_source_render,
	.get_width    = spice_source_width,
	.get_height   = spice_source_height
};
