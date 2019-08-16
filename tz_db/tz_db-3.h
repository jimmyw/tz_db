#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

struct zone_store_3 {
  const char *name;
  const size_t offset;
  uint8_t *data;
  const size_t data_size;
};

struct zone_store_3 *get_tz_by_name_3(const char *name);
void free_tzstore(struct zone_store_3 *store);

#ifdef __cplusplus
}
#endif

