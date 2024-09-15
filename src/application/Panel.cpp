#include "Panel.hpp"

Panel::Panel(std::string name, Size size, Point position) noexcept : name_(name), size_(size), position_(position) {}
void Panel::move(Point topleft) noexcept { position_ = topleft; }
void Panel::resize(Size size) noexcept { size_ = size; }
Size Panel::size() const noexcept { return size_; }
Point Panel::position() const noexcept { return position_; }

void Panel::rename(std::string name) noexcept { name_ = name; }
std::string Panel::name() const noexcept { return name_; }