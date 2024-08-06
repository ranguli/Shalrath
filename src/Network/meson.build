network_sources = [
  'NetworkUtils.cpp',
  'QuaddictedClient.cpp',
  'XMLParser.cpp'
]

network_dep = declare_dependency(
  sources: network_sources,
  include_directories: include_directories('.'),
  dependencies: [curl_dep]
)
