
#include <string_view>
namespace logger {
bool initialize() noexcept;
bool info(std::string_view message) noexcept;

}  // namespace logger