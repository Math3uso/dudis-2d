dd_add_benchmark(scene_benchmark
  SOURCES
    scene_benchmark.cpp
)

add_custom_target(dd_benchmarks DEPENDS scene_benchmark)
