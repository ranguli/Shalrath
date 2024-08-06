sqlite3_dep = dependency('sqlite3', required: true)

database_sources = [
  'SQLManager.cpp'
]

database_dep = declare_dependency(
  sources: database_sources,
  include_directories: include_directories('.'),
  dependencies: [sqlite3_dep]
)
