curl_dep = dependency('libcurl', required: true)

network_sources = [
  'NetworkUtils.cpp',
]

network_dep = declare_dependency(
  sources: network_sources,
  dependencies: [curl_dep],
  include_directories: include_directories('.')
)
