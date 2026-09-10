#pragma once

#include <cstddef>
#include <cstdint>

namespace sdl3
{

constexpr int SDL_GETEVENT{2};
constexpr std::uint32_t SDL_EVENT_KEY_DOWN{0x300};
constexpr std::uint32_t SDL_SCANCODE_INSERT{73};

struct KeyboardEvent {
    std::uint32_t type;
    std::uint32_t reserved;
    std::uint64_t timestamp;
    std::uint32_t windowId;
    std::uint32_t which;
    std::uint32_t scancode;
    std::uint32_t key;
    std::uint16_t mod;
    std::uint16_t raw;
    bool down;
    bool repeat;
};

union Event {
    std::uint32_t type;
    KeyboardEvent key;
    std::uint8_t padding[128];
};

static_assert(sizeof(Event) == 128);
static_assert(offsetof(KeyboardEvent, scancode) == 24);

[[nodiscard]] inline bool isMenuToggleEvent(const Event& event) noexcept
{
    return event.type == SDL_EVENT_KEY_DOWN
        && event.key.scancode == SDL_SCANCODE_INSERT
        && !event.key.repeat;
}

}
