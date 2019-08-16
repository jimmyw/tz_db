#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

struct zone_store {
  const char *name;
  const uint8_t *data;
  const size_t data_size;
};

const struct zone_store *get_tz_by_name(const char *name);

#ifdef __cplusplus
}
#endif

