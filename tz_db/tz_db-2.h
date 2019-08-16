#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

struct zone_store_2 {
  const char *name;
  const uint8_t *data;
  const size_t data_size;
};

const struct zone_store_2 *get_tz_by_name_2(const char *name);

#ifdef __cplusplus
}
#endif

