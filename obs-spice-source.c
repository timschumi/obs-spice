#include <obs-module.h>
#include <spice-client.h>

struct spice_source {
	obs_source_t *source;
	SpiceSession *session;
	bool session_connected;
};

static const char *spice_source_name(void *type) {
	return obs_module_text("SpiceInput");
}

static obs_properties_t *spice_source_properties(void *data) {
	obs_properties_t *props = obs_properties_create();

	obs_properties_add_text(props, "uri", obs_module_text("PropUri"), OBS_TEXT_DEFAULT);

	return props;
}

static void spice_source_disconnect(struct spice_source *context) {
	assert(context->session != NULL);

	if (!context->session_connected)
		return;

	spice_session_disconnect(context->session);
	context->session_connected = false;
}

static void spice_source_connect(struct spice_source *context) {
	assert(context->session != NULL);

	if (context->session_connected)
		return;

	spice_session_connect(context->session);
	context->session_connected = true;
}

static void spice_source_update(void *data, obs_data_t *settings) {
	struct spice_source *context = data;

	bool reconnect = context->session_connected;

	spice_source_disconnect(context);

	g_object_set(context->session, "uri", obs_data_get_string(settings, "uri"), NULL);

	if (reconnect) {
		spice_source_connect(context);
	}
}

static void *spice_source_create(obs_data_t *settings, obs_source_t *source) {
	struct spice_source *context = bzalloc(sizeof(struct spice_source));
	context->source = source;

	// Set up session
	context->session_connected = false;
	context->session = spice_session_new();
	g_object_set(context->session, "read-only", TRUE, NULL);

	// Dial in the settings
	spice_source_update(context, settings);

	spice_source_connect(context);

	return context;
}

static void spice_source_destroy(void *data) {
	struct spice_source *context = data;

	if (context->session) {
		spice_source_disconnect(context);
		g_clear_object(&context->session);
	}

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
	struct spice_source *context = data;
}

struct obs_source_info obs_spice_source = {
	.id           = "obs_spice_source",
	.type         = OBS_SOURCE_TYPE_INPUT,
	.output_flags = OBS_SOURCE_VIDEO,
	.get_name     = spice_source_name,
	.get_properties = spice_source_properties,
	.create       = spice_source_create,
	.destroy      = spice_source_destroy,
	.update       = spice_source_update,
	.video_render = spice_source_render,
	.get_width    = spice_source_width,
	.get_height   = spice_source_height
};
