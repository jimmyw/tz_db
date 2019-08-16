
#include <cstring>
#include <algorithm>

#include "cctz/zone_info_source.h"
#include "tz_db-3.h"

namespace cctz_extension {

  namespace {
    class InternalSource : public cctz::ZoneInfoSource {
    public:
      explicit InternalSource(const std::string &name) :
        store(get_tz_by_name_3(name.c_str())),
        offset(0)
      {
        //printf("InternalSource '%s' %p bytes: %lu\n", name.c_str(), store, store ? store->data_size : 0);
      }
      ~InternalSource() {
        free_tzstore(store);
      }

      std::size_t Read(void* ptr, std::size_t size) override {
        if (!store)
          return 0;

        const std::size_t new_size = std::min(size, store->data_size - offset);
        std::memcpy(ptr, store->data + offset, new_size);
        //printf("Read %lu offset %lu returned %lu\n", size, offset, new_size);
        this->offset += new_size;
        return new_size;
      }
      int Skip(std::size_t offset_) override {
        //printf("SKIP %lu\n", offset_);
        this->offset += offset_;
        return 0;
      }

      // Until the zoneinfo data supports versioning information, we provide
      // a way for a ZoneInfoSource to indicate it out-of-band.  The default
      // implementation returns an empty string.
      std::string Version() const override {
        return "";
      }
      struct zone_store_3 *store;
      std::size_t offset;

    };

    std::unique_ptr<cctz::ZoneInfoSource> CustomFactory(const std::string& name, const std::function<std::unique_ptr<cctz::ZoneInfoSource>(const std::string& name)>& fallback_factory) {
      return std::make_unique<InternalSource>(name);
    }

  }  // anonymous namespace

  ZoneInfoSourceFactory zone_info_source_factory = CustomFactory;
}  // namespace cctz_extension

