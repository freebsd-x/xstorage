#include "xserver/storage_service.h"
#include "shared/protocol.h"
#include "shared/logger.h"
#include "xserver/crash_handler.h"
#include <csignal>
#include <unistd.h>
#include <atomic>

static std::atomic<bool> g_running{true};

static void signal_handler(int) {
    g_running = false;
}

int main() {
    fbx::shared::Logger::init("xstorage");
    fbx::xserver::installCrashHandler("xstorage");
    LOG_INFO("xstorage starting...");

    signal(SIGTERM, signal_handler);
    signal(SIGINT, signal_handler);

    LOG_INFO("StorageService running. Waiting for SIGTERM/SIGINT.");

    // StorageService is stateless (all methods are static); the IPC socket
    // is managed by the compositor. This daemon is a placeholder for running
    // StorageService as a standalone process in the future.
    while (g_running) {
        pause();
    }

    LOG_INFO("xstorage shutting down.");
    return 0;
}
