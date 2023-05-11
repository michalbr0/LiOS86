#include "memory_manager.hpp"
#include "shell.hpp"

extern "C" [[noreturn]] void kmain() {
    LiOS86::MemoryManager::instance();
    LiOS86::Shell::instance();
    while(true) {}
}
