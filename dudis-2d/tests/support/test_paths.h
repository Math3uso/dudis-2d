#pragma once

#include <filesystem>

namespace dudis::tests
{
inline std::filesystem::path rootDir()
{
    return std::filesystem::path(DD_TEST_ROOT_DIR);
}

inline std::filesystem::path assetsDir()
{
    return std::filesystem::path(DD_TEST_ASSETS_DIR);
}

inline std::filesystem::path baselinesDir()
{
    return std::filesystem::path(DD_TEST_BASELINES_DIR);
}

inline std::filesystem::path artifactsDir()
{
    return std::filesystem::path(DD_TEST_ARTIFACTS_DIR);
}

inline std::filesystem::path assetPath(const std::string &name)
{
    return assetsDir() / name;
}

inline std::filesystem::path artifactPath(const std::string &name)
{
    return artifactsDir() / name;
}
} // namespace dudis::tests
