#include <common.h>
#include <device.h>

#if defined(MULTIPROGRAM) && !defined(TIME_SHARING)
# define MULTIPROGRAM_YIELD() yield()
#else
# define MULTIPROGRAM_YIELD()
#endif

#define NAME(key) \
  [AM_KEY_##key] = #key,

static const char *keyname[256] __attribute__((used)) = {
  [AM_KEY_NONE] = "NONE",
  AM_KEYS(NAME)
};

size_t serial_write(const void *buf, size_t offset, size_t len) {
  	int i;
		for(i=0; i<len; i++){
				putch(*((char *)buf+i));
		}
		return 0;
}

size_t events_read(void *buf, size_t offset, size_t len) {
  	AM_INPUT_KEYBRD_T input = io_read(AM_INPUT_KEYBRD);
		if( input.keycode == AM_KEY_NONE ){
				return 0;
		}
		if( input.keydown ){
				return snprintf(buf, len, "kd %s", keyname[input.keycode]);
		}
		return snprintf(buf, len, "ku %s", keyname[input.keycode]);
}

size_t dispinfo_read(void *buf, size_t offset, size_t len) {
  	AM_GPU_CONFIG_T gpu_config = io_read(AM_GPU_CONFIG);
		return snprintf(buf, len, "WIDTH:%d\nHEIGHT:%d", gpu_config.width,gpu_config.height);
}

size_t fb_write(const void *buf, size_t offset, size_t len) {
  return 0;
}

void init_device() {
  Log("Initializing devices...");
  ioe_init();
}
