project('pugixml', 'cpp')

pugixml_sources = [
  'pugixml.cpp'
]

pugixml_lib = static_library('pugixml', pugixml_sources, 
  include_directories: include_directories('.'))

pugixml_headers = [
  'pugixml.hpp',
  'pugiconfig.hpp'
]

install_headers(pugixml_headers, subdir: 'pugixml')

pugixml_dep = declare_dependency(
  include_directories: include_directories('.'),
  link_with: pugixml_lib
)
