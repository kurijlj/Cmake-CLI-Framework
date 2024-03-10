# =============================================================================
# Build source targets
# =============================================================================

# Print message to console that we are building the source targets
message(STATUS "Going through ./src")

# Build the "app" target
add_executable(app app.cpp)
target_link_libraries(app PRIVATE
    clipp
    sqlite3
    Libsodium
)