# Find the libcurl and sqlite3 dependencies
curl_dep = dependency('libcurl', required: true)
sqlite3_dep = dependency('sqlite3', required: true)

# Link against the pugixml library
pugixml_dep = subproject('pugixml').get_variable('pugixml_dep')

# Add UI subdirectory
subdir('UI')

executable('shalrath',
  sources: [
    'main.cpp',
  ],
  dependencies: [curl_dep, sqlite3_dep, pugixml_dep, ui_dep],
  install: true
)
